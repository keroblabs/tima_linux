#include "board.h"
#include "io_addr.h"
#include "cpu.h"
#include "ram_ctrl.h"
#include "video.h"
#include "mouse.h"
#include "keyboard_drv.h"

#ifdef ENABLE_EMBEDDED_ASM
#include "embedded.h"
#endif

//////////////////////////////////////////////////////////////////////////////////////

#define MODEON          1
#define MODEIRQMOVE     2
#define MODEIRQBUTTON   4
#define MODEIRQVBL      8
#define MODEIRQCXFALL   16
#define MODEIRQCXRAISE  32
#define MODEIRQCYFALL   64
#define MODEIRQCYRAISE  128

#define IRQBUTTON1PREV  1
#define IRQMOVE         2
#define IRQBUTTON       4
#define IRQVBL          8
#define IRQBUTTON1      16
#define IRQXYMOVE       32
#define IRQBUTTON0PREV  64
#define IRQBUTTON0      128
#define IRQCXFALL       16
#define IRQCXRAISE      32
#define IRQCYFALL       64
#define IRQCYRAISE      128

//////////////////////////////////////////////////////////////////////////////////////

#define MOUSE_USE_FILE
#define MOUSE_FW_BINARY		"rom/mouse_fw.bin"
#define MOUSE_FW_SOURCE		"fw/mouse_driver/mouse_src_org.asm"

//////////////////////////////////////////////////////////////////////////////////////

#ifdef MOUSE_USE_FILE

static uint8_t mouse_fw[4096];
static const char * mouse_source_list[2] =
{
	MOUSE_FW_SOURCE,
	NULL
};

#else
const static uint8_t mouse_fw[] =
{
	0x2C, 0x58, 0xFF, 0x70, 0x1B, 0x38, 0x90, 0x18, 0xB8, 0x50, 0x15, 0x01, 0x20, 0x9E, 0x9E, 0x9E, 
	0x9E, 0x00, 0x5D, 0x65, 0x7E, 0x8F, 0x94, 0x76, 0x99, 0x87, 0x9E, 0x9E, 0x9E, 0x9E, 0x9E, 0x9E, 
	0x5A, 0xDA, 0x48, 0x08, 0x78, 0x20, 0x58, 0xFF, 0xBA, 0xBD, 0x00, 0x01, 0xAA, 0x0A, 0x0A, 0x0A, 
	0x0A, 0xA8, 0x28, 0x50, 0x0F, 0xA5, 0x38, 0xD0, 0x0D, 0x8A, 0x45, 0x39, 0xD0, 0x08, 0xA9, 0x05, 
	0x85, 0x38, 0xD0, 0x0B, 0xB0, 0x09, 0x68, 0x48, 0x99, 0x80, 0xC0, 0x68, 0xFA, 0x7A, 0x60, 0x99, 
	0x81, 0xC0, 0x68, 0xBD, 0x38, 0x06, 0xAA, 0x68, 0xBD, 0x00, 0x02, 0x7A, 0x60, 0xC9, 0x10, 0xB0, 
	0x3F, 0x99, 0x82, 0xC0, 0x60, 0x48, 0x18, 0xA9, 0x03, 0x99, 0x83, 0xC0, 0xBD, 0xB8, 0x06, 0x29, 
	0x0E, 0xD0, 0x01, 0x38, 0x68, 0x60, 0xC9, 0x02, 0xB0, 0x26, 0x99, 0x83, 0xC0, 0x60, 0xA9, 0x04, 
	0x99, 0x83, 0xC0, 0xBD, 0xB8, 0x06, 0x60, 0x48, 0xA9, 0x02, 0x99, 0x83, 0xC0, 0x68, 0x60, 0x48, 
	0xA9, 0x05, 0xD0, 0xF6, 0x48, 0xA9, 0x06, 0xD0, 0xF1, 0x48, 0xA9, 0x07, 0xD0, 0xEC, 0xA2, 0x03, 
	0x38, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xD6, 0x00, 0x00, 0x00, 0x01, 

};
#endif

