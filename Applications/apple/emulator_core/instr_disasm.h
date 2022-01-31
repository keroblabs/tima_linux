#ifndef _INSTR_DISASM_H__
#define _INSTR_DISASM_H__

/****************************************************************************
*
*  ADDRESSING MODE MACROS
*
***/

#define AABS     addr_id = ADDR_ABS;   comment_addr = cpu_read_16( curr_pc + 1 );
#define ABSIINDX addr_id = ADDR_INDX;  comment_addr = cpu_read_16( cpu_read_16( curr_pc + 1 ) + ( uint16_t )regs.x );
#define ABSX     addr_id = ADDR_ABSX;  comment_addr = cpu_read_16( curr_pc + 1 ) + ( uint16_t )regs.x;
#define ABSY     addr_id = ADDR_ABSY;  comment_addr = cpu_read_16( curr_pc + 1 ) + ( uint16_t )regs.y;
#define IABS     addr_id = ADDR_IABS;  comment_addr = cpu_read_16( cpu_read_16( curr_pc + 1 ) );
#define ACC      addr_id = ADDR_IMM;
#define IMM      addr_id = ADDR_IMM;   comment_addr = curr_pc + 1;
#define IMPLIED  addr_id = ADDR_IMM;
#define REL      addr_id = ADDR_REL;   comment_addr = ( signed char )cpu_read_8( curr_pc + 1 ) + curr_pc;
#define STACK    addr_id = ADDR_IMM;
#define ZPG      addr_id = ADDR_ZPG;   comment_addr = ( uint16_t )cpu_read_8( curr_pc + 1 );
#define INDX     addr_id = ADDR_INDX;  comment_addr = cpu_read_16( ( cpu_read_8( curr_pc + 1 ) + regs.x ) & 0xFF);
#define ZPGX     addr_id = ADDR_ZPGX;  comment_addr = ( uint16_t )( cpu_read_8( curr_pc + 1 ) + regs.x ) & 0xFF;
#define ZPGY     addr_id = ADDR_ZPGY;  comment_addr = ( uint16_t )( cpu_read_8( curr_pc + 1 ) + regs.y ) & 0xFF;
#define INDY     addr_id = ADDR_INDY;  comment_addr = ( cpu_read_16( ( uint16_t )cpu_read_8( curr_pc + 1 ) ) ) + ( uint16_t )regs.y;
#define IZPG     addr_id = ADDR_IZPG;  if( cpu_read_8( curr_pc + 1 ) == 0xFF ) {                                                            \
                                            comment_addr = ( uint16_t )cpu_read_8( 0xFF ) + ( ( uint16_t )cpu_read_8( 0 ) * 256 );      \
                                            }                                                                                           \
                                        else                                                                                            \
                                            comment_addr = cpu_read_16( ( uint16_t )cpu_read_8( curr_pc + 1 ) );


#define CYC(a)
#define CMOS


/****************************************************************************
*
*  INSTRUCTION MACROS
*
***/

