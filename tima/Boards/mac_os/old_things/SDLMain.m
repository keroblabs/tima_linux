/*   SDLMain.m - main entry point for our Cocoa-ized SDL app
 Initial Version: Darrell Walisser <dwaliss1@purdue.edu>
 Non-NIB-Code & other changes: Max Horn <max@quendi.de>
 
 Feel free to customize this file to suit your needs
 */

#include <SDL/SDL.h>
#include "SDLMain.h"
#include <sys/param.h> /* for MAXPATHLEN */
#include <unistd.h>

#include "gpio_driver.h"

/* For some reaon, Apple removed setAppleMenu from the headers in 10.4,
 but the method still is there and works. To avoid warnings, we declare
 it ourselves here. */
@interface NSApplication(SDL_Missing_Methods)
- (void)setAppleMenu:(NSMenu *)menu;
@end

/* Use this flag to determine whether we use SDLMain.nib or not */
#define		SDL_USE_NIB_FILE	0

/* Use this flag to determine whether we use CPS (docking) or not */
#define		SDL_USE_CPS		1
#ifdef SDL_USE_CPS
/* Portions of CPS.h */
typedef struct CPSProcessSerNum
{
	UInt32		lo;
	UInt32		hi;
} CPSProcessSerNum;

extern OSErr	CPSGetCurrentProcess( CPSProcessSerNum *psn);
extern OSErr 	CPSEnableForegroundOperation( CPSProcessSerNum *psn, UInt32 _arg2, UInt32 _arg3, UInt32 _arg4, UInt32 _arg5);
extern OSErr	CPSSetFrontProcess( CPSProcessSerNum *psn);

#endif /* SDL_USE_CPS */

static int    gArgc;
static char  **gArgv;
static BOOL   gFinderLaunch;
static BOOL   gCalledAppMainline = FALSE;

static NSWindowController *wc;

static int gpio_state[80];
static int adc_value[16];
static NSButton * gpio_out[80];

static int button_posx;
static int button_posy;

static const char * gpio_names[80] = {
    "PE00",  "PE01",  "PE02",  "PE03",  "PE04",  "PE05",  "PE06",  "PE07",
    "PE08",  "PE09",  "PE10",  "PE11",  "PI14",  "PI15",  "PI00",  "PI01",
    "PI02",  "PI03",  "PI10",  "PI11",  "PC03",  "PC07",  "PC16",  "PC17",
    "PC18",  "PC23",  "PC24",  "PB03",  "PB04",  "PB05",  "PB06",  "PB07",
    "PB08",  "PB10",  "PB11",  "PB12",  "PB13",  "PB14",  "PB15",  "PB16",
    "PB17",  "PH24",  "PH25",  "PH26",  "PH27",  "PH00",  "PH02",  "PH07",
    "PH09",  "PH10",  "PH11",  "PH12",  "PH13",  "PH14",  "PH15",  "PH16",
    "PH17",  "PH18",  "PH19",  "PH20",  "PH21",  "PH22",  "PH23",  "PG00",
    "PG01",  "PG02",  "PG03",  "PG04",  "PG05",  "PG06",  "PG07",  "PG08",
    "PG09",  "PG10",  "PG11",  "PI16",  "PI17",  "PI18",  "PI19",
};

static id thisClass;

static NSString *getApplicationName(void)
{
    const NSDictionary *dict;
    NSString *appName = 0;
    
    /* Determine the application name */
    dict = (__bridge const NSDictionary *)CFBundleGetInfoDictionary(CFBundleGetMainBundle());
    if (dict)
        appName = [dict objectForKey: @"CFBundleName"];
    
    if (![appName length])
        appName = [[NSProcessInfo processInfo] processName];
    
    return appName;
}

#if SDL_USE_NIB_FILE
/* A helper category for NSString */
@interface NSString (ReplaceSubString)
- (NSString *)stringByReplacingRange:(NSRange)aRange with:(NSString *)aString;
@end
#endif

@interface SDLApplication : NSApplication
@end

