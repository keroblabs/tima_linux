#ifndef _INSTR_DEF_H__
#define _INSTR_DEF_H__


/****************************************************************************
*
*  GENERAL PURPOSE MACROS
*
***/

#define AF_TO_EF  	flagc = ( regs.ps & AF_CARRY);                          \
                  	flagn = ( regs.ps & AF_SIGN);                           \
                  	flagv = ( regs.ps & AF_OVERFLOW);                       \
                  	flagz = ( regs.ps & AF_ZERO)
#define EF_TO_AF  	regs.ps = ( regs.ps & ~( AF_CARRY | AF_SIGN |           \
                                         	 AF_OVERFLOW | AF_ZERO) )       \
                              | (flagc ? AF_CARRY    : 0 )                  \
                              | (flagn ? AF_SIGN     : 0 )                  \
                              | (flagv ? AF_OVERFLOW : 0 )                  \
                              | (flagz ? AF_ZERO     : 0 )
#define CMOS      	{ }
#define CYC(a)   	cycles += a;
#define POP      	cpu_read_8( ( regs.sp >= 0x01FF ) ? ( regs.sp = 0x100 ) : ++regs.sp )
#define PUSH(a)  	cpu_write_8( regs.sp--, (a) );                            \
                 	if( regs.sp < 0x100 ) regs.sp = 0x1FF;
					
#define READ_     	( ( ( addr & 0xFF00 ) == 0xC000 ) ? 					\
						ioread[ addr & 0xFF ]( ( uint8_t )( addr & 0xff ), 0 ) \
						: cpu_read_8( addr ) )

#define READ		cpu_read_8( addr )
						
#define SETNZ(a) {                                                          \
                   flagn = ((a) & 0x80);                                    \
                   flagz = !(a & 0xFF);                                     \
                 }
#define SETZ(a)  flagz = !(a & 0xFF);
#define TOBCD(a) (((((a)/10) % 10) << 4) | ((a) % 10))
#define TOBIN(a) (((a) >> 4)*10 + ((a) & 0x0F))

#define WRITE_(a) { if ((addr) < 0xC000)                          			\
                     cpu_write_8(addr,(a));                               	\
                   else if ((addr & 0xFF00) == 0xC000)           			\
                     iowrite[addr & 0xFF]((uint8_t)(addr & 0xff),(uint8_t)(a));   \
                 }

#define WRITE(a) cpu_write_8( addr, a );

#define IRQ  {       PUSH(regs.pc >> 8)                                     \
                     PUSH(regs.pc & 0xFF)                                   \
                     SEI                                                    \
			         EF_TO_AF;      										\
			   		 regs.ps &= ~AF_BREAK;                                  \
                     PUSH(regs.ps)                                          \
					 regs.ps |= AF_BREAK;                                   \
  			         regs.pc = cpu_read_16(0xFFFE); CYC(7)                	\
			 }

#define NMI  {   PUSH(regs.pc >> 8)                                         \
                 PUSH(regs.pc & 0xFF)                                       \
				 SEI                                                		\
				 EF_TO_AF;                                           		\
                 PUSH(regs.ps)                                              \
				 regs.pc = cpu_read_16(0xFFFA);                   			\
				 CYC(7)						  	 			                \
			 }

/****************************************************************************
*
*  ADDRESSING MODE MACROS
*
***/


// BUG REPORT!!! IND ZP when set to $FF will get hi byte from $0100 vs. $0000 !!!!

#define AABS     addr = cpu_read_16( regs.pc );  regs.pc += 2;
#define ABSIINDX addr = cpu_read_16( cpu_read_16( regs.pc ) + ( uint16_t )regs.x );  regs.pc += 2;
#define ABSX     addr = cpu_read_16( regs.pc ) + ( uint16_t )regs.x;  regs.pc += 2;
#define ABSY     addr = cpu_read_16( regs.pc ) + ( uint16_t )regs.y;  regs.pc += 2;
#define IABS     addr = cpu_read_16( cpu_read_16( regs.pc ) );  regs.pc += 2;
#define ACC      { }
#define IMM      addr = regs.pc++;
#define IMPLIED  { }
#define REL      addr = ( signed char )cpu_read_8( regs.pc++ );
#define STACK    { }
#define ZPG      addr = ( uint16_t )cpu_read_8( regs.pc++ );
#define INDX     addr = cpu_read_16( ( cpu_read_8( regs.pc++ ) + regs.x ) & 0xFF);
#define ZPGX     addr = ( uint16_t )( cpu_read_8( regs.pc++ ) + regs.x ) & 0xFF;
#define ZPGY     addr = ( uint16_t )( cpu_read_8( regs.pc++ ) + regs.y ) & 0xFF;
// #define IZPG     addr = *(LPWORD)(mem+*(mem+regs.pc++));
#define INDY     addr = ( cpu_read_16( ( uint16_t )cpu_read_8( regs.pc++ ) ) ) + ( uint16_t )regs.y;

