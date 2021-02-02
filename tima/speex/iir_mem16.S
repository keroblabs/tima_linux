//#include <linux/linkage.h>	

#define ALIGN		.align 4,0x90	
#define __LINUX_ARM_ARCH__  1

/*
#define ENTRY(name)  	.globl name;	\
  						.align 4,0x90; 	\
  						name:
*/

#define  ptr_x 		r0
#define  ptr_den 	r1
#define  ptr_y      r2
#define  ptr_men    r3

#define  cnt_i		r4
#define  cnt_j      r5
#define  var_yi     r6
#define  var_nyi    r7

#define  tmp1       r8
#define  tmp2       r9
#define  tmp3       r10
							
// ENTRY(iir_mem16_40_10)
		.globl iir_mem16_40_10;
		.align 4,0x90;
		iir_mem16_40_10:
		
		stmdb	sp!, {r4, r5, r6, r7, r8, r9, r10, lr}

		mov		cnt_i, #0
		
ii1_40:	
		ldr     tmp1, 	[ptr_men]
        add     tmp1, 	tmp1, #0x1000
        mov     var_yi, tmp1, asr #13
        ldrsh   tmp1, 	[ptr_x, cnt_i]
        add     var_yi, var_yi, tmp1
        
        @ get signal
        tst     var_yi, #0x80000000
        bne		ii_neg_40
        
        cmp     var_yi, #0x8000
        blt		ii2_40
        mov     var_yi, #0x8000
        sub     var_yi, var_yi, #1
        b       ii2_40
        
ii_neg_40: 
		mov     tmp1, 	#0
        sub     tmp1, 	tmp1, #0x8000
        cmp     var_yi, tmp1
        bgt     ii2_40
        mov     var_yi, tmp1
        
ii2_40:
        @ nyi = NEG16(yi);
		mov     tmp1, 	 #0
        sub     var_nyi, tmp1, var_yi
        
        @ for (j=0;j<NB_LPC_SIZE-1;j++)
        @     mem[j] = MAC16_16(mem[j+1],den[j],nyi);
        
		mov     cnt_j, #0

