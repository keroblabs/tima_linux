#include "led_frame.h"
#include "board.h"
#include "io_addr.h"
#include "cpu.h"
#include "timer.h"
#include "ram_ctrl.h"
#include "extension.h"
#include "draw.h"

//////////////////////////////////////////////////////////////////////////////////////

#define BUTTON_HIGHT			20

#define LCD_INACTIVE_COLOUR		APP_RGB(100, 100, 100)
#define LCD_INACTIVE_TEXT		APP_RGB(0, 0, 0)

//////////////////////////////////////////////////////////////////////////////////////

static const button_data_t led_data[] = 
{
	{ LCD_WIDTH - BUTTON_WIDTH, 10, BUTTON_WIDTH, BUTTON_HIGHT, LED_ID_HDD_D1 },
	{ LCD_WIDTH - BUTTON_WIDTH, 35, BUTTON_WIDTH, BUTTON_HIGHT, LED_ID_HDD_D2 },

	{ LCD_WIDTH - BUTTON_WIDTH, 70, BUTTON_WIDTH, BUTTON_HIGHT, LED_ID_DISC_D1 },
	{ LCD_WIDTH - BUTTON_WIDTH, 95, BUTTON_WIDTH, BUTTON_HIGHT, LED_ID_DISC_D2 },

	{ LCD_WIDTH - BUTTON_WIDTH, 130, BUTTON_WIDTH, BUTTON_HIGHT, LED_ID_TURBO },
	{ LCD_WIDTH - BUTTON_WIDTH, 200, BUTTON_WIDTH, BUTTON_HIGHT, LED_ID_CAPSLOCK },
	{ LCD_WIDTH - BUTTON_WIDTH, 240, BUTTON_WIDTH, BUTTON_HIGHT, LED_ID_PRINTER },

	{ LCD_WIDTH - BUTTON_WIDTH, 165, BUTTON_WIDTH, BUTTON_HIGHT, LED_ID_DESKTOP_1 },
	{ LCD_WIDTH - BUTTON_WIDTH, 165, BUTTON_WIDTH, BUTTON_HIGHT, LED_ID_DESKTOP_2 },
	{ LCD_WIDTH - BUTTON_WIDTH, 165, BUTTON_WIDTH, BUTTON_HIGHT, LED_ID_DESKTOP_3 },
	{ LCD_WIDTH - BUTTON_WIDTH, 165, BUTTON_WIDTH, BUTTON_HIGHT, LED_ID_DESKTOP_4 },
	{ LCD_WIDTH - BUTTON_WIDTH, 165, BUTTON_WIDTH, BUTTON_HIGHT, LED_ID_DESKTOP_5 },
	{ LCD_WIDTH - BUTTON_WIDTH, 165, BUTTON_WIDTH, BUTTON_HIGHT, LED_ID_DESKTOP_6 },
	{ LCD_WIDTH - BUTTON_WIDTH, 165, BUTTON_WIDTH, BUTTON_HIGHT, LED_ID_DESKTOP_7 },
	{ LCD_WIDTH - BUTTON_WIDTH, 165, BUTTON_WIDTH, BUTTON_HIGHT, LED_ID_DESKTOP_8 },
	{ LCD_WIDTH - BUTTON_WIDTH, 165, BUTTON_WIDTH, BUTTON_HIGHT, LED_ID_DESKTOP_9 },

	{ 0, 0, 0, 0, NEG_U32 },
};

static const pixel_t led_active_colour[] =
{
	APP_RGB(255, 64, 64),
	APP_RGB(255, 64, 64),
	APP_RGB(255, 64, 64),
	APP_RGB(255, 64, 64),

	APP_RGB(100, 255, 100),
	APP_RGB(100, 255, 100),
	APP_RGB(100, 255, 100),

	APP_RGB(100, 100, 100),
	APP_RGB(100, 100, 100),
	APP_RGB(100, 100, 100),
	APP_RGB(100, 100, 100),
	APP_RGB(100, 100, 100),
	APP_RGB(100, 100, 100),
	APP_RGB(100, 100, 100),
	APP_RGB(100, 100, 100),
	APP_RGB(100, 100, 100)
};

static const pixel_t led_active_text[] =
{
	APP_RGB(0, 0, 0),
	APP_RGB(0, 0, 0),
	APP_RGB(0, 0, 0),
	APP_RGB(0, 0, 0),

	APP_RGB(0, 0, 0),
	APP_RGB(0, 0, 0),
	APP_RGB(0, 0, 0),

	APP_RGB(0, 0, 0),
	APP_RGB(0, 0, 0),
	APP_RGB(0, 0, 0),
	APP_RGB(0, 0, 0),
	APP_RGB(0, 0, 0),
	APP_RGB(0, 0, 0),
	APP_RGB(0, 0, 0),
	APP_RGB(0, 0, 0),
	APP_RGB(0, 0, 0)
};

static const char * led_caption[] = 
{
	"H1", "H2", "D1", "D2", "T", "C", "P", "1", "2", "3", "4", "5", "6", "7", "8", "9"
};

//static const uint32_t led_reset_seq[] = 
//{
//	LED_ID_HDD_D1, LED_ID_HDD_D2, LED_ID_DISC_D1, LED_ID_DISC_D2, LED_ID_TURBO, LED_ID_CAPSLOCK, LED_ID_PRINTER, LED_ID_DESKTOP_1, NEG_U32,
//};

//////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////

void led_show( uint32_t id, uint8_t state )
{
#ifdef ENABLE_VIDEO
	int cnt;
	button_data_t * curr_button;
	pixel_t colour_f, colour_b;

	curr_button = NULL;

	for( cnt = 0; cnt < 255; cnt++ )
	{
		if( led_data[cnt].id_button == NEG_U32 ) break;

		if( led_data[cnt].id_button == id )
		{
			curr_button = ( button_data_t * )&led_data[cnt];
			break;
		}
	}

	if( curr_button != NULL )
	{
		if( state == FALSE )
		{
			colour_f = LCD_INACTIVE_TEXT;
			colour_b = LCD_INACTIVE_COLOUR;
		}
		else
		{
			colour_f = led_active_text[cnt];
			colour_b = led_active_colour[cnt];
		}
        
        void * lcd = graphics_claim();
		graphics_button_show( lcd, curr_button, ( char * )led_caption[cnt], colour_f, colour_b );
        graphics_release();
	}
#endif
}
