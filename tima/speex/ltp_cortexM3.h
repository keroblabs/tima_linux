/* Copyright (C) 2008 STMicroelectronics, MCD */
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

#ifndef __LTP_M3_H
#define __LTP_M3_H

#define OVERRIDE_INNER_PROD

#define OVERRIDE_COMPUTE_PITCH_ERROR
#define OVERRIDE_PITCH_GAIN_SEARCH_3TAP_VQ
int pitch_gain_search_3tap_vq(
  const signed char *gain_cdbk,
  int                gain_cdbk_size,
  spx_word16_t      *C16,
  spx_word16_t       max_gain
)
{
  int                best_cdbk=0;
  spx_word32_t       best_sum=-VERY_LARGE32;

  int                i;


spx_word16_t g_0[32]={
0, 1, -9, -24, 
19, 28, -9, 24, 
33, 10, -6, 11, 
32, -21, -5, 13, 
38, -1, -8, 15,
1, 9, -11, -2, 
16, 18, 1, 11,
-15, -14, 4, 22};

spx_word16_t g_1[32]={
0, -26, 8, 10, 
65, -7, 47, 17, 
34, -34, 60, 46, 
53, -39, 31, 27, 
97, -16, 89, 36, 
70, 60, 61, 45, 
47, -50, 57, 37, 
-31, 44, 15, 46};

spx_word16_t g_2[32]={
0, 16, -11, -23, 
-9, 23, 20, 20, 
-12, -10, 9, -5, 
-18, 5, 13, 4, 
-12, -1, 18, -13, 
-1, -8, 20, 9, 
5, 17, 0, 27, 
-19, 35, 3, -8};

spx_word16_t gain_sum[32]={
0, 22, 14, 29, 
47, 29, 38, 31, 
40, 27, 38, 31, 
52, 33, 25, 22, 
74, 9, 58, 32, 
36, 39, 46, 28, 
34, 43, 29, 38, 
33, 47, 11, 38};

  for (i=0;i<32;i++) 
  {
    
	spx_word32_t sum = 0;     
         
    sum = ADD32(sum,MULT16_16(MULT16_16_16(g_0[i],64),C16[0]));
    sum = ADD32(sum,MULT16_16(MULT16_16_16(g_1[i],64),C16[1]));
    sum = ADD32(sum,MULT16_16(MULT16_16_16(g_2[i],64),C16[2]));
    sum = SUB32(sum,MULT16_16(MULT16_16_16(g_0[i],g_1[i]),C16[3]));
    sum = SUB32(sum,MULT16_16(MULT16_16_16(g_2[i],g_1[i]),C16[4]));
    sum = SUB32(sum,MULT16_16(MULT16_16_16(g_2[i],g_0[i]),C16[5]));
    sum = SUB32(sum,MULT16_16(MULT16_16_16(g_0[i],g_0[i]),C16[6]));
    sum = SUB32(sum,MULT16_16(MULT16_16_16(g_1[i],g_1[i]),C16[7]));
    sum = SUB32(sum,MULT16_16(MULT16_16_16(g_2[i],g_2[i]),C16[8]));
         
    if (sum>best_sum && gain_sum[i]<=max_gain) {
      best_sum=sum;
      best_cdbk=i;
    }
  }

  return best_cdbk;
}


#define OVERRIDE_PITCH_XCORR
void pitch_xcorr(const spx_word16_t *_x, const spx_word16_t *_y, spx_word32_t *corr, int len, int nb_pitch, char *stack)
{
   int i,j;
   for (i=0;i<nb_pitch;i+=4)
   {
      /* Compute correlation*/
      //corr[nb_pitch-1-i]=inner_prod(x, _y+i, len);
      spx_word32_t sum1=0;
      spx_word32_t sum2=0;
      spx_word32_t sum3=0;
      spx_word32_t sum4=0;
      const spx_word16_t *y = _y+i;
      const spx_word16_t *x = _x;
      spx_word32_t y0, y1, y2, y3;
      y0=*y++;
      y1=*y++;
      y2=*y++;
      y3=*y++;
      for (j=0;j<len;j+=4)
      {
         spx_word32_t part1, part2, part3, part4, x0;
         spx_word32_t dead1;
         __asm__ __volatile__ (
#ifdef SHORTCUTS
               "\tldrsh %10, [%8], #4 \n"
               "\tmul %4, %10, %0 \n"
               "\tldrsh %15, [%8], #4 \n"
               "\tmul %5, %10, %1 \n"
               "\tldrsh %0, [%9], #2 \n"
               "\tmul %6, %10, %2 \n"
               "\tldrsh %1, [%9], #2 \n"
               "\tmul %7, %10, %3 \n"
               
               
               "\tmla %4, %15, %2, %4 \n"
               "\tldrsh %2, [%9], #2 \n"
               "\tmla %5, %15, %3, %5 \n"
               "\tldrsh %3, [%9], #2 \n"
               "\tmla %6, %15, %0, %6 \n"
               "\tmla %7, %15, %1, %7 \n"

#else
               "\tldrsh %10, [%8], #2 \n"
               "\tmul %4, %10, %0 \n"
               "\tmul %5, %10, %1 \n"
               "\tmul %6, %10, %2 \n"
               "\tmul %7, %10, %3 \n"

               "\tldrsh %10, [%8], #2 \n"
               "\tldrsh %0, [%9], #2 \n"
               "\tmla %4, %10, %1, %4 \n"
               "\tmla %5, %10, %2, %5 \n"
               "\tmla %6, %10, %3, %6 \n"
               "\tmla %7, %10, %0, %7 \n"

               "\tldrsh %10, [%8], #2 \n"
               "\tldrsh %1, [%9], #2 \n"
               "\tmla %4, %10, %2, %4 \n"
               "\tmla %5, %10, %3, %5 \n"
               "\tmla %6, %10, %0, %6 \n"
               "\tmla %7, %10, %1, %7 \n"

               "\tldrsh %10, [%8], #2 \n"
               "\tldrsh %2, [%9], #2 \n"
               "\tmla %4, %10, %3, %4 \n"
               "\tmla %5, %10, %0, %5 \n"
               "\tmla %6, %10, %1, %6 \n"
               "\tmla %7, %10, %2, %7 \n"

               "\tldrsh %3, [%9], #2 \n"
#endif

               "\tldr %10, %11 \n"
               "\tldr %15, %12 \n"
               "\tadd %4, %10, %4, asr #6 \n"
               "\tstr %4, %11 \n"
               "\tldr %10, %13 \n"
               "\tadd %5, %15, %5, asr #6 \n"
               "\tstr %5, %12 \n"
               "\tldr %15, %14 \n"
               "\tadd %6, %10, %6, asr #6 \n"
               "\tadd %7, %15, %7, asr #6 \n"
               "\tstr %6, %13 \n"
               "\tstr %7, %14 \n"

            : "+r" (y0), "+r" (y1), "+r" (y2), "+r" (y3),
         "=r" (part1),  "=r" (part2),  "=r" (part3),  "=r" (part4),
              "+r" (x), "+r" (y), "=r" (x0), "+m" (sum1),
              "+m" (sum2), "+m" (sum3), "+m" (sum4), "=r" (dead1)
            :
            : "cc", "memory"
                              );
      }
      corr[nb_pitch-1-i]=sum1;
      corr[nb_pitch-2-i]=sum2;
      corr[nb_pitch-3-i]=sum3;
      corr[nb_pitch-4-i]=sum4;
   }

}

#endif