ii21_40:
    	ldrsh   tmp1, [ptr_den, cnt_j]
        add     cnt_j, cnt_j, #2
        smull   tmp2, tmp3, tmp1, var_nyi
        ldr     tmp3, [ptr_men, cnt_j, lsl #1]
        sub     cnt_j, cnt_j, #2
        add     tmp1, tmp2, tmp3
        str     tmp1, [ptr_men, cnt_j, lsl #1]
        add     cnt_j, cnt_j, #2
        cmp     cnt_j, #18
        bne     ii21_40
        
        @ mem[NB_LPC_SIZE-1] = MULT16_16(den[NB_LPC_SIZE-1],nyi);
        ldrsh   tmp1, [ptr_den, #18]    
        smull   tmp2, tmp3, tmp1, var_nyi
        str     tmp2, [ptr_men, #36]
        
        @ y[i] = yi;
        strh    var_yi, [ptr_y, cnt_i]
        
        add     cnt_i, cnt_i, #2
        cmp     cnt_i, #80
        bne     ii1_40
		
		ldmia	sp!, {r4, r5, r6, r7, r8, r9, r10, pc}

							
// ENTRY(iir_mem16_160_10)
		.globl iir_mem16_160_10;
		.align 4,0x90;
		iir_mem16_160_10:

							
		stmdb	sp!, {r4, r5, r6, r7, r8, r9, r10, lr}

		mov		cnt_i, #0
		
ii1_160:	
        ldr     tmp1, 	[ptr_men]
        add     tmp1, 	tmp1, #0x1000
        mov     var_yi, tmp1, asr #13
        ldrsh   tmp1, 	[ptr_x, cnt_i]
        add     var_yi, var_yi, tmp1
        
        @ get signal
        tst     var_yi, #0x80000000
        bne		ii_neg_160
        
        cmp     var_yi, #0x8000
        blt		ii2_160
        mov     var_yi, #0x8000
        sub     var_yi, var_yi, #1
        b       ii2_160
        
ii_neg_160: 
        mov     tmp1, 	#0
        sub     tmp1, 	tmp1, #0x8000
        cmp     var_yi, tmp1
        bgt     ii2_160
        mov     var_yi, tmp1
        
ii2_160:		        
        @ nyi = NEG16(yi);
		mov     tmp1, 	 #0
        sub     var_nyi, tmp1, var_yi
        
        @ for (j=0;j<NB_LPC_SIZE-1;j++)
        @     mem[j] = MAC16_16(mem[j+1],den[j],nyi);
        
		mov     cnt_j, #0

ii21_160:	
        ldrsh   tmp1, [ptr_den, cnt_j]
        add     cnt_j, cnt_j, #2
        smull   tmp2, tmp3, tmp1, var_nyi
        ldr     tmp3, [ptr_men, cnt_j, lsl #1]
        sub     cnt_j, cnt_j, #2
        add     tmp1, tmp2, tmp3
        str     tmp1, [ptr_men, cnt_j, lsl #1]
        add     cnt_j, cnt_j, #2
        cmp     cnt_j, #18
        bne     ii21_160
        
        @ mem[NB_LPC_SIZE-1] = MULT16_16(den[NB_LPC_SIZE-1],nyi);
        ldrsh   tmp1, [ptr_den, #18]    
        smull   tmp2, tmp3, tmp1, var_nyi
        str     tmp2, [ptr_men, #36]
        
        @ y[i] = yi;
        strh    var_yi, [ptr_y, cnt_i]
        
        add     cnt_i, cnt_i, #2
        cmp     cnt_i, #320
        bne     ii1_160
		
		ldmia	sp!, {r4, r5, r6, r7, r8, r9, r10, pc}
	
/*
void iir_mem16_encode(const spx_word16_t *x, const spx_coef_t *den, spx_mem_t *mem)
{
	// NB_SUBFRAME_SIZE, NB_LPC_SIZE
   int 			i,j;
   spx_word16_t yi,nyi;

   for (i=0;i<NB_SUBFRAME_SIZE;i++)
   {
      yi = EXTRACT16(SATURATE(ADD32(EXTEND32(x[i]),PSHR32(mem[0],LPC_SHIFT)),32767));
      nyi = NEG16(yi);
      for (j=0;j<NB_LPC_SIZE-1;j++) 
	  	mem[j] = MAC16_16(mem[j+1],den[j],nyi); 				// mem[j] = mem[j+1] + ( den[j] * nyi )
      mem[NB_LPC_SIZE-1] = MULT16_16(den[NB_LPC_SIZE-1],nyi);   // mem[ord-1] = den[ord-1] * nyi
      x[i] = yi;
   }
}
*/

/*
			   // exci...............16
			   // *exc...............16
			   // st->voc_m1.........16
			   // st->voc_m2.........32
			   // st->voc_mean.......16
			   // *dec_mmu._innov....32
			   // g..................16
			   
			   // spx_word16_t tmp1;
			   // spx_word16_t tmp2;
			   // spx_word16_t tmp3;
			   // spx_word16_t tmp4;
			   
#define exci   		r0
#define exc    		r1
#define voc_m1 		r2
#define voc_m2 		r3
#define voc_mean	r4
#define _innov		r5
#define var_g		r6

#define temp1		r7
#define temp2		r8
#define temp3		r9
#define temp4		r10
#define temp5		r11
#define temp6		r12
			   
		.globl nb_decode_opt1;
		.align 4,0x90;
		nb_decode_opt1:
		
		stmdb	sp!, {r7, r8, r9, r10, r11, r12, lr}
		
		ldr     temp2, val_435
		smull   temp1, temp6, temp2, var_g
		ldr     temp2, val_32767
		sub     temp1, temp2, temp1
		
		ldr     temp2, [ _innov ]
		add     temp2, temp2, #0x2000
		mov     temp2, temp2, asr #14
		smull   temp3, temp4, temp1, temp2
		mov     temp3, temp3, asr #15
		
		mov     temp4, #77
		smull   temp1, temp2, temp4, var_g
		mov     temp1, temp1, asr #15
		
		add     temp2, voc_m2, #0x2000
		mov     temp2, temp2, asr #14
		
		smull   temp4, temp5, temp1, temp2
		mov     temp4, temp4, asr #15
		
		sub     temp3, temp3, temp4
		 
		ldr     temp4, val_9830
		smull   temp2, temp1, voc_m1, temp4
		mov     temp2, temp2, asr #15

		ldr     temp4, val_229381
		ldrsh   temp5, [exc]
		smull   temp1, temp6, temp4, temp5
		mov     temp1, temp1, asr #15
	
		sub     temp4, temp1, temp2
		
		mov     exci, temp5
		add     temp5, temp3, temp4
		strh    temp5, [exc]
		
		
		
		
		ldmia	sp!, {r7, r8, r9, r10, r11, r12, pc}
		
val_435:    .long #435
val_32767:  .long #32767
val_229381: .long #229381
val_9830:   .long #9830

*/

/*
static inline spx_word16_t spx_sqrt(spx_word32_t x)
{
   int k;
   spx_word32_t rt;
   k = spx_ilog4(x)-6;
   x = VSHR32(x, (k<<1));
   rt = ADD16(C0, MULT16_16_Q14(x, ADD16(C1, MULT16_16_Q14(x, ADD16(C2, MULT16_16_Q14(x, (C3)))))));
   rt = VSHR32(rt,7-k);
   return( ( spx_word16_t )( rt & 0x0FFFF ) );
}
*/

#define var_x   r0
#define var_k	r1
#define var_rt  r2
#define temp1   r3
#define temp2   r4

		.globl spx_sqrt;
		.align 4,0x90;
		spx_sqrt:
		stmdb  sp!,{r1,r2,r3,r4,lr}
		
		mov    var_k, #0
		mov    temp1, var_x
		cmp    temp1, #0x10000
		blt    spx_ilog4_01
		mov    temp1, temp1, asr #16
		add    var_k, var_k, #8

spx_ilog4_01:
		cmp    temp1, #0x100
		blt    spx_ilog4_02
		mov    temp1, temp1, asr #8
		add    var_k, var_k, #4
		
spx_ilog4_02:
		cmp    temp1, #0x10
		blt    spx_ilog4_03
		mov    temp1, temp1, asr #4
		add    var_k, var_k, #2

spx_ilog4_03:
		cmp    temp1, #0x04
		blt    spx_ilog4_04
		add    var_k, var_k, #1

spx_ilog4_04:
		sub    var_k, var_k, #6
		mov    var_k, var_k, lsl #1
		
		tst    var_k, #0x80000000
		movne  var_x, var_x, asr var_k
		moveq  var_x, var_x, lsl var_k
		
		ldr    temp1,  CONST_C3
		smull  var_rt, temp2, temp1, var_x
		ldr    temp1,  CONST_C2
		add    var_rt, temp1, var_rt, asr #14
		smull  temp1,  temp2, var_rt, var_x
		ldr    temp2,  CONST_C1
		add    var_rt, temp2, temp1, asr #14
		smull  temp1,  temp2, var_rt, var_x
		ldr    temp2,  CONST_C0
		add    var_rt, temp2, temp1, asr #14
		
		mov    temp1, #7
		sub    var_k, temp1, var_k, asr #1
		
		tst    var_k, #0x80000000
		movne  var_rt, var_rt, asr var_k
		moveq  var_rt, var_rt, lsl var_k
		
		ldr    temp1, CONST_C4
		and    r0, var_rt, temp1
		
		ldmia  sp!,{r1,r2,r3,r4,pc}
		
CONST_C0:	.long  3634
CONST_C1:	.long  21173
CONST_C2:	.long  -12627
CONST_C3:	.long  4204
CONST_C4:	.long  0xFFFF