//////////////////////////////////////////////////////////////////////////////////////

#define    mouseirq		mouse_data.mouse_irq
#define    mousemode    mouse_data.mouse_mode
#define    mouseleft	mouse_data.mouse_left
#define    mousetop		mouse_data.mouse_top
#define    mouseright   mouse_data.mouse_right
#define    mousedown	mouse_data.mouse_down

//////////////////////////////////////////////////////////////////////////////////////

typedef struct _mouse_data_t_
{
    uint8_t    mouse_irq;
    uint8_t    mouse_mode;
    uint32_t   mouse_left;
    uint32_t   mouse_top;
    uint32_t   mouse_right;
    uint32_t   mouse_down;

} mouse_data_t;

//////////////////////////////////////////////////////////////////////////////////////

static uint32_t   mouseslot;
static uint8_t    mousestate;
static uint32_t   mousex;
static uint32_t   mousey;
static uint32_t   mousereadx;
static uint32_t   mouseready;
static uint32_t   mouseoldx;
static uint32_t   mouseoldy;

static uint32_t   mousebutton;
static uint32_t	  mouseoldbutton;

static bool_t     mouse_irq_trigger;
static bool_t     mouse_irq_state;

static board_data_t * board;
static loop_hdl_t local_loop;
static vbl_hdl_t local_vbl;
static interrupt_hdl_t local_irq;
static mouse_data_t mouse_data;

//////////////////////////////////////////////////////////////////////////////////////

static void mouse_mem_dma_write( uint16_t addr, uint8_t data )
{
    ram_ctrl_write_8( addr, data );
}

static uint8_t mouse_mem_dma_read( uint16_t addr )
{
    return ram_ctrl_read_8( addr );
}

static void mouse_reset( void )
{
	mousemode       = 0;
	mousestate      = 0;
	mouseirq        = 0;
	mousex          = 0;
	mousey          = 0;
	mousereadx      = 0;
	mouseready      = 0;
	mouseoldx       = 0;
	mouseoldy       = 0;
	mouseleft       = 0;
	mousetop        = 0;
	mouseright      = 1023;//4095;
	mousedown       = 1023;//4095;
	mousebutton     = 0;
	mouseoldbutton  = 0;

	mouse_irq_trigger = FALSE;
	mouse_irq_state   = FALSE;
}

static void mouse_write_coords( void )
{
	mouse_mem_dma_write( 0x478 + mouseslot, mousex & 0x0FF );
	mouse_mem_dma_write( 0x578 + mouseslot, mousex >> 8 );
	mouse_mem_dma_write( 0x4f8 + mouseslot, mousey & 0x0FF );
	mouse_mem_dma_write( 0x5f8 + mouseslot, mousey >> 8 );
}