#define IZPG     if( cpu_read_8( regs.pc ) == 0xFF ) {									\
					addr = ( uint16_t )cpu_read_8( 0xFF ) + ( ( uint16_t )cpu_read_8( 0 ) * 256 ); 	\
					regs.pc++;															\
					}																	\
				 else																	\
	  				addr = cpu_read_16( ( uint16_t )cpu_read_8( regs.pc++ ) );



/****************************************************************************
*
*  INSTRUCTION MACROS
*
***/

#define ADC      temp = READ;                                               \
                 if (regs.ps & AF_DECIMAL) {                                \
                   val    = TOBIN(regs.a)+TOBIN(temp)+(flagc != 0);         \
                   flagc  = (val > 99);                                     \
                   regs.a = TOBCD(val); CYC(1)                              \
                   SETNZ(regs.a);         /* check */                       \
                 }                                                          \
                 else {                                                     \
                   val    = regs.a+temp+(flagc != 0);                       \
                   flagc  = (val > 0xFF);                                   \
                   flagv  = (((regs.a & 0x80) == (temp & 0x80)) &&          \
                             ((regs.a & 0x80) != (val & 0x80)));            \
                   regs.a = val & 0xFF;                                     \
                   SETNZ(regs.a);                                           \
                 }
#define AND      regs.a &= READ;                                            \
                 SETNZ(regs.a)
#define ASL      val   = READ << 1;                                         \
                 flagc = (val > 0xFF);                                      \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define ASLA     val   = regs.a << 1;                                       \
                 flagc = (val > 0xFF);                                      \
                 SETNZ(val)                                                 \
                 regs.a = (uint8_t)val;
#define BBR0     val = READ & 0x01; REL                                     \
                 if (!val) { regs.pc += addr; CYC(1) }
#define BBR1     val = READ & 0x02; REL                                     \
                 if (!val) { regs.pc += addr; CYC(1) }
#define BBR2     val = READ & 0x04; REL                                     \
                 if (!val) { regs.pc += addr; CYC(1) }
#define BBR3     val = READ & 0x08; REL                                     \
                 if (!val) { regs.pc += addr; CYC(1) }
#define BBR4     val = READ & 0x10; REL                                     \
                 if (!val) { regs.pc += addr; CYC(1) }
#define BBR5     val = READ & 0x20; REL                                     \
                 if (!val) { regs.pc += addr; CYC(1) }
#define BBR6     val = READ & 0x40; REL                                     \
                 if (!val) { regs.pc += addr; CYC(1) }
#define BBR7     val = READ & 0x80; REL                                     \
                 if (!val) { regs.pc += addr; CYC(1) }
#define BBS0     val = READ & 0x01; REL                                     \
                 if (val) { regs.pc += addr; CYC(1) }
#define BBS1     val = READ & 0x02; REL                                     \
                 if (val) { regs.pc += addr; CYC(1) }
#define BBS2     val = READ & 0x04; REL                                     \
                 if (val) { regs.pc += addr; CYC(1) }
#define BBS3     val = READ & 0x08; REL                                     \
                 if (val) { regs.pc += addr; CYC(1) }
#define BBS4     val = READ & 0x10; REL                                     \
                 if (val) { regs.pc += addr; CYC(1) }
#define BBS5     val = READ & 0x20; REL                                     \
                 if (val) { regs.pc += addr; CYC(1) }
#define BBS6     val = READ & 0x40; REL                                     \
                 if (val) { regs.pc += addr; CYC(1) }
#define BBS7     val = READ & 0x80; REL                                     \
                 if (val) { regs.pc += addr; CYC(1) }