@implementation SDLApplication
/* Invoked from the Quit menu item */
- (void)terminate:(id)sender
{
    /* Post a SDL_QUIT event */
    SDL_Event event;
    event.type = SDL_QUIT;
    SDL_PushEvent(&event);
}
@end

/* The main class of the application, the application's delegate */
@implementation SDLMain

/* Set the working directory to the .app's parent directory */
- (void) setupWorkingDirectory:(BOOL)shouldChdir
{
    if (shouldChdir)
    {
        char parentdir[MAXPATHLEN];
        CFURLRef url = CFBundleCopyBundleURL(CFBundleGetMainBundle());
        CFURLRef url2 = CFURLCreateCopyDeletingLastPathComponent(0, url);
        if (CFURLGetFileSystemRepresentation(url2, 1, (UInt8 *)parentdir, MAXPATHLEN)) {
            chdir(parentdir);   /* chdir to the binary app's parent */
        }
        CFRelease(url);
        CFRelease(url2);
    }
}

#if SDL_USE_NIB_FILE

/* Fix menu to contain the real app name instead of "SDL App" */
- (void)fixMenu:(NSMenu *)aMenu withAppName:(NSString *)appName
{
    NSRange aRange;
    NSEnumerator *enumerator;
    NSMenuItem *menuItem;
    
    aRange = [[aMenu title] rangeOfString:@"SDL App"];
    if (aRange.length != 0)
        [aMenu setTitle: [[aMenu title] stringByReplacingRange:aRange with:appName]];
    
    enumerator = [[aMenu itemArray] objectEnumerator];
    while ((menuItem = [enumerator nextObject]))
    {
        aRange = [[menuItem title] rangeOfString:@"SDL App"];
        if (aRange.length != 0)
            [menuItem setTitle: [[menuItem title] stringByReplacingRange:aRange with:appName]];
        if ([menuItem hasSubmenu])
            [self fixMenu:[menuItem submenu] withAppName:appName];
    }
    [ aMenu sizeToFit ];
}

#else

static void setApplicationMenu(void)
{
    /* warning: this code is very odd */
    NSMenu *appleMenu;
    NSMenuItem *menuItem;
    NSString *title;
    NSString *appName;
    
    appName = getApplicationName();
    appleMenu = [[NSMenu alloc] initWithTitle:@""];
    
    /* Add menu items */
    title = [@"About " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(orderFrontStandardAboutPanel:) keyEquivalent:@""];
    
    [appleMenu addItem:[NSMenuItem separatorItem]];
    
    title = [@"Hide " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(hide:) keyEquivalent:@"h"];
    
    menuItem = (NSMenuItem *)[appleMenu addItemWithTitle:@"Hide Others" action:@selector(hideOtherApplications:) keyEquivalent:@"h"];
    [menuItem setKeyEquivalentModifierMask:(NSAlternateKeyMask|NSCommandKeyMask)];
    
    [appleMenu addItemWithTitle:@"Show All" action:@selector(unhideAllApplications:) keyEquivalent:@""];
    
    [appleMenu addItem:[NSMenuItem separatorItem]];
    
    title = [@"Quit " stringByAppendingString:appName];
    [appleMenu addItemWithTitle:title action:@selector(terminate:) keyEquivalent:@"q"];
    
    
    /* Put menu into the menubar */
    menuItem = [[NSMenuItem alloc] initWithTitle:@"" action:nil keyEquivalent:@""];
    [menuItem setSubmenu:appleMenu];
    [[NSApp mainMenu] addItem:menuItem];
    
    /* Tell the application object that this is now the application menu */
    [NSApp setAppleMenu:appleMenu];
    
    /* Finally give up our references to the objects */
    [appleMenu release];
    [menuItem release];
}

