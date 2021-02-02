#include "types.h"
#include "bitmap.h"

///////////////////////////////////////////////////////////////////////////

#define MAX_ALLOC_SIZE  8192

///////////////////////////////////////////////////////////////////////////

typedef struct
{
	uint16_t reserved;
	uint16_t bitmap_id;
	uint32_t file_size;
	uint16_t reserved1;
	uint16_t reserved2;
	uint32_t file_offset;

} bitmap_file_header_t;

typedef struct
{
	uint32_t data_size;
	uint32_t bitmap_width;
	uint32_t bitmap_height;

	uint16_t bitmap_planes;
	uint16_t bit_count;

	uint32_t compression;
	uint32_t image_size;
	uint32_t resolution_x;
	uint32_t resolution_y;
	uint32_t colour_used;
	uint32_t important_colour;

} bitmap_info_header_t;

typedef struct
{
	bitmap_file_header_t file_header;
	bitmap_info_header_t info_header;

} bitmap_file_t;

typedef struct
{
	uint8_t blue;
	uint8_t green;
	uint8_t red;

} tBitmapPixel;

///////////////////////////////////////////////////////////////////////////

int bitmap_load_to_lcd( bitmap_t * lcd, const char * filename, uint16_t posx, uint16_t posy )
{
    FILE * bitmap_file;
   
    //pixel_t * lcd_buffer;

    bitmap_file_t bitmap_header;
    
    uint8_t pixel_array[4];
    uint32_t read_len;
    uint32_t line_size;
    uint32_t pixel_size;
    uint16_t x,y;
    //uint16_t lcd_width;
    //uint16_t lcd_height;
    uint32_t lcd_temp_pos;
    uint8_t is_fail = FALSE;
    
    bitmap_file = fopen( filename, "rb" );
    if( bitmap_file == NULL )
    {
        printf( "fopen failed \r\n" );
        return( -1 );
    }

    // read the bitmap header
    if( fread( ( uint8_t * )&bitmap_header.file_header.bitmap_id, sizeof( bitmap_header ) - 2, 1, bitmap_file ) == 0 )
        is_fail = TRUE;
    
    if( bitmap_header.info_header.image_size == 0 )
        bitmap_header.info_header.image_size = bitmap_header.file_header.file_size - bitmap_header.file_header.file_offset;
    
    // this is the supported format
    if( bitmap_header.file_header.bitmap_id != 0x4D42 ) is_fail = TRUE;
    if( bitmap_header.info_header.bitmap_planes != 1 ) is_fail = TRUE;
    if( bitmap_header.info_header.bit_count != 24 ) is_fail = TRUE;
    if( bitmap_header.info_header.compression != 0 ) is_fail = TRUE;
    
    if( is_fail == TRUE )
    {
        printf( "bitmap unknown format\r\n" );
        fclose( bitmap_file );
        return( -2 );
    }

    line_size = bitmap_header.info_header.image_size / bitmap_header.info_header.bitmap_height;
    pixel_size = line_size / bitmap_header.info_header.bitmap_width;

    lcd_temp_pos = ( lcd->width * ( posy + bitmap_header.info_header.bitmap_height - 1 ) ) + posx;
    
    for( y = 0; y < bitmap_header.info_header.bitmap_height; y++ )
    {
        for( x = 0; x < bitmap_header.info_header.bitmap_width; x++ )
        {
            read_len = (uint32_t)fread( ( uint8_t * )pixel_array, pixel_size, 1, bitmap_file );
            if( read_len == 0 ) break;

            lcd->buffer[lcd_temp_pos++] = APP_RGB(pixel_array[2], pixel_array[1], pixel_array[0]);
        }
        
        lcd_temp_pos -= ( bitmap_header.info_header.bitmap_width << 1 );
    }

    // close file
    fclose( bitmap_file );

    return 0;
}