#define ADC      strcpy( str_opcode, "ADC" );
#define AND      strcpy( str_opcode, "AND" );
#define ASL      strcpy( str_opcode, "ASL" );
#define ASLA     strcpy( str_opcode, "ASL" );
#define BBR0     strcpy( str_opcode, "BR0" );
#define BBR1     strcpy( str_opcode, "BR1" );
#define BBR2     strcpy( str_opcode, "BR2" );
#define BBR3     strcpy( str_opcode, "BR3" );
#define BBR4     strcpy( str_opcode, "BR4" );
#define BBR5     strcpy( str_opcode, "BR5" );
#define BBR6     strcpy( str_opcode, "BR6" );
#define BBR7     strcpy( str_opcode, "BR7" );
#define BBS0     strcpy( str_opcode, "BS0" );
#define BBS1     strcpy( str_opcode, "BS1" );
#define BBS2     strcpy( str_opcode, "BS2" );
#define BBS3     strcpy( str_opcode, "BS3" );
#define BBS4     strcpy( str_opcode, "BS4" );
#define BBS5     strcpy( str_opcode, "BS5" );
#define BBS6     strcpy( str_opcode, "BS6" );
#define BBS7     strcpy( str_opcode, "BS7" );
#define BCC      strcpy( str_opcode, "BCC" );
#define BCS      strcpy( str_opcode, "BCS" );
#define BEQ      strcpy( str_opcode, "BEQ" );
#define BIT      strcpy( str_opcode, "BIT" );
#define BITI     strcpy( str_opcode, "BIT" );
#define BMI      strcpy( str_opcode, "BMI" );
#define BNE      strcpy( str_opcode, "BNE" );
#define BPL      strcpy( str_opcode, "BPL" );
#define BRA      strcpy( str_opcode, "BRA" );
#define BRK      strcpy( str_opcode, "BRK" );
#define BVC      strcpy( str_opcode, "BVC" );
#define BVS      strcpy( str_opcode, "BVS" );
#define CLC      strcpy( str_opcode, "CLC" );
#define CLD      strcpy( str_opcode, "CLD" );
#define CLI      strcpy( str_opcode, "CLI" );
#define CLV      strcpy( str_opcode, "CLV" );
#define CMP      strcpy( str_opcode, "CMP" );
#define CPX      strcpy( str_opcode, "CPX" );
#define CPY      strcpy( str_opcode, "CPY" );
#define DEA      strcpy( str_opcode, "DEA" );
#define DEC      strcpy( str_opcode, "DEC" );
#define DEX      strcpy( str_opcode, "DEX" );
#define DEY      strcpy( str_opcode, "DEY" );
#define EOR      strcpy( str_opcode, "EOR" );
#define INA      strcpy( str_opcode, "INA" );
#define INC      strcpy( str_opcode, "INC" );
#define INX      strcpy( str_opcode, "INX" );
#define INY      strcpy( str_opcode, "INY" );
#define JMP      strcpy( str_opcode, "JMP" );
#define JSR      strcpy( str_opcode, "JSR" );
#define LDA      strcpy( str_opcode, "LDA" );
#define LDX      strcpy( str_opcode, "LDX" );
#define LDY      strcpy( str_opcode, "LDY" );
#define LSR      strcpy( str_opcode, "LSR" );
#define LSRA     strcpy( str_opcode, "LSR" );
#define NOP      strcpy( str_opcode, "NOP" );
#define ORA      strcpy( str_opcode, "ORA" );
#define PHA      strcpy( str_opcode, "PHA" );
#define PHP      strcpy( str_opcode, "PHP" );
#define PHX      strcpy( str_opcode, "PHX" );
#define PHY      strcpy( str_opcode, "PHY" );
#define PLA      strcpy( str_opcode, "PLA" );
#define PLP      strcpy( str_opcode, "PLP" );
#define PLX      strcpy( str_opcode, "PLX" );
#define PLY      strcpy( str_opcode, "PLY" );
#define RMB0     strcpy( str_opcode, "RB0" );
#define RMB1     strcpy( str_opcode, "RB1" );
#define RMB2     strcpy( str_opcode, "RB2" );
#define RMB3     strcpy( str_opcode, "RB3" );
#define RMB4     strcpy( str_opcode, "RB4" );
#define RMB5     strcpy( str_opcode, "RB5" );
#define RMB6     strcpy( str_opcode, "RB6" );
#define RMB7     strcpy( str_opcode, "RB7" );
#define ROL      strcpy( str_opcode, "ROL" );
#define ROLA     strcpy( str_opcode, "ROL" );
#define ROR      strcpy( str_opcode, "ROR" );
#define RORA     strcpy( str_opcode, "ROR" );
#define RTI      strcpy( str_opcode, "RTI" );
#define RTS      strcpy( str_opcode, "RTS" );
#define SBC      strcpy( str_opcode, "SBC" );
#define SEC      strcpy( str_opcode, "SEC" );
#define SED      strcpy( str_opcode, "SED" );
#define SEI      strcpy( str_opcode, "SEI" );
#define SMB0     strcpy( str_opcode, "SB0" );
#define SMB1     strcpy( str_opcode, "SB1" );
#define SMB2     strcpy( str_opcode, "SB2" );
#define SMB3     strcpy( str_opcode, "SB3" );
#define SMB4     strcpy( str_opcode, "SB4" );
#define SMB5     strcpy( str_opcode, "SB5" );
#define SMB6     strcpy( str_opcode, "SB6" );
#define SMB7     strcpy( str_opcode, "SB7" );
#define STA      strcpy( str_opcode, "STA" );
#define STP      strcpy( str_opcode, "STP" );
#define STX      strcpy( str_opcode, "STX" );
#define STY      strcpy( str_opcode, "STY" );
#define STZ      strcpy( str_opcode, "STZ" );
#define TAX      strcpy( str_opcode, "TAX" );
#define TAY      strcpy( str_opcode, "TAY" );
#define TRB      strcpy( str_opcode, "TRB" );
#define TSB      strcpy( str_opcode, "TSB" );
#define TSX      strcpy( str_opcode, "TSX" );
#define TXA      strcpy( str_opcode, "TXA" );
#define TXS      strcpy( str_opcode, "TXS" );
#define TYA      strcpy( str_opcode, "TYA" );
#define WAI      strcpy( str_opcode, "WAI" );
#define INVALID1 strcpy( str_opcode, "NOP" ); addr_id = ADDR_INVALID1;
#define INVALID2 strcpy( str_opcode, "NOP" ); addr_id = ADDR_INVALID1;
#define INVALID3 strcpy( str_opcode, "NOP" ); addr_id = ADDR_INVALID1;


#endif