/* Create a window menu */
static void setupWindowMenu(void)
{
    NSMenu      *windowMenu;
    NSMenuItem  *windowMenuItem;
    NSMenuItem  *menuItem;
    
    windowMenu = [[NSMenu alloc] initWithTitle:@"Window"];
    
    /* "Minimize" item */
    menuItem = [[NSMenuItem alloc] initWithTitle:@"Minimize" action:@selector(performMiniaturize:) keyEquivalent:@"m"];
    [windowMenu addItem:menuItem];
    //[menuItem release];
    
    /* Put menu into the menubar */
    windowMenuItem = [[NSMenuItem alloc] initWithTitle:@"Window" action:nil keyEquivalent:@""];
    [windowMenuItem setSubmenu:windowMenu];
    [[NSApp mainMenu] addItem:windowMenuItem];
    
    /* Tell the application object that this is now the window menu */
    [NSApp setWindowsMenu:windowMenu];
    
    /* Finally give up our references to the objects */
    [windowMenu release];
    [windowMenuItem release];
}

/* Replacement for NSApplicationMain */
void CustomApplicationMain (int argc, const char **argv)
{
    NSAutoreleasePool	*pool = [[NSAutoreleasePool alloc] init];
    SDLMain				*sdlMain;
    
    /* Ensure the application object is initialised */
    [SDLApplication sharedApplication];
    
#ifdef SDL_USE_CPS
    {
        CPSProcessSerNum PSN;
        /* Tell the dock about us */
        if (!CPSGetCurrentProcess(&PSN))
            if (!CPSEnableForegroundOperation(&PSN,0x03,0x3C,0x2C,0x1103))
                if (!CPSSetFrontProcess(&PSN))
                    [SDLApplication sharedApplication];
    }
#endif /* SDL_USE_CPS */
    
    /* Set up the menubar */
    [NSApp setMainMenu:[[NSMenu alloc] init]];
    setApplicationMenu();
    setupWindowMenu();
    
    /* Create SDLMain and make it the app delegate */
    sdlMain = [[SDLMain alloc] init];
    [NSApp setDelegate:sdlMain];
    
    /* Start the main event loop */
    [NSApp run];
    
    [sdlMain release];
    [pool release];
}

#endif


/*
 * Catch document open requests...this lets us notice files when the app
 *  was launched by double-clicking a document, or when a document was
 *  dragged/dropped on the app's icon. You need to have a
 *  CFBundleDocumentsType section in your Info.plist to get this message,
 *  apparently.
 *
 * Files are added to gArgv, so to the app, they'll look like command line
 *  arguments. Previously, apps launched from the finder had nothing but
 *  an argv[0].
 *
 * This message may be received multiple times to open several docs on launch.
 *
 * This message is ignored once the app's mainline has been called.
 */
- (BOOL)application:(NSApplication *)theApplication openFile:(NSString *)filename
{
    const char *temparg;
    size_t arglen;
    char *arg;
    char **newargv;
    
    if (!gFinderLaunch)  /* MacOS is passing command line args. */
        return FALSE;
    
    if (gCalledAppMainline)  /* app has started, ignore this document. */
        return FALSE;
    
    temparg = [filename UTF8String];
    arglen = SDL_strlen(temparg) + 1;
    arg = (char *) SDL_malloc(arglen);
    if (arg == NULL)
        return FALSE;
    
    newargv = (char **) realloc(gArgv, sizeof (char *) * (gArgc + 2));
    if (newargv == NULL)
    {
        SDL_free(arg);
        return FALSE;
    }
    gArgv = newargv;
    
    SDL_strlcpy(arg, temparg, arglen);
    gArgv[gArgc++] = arg;
    gArgv[gArgc] = NULL;
    return TRUE;
}


/* Called when the internal event loop has just started running */
- (void) applicationDidFinishLaunching: (NSNotification *) note
{
    int status;
    
    /* Set the working directory to the .app's parent directory */
    [self setupWorkingDirectory:gFinderLaunch];
    
#if SDL_USE_NIB_FILE
    /* Set the main menu to contain the real app name instead of "SDL App" */
    [self fixMenu:[NSApp mainMenu] withAppName:getApplicationName()];
#endif
    
    wc = [[NSWindowController alloc] initWithWindowNibName:@"GPIO_Ctrl" ];
    [wc showWindow:self];
    
    thisClass = self;
    
    for( int i = 0; i < 80; i++ )
    {
        gpio_state[i] = 0;
        gpio_out[i] = nil;
    }
    
    for( int i = 0; i < 16; i++ )
    {
        adc_value[i] = 0;
    }
    
    button_posx = 152;
    button_posy = 455;
    
    /* Hand off to main application code */
    gCalledAppMainline = TRUE;
    status = SDL_main (gArgc, gArgv);
    
    /* We're done, thank you for playing */
    exit(status);
}

