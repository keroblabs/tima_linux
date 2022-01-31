#ifndef _INSTR_CODE_H__
#define _INSTR_CODE_H__

#define INSTR_DECODE(a)		switch(a) {											 \
							case 0x00:       BRK           CYC(7)    break;      \
							case 0x01:       INDX ORA      CYC(6)    break;      \
							case 0x02:       INVALID2      CYC(2)    break;      \
							case 0x03:       INVALID1      CYC(1)    break;      \
							case 0x04: CMOS  ZPG TSB       CYC(5)    break;      \
							case 0x05:       ZPG ORA       CYC(3)    break;      \
							case 0x06:       ZPG ASL       CYC(5)    break;      \
							case 0x07: CMOS  ZPG RMB0      CYC(5)    break;      \
							case 0x08:       PHP           CYC(3)    break;      \
							case 0x09:       IMM ORA       CYC(2)    break;      \
							case 0x0A:       ASLA          CYC(2)    break;      \
							case 0x0B:       INVALID1      CYC(1)    break;      \
							case 0x0C: CMOS  AABS TSB      CYC(6)    break;      \
							case 0x0D:       AABS ORA      CYC(4)    break;      \
							case 0x0E:       AABS ASL      CYC(6)    break;      \
							case 0x0F: CMOS  ZPG BBR0      CYC(5)    break;      \
							case 0x10:       REL BPL       CYC(2)    break;      \
							case 0x11:       INDY ORA      CYC(5)    break;      \
							case 0x12: CMOS  IZPG ORA      CYC(5)    break;      \
							case 0x13:       INVALID1      CYC(1)    break;      \
							case 0x14: CMOS  ZPG TRB       CYC(5)    break;      \
							case 0x15:       ZPGX ORA      CYC(4)    break;      \
							case 0x16:       ZPGX ASL      CYC(6)    break;      \
							case 0x17: CMOS  ZPG RMB1      CYC(5)    break;      \
							case 0x18:       CLC           CYC(2)    break;      \
							case 0x19:       ABSY ORA      CYC(4)    break;      \
							case 0x1A: CMOS  INA           CYC(2)    break;      \
							case 0x1B:       INVALID1      CYC(1)    break;      \
							case 0x1C: CMOS  AABS TRB      CYC(6)    break;      \
							case 0x1D:       ABSX ORA      CYC(4)    break;      \
							case 0x1E:       ABSX ASL      CYC(6)    break;      \
							case 0x1F: CMOS  ZPG BBR1      CYC(5)    break;      \
							case 0x20:       AABS JSR      CYC(6)    break;      \
							case 0x21:       INDX AND      CYC(6)    break;      \
							case 0x22:       INVALID2      CYC(2)    break;      \
							case 0x23:       INVALID1      CYC(1)    break;      \
							case 0x24:       ZPG BIT       CYC(3)    break;      \
							case 0x25:       ZPG AND       CYC(3)    break;      \
							case 0x26:       ZPG ROL       CYC(5)    break;      \
							case 0x27: CMOS  ZPG RMB2      CYC(5)    break;      \
							case 0x28:       PLP           CYC(4)    break;      \
							case 0x29:       IMM AND       CYC(2)    break;      \
							case 0x2A:       ROLA          CYC(2)    break;      \
							case 0x2B:       INVALID1      CYC(1)    break;      \
							case 0x2C:       AABS BIT      CYC(4)    break;      \
							case 0x2D:       AABS AND      CYC(4)    break;      \
							case 0x2E:       AABS ROL      CYC(6)    break;      \
							case 0x2F: CMOS  ZPG BBR2      CYC(5)    break;      \
							case 0x30:       REL BMI       CYC(2)    break;      \
							case 0x31:       INDY AND      CYC(5)    break;      \
							case 0x32: CMOS  IZPG AND      CYC(5)    break;      \
							case 0x33:       INVALID1      CYC(1)    break;      \
							case 0x34: CMOS  ZPGX BIT      CYC(4)    break;      \
							case 0x35:       ZPGX AND      CYC(4)    break;      \
							case 0x36:       ZPGX ROL      CYC(6)    break;      \
							case 0x37: CMOS  ZPG RMB3      CYC(5)    break;      \
							case 0x38:       SEC           CYC(2)    break;      \
							case 0x39:       ABSY AND      CYC(4)    break;      \
							case 0x3A: CMOS  DEA           CYC(2)    break;      \
							case 0x3B:       INVALID1      CYC(1)    break;      \
							case 0x3C: CMOS  ABSX BIT      CYC(4)    break;      \
							case 0x3D:       ABSX AND      CYC(4)    break;      \
							case 0x3E:       ABSX ROL      CYC(6)    break;      \
							case 0x3F: CMOS  ZPG BBR3      CYC(5)    break;      \
							case 0x40:       RTI           CYC(6)    break;      \
							case 0x41:       INDX EOR      CYC(6)    break;      \
							case 0x42:       INVALID2      CYC(2)    break;      \
							case 0x43:       INVALID1      CYC(1)    break;      \
							case 0x44:       INVALID2      CYC(3)    break;      \
							case 0x45:       ZPG EOR       CYC(3)    break;      \
							case 0x46:       ZPG LSR       CYC(5)    break;      \
							case 0x47: CMOS  ZPG RMB4      CYC(5)    break;      \
							case 0x48:       PHA           CYC(3)    break;      \
							case 0x49:       IMM EOR       CYC(2)    break;      \
							case 0x4A:       LSRA          CYC(2)    break;      \
							case 0x4B:       INVALID1      CYC(1)    break;      \
							case 0x4C:       AABS JMP      CYC(3)    break;      \
							case 0x4D:       AABS EOR      CYC(4)    break;      \
							case 0x4E:       AABS LSR      CYC(6)    break;      \
							case 0x4F: CMOS  ZPG BBR4      CYC(5)    break;      \
							case 0x50:       REL BVC       CYC(2)    break;      \
							case 0x51:       INDY EOR      CYC(5)    break;      \
							case 0x52: CMOS  IZPG EOR      CYC(5)    break;      \
							case 0x53:       INVALID1      CYC(1)    break;      \
							case 0x54:       INVALID2      CYC(4)    break;      \
							case 0x55:       ZPGX EOR      CYC(4)    break;      \
							case 0x56:       ZPGX LSR      CYC(6)    break;      \
							case 0x57: CMOS  ZPG RMB5      CYC(5)    break;      \
							case 0x58:       CLI           CYC(2)    break;      \
							case 0x59:       ABSY EOR      CYC(4)    break;      \
							case 0x5A: CMOS  PHY           CYC(3)    break;      \
							case 0x5B:       INVALID1      CYC(1)    break;      \
							case 0x5C:       INVALID3      CYC(8)    break;      \
							case 0x5D:       ABSX EOR      CYC(4)    break;      \
							case 0x5E:       ABSX LSR      CYC(6)    break;      \
							case 0x5F: CMOS  ZPG BBR5      CYC(5)    break;      \
							case 0x60:       RTS           CYC(6)    break;      \
							case 0x61:       INDX ADC      CYC(6)    break;      \
							case 0x62:       INVALID2      CYC(2)    break;      \
							case 0x63:       INVALID1      CYC(1)    break;      \
							case 0x64: CMOS  ZPG STZ       CYC(3)    break;      \
							case 0x65:       ZPG ADC       CYC(3)    break;      \
							case 0x66:       ZPG ROR       CYC(5)    break;      \
							case 0x67: CMOS  ZPG RMB6      CYC(5)    break;      \
							case 0x68:       PLA           CYC(4)    break;      \
							case 0x69:       IMM ADC       CYC(2)    break;      \
							case 0x6A:       RORA          CYC(2)    break;      \
							case 0x6B:       INVALID1      CYC(1)    break;      \
							case 0x6C:       IABS JMP      CYC(6)    break;      \
							case 0x6D:       AABS ADC      CYC(4)    break;      \
							case 0x6E:       AABS ROR      CYC(6)    break;      \
							case 0x6F: CMOS  ZPG BBR6      CYC(5)    break;      \
							case 0x70:       REL BVS       CYC(2)    break;      \
							case 0x71:       INDY ADC      CYC(5)    break;      \
							case 0x72: CMOS  IZPG ADC      CYC(5)    break;      \
							case 0x73:       INVALID1      CYC(1)    break;      \
							case 0x74: CMOS  ZPGX STZ      CYC(4)    break;      \
							case 0x75:       ZPGX ADC      CYC(4)    break;      \
							case 0x76:       ZPGX ROR      CYC(6)    break;      \
							case 0x77: CMOS  ZPG RMB7      CYC(5)    break;      \
							case 0x78:       SEI           CYC(2)    break;      \
							case 0x79:       ABSY ADC      CYC(4)    break;      \
							case 0x7A: CMOS  PLY           CYC(4)    break;      \
							case 0x7B:       INVALID1      CYC(1)    break;      \
							case 0x7C: CMOS  ABSIINDX JMP  CYC(6)    break;      \
							case 0x7D:       ABSX ADC      CYC(4)    break;      \
							case 0x7E:       ABSX ROR      CYC(6)    break;      \
							case 0x7F: CMOS  ZPG BBR7      CYC(5)    break;      \
							case 0x80: CMOS  REL BRA       CYC(3)    break;      \
							case 0x81:       INDX STA      CYC(6)    break;      \
							case 0x82:       INVALID2      CYC(2)    break;      \
							case 0x83:       INVALID1      CYC(1)    break;      \
							case 0x84:       ZPG STY       CYC(3)    break;      \
							case 0x85:       ZPG STA       CYC(3)    break;      \
							case 0x86:       ZPG STX       CYC(3)    break;      \
							case 0x87: CMOS  ZPG SMB0      CYC(5)    break;      \
							case 0x88:       DEY           CYC(2)    break;      \
							case 0x89: CMOS  IMM BITI      CYC(2)    break;      \
							case 0x8A:       TXA           CYC(2)    break;      \
							case 0x8B:       INVALID1      CYC(1)    break;      \
							case 0x8C:       AABS STY      CYC(4)    break;      \
							case 0x8D:       AABS STA      CYC(4)    break;      \
							case 0x8E:       AABS STX      CYC(4)    break;      \
							case 0x8F: CMOS  ZPG BBS0      CYC(5)    break;      \
							case 0x90:       REL BCC       CYC(2)    break;      \
							case 0x91:       INDY STA      CYC(6)    break;      \
							case 0x92: CMOS  IZPG STA      CYC(5)    break;      \
							case 0x93:       INVALID1      CYC(1)    break;      \
							case 0x94:       ZPGX STY      CYC(4)    break;      \
							case 0x95:       ZPGX STA      CYC(4)    break;      \
							case 0x96:       ZPGY STX      CYC(4)    break;      \
							case 0x97: CMOS  ZPG SMB1      CYC(5)    break;      \
							case 0x98:       TYA           CYC(2)    break;      \
							case 0x99:       ABSY STA      CYC(5)    break;      \
							case 0x9A:       TXS           CYC(2)    break;      \
							case 0x9B:       INVALID1      CYC(1)    break;      \
							case 0x9C: CMOS  AABS STZ      CYC(4)    break;      \
							case 0x9D:       ABSX STA      CYC(5)    break;      \
							case 0x9E: CMOS  ABSX STZ      CYC(5)    break;      \
							case 0x9F: CMOS  ZPG BBS1      CYC(5)    break;      \
							case 0xA0:       IMM LDY       CYC(2)    break;      \
							case 0xA1:       INDX LDA      CYC(6)    break;      \
							case 0xA2:       IMM LDX       CYC(2)    break;      \
							case 0xA3:       INVALID1      CYC(1)    break;      \
							case 0xA4:       ZPG LDY       CYC(3)    break;      \
							case 0xA5:       ZPG LDA       CYC(3)    break;      \
							case 0xA6:       ZPG LDX       CYC(3)    break;      \
							case 0xA7: CMOS  ZPG SMB2      CYC(5)    break;      \
							case 0xA8:       TAY           CYC(2)    break;      \
							case 0xA9:       IMM LDA       CYC(2)    break;      \
							case 0xAA:       TAX           CYC(2)    break;      \
							case 0xAB:       INVALID1      CYC(1)    break;      \
							case 0xAC:       AABS LDY      CYC(4)    break;      \
							case 0xAD:       AABS LDA      CYC(4)    break;      \
							case 0xAE:       AABS LDX      CYC(4)    break;      \
							case 0xAF: CMOS  ZPG BBS2      CYC(5)    break;      \
							case 0xB0:       REL BCS       CYC(2)    break;      \
							case 0xB1:       INDY LDA      CYC(5)    break;      \
							case 0xB2: CMOS  IZPG LDA      CYC(5)    break;      \
							case 0xB3:       INVALID1      CYC(1)    break;      \
							case 0xB4:       ZPGX LDY      CYC(4)    break;      \
							case 0xB5:       ZPGX LDA      CYC(4)    break;      \
							case 0xB6:       ZPGY LDX      CYC(4)    break;      \
							case 0xB7: CMOS  ZPG SMB3      CYC(5)    break;      \
							case 0xB8:       CLV           CYC(2)    break;      \
							case 0xB9:       ABSY LDA      CYC(4)    break;      \
							case 0xBA:       TSX           CYC(2)    break;      \
							case 0xBB:       INVALID1      CYC(1)    break;      \
							case 0xBC:       ABSX LDY      CYC(4)    break;      \
							case 0xBD:       ABSX LDA      CYC(4)    break;      \
							case 0xBE:       ABSY LDX      CYC(4)    break;      \
							case 0xBF: CMOS  ZPG BBS3      CYC(5)    break;      \
							case 0xC0:       IMM CPY       CYC(2)    break;      \
							case 0xC1:       INDX CMP      CYC(6)    break;      \
							case 0xC2:       INVALID2      CYC(2)    break;      \
							case 0xC3:       INVALID1      CYC(1)    break;      \
							case 0xC4:       ZPG CPY       CYC(3)    break;      \
							case 0xC5:       ZPG CMP       CYC(3)    break;      \
							case 0xC6:       ZPG DEC       CYC(5)    break;      \
							case 0xC7: CMOS  ZPG SMB4      CYC(5)    break;      \
							case 0xC8:       INY           CYC(2)    break;      \
							case 0xC9:       IMM CMP       CYC(2)    break;      \
							case 0xCA:       DEX           CYC(2)    break;      \
							case 0xCB: CMOS  WAI           CYC(3)    break;      \
							case 0xCC:       AABS CPY      CYC(4)    break;      \
							case 0xCD:       AABS CMP      CYC(4)    break;      \
							case 0xCE:       AABS DEC      CYC(6)    break;      \
							case 0xCF: CMOS  ZPG BBS4      CYC(5)    break;      \
							case 0xD0:       REL BNE       CYC(2)    break;      \
							case 0xD1:       INDY CMP      CYC(5)    break;      \
							case 0xD2: CMOS  IZPG CMP      CYC(5)    break;      \
							case 0xD3:       INVALID1      CYC(1)    break;      \
							case 0xD4:       INVALID2      CYC(4)    break;      \
							case 0xD5:       ZPGX CMP      CYC(4)    break;      \
							case 0xD6:       ZPGX DEC      CYC(6)    break;      \
							case 0xD7: CMOS  ZPG SMB5      CYC(5)    break;      \
							case 0xD8:       CLD           CYC(2)    break;      \
							case 0xD9:       ABSY CMP      CYC(4)    break;      \
							case 0xDA: CMOS  PHX           CYC(3)    break;      \
							case 0xDB: CMOS  STP           CYC(3)    break;      \
							case 0xDC:       INVALID3      CYC(4)    break;      \
							case 0xDD:       ABSX CMP      CYC(4)    break;      \
							case 0xDE:       ABSX DEC      CYC(6)    break;      \
							case 0xDF: CMOS  ZPG BBS5      CYC(5)    break;      \
							case 0xE0:       IMM CPX       CYC(2)    break;      \
							case 0xE1:       INDX SBC      CYC(6)    break;      \
							case 0xE2:       INVALID2      CYC(2)    break;      \
							case 0xE3:       INVALID1      CYC(1)    break;      \
							case 0xE4:       ZPG CPX       CYC(3)    break;      \
							case 0xE5:       ZPG SBC       CYC(3)    break;      \
							case 0xE6:       ZPG INC       CYC(5)    break;      \
							case 0xE7: CMOS  ZPG SMB6      CYC(5)    break;      \
							case 0xE8:       INX           CYC(2)    break;      \
							case 0xE9:       IMM SBC       CYC(2)    break;      \
							case 0xEA:       NOP           CYC(2)    break;      \
							case 0xEB:       INVALID1      CYC(1)    break;      \
							case 0xEC:       AABS CPX      CYC(4)    break;      \
							case 0xED:       AABS SBC      CYC(4)    break;      \
							case 0xEE:       AABS INC      CYC(6)    break;      \
							case 0xEF: CMOS  ZPG BBS6      CYC(5)    break;      \
							case 0xF0:       REL BEQ       CYC(2)    break;      \
							case 0xF1:       INDY SBC      CYC(5)    break;      \
							case 0xF2: CMOS  IZPG SBC      CYC(5)    break;      \
							case 0xF3:       INVALID1      CYC(1)    break;      \
							case 0xF4:       INVALID2      CYC(4)    break;      \
							case 0xF5:       ZPGX SBC      CYC(4)    break;      \
							case 0xF6:       ZPGX INC      CYC(6)    break;      \
							case 0xF7: CMOS  ZPG SMB7      CYC(5)    break;      \
							case 0xF8:       SED           CYC(2)    break;      \
							case 0xF9:       ABSY SBC      CYC(4)    break;      \
							case 0xFA: CMOS  PLX           CYC(4)    break;      \
							case 0xFB:       INVALID1      CYC(1)    break;      \
							case 0xFC:       INVALID3      CYC(4)    break;      \
							case 0xFD:       ABSX SBC      CYC(4)    break;      \
							case 0xFE:       ABSX INC      CYC(6)    break;      \
							case 0xFF: CMOS  ZPG BBS7      CYC(5)    break;  }

#endif