bitmap_t * bitmap_load_file( const char * filename )
{
    bitmap_t * local_bitmap;

    FILE * bitmap_file;

    bitmap_file_t bitmap_header;

    uint8_t is_fail = FALSE;
	uint16_t x;
	uint16_t y;

	uint32_t line_size;
    uint32_t pixel_size;
    uint32_t read_len;

    uint8_t * line_buffer;
    uint8_t * ptr_line_buffer;
    pixel_t * input_buffer;

    // open the file
    bitmap_file = fopen( filename, "rb" );
    if( bitmap_file == NULL )
    {
        DEBUG_PRINTK( "fopen failed (%s)\r\n", filename );
        return( NULL );
    }

    // read the bitmap header
    if( fread( ( uint8_t * )&bitmap_header.file_header.bitmap_id, sizeof( bitmap_header ) - 2, 1, bitmap_file ) == 0 )
		is_fail = TRUE;

    if( bitmap_header.info_header.image_size == 0 )
        bitmap_header.info_header.image_size = bitmap_header.file_header.file_size - bitmap_header.file_header.file_offset;

    // this is the supported format
	if( bitmap_header.file_header.bitmap_id != 0x4D42 ) is_fail = TRUE;
	if( bitmap_header.info_header.bitmap_planes != 1 ) is_fail = TRUE;
	if( bitmap_header.info_header.bit_count != 24 ) is_fail = TRUE;
	if( bitmap_header.info_header.compression != 0 ) is_fail = TRUE;

	if( is_fail == TRUE )
	{
        DEBUG_PRINTK( "bitmap unknown format\r\n" );
        fclose( bitmap_file );
        return( NULL );
	}

    // allocate bitmap data
    local_bitmap = ( bitmap_t * )MMALLOC( sizeof( bitmap_t ) );
    if( local_bitmap == NULL )
	{
        DEBUG_PRINTK( "local_bitmap error\r\n" );
        fclose( bitmap_file );
        return( NULL );
    }

    // allocate buffer
    local_bitmap->buffer = ( pixel_t * )MMALLOC( bitmap_header.info_header.bitmap_height *
                                              bitmap_header.info_header.bitmap_width * sizeof( pixel_t ) );

    if( local_bitmap->buffer == NULL )
    {
        DEBUG_PRINTK( "local_bitmap->buffer error\r\n" );
        MFREE( local_bitmap );
        fclose( bitmap_file );
        return( NULL );
    }

    // insert bitmap data
    local_bitmap->width = bitmap_header.info_header.bitmap_width;
    local_bitmap->height = bitmap_header.info_header.bitmap_height;

    // line size regarding the BMP standard
    line_size = bitmap_header.info_header.image_size / bitmap_header.info_header.bitmap_height;
    pixel_size = line_size / bitmap_header.info_header.bitmap_width;
    
    // allocate one line
	line_buffer = ( uint8_t * )MMALLOC( line_size );
	if( line_buffer == NULL )
	{
        DEBUG_PRINTK( "line_buffer error\r\n" );
		MFREE( local_bitmap->buffer );
		MFREE( local_bitmap );
        fclose( bitmap_file );
        return( NULL );
	}

    input_buffer = &local_bitmap->buffer[ ( bitmap_header.info_header.bitmap_height *
                                            bitmap_header.info_header.bitmap_width ) ];

    input_buffer -= bitmap_header.info_header.bitmap_width;

	for( y = 0; y < bitmap_header.info_header.bitmap_height; y++ )
	{
        // read BMP from the bottom
		read_len = (uint32_t)fread( ( uint8_t * )line_buffer, line_size, 1, bitmap_file );
        ptr_line_buffer = line_buffer;

        for( x = 0; x < bitmap_header.info_header.bitmap_width; x++ )
        {
            *input_buffer = APP_RGB(*( ptr_line_buffer+2 ), *( ptr_line_buffer+1 ), *( ptr_line_buffer+0 ));
            
            ptr_line_buffer += pixel_size;
            input_buffer++;
        }

        input_buffer -= ( bitmap_header.info_header.bitmap_width << 1 );
	}

    local_bitmap->background_colour = local_bitmap->buffer[ 0 ];

    // release one line
    MFREE( line_buffer );

    // close file
    fclose( bitmap_file );

    return( local_bitmap );
}

bitmap_t * bitmap_create( uint16_t width, uint16_t height )
{
	bitmap_t * local_bitmap;

    // allocate bitmap data
    local_bitmap = ( bitmap_t * )malloc( sizeof( bitmap_t ) );
    if( local_bitmap == NULL )
	{
        DEBUG_PRINTK( "local_bitmap error\r\n" );
        return( NULL );
    }

    // allocate buffer
    local_bitmap->buffer = ( pixel_t * )MMALLOC( height * width * sizeof( pixel_t ) );

    if( local_bitmap->buffer == NULL )
    {
        DEBUG_PRINTK( "local_bitmap->buffer error\r\n" );
        MFREE( local_bitmap );
        return( NULL );
    }

    memset( local_bitmap->buffer, 0x00, height * width * sizeof( pixel_t ) );
    local_bitmap->width = width;
    local_bitmap->height = height;
    local_bitmap->background_colour = 0;

    return local_bitmap;
}

void bitmap_release( bitmap_t * bitmap )
{
    MFREE( bitmap->buffer );
    MFREE( bitmap );
}