#define BCC      if (!flagc) { regs.pc += addr; CYC(1) }
#define BCS      if ( flagc) { regs.pc += addr; CYC(1) }
#define BEQ      if ( flagz) { regs.pc += addr; CYC(1) }
#define BIT      val   = READ;                                              \
                 flagz = !(regs.a & val);                                   \
                 flagn = val & 0x80;                                        \
                 flagv = val & 0x40;
#define BITI     flagz = !(regs.a & READ);
#define BMI      if ( flagn) { regs.pc += addr; CYC(1) }
#define BNE      if (!flagz) { regs.pc += addr; CYC(1) }
#define BPL      if (!flagn) { regs.pc += addr; CYC(1) }
#define BRA      regs.pc += addr;
#define BRK      PUSH(++regs.pc >> 8)                                       \
                 PUSH(regs.pc & 0xFF)                                       \
                 EF_TO_AF;                                                  \
                 regs.ps |= AF_BREAK;                                       \
                 PUSH(regs.ps)                                              \
                 regs.ps |= AF_INTERRUPT;                                   \
                 regs.pc = cpu_read_16(0xFFFE);
#define BVC      if (!flagv) { regs.pc += addr; CYC(1) }
#define BVS      if ( flagv) { regs.pc += addr; CYC(1) }
#define CLC      flagc = 0;
#define CLD      regs.ps &= ~AF_DECIMAL;
#define CLI      regs.ps &= ~AF_INTERRUPT;
#define CLV      flagv = 0;
#define CMP      val   = READ;                                              \
                 flagc = (regs.a >= val);                                   \
                 val   = regs.a-val;                                        \
                 SETNZ(val)
#define CPX      val   = READ;                                              \
                 flagc = (regs.x >= val);                                   \
                 val   = regs.x-val;                                        \
                 SETNZ(val)
#define CPY      val   = READ;                                              \
                 flagc = (regs.y >= val);                                   \
                 val   = regs.y-val;                                        \
                 SETNZ(val)
#define DEA      --regs.a;                                                  \
                 SETNZ(regs.a)
#define DEC      val = READ-1;                                              \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define DEX      --regs.x;                                                  \
                 SETNZ(regs.x)
#define DEY      --regs.y;                                                  \
                 SETNZ(regs.y)
#define EOR      regs.a ^= READ;                                            \
                 SETNZ(regs.a)
#define INA      ++regs.a;                                                  \
                 SETNZ(regs.a)
#define INC      val = READ+1;                                              \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define INX      ++regs.x;                                                  \
                 SETNZ(regs.x)
#define INY      ++regs.y;                                                  \
                 SETNZ(regs.y)
#define JMP      regs.pc = addr;
#define JSR      if(addr != 0xFFFF) {                                        \
                     --regs.pc;                                             \
                     PUSH(regs.pc >> 8)                                     \
                     PUSH(regs.pc & 0xFF)                                   \
                     prev_pc = regs.pc = addr;                              \
                 } else {                                                   \
                     p_co_proc(regs.pc);                                    \
                     regs.pc += cpu_read_8( regs.pc + 1 ) + 2; }
#define LDA      regs.a = READ;                                             \
                 SETNZ(regs.a)
#define LDX      regs.x = READ;                                             \
                 SETNZ(regs.x)
#define LDY      regs.y = READ;                                             \
                 SETNZ(regs.y)
#define LSR      val   = READ;                                              \
                 flagc = (val & 1);                                         \
                 flagn = 0;                                                 \
                 val >>= 1;                                                 \
                 SETZ(val)                                                  \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define LSRA     flagc = (regs.a & 1);                                      \
                 flagn = 0;                                                 \
                 regs.a >>= 1;                                              \
                 SETZ(regs.a)
#define NOP      { }
#define ORA      regs.a |= READ;                                            \
                 SETNZ(regs.a)
#define PHA      PUSH(regs.a)
#define PHP      EF_TO_AF;                                                   \
                 regs.ps |= AF_RESERVED;                                    \
                 PUSH(regs.ps)
#define PHX      PUSH(regs.x)
#define PHY      PUSH(regs.y)
#define PLA      regs.a = POP;                                              \
                 SETNZ(regs.a)
#define PLP      regs.ps = POP;                                             \
				 regs.ps |= AF_BREAK;										\
                 AF_TO_EF;
#define PLX      regs.x = POP;                                              \
                 SETNZ(regs.x)
#define PLY      regs.y = POP;                                              \
                 SETNZ(regs.y)