static uint8_t mouse_io_controller( uint8_t address, uint8_t data )
{
	uint32_t t1;
	uint32_t t2;

	t1 = 0;

	switch( address & 0x0F )
	{
		case 0x02:
			// set mouse
		    printf( "SetMouse 0x%02x\n", data );
			mousemode = data & (MODEON | MODEIRQMOVE | MODEIRQBUTTON | MODEIRQVBL);
			mouse_mem_dma_write( 0x07F8 + mouseslot, mousemode );
			break;

		case 0x03:
			switch( data )
			{
				case 0:
				case 1:
					t1 = mouse_mem_dma_read( 0x0578 );
					t1 = ( t1 << 8 ) + mouse_mem_dma_read( 0x0478 );

					t2 = mouse_mem_dma_read( 0x05f8 );
					t2 = ( t2 << 8 ) + mouse_mem_dma_read( 0x04f8 );

					if( data == 0 )
					{
						// clampxmouse
						if (t1 > t2) 
						{
							mouseleft  = t2;
							mouseright = t1;
						}
						else
						{
							mouseleft  = t1;
							mouseright = t2;
						}
					}
					else
					{
						// clampymouse
						if (t1 > t2) 
						{
							mousetop  = t2;
							mousedown = t1;
						}
						else
						{
							mousetop  = t1;
							mousedown = t2;
						}
					}

                    //printf( "ClampMouse = %d, %d (%d)\n", t1, t2, data, mousedown );

					keybdrv_mouse_set_limits( mouseleft, mouseright, mousetop, mousedown );
					break;

				case 0x02:
					// initmouse
                    //printf( "InitMouse\n" );
					mouse_reset();
					mouse_write_coords();
					mouse_mem_dma_write( 0x778+mouseslot, mousestate );
					mouse_mem_dma_write( 0x7f8+mouseslot, mousemode );
					break;

				case 0x03:
					// serevemouse
				    //printf( "ServeMouse\n" );
                    mousestate = 0;
                    if ((mousex != mouseoldx) || (mousey != mouseoldy))
                    {
                        mousestate = mousestate | IRQXYMOVE;
                        mouseoldx = mousex;
                        mouseoldy = mousey;
                    }

                    mousestate |= ( mousebutton == 1 ) ? IRQBUTTON0 : 0;
                    mousestate |= ( mouseoldbutton == 1 ) ? IRQBUTTON0PREV : 0;

					mouse_mem_dma_write( 0x778+mouseslot, mousestate | (mouseirq & (IRQMOVE | IRQBUTTON | IRQVBL)) );
                    //mouse_mem_dma_write( 0x6B8+mouseslot, mousestate | (mouseirq & (IRQMOVE | IRQBUTTON | IRQVBL)) );
					mouseirq = 0;   // reset mouse's interrupt line
					mouse_irq_state = FALSE;
			        mouse_irq_trigger = FALSE;
					break;

				case 0x04:
					// mouseread
                    //printf( "ReadMouse\n" );
					mouse_write_coords();

					mousestate = 0;
                    if ((mousex != mouseoldx) || (mousey != mouseoldy))
                    {
                        mousestate = mousestate | IRQXYMOVE;
                        mouseoldx = mousex;
                        mouseoldy = mousey;
                    }

                    mousestate |= ( mousebutton == 1 ) ? IRQBUTTON0 : 0;
                    mousestate |= ( mouseoldbutton == 1 ) ? IRQBUTTON0PREV : 0;
                    mouseoldbutton = mousebutton;

					mouse_mem_dma_write(0x778+mouseslot, mousestate | (mouseirq & (IRQMOVE | IRQBUTTON | IRQVBL)) );
                    //mouse_mem_dma_write(0x6B8+mouseslot, mousestate | (mouseirq & (IRQMOVE | IRQBUTTON | IRQVBL)) );
					break;

				case 0x05:
					// clearmouse
                    //printf( "ClearMouse\n" );
				    mousex = 0;
				    mousey = 0;
				    mouse_write_coords();
				    keybdrv_mouse_set_pos( mousex, mousey );
					break;

				case 0x06:
					// posmouse
					t1 = mouse_mem_dma_read( 0x0578+mouseslot );
					t1 = ( t1 << 8 ) + mouse_mem_dma_read( 0x0478+mouseslot );
					mousex = (t1 < mouseleft) ? mouseleft : (t1 > mouseright) ? mouseright : t1;

                    t1 = mouse_mem_dma_read( 0x05f8+mouseslot );
                    t1 = ( t1 << 8 ) + mouse_mem_dma_read( 0x04f8+mouseslot );
                    mousey = (t1 < mousetop) ? mousetop : (t1 > mousedown) ? mousedown : t1;

                    keybdrv_mouse_set_pos( mousex, mousey );
					mouse_write_coords();
					break;

				case 0x07:
					// homemouse
                    //printf( "HomeMouse\n" );
					mousex = mouseleft;
					mousey = mousetop;
					mouse_write_coords();
					break;
			}

			break;
	}

	return 0xA0;
}

static void mouse_vbl( void )
{
    local_vbl();


    if( ( mouse_irq_trigger == FALSE ) && ( mousemode & MODEIRQVBL ) && (!(mouseirq & IRQVBL)) )
    {
        mouse_irq_trigger = TRUE;
        mouseirq |= IRQVBL;
    }
}

