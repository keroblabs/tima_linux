
#define ptr_x   		r0
#define ptr_y			r1
#define scale  			r2
#define len   			r3

#define tmp		  		r4
#define tmp1			r5
#define tmp2			r6

#define scale_low		r2
#define scale_high      r7

		.globl signal_mul;
		.align 4,0x90;
		signal_mul:
		stmdb  	sp!,{r4,r5,r6,r7,lr}
				
		mov		scale_high, scale, asr #14
		
		mov     tmp, #4000
		sub     tmp, tmp, #1
		and     scale_low, tmp, scale
				
//signal_mul_01:		
		
		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		ldr		tmp, [ptr_x],#4
		mov		tmp, tmp, asr #7
		mul		tmp1, tmp, scale_low
		mov     tmp1, tmp1, asr #14
		mla     tmp,  scale_high, tmp, tmp1
		mov		tmp, tmp, lsl #7
		str     tmp, [ptr_y],#4

		//subs	len, len, #1
		//bne		signal_mul_01
		
		ldmia  	sp!,{r4,r5,r6,r7,pc}
