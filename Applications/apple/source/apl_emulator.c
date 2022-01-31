//
//  main.c
//  AppleEmulator
//
//  Created by Marcio Cherobim on 07/04/2014.
//  Copyright (c) 2014 Marcio Cherobim. All rights reserved.
//

#include "types.h"

#include "board.h"
#include "draw.h"
#include "bitmap.h"
#include "keyboard_drv.h"
#include "disc_utils.h"
#include "socket_dma.h"
#include "ram_ctrl.h"

//#define _USE_OLIMEX_
// #define _USE_RPI_

////////////////////////////////////////////////////////////////////////

#if defined __MACH__
#define BOARD_PATH			"/Users/marciocherobim/Projects/GIT_Dev/tima_linux/Applications/apple/images"
#elif defined TIMA_LINUX
#ifdef _USE_OLIMEX_
#define BOARD_PATH          "/root/apple/images"
#else
#define BOARD_PATH          "/home/pi/apple/images"
#endif
#endif

////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////

static board_data_t board_data;
static char image_filename[256];
//static pixel_t * temp_frame;
static bitmap_t * lcd;
static list_t image_file_list;

////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////

void print_handler( char * data )
{
    printf( "%s", ( const char * )data );
}

char * convert_filename( const char * handler )
{
    //char * p_name;
    
    strcpy( image_filename, BOARD_PATH );
    strcat( image_filename, "/" );
    strcat( image_filename, handler );
    
#ifdef WIN32
    while( ( p_name = strchr( image_filename, '/' ) ) != NULL )
    {
        *p_name = '\\';
    }
#endif
    
    return &image_filename[0];
}

void dump_memory_filesys( uint16_t addr, uint16_t len, const char * name )
{
    FILE * fp = fopen( convert_filename( name ), "wb" );
    if( fp != NULL )
    {
        uint8_t * ram_dma_addr = ram_get_dma_pointer( addr );
        fwrite( ram_dma_addr, len, 1, fp );
        fclose( fp );
    }
}

uint32_t disc_image_entry_point( const char * handler, uint8_t mode, uint32_t pos, uint8_t * buffer, uint32_t size )
{
    fpos_t end_ptr;
    uint32_t ret = 0;
    FILE * fp = NULL;
    
    if( mode == Disc_Mode_Remove )
    {
        return ( uint32_t )remove( convert_filename( handler ) );
    }
    
    else if( mode == Disc_Mode_Append )
    {
        fp = fopen( convert_filename( handler ), "ab" );
    }
    else
    {
        fp = fopen( convert_filename( handler ), "r+b" );
        if( fp == NULL )
        {
            if( mode == Disc_Mode_Write )
            {
                fp = fopen( convert_filename( handler ), "wb" );
            }
            
            if( fp == NULL ) return 0;
        }
        
        if( pos != 0 ) fseek( fp, ( long )pos, SEEK_SET );
    }
    
    switch( mode )
    {
        case Disc_Mode_Read:
            ret = ( uint32_t )fread( buffer, 1, size, fp );
            break;
            
        case Disc_Mode_Append:
        case Disc_Mode_Write:
            ret = ( uint32_t )fwrite( buffer, 1, size, fp );
            break;
            
        case Disc_Mode_Size:
            fseek( fp, ( long )0, SEEK_END );
            ret = ( uint32_t )ftell(fp);
            break;
    }
    
    fclose( fp );
    
    return( ret );
}

string_t * image_list_controller( void ** item )
{
    file_data_t * p_item = ( file_data_t * )*item;

    if( p_item == NULL ) p_item = ( file_data_t * )list_get_head( &image_file_list );
    else                 p_item = ( file_data_t * )list_get_next( &image_file_list, &p_item->node );

    if( p_item == NULL ) return NULL;
    *item = p_item;

    string_t * sub_string = string_get_substring( p_item->full_path, strlen( BOARD_PATH ) + 1, NEG_U32 );
    return sub_string;
}

board_data_t * apl_emulator_init( void )
{
    printf( "Using %s\n", BOARD_PATH );
    keybdrv_init();
    lcd_driver_mouse_init( "/dev/input/event0" );
    lcd = graphics_init();

    memset( &board_data, 0x00, sizeof( board_data ) );

    // setup board data
    board_data.p_image_list  = image_list_controller;    
    board_data.p_print       = print_handler;
    board_data.p_disc_access = disc_image_entry_point;

    // initialize board
    board_startup( &board_data );

    disc_utils_init_file_list( &image_file_list );
    disc_utils_read_dir( BOARD_PATH, ".dsk", &image_file_list, TRUE );
    
    return &board_data;
}
