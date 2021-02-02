/* Copyright (C) 2003 Jean-Marc Valin */
/**
   @file fixed_generic.h
   @brief Generic fixed-point operations
*/
/*
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:
   
   - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
   
   - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
   
   - Neither the name of the Xiph.org Foundation nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.
   
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

long __divsi3_c (long numerator, long denominator);

#ifndef FIXED_GENERIC_H
#define FIXED_GENERIC_H

#define QCONST16(x,bits) ((spx_word16_t)(.5+(x)*(((spx_word32_t)1)<<(bits))))
#define QCONST32(x,bits) ((spx_word32_t)(.5+(x)*(((spx_word32_t)1)<<(bits))))

#define NEG16(x) (-(x))
#define NEG32(x) (-(x))
#define EXTRACT16(x) ((spx_word16_t)(x))
#define EXTEND32(x) ((spx_word32_t)(x))
#define SHR16(a,shift) ((a) >> (shift))
#define SHL16(a,shift) ((a) << (shift))
#define SHR32(a,shift) ((a) >> (shift))
#define SHL32(a,shift) ((a) << (shift))
#define PSHR16(a,shift) (SHR16((a)+((         1 <<((shift))>>1)),shift))
#define PSHR32(a,shift) (SHR32((a)+((EXTEND32(1)<<((shift))>>1)),shift))
#define PSHR(a,shift)   (SHR  ((a)+((EXTEND32(1)<<((shift))>>1)),shift))
#define VSHR32(a, shift) (((shift)>0) ? SHR32(a, shift) : SHL32(a, -(shift)))
#define SATURATE16(x,a) (((x)>(a) ? (a) : (x)<-(a) ? -(a) : (x)))
#define SATURATE32(x,a) (((x)>(a) ? (a) : (x)<-(a) ? -(a) : (x)))

#define SHR(a,shift) (              (a) >> (shift))
#define SHL(a,shift) ((spx_word32_t)(a) << (shift))
#define SATURATE(x,a) (((x)>(a) ? (a) : (x)<-(a) ? -(a) : (x)))

//#define ADD16(a,b) ((spx_word16_t)((spx_word16_t)(a)+(spx_word16_t)(b)))
//#define SUB16(a,b) ((spx_word16_t)(a)-(spx_word16_t)(b))
//#define ADD32(a,b) ((spx_word32_t)(a)+(spx_word32_t)(b))
//#define SUB32(a,b) ((spx_word32_t)(a)-(spx_word32_t)(b))

#define ADD16(a,b) (a+b)
#define SUB16(a,b) (a-b)
#define ADD32(a,b) (a+b)
#define SUB32(a,b) (a-b)


/* result fits in 16 bits */
// #define MULT16_16_16(a,b)     ((((spx_word16_t)(a))*((spx_word16_t)(b)))) // asm: arm
#define MULT16_16_16(a,b)     (a*b) // asm: arm

/* (spx_word32_t)(spx_word16_t) gives TI compiler a hint that it's 16x16->32 multiply */
// #define MULT16_16(a,b)       (((spx_word32_t)(spx_word16_t)(a))*((spx_word32_t)(spx_word16_t)(b)))  // asm: arm
#define MULT16_16(a,b)       (a*b)  // asm: arm

// 12, 13, 14 and 15 are similar to 15, just ( a x b ) >> Qn
// a = 16 bits, b = 16 bits
#define MULT16_16_Q13(a,b)		(SHR(		  MULT16_16((a),(b)) ,13)) // asm: arm
#define MULT16_16_Q14(a,b)		(SHR(		  MULT16_16((a),(b)) ,14)) // asm: arm
#define MULT16_16_Q15(a,b)		(SHR(		  MULT16_16((a),(b)) ,15)) // asm: arm

// #define MULT_16_16_P(a,b,x,y)	(SHR(ADD32(a, MULT16_16((x),(y))),b )) // asm: arm
#define MULT_16_16_P(a,b,x,y)	((a+ (x*y)) >> b ) // asm: arm

