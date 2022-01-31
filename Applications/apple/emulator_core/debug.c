#include "message.h"
#include "board.h"
#include "debug.h"
#include "sw_switch.h"
#include "debug.h"
#include "cpu.h"
#include "ram_ctrl.h"
#include "video.h"
#include "led_frame.h"
#include "draw.h"

////////////////////////////////////////////////////////////////////////////////////

#define TRACE_DATA_MAX		8192
#define BREAK_DATA_MAX		32

#define  ADDR_IMPLIED		  0
#define  ADDR_INVALID1        1
#define  ADDR_INVALID2        2
#define  ADDR_INVALID3        3
#define  ADDR_IMM        4
#define  ADDR_ABS        5
#define  ADDR_ZPG        6
#define  ADDR_ABSX       7
#define  ADDR_ABSY       8
#define  ADDR_ZPGX       9
#define  ADDR_ZPGY       10
#define  ADDR_REL        11
#define  ADDR_INDX       12
#define  ADDR_ABSIINDX   13
#define  ADDR_INDY       14
#define  ADDR_IZPG       15
#define  ADDR_IABS       16

////////////////////////////////////////////////////////////////////////////////////

typedef struct _trace_entry_t
{
	uint16_t pc;
	uint8_t data[4];

} trace_entry_t;

typedef struct _addrrec
{
    const char format[12];
    uint8_t   bytes;
    bool_t add_comment;
    uint8_t show_reg;
} addrrec_t;

////////////////////////////////////////////////////////////////////////////////////

#ifdef TEXT
#undef TEXT
#endif

#define TEXT(a) a

#define SHOW_REG_NONE       0
#define SHOW_REG_ACC        1
#define SHOW_REG_X          2
#define SHOW_REG_Y          3

////////////////////////////////////////////////////////////////////////////////////

static uint8_t addr_id;
static char str_opcode[5];

char debug_temp_string[256];

static char tab_str[100];

//////////////////////////////////////////////////////////////////////////////////////

#include "instr_disasm.h"
#include "instr_code.h"

//////////////////////////////////////////////////////////////////////////////////////

addrrec_t addressmode[17]  = {   {TEXT("        ")		,1, TRUE , SHOW_REG_NONE },        // (implied)
								 {TEXT("        ")		,1, FALSE, SHOW_REG_NONE },        // INVALID1
								 {TEXT("        ")		,2, FALSE, SHOW_REG_NONE },        // INVALID2
								 {TEXT("        ")		,3, FALSE, SHOW_REG_NONE },        // INVALID3
								 {TEXT("#$%02X    ")	,2, FALSE, SHOW_REG_NONE },        // ADDR_IMM
								 {TEXT("$%04X   ")		,3, TRUE , SHOW_REG_NONE },        // ADDR_ABS
								 {TEXT("$%02X     ")	,2, TRUE , SHOW_REG_NONE },        // ADDR_ZPG
								 {TEXT("$%04X,X ")		,3, TRUE , SHOW_REG_X    },        // ADDR_ABSX
								 {TEXT("$%04X,Y ")		,3, TRUE , SHOW_REG_Y    },        // ADDR_ABSY
								 {TEXT("$%02X,X   ")	,2, TRUE , SHOW_REG_X    },        // ADDR_ZPGX
								 {TEXT("$%02X,Y   ")	,2, TRUE , SHOW_REG_Y    },        // ADDR_ZPGY
								 {TEXT("$%04X   ")		,2, TRUE , SHOW_REG_NONE },        // ADDR_REL
								 {TEXT("($%02X,X)  ")	,2, TRUE , SHOW_REG_X    },        // ADDR_INDX
								 {TEXT("($%04X,X) ")	,3, TRUE , SHOW_REG_X    },        // ADDR_ABSIINDX
								 {TEXT("($%02X),Y ")	,2, TRUE , SHOW_REG_Y    },        // ADDR_INDY
								 {TEXT("($%02X)    ")	,2, TRUE , SHOW_REG_NONE },        // ADDR_IZPG
								 {TEXT("($%04X) ")		,3, TRUE , SHOW_REG_NONE }         // ADDR_IABS
 };

////////////////////////////////////////////////////////////////////////////////////

static INLINE uint8_t cpu_read_8(uint16_t addr)
{
    return ram_ctrl_read_8( addr );
}

static INLINE uint16_t cpu_read_16(uint16_t addr)
{
    return ram_ctrl_read_16( addr );
}