static bool_t mouse_irq_hook( void )
{
    bool_t ret = local_irq();

    if( ( mouse_irq_trigger == TRUE ) && ( mouse_irq_state == FALSE ) )
    {
        mouse_irq_state   = TRUE;

        //printf( "IRQ generated\n" );
    }

    return mouse_irq_state ? TRUE : ret;
}

uint8_t mouse_loop( uint32_t cycles )
{
	uint8_t mouseirqold;
	uint8_t prev_mousebutton;
	uint16_t read_x, read_y, read_z;
	uint8_t ret;
	uint8_t ret_mouse;

	ret = local_loop( cycles );
	ret_mouse = keybdrv_mouse_get_pos( &read_x, &read_y, &read_z );

	if( mousemode & MODEON )
	{
		if( ret_mouse == TRUE )
		{
	        mouseirqold = mouseirq;

		    mousex = read_x;
		    mousey = read_y;

		    prev_mousebutton = mousebutton;
		    mousebutton = ( read_z > 0 ) ? 1 : 0;

		    if( mouse_irq_trigger == FALSE )
		    {
	            mouseirq |= ( (mousex < mousereadx) && (mousemode & MODEIRQCXFALL) ) ? IRQCXFALL : 0;
	            mouseirq |= ( (mousex > mousereadx) && (mousemode & MODEIRQCXRAISE) ) ? IRQCXRAISE : 0;

	            mouseirq |= ( (mousey < mouseready) && (mousemode & MODEIRQCYFALL) ) ? IRQCYFALL : 0;
	            mouseirq |= ( (mousey > mouseready) && (mousemode & MODEIRQCYRAISE) ) ? IRQCYRAISE : 0;

	            mouseirq |= ( (mousebutton != prev_mousebutton) && (mousemode & MODEIRQBUTTON) ) ? IRQBUTTON : 0;
		    }

			if ((mousex != mousereadx) || (mousey != mouseready)) 
			{
				if ( ( mouse_irq_trigger == FALSE ) && ( mousemode & MODEIRQMOVE ) )
				{
				    mouseirq = mouseirq | IRQMOVE;
				}
				mousereadx = mousex;
				mouseready = mousey;
			}

			if (mouseirqold != mouseirq)
			{
			    //printf( "IRQ Trigger\n" );
			    mouse_irq_trigger = TRUE;
			}
		}
	}

	return ret;
}

#ifdef MOUSE_USE_FILE
void mouse_card_fw_rebuild( bool_t force_build )
{
	if( ( board->p_disc_access( MOUSE_FW_BINARY, Disc_Mode_Size, 0, ( uint8_t * )&mouse_fw[0], 256 ) == 0 ) ||
		( force_build == TRUE ) )
	{
		#ifdef ENABLE_EMBEDDED_ASM
		assembler( mouse_source_list, 1, MOUSE_FW_BINARY, board );
		#endif
	}
}
#endif

void mouse_card_insert( uint8_t slot )
{
	int counter;
	uint8_t page = ( 0x08 + slot ) << 4;

	#ifdef MOUSE_USE_FILE
	mouse_card_fw_rebuild( TRUE );
	board->p_disc_access( MOUSE_FW_BINARY, Disc_Mode_Read, 0, ( uint8_t * )&mouse_fw[0], 256 );
	#endif

	mouseslot = slot;
	ram_ctrl_insert_slot( slot, ( uint8_t * )mouse_fw );

	local_irq = cpu_hook_irq( mouse_irq_hook );

	for( counter = 0; counter < 16; counter++ )
	{
		memory_io_set_handler( page + counter, mouse_io_controller, mouse_io_controller );
	}
}

void mouse_card_init( void * p_board )
{
	board = ( board_data_t * )p_board;

	mouse_reset();

	local_loop = board_hook_loop( mouse_loop );
	local_vbl = video_hook_vlb( mouse_vbl );
}