#define MULT16_16_P13(a,b)		MULT_16_16_P(4096, 13, a, b) //  (SHR(ADD32(4096, MULT16_16((a),(b))),13))
#define MULT16_16_P14(a,b) 		MULT_16_16_P(8192, 14, a, b) //  (SHR(ADD32(8192, MULT16_16((a),(b))),14))
#define MULT16_16_P15(a,b) 		MULT_16_16_P(16384,15, a, b) //  (SHR(ADD32(16384,MULT16_16((a),(b))),15))

// 12, 13, 14 and 15 are similar to 15, just ( a x b ) >> Qn
// a = 16 bits, b = 32 bits
#define MULT16_32_Q13(a,b)					ADD32(MULT16_16((a),SHR((b),13)), SHR(MULT16_16((a),((b)&0x00001fff)),13))  // asm: arm
#define MULT16_32_Q14(a,b)	 				ADD32(MULT16_16((a),SHR((b),14)), SHR(MULT16_16((a),((b)&0x00003fff)),14))  // asm: arm
#define MULT16_32_Q15(a,b)		            ADD32(MULT16_16((a),SHR((b),15)), SHR(MULT16_16((a),((b)&0x00007fff)),15))  // asm: arm
#define MAC16_32_Q15(c,a,b)       ADD32 (c, MULT16_32_Q15(a,b)                                                        ) // asm: arm

#define MAC16_16(c,a,b)                       ( ADD32((c) ,MULT16_16((a),(b))) )		// asm: arm
#define MAC16_16_P13(c,a,b)     (ADD32((c),SHR( ADD32(4096,MULT16_16((a),(b))) ,13)))	// asm: arm

// #define DIV32_16(a,b) ((spx_word16_t) __divsi3_c(((spx_word32_t)(a)),((spx_word16_t)(b))) ) // asm: arm
// #define DIV32(a,b)                    __divsi3_c(((spx_word32_t)(a)),((spx_word32_t)(b)))   // same as DIV32_16, but return 32

#define DIV32_16(a,b)   ((spx_word16_t) (((spx_word32_t)(a))/((spx_word16_t)(b))) ) // asm: arm
#define DIV32(a,b)                      (((spx_word32_t)(a))/((spx_word32_t)(b)))   // same as DIV32_16, but return 32

// #define DIV32_16(a,b)   (a/b)   // asm: arm
// #define DIV32(a,b)      (a/b)   // same as DIV32_16, but return 32

#define PDIV32_16(a,b)  DIV32_16( a + ((spx_word16_t)(b)>>1), b )
#define PDIV32(a,b)     DIV32   ( a + ((spx_word16_t)(b)>>1), b )

/*
#undef MULT16_16
static spx_word32_t MULT16_16(spx_word16_t x, spx_word16_t y) 
{
	asm 
	(
		"stmdb  sp!,{R2,R3} \n"
		"smull  R2,R3,R0,R1 \n"
		"mov    R0,R2       \n"
		"ldmia  sp!,{R2,R3} \n"
	);
}
*/

// #undef MAC16_16
// inline spx_word32_t MAC16_16(spx_word32_t c, spx_word16_t x, spx_word16_t y) ;
/*
static inline long __divsi3_c (long numerator, long denominator)
{
  int sign;
  long dividend;
  long int bit = 1;				

  sign = 1;
  if (numerator < 0) numerator = -numerator;
  else sign = 0;

  if (denominator < 0)
  {
      denominator = - denominator;
      sign = 1 - sign;
  }

  dividend = 0;				

  while( ( denominator < numerator ) && ( bit != 0 ) && !( denominator & 0x80000000 ) )
  {
      denominator <<=1;					
      bit <<=1;					
  }	

  while (bit)
  {					
      if (numerator >= denominator)
	  {				
		  numerator -= denominator;				
		  dividend |= bit;				
	  }						
      bit >>=1;					
      denominator >>=1;					
  }						

  if (sign) dividend = - dividend;

  return dividend;
}
*/

#endif