- (int)objc_window_ready
{
    NSArray *wn_array = [[NSApplication sharedApplication]windows];
    if( wn_array == nil ) return 0;
    
    NSWindow * wn = [wn_array objectAtIndex:0];
    printf( "Loaded %s %d\n", [[wn title]UTF8String], (int)[[[NSApplication  sharedApplication]windows]count] );

    return 1;
}

- (int)objc_add_button:(int) gpio_index
{
    NSArray *wn_array = [[NSApplication sharedApplication]windows];
    if( wn_array == nil ) return 0;

    int total = (int)[wn_array count];
    int index;
    NSWindow * wn = NULL;
    
    for( index = 0; index < total; index++ )
    {
        wn = [wn_array objectAtIndex:index];
        if( !strcmp( "Window", [[wn title]UTF8String]) ) break;
        wn = NULL;
    }
    
    if( wn != NULL )
    {
        NSView * view = [wn contentView];
        
        NSRect button_frame = NSMakeRect(button_posx + 35, button_posy, 55, 30);
        NSRect label_frame = NSMakeRect(button_posx, button_posy-5, 55, 30);
        
        NSButton * button = [[NSButton alloc] initWithFrame:button_frame];
        NSTextField * label = [[NSTextField alloc] initWithFrame:label_frame];
        
        char * button_name = ( char * )gpio_names[gpio_index];
        
        printf( "Button %s\n", button_name );
        
        [label setStringValue:[NSString stringWithUTF8String:button_name]];
        [label setBezeled:NO];
        [label setDrawsBackground:NO];
        [label setEditable:NO];
        [label setSelectable:NO];
        
        [button setBezelStyle:NSRegularSquareBezelStyle];
        [button setTitle:@""];
        [view addSubview:button];
        [view addSubview:label];

        gpio_out[gpio_index] = button;
        button_posy -= 30;
    }

    return 1;
}

- (IBAction)oil_gpio_action:(id)sender
{
    NSButton * btn = ( NSButton * )sender;
    
    const char *c_id = [[btn identifier] UTF8String];
    
    if( !strcmp( c_id, "gpio_oil" ) )
    {
        gpio_state[(int)GPIO_PC23] = (int)[btn state];
    }
    else if( !strcmp( c_id, "handbrake_released" ) )
    {
        gpio_state[(int)GPIO_PE10] = (int)[btn state];
    }
    else if( !strcmp( c_id, "handbrake_pulled" ) )
    {
        gpio_state[(int)GPIO_PE11] = (int)[btn state];
    }
    else if( !strcmp( c_id, "ind_left" ) )
    {
        gpio_state[(int)GPIO_PE00] = (int)[btn state];
    }
    else if( !strcmp( c_id, "ind_right" ) )
    {
        gpio_state[(int)GPIO_PE01] = (int)[btn state];
    }
    else if( !strcmp( c_id, "hazard" ) )
    {
        gpio_state[(int)GPIO_PE06] = (int)[btn state];
    }
    else if( !strcmp( c_id, "ign_key" ) )
    {
        gpio_state[(int)GPIO_PC17] = (int)[btn state];
    }
    else if( !strcmp( c_id, "engine_run" ) )
    {
        gpio_state[(int)GPIO_PC16] = (int)[btn state];
    }
    else if( !strcmp( c_id, "headlights" ) )
    {
        gpio_state[(int)GPIO_PH09] = (int)[btn state];
    }
    else if( !strcmp( c_id, "fog_lights" ) )
    {
        gpio_state[(int)GPIO_PH10] = (int)[btn state];
    }
    else if( !strcmp( c_id, "full_beam" ) )
    {
        gpio_state[(int)GPIO_PC18] = (int)[btn state];
    }
    
    //[btn identifier]
    //printf("action: %s\n", c_id );
}