uint8_t disasm_instruction( dump_hdl_t dump_hdl, uint16_t curr_pc )
{
	uint8_t addr;
	uint8_t bytes;
    
    uint8_t opcode;
    uint8_t byte1;
    uint8_t byte2;
    regsrec_t regs;
    
	char addr_str[20];
	char asm_code[20];
    char comment_str[80];
    char reg_str[80];
    
    uint16_t comment_addr = 0;

	addr_id = ADDR_IMPLIED;
    opcode = cpu_read_8( curr_pc );
    byte1 = cpu_read_8( curr_pc+1 );
    byte2 = cpu_read_8( curr_pc+2 );
    cpu_get_regs( &regs );

	INSTR_DECODE( opcode );

	addr = addr_id;
	bytes = addressmode[addr].bytes;

    if( addressmode[addr].add_comment )
    {
        strcpy( reg_str, "" );
        sprintf( comment_str, "%s <- 0x%04X", str_opcode, comment_addr );
        
        uint8_t show_reg = addressmode[addr].show_reg;
        
        if( show_reg == SHOW_REG_NONE )
        {
            if( !strcmp( str_opcode, "LDA" ) || !strcmp( str_opcode, "STA" ) ) show_reg = SHOW_REG_ACC;
            if( !strcmp( str_opcode, "AND" ) || !strcmp( str_opcode, "ORA" ) || !strcmp( str_opcode, "CMP" ) || !strcmp( str_opcode, "SUB" ) ) show_reg = SHOW_REG_ACC;
            if( !strcmp( str_opcode, "SBC" ) || !strcmp( str_opcode, "EOR" ) || !strcmp( str_opcode, "ADC" ) || !strcmp( str_opcode, "TAX" ) ) show_reg = SHOW_REG_ACC;

            if( !strcmp( str_opcode, "LDX" ) || !strcmp( str_opcode, "STX" ) || !strcmp( str_opcode, "INX" ) ||
                !strcmp( str_opcode, "DEX" ) || !strcmp( str_opcode, "TXA" ) ) show_reg = SHOW_REG_X;
            
            if( !strcmp( str_opcode, "LDY" ) || !strcmp( str_opcode, "STY" ) || !strcmp( str_opcode, "INY" ) || !strcmp( str_opcode, "DEY" ) ) show_reg = SHOW_REG_Y;
        }

        if( show_reg == SHOW_REG_ACC ) sprintf( reg_str, " (ACC = 0x%02x)", regs.a );
        else if( show_reg == SHOW_REG_X ) sprintf( reg_str, " (REG.X = 0x%02x)", regs.x );
        else if( show_reg == SHOW_REG_Y ) sprintf( reg_str, " (REG.Y = 0x%02x)", regs.y );

        if( ( !strcmp( str_opcode, "LDA" ) || !strcmp( str_opcode, "STA" ) ||
              !strcmp( str_opcode, "AND" ) || !strcmp( str_opcode, "ORA" ) || !strcmp( str_opcode, "CMP" ) || !strcmp( str_opcode, "SUB" ) ||
              !strcmp( str_opcode, "SBC" ) || !strcmp( str_opcode, "EOR" ) || !strcmp( str_opcode, "ADC" ) )
            && ( show_reg != SHOW_REG_NONE ) )
        {
            char reg_str2[80];
            sprintf( reg_str2, " (ACC = 0x%02x)", regs.a );
            strcat( reg_str, reg_str2 );
        }

        
        if( strlen( reg_str ) > 2 ) strcat( comment_str, reg_str );
    }
    else
    {
        strcpy( comment_str, "" );
    }

	switch( bytes )
	{
		case 1:
			sprintf( asm_code, "$%04X: %02X      ", curr_pc, opcode );
			sprintf( addr_str, addressmode[addr].format );
			break;

		case 2:
			sprintf( asm_code, "$%04X: %02X %02X   ", curr_pc, opcode, byte1 );

			if( addr == ADDR_REL )
			{
				int target_addr = ( int )curr_pc + ( char )byte1 + bytes;
				sprintf( addr_str, addressmode[addr].format, target_addr );
			}
			else
			{
				sprintf( addr_str, addressmode[addr].format, byte1 );
			}
			break;

		case 3:
			sprintf( asm_code, "$%04X: %02X %02X %02X", curr_pc, opcode, byte1, byte2 );

			{
				uint16_t val16;

				val16 = byte2;
				val16 = ( val16 << 8 ) + byte1;
				sprintf( addr_str, addressmode[addr].format, val16 );
			}
			break;
	}
    
    tab_str[0] = 0;

	sprintf( debug_temp_string, "%s %s %s %s ; %s", tab_str, asm_code, str_opcode, addr_str, comment_str );
	dump_hdl( debug_temp_string );

	return bytes;
}