#define RMB0     val = READ & 0xFE;                                         \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define RMB1     val = READ & 0xFD;                                         \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define RMB2     val = READ & 0xFB;                                         \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define RMB3     val = READ & 0xF7;                                         \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define RMB4     val = READ & 0xEF;                                         \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define RMB5     val = READ & 0xDF;                                         \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define RMB6     val = READ & 0xBF;                                         \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define RMB7     val = READ & 0x7F;                                         \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define ROL      val   = (READ << 1) | (flagc != 0);                        \
                 flagc = (val > 0xFF);                                      \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define ROLA     val    = (((uint16_t)regs.a) << 1) | (flagc != 0);         \
                 flagc  = (val > 0xFF);                                     \
                 regs.a = val & 0xFF;                                       \
                 SETNZ(regs.a);
#define ROR      temp  = READ;                                              \
                 val   = (temp >> 1) | (flagc ? 0x80 : 0);                  \
                 flagc = temp & 1;                                          \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define RORA     val    = (((uint16_t)regs.a) >> 1) | (flagc ? 0x80 : 0);   \
                 flagc  = regs.a & 1;                                       \
                 regs.a = val & 0xFF;                                       \
                 SETNZ(regs.a)
#define RTI      regs.ps = POP;                                             \
				 regs.ps |= AF_BREAK;										\
	             CLI														\
	             regs.irq = IRQ_STATE_NONE;                                 \
				 AF_TO_EF;                                                  \
                 regs.pc = POP;												\
                 regs.pc |= (((uint16_t)POP) << 8);
#define RTS      regs.pc = POP;                                             \
                 regs.pc |= (((uint16_t)POP) << 8);                         \
                 ++regs.pc;
#define SBC      temp = READ;                                               \
                 if (regs.ps & AF_DECIMAL) {                                \
                   val    = TOBIN(regs.a)-TOBIN(temp)-!flagc;               \
                   flagc  = (val < 0x8000);                                 \
                   regs.a = TOBCD(val);                                     \
				   SETNZ(regs.a); CYC(1) /* check*/                 		\
                 }                                                          \
                 else {                                                     \
                   val    = regs.a-temp-!flagc;                             \
                   flagc  = (val < 0x8000);                                 \
                   flagv  = (((regs.a & 0x80) != (temp & 0x80)) &&          \
                             ((regs.a & 0x80) != (val & 0x80)));            \
                   regs.a = val & 0xFF;                                     \
                   SETNZ(regs.a);                                           \
                 }
#define SEC      flagc = 1;
#define SED      regs.ps |= AF_DECIMAL;
#define SEI      regs.ps |= AF_INTERRUPT;
#define SMB0     val = READ | 0x01;                                         \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define SMB1     val = READ | 0x02;                                         \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define SMB2     val = READ | 0x04;                                         \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define SMB3     val = READ | 0x08;                                         \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define SMB4     val = READ | 0x10;                                         \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define SMB5     val = READ | 0x20;                                         \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define SMB6     val = READ | 0x40;                                         \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define SMB7     val = READ | 0x80;                                         \
                 SETNZ(val)                                                 \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define STA      WRITE(regs.a)
#define STP      regs.pc--; regs.stp=1;
#define STX      WRITE(regs.x)
#define STY      WRITE(regs.y)
#define STZ      WRITE(0)
#define TAX      regs.x = regs.a;                                           \
                 SETNZ(regs.x)
#define TAY      regs.y = regs.a;                                           \
                 SETNZ(regs.y)
#define TRB      val   = READ;                                              \
                 flagz = !(regs.a & val);                                   \
                 val  &= ~regs.a;                                           \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define TSB      val   = READ;                                              \
                 flagz = !(regs.a & val);                                   \
                 val   |= regs.a;                                           \
                 WRITE( ( uint8_t )( val & 0x0FF ) )
#define TSX      regs.x = regs.sp & 0xFF;                                   \
                 SETNZ(regs.x)
#define TXA      regs.a = regs.x;                                           \
                 SETNZ(regs.a)
#define TXS      regs.sp = 0x100 | regs.x;
#define TYA      regs.a = regs.y;                                           \
                 SETNZ(regs.a)
#define WAI      regs.pc--; regs.wai = 1;
#define INVALID1 { }
#define INVALID2 ++regs.pc;
#define INVALID3 regs.pc += 2;

#endif