- (void)obj_c_set_gpio_state:(int)index setstate:(int)state
{
    NSImage * image;
    NSButton * button = NULL;
    
    button = gpio_out[index];
    if( button == NULL ) return;
    
    if( state )
    {
        image = [NSImage imageNamed:@"enable.png"];
    }
    else
    {
        image = [NSImage imageNamed:@"Zero.png"];
    }

    [button setImage:image];
}

- (IBAction)fuel_adc_action:(id)sender
{
    NSSlider * slider = ( NSSlider * )sender;
    const char * c_id = [[slider identifier] UTF8String];

    if( !strcmp( c_id, "adc_fuel" ) )
    {
        adc_value[0] = (int)[slider integerValue];
    }
    
    //printf("action: %s\n", c_id );
}

int ui_is_window_ready( void )
{
    return [thisClass objc_window_ready];
}

int ui_add_button( int index )
{
    return [thisClass objc_add_button:index];
}

void set_gpio_state( int index, int state )
{
    [ thisClass obj_c_set_gpio_state:index setstate:state ];
}

int get_gpio_state( int index )
{
    if( (gpio_t)index == GPIO_PE06 )
    {
        //printf( "debug\n" );
    }
    return gpio_state[index];
}

int cocoa_get_adc_value( int index )
{
    return adc_value[index];
}

@end


@implementation NSString (ReplaceSubString)

- (NSString *)stringByReplacingRange:(NSRange)aRange with:(NSString *)aString
{
    unsigned int bufferSize;
    unsigned int selfLen = (unsigned int)[self length];
    unsigned int aStringLen = (unsigned int)[aString length];
    unichar *buffer;
    NSRange localRange;
    NSString *result;
    
    bufferSize = (unsigned int)( selfLen + aStringLen - aRange.length );
    buffer = (unichar *)NSAllocateMemoryPages(bufferSize*sizeof(unichar));
    
    /* Get first part into buffer */
    localRange.location = 0;
    localRange.length = aRange.location;
    [self getCharacters:buffer range:localRange];
    
    /* Get middle part into buffer */
    localRange.location = 0;
    localRange.length = aStringLen;
    [aString getCharacters:(buffer+aRange.location) range:localRange];
    
    /* Get last part into buffer */
    localRange.location = aRange.location + aRange.length;
    localRange.length = selfLen - localRange.location;
    [self getCharacters:(buffer+aRange.location+aStringLen) range:localRange];
    
    /* Build output string */
    result = [NSString stringWithCharacters:buffer length:bufferSize];
    
    NSDeallocateMemoryPages(buffer, bufferSize);
    
    return result;
}

@end



//#ifdef USING_CONSOLE_PROJECT
#ifdef main
#  undef main
#endif

/* Main entry point to executable - should *not* be SDL_main! */
int main (int argc, char **argv)
{
    /* Copy the arguments into a global variable */
    /* This is passed if we are launched by double-clicking */
    if ( argc >= 2 && strncmp (argv[1], "-psn", 4) == 0 ) {
        gArgv = (char **) SDL_malloc(sizeof (char *) * 2);
        gArgv[0] = argv[0];
        gArgv[1] = NULL;
        gArgc = 1;
        gFinderLaunch = YES;
    } else {
        int i;
        gArgc = argc;
        gArgv = (char **) SDL_malloc(sizeof (char *) * (argc+1));
        for (i = 0; i <= argc; i++)
            gArgv[i] = argv[i];
        gFinderLaunch = NO;
    }
    
#if SDL_USE_NIB_FILE
    [SDLApplication poseAsClass:[NSApplication class]];
    NSApplicationMain (argc, argv);
#else
    CustomApplicationMain (argc, argv);
#endif
    return 0;
}
//#endif


