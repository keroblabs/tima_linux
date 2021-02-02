/* Copyright (C) 2002-2006 Jean-Marc Valin 
   File: nb_celp.c

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

#include "speex_config.h"
#include <math.h>
#include "nb_celp.h"
#include "lpc.h"
#include "lsp.h"
#include "ltp.h"
#include "quant_lsp.h"
#include "cb_search.h"
#include "filters.h"
#include "os_support.h"
#include "vq.h"
#include "speex.h"
#include "speex_bits.h"
#include "arch.h"
#include "math_approx.h"
#include "os_support.h"

#ifndef M_PI
#define M_PI           3.14159265358979323846  /* pi */
#endif

#ifndef NULL
#define NULL 0
#endif

#define SUBMODE(x) st->submodes[st->submodeID]->x
#define DEC_SUBMODE(x) dec_mmu._local_st.submodes[dec_mmu._local_st.submodeID]->x

/* Default size for the encoder and decoder stack (can be changed at compile time).
   This does not apply when using variable-size arrays or alloca. */
#ifndef NB_ENC_STACK
#define NB_ENC_STACK (8000*sizeof(spx_sig_t))
#endif

#ifndef NB_DEC_STACK
#define NB_DEC_STACK (4000*sizeof(spx_sig_t))
#endif

/** Handle in-band request */
int speex_inband_handler(SpeexBits *bits, SpeexCallback *callback_list, void *state);

/** Default handler for user-defined requests: in this case, just ignore */
int speex_default_user_handler(SpeexBits *bits, void *state, void *data);

const spx_word32_t ol_gain_table[32]={18900, 25150, 33468, 44536, 59265, 78865, 104946, 139653, 185838, 247297, 329081, 437913, 582736, 775454, 1031906, 1373169, 1827293, 2431601, 3235761, 4305867, 5729870, 7624808, 10146425, 13501971, 17967238, 23909222, 31816294, 42338330, 56340132, 74972501, 99766822, 132760927};
const spx_word16_t exc_gain_quant_scal3_bound[7]={1841, 3883, 6051, 8062, 10444, 13580, 18560};
const spx_word16_t exc_gain_quant_scal3[8]={1002, 2680, 5086, 7016, 9108, 11781, 15380, 21740};
const spx_word16_t exc_gain_quant_scal1_bound[1]={14385};
const spx_word16_t exc_gain_quant_scal1[2]={11546, 17224};

#define LSP_MARGIN 16
#define LSP_DELTA1 6553
#define LSP_DELTA2 1638

#define EXTRA_BUFFER 0

#define sqr(x) ((x)*(x))

extern const spx_word16_t lag_window[];
extern const spx_word16_t lpc_window[];

void nb_decode_vocoder_submode1( spx_word16_t * exc, int ol_pitch, spx_word16_t ol_pitch_coef, spx_word32_t ol_gain );

typedef struct
{
	EncState	 _local_st;

	spx_coef_t	 _lpc[ NB_LPC_SIZE ];
	spx_coef_t	 _bw_lpc1[ NB_LPC_SIZE ];
	spx_coef_t	 _bw_lpc2[ NB_LPC_SIZE ];
	spx_lsp_t	 _lsp[ NB_LPC_SIZE ];
	spx_lsp_t	 _qlsp[ NB_LPC_SIZE ];
	spx_lsp_t	 _interp_lsp[ NB_LPC_SIZE ];
	spx_lsp_t	 _interp_qlsp[ NB_LPC_SIZE ];
	spx_coef_t	 _interp_lpc[ NB_LPC_SIZE ];
	spx_coef_t	 _interp_qlpc[ NB_LPC_SIZE ];
	spx_mem_t	 _mem[ NB_LPC_SIZE ];

	spx_word16_t _w_sig[ NB_FRAME_SIZE + NB_SUBFRAME_SIZE ];

	spx_word16_t _autocorr[ NB_LPC_SIZE + 1 ];

	spx_sig_t    _innov[ NB_SUBFRAME_SIZE ];
	spx_sig_t    _innov2[ NB_SUBFRAME_SIZE ];

	spx_word16_t _target[ NB_SUBFRAME_SIZE ];
	spx_word16_t _ringing[ NB_SUBFRAME_SIZE ];
    spx_word16_t _syn_resp[ NB_SUBFRAME_SIZE ];
    spx_word16_t _real_exc[ NB_SUBFRAME_SIZE ];
    spx_word32_t _exc32[ NB_SUBFRAME_SIZE ];

} tEncodeMMU;

typedef struct
{
	DecState		_local_st;

	spx_sig_t		_innov[ NB_SUBFRAME_SIZE ];
	spx_sig_t		_innov2[ NB_SUBFRAME_SIZE ];
	
	spx_word32_t	_exc32[ NB_SUBFRAME_SIZE ];
	spx_coef_t		_ak[ NB_LPC_SIZE ];
	spx_lsp_t		_qlsp[ NB_LPC_SIZE ];
	spx_lsp_t		_interp_qlsp[ NB_LPC_SIZE ];
	
	spx_coef_t      _lpc[ NB_LPC_SIZE ];

} tDecodeMMU;

static tEncodeMMU enc_mmu;
static tDecodeMMU dec_mmu;

void *nb_encoder_init(const SpeexMode *m)
{
   EncState *st;
   const SpeexNBMode *mode;
   int i;

   memset( &enc_mmu, 0x00, sizeof( tEncodeMMU ) );

   mode=(const SpeexNBMode *)m->mode;
   st =  &enc_mmu._local_st;

   st->mode=m;

   st->submodes=mode->submodes;
   st->submodeID=st->submodeSelect=mode->defaultSubmode;
   st->bounded_pitch = 1;

   st->encode_submode = 1;

   st->cumul_gain = 1024;

   st->exc = st->excBuf + NB_PITCH_END + 2;
   st->sw = st->swBuf + NB_PITCH_END + 2;

   st->window= lpc_window;
   
   /* Create the window for autocorrelation (lag-windowing) */
   st->lagWindow = lag_window;

   st->first = 1;
   
   for (i=0;i<NB_LPC_SIZE;i++)
      st->old_lsp[i]= DIV32(MULT16_16(QCONST16(3.1415927f, LSP_SHIFT), i+1), NB_LPC_SIZE+1);

   st->innov_rms_save = NULL;
   
   st->plc_tuning = 2;
   st->complexity=2;
   st->sampling_rate=8000;
   
   return st;
}

void nb_encoder_destroy(void *state)
{
}

int nb_encode(void *state, void *vin, SpeexBits *bits)
{
	EncState *st;
	int i, sub, roots;
	int ol_pitch;
	spx_word16_t ol_pitch_coef;
	spx_word32_t ol_gain;

	spx_word32_t ener=0;
	spx_word16_t fine_gain;
	spx_word16_t *in = (spx_word16_t*)vin;

	st=(EncState *)state;

	/* Move signals 1 frame towards the past */
	SPEEX_MOVE(st->excBuf, st->excBuf+NB_FRAME_SIZE, NB_PITCH_END+2);
	SPEEX_MOVE(st->swBuf, st->swBuf+NB_FRAME_SIZE, NB_PITCH_END+2);

	highpass(in, in, NB_FRAME_SIZE, HIGHPASS_NARROWBAND|HIGHPASS_INPUT, st->mem_hp);
   
	/* Window for analysis */
	for (i=0;i<NB_SUBFRAME_SIZE;i++) // FIXME - optimization: ( st->winBuf[i] * st->window[i] ) >> SIG_SHIFT
		enc_mmu._w_sig[i] = EXTRACT16(SHR32(MULT16_16(st->winBuf[i],st->window[i]),SIG_SHIFT));

	for (;i<NB_WINDOW_SIZE;i++) // FIXME - optimization: ( in[i-st->windowSize+NB_FRAME_SIZE] * st->window[i] ) >> SIG_SHIFT
		enc_mmu._w_sig[i] = EXTRACT16(SHR32(MULT16_16(in[i-NB_WINDOW_SIZE+NB_FRAME_SIZE],st->window[i]),SIG_SHIFT));

	/* Compute auto-correlation */
	_spx_autocorr(enc_mmu._w_sig, enc_mmu._autocorr, NB_LPC_SIZE+1, NB_WINDOW_SIZE);

	/* Noise floor in auto-correlation domain */
	enc_mmu._autocorr[0] = ADD16(enc_mmu._autocorr[0],MULT16_16_Q15(enc_mmu._autocorr[0],QCONST16(.0002,15))); 

	/* Lag windowing: equivalent to filtering in the power-spectrum domain */
	for (i=0;i<NB_LPC_SIZE+1;i++) // FIXME - optimization: ( autocorr[i] * st->lagWindow[i] ) >> 14
		enc_mmu._autocorr[i] = MULT16_16_Q14(enc_mmu._autocorr[i],st->lagWindow[i]);

	/* Levinson-Durbin */
	_spx_lpc(enc_mmu._lpc, enc_mmu._autocorr, NB_LPC_SIZE);

	/* LPC to LSPs (x-domain) transform */
	roots=lpc_to_lsp (enc_mmu._lpc, NB_LPC_SIZE, enc_mmu._lsp, 10, LSP_DELTA1, NULL);

	/* Check if we found all the roots */
	if (roots!=NB_LPC_SIZE)
	{
		/*If we can't find all LSP's, do some damage control and use previous filter*/
		// FIXME: memory copy (5xDWORD)
		for (i=0;i<NB_LPC_SIZE;i++) enc_mmu._lsp[i]=st->old_lsp[i];
	}

	/* Whole frame analysis (open-loop estimation of pitch and excitation gain) */
	{
		int diff = NB_SUBFRAME_SIZE;
		if (st->first)
		{
			// FIXME: memory copy (5xDWORD)
			for (i=0;i<NB_LPC_SIZE;i++) enc_mmu._interp_lsp[i] = enc_mmu._lsp[i];
		}
		else
		{
			lsp_interpolate(st->old_lsp, enc_mmu._lsp, enc_mmu._interp_lsp, NB_LPC_SIZE, NB_TOTAL_SUBFRAMES, NB_TOTAL_SUBFRAMES<<1);
		}

		lsp_enforce_margin(enc_mmu._interp_lsp, NB_LPC_SIZE, LSP_MARGIN);

		/* Compute interpolated LPCs (unquantized) for whole frame*/
		lsp_to_lpc(enc_mmu._interp_lsp, enc_mmu._interp_lpc, NB_LPC_SIZE,NULL);

		/*Open-loop pitch*/
		if( !st->submodes[st->submodeID] || 
	  		(st->complexity>2 && SUBMODE(have_subframe_gain)<3) || 
	  		SUBMODE(forced_pitch_gain) || 
	  		SUBMODE(lbr_pitch) != -1 )
		{
			int nol_pitch[6];
			spx_word16_t nol_pitch_coef[6];

			bw_lpc(NB_GAMA_1, enc_mmu._interp_lpc, enc_mmu._bw_lpc1, NB_LPC_SIZE);
			bw_lpc(NB_GAMA_2, enc_mmu._interp_lpc, enc_mmu._bw_lpc2, NB_LPC_SIZE);

			// FIXME: memory copy
			SPEEX_COPY(st->sw, st->winBuf, diff);
			SPEEX_COPY(st->sw+diff, in, NB_FRAME_SIZE-diff);

			filter_mem16(st->sw, enc_mmu._bw_lpc1, enc_mmu._bw_lpc2, st->sw, NB_FRAME_SIZE, NB_LPC_SIZE, st->mem_sw_whole, NULL);

			open_loop_nbest_pitch(st->sw, NB_PITCH_START, NB_PITCH_END, NB_FRAME_SIZE, nol_pitch, nol_pitch_coef, 6, NULL);
			ol_pitch=nol_pitch[0];
			ol_pitch_coef = nol_pitch_coef[0];

			/*Try to remove pitch multiples*/
			for (i=1;i<6;i++)
			{
				if ((nol_pitch_coef[i]>MULT16_16_Q15(nol_pitch_coef[0],27853)) && 
					(ABS(2*nol_pitch[i]-ol_pitch)<=2 || ABS(3*nol_pitch[i]-ol_pitch)<=3 || 
					ABS(4*nol_pitch[i]-ol_pitch)<=4 || ABS(5*nol_pitch[i]-ol_pitch)<=5))
				{
					/*ol_pitch_coef=nol_pitch_coef[i];*/
					ol_pitch = nol_pitch[i];
				}
			}
		} 
		else 
		{
			ol_pitch=0;
			ol_pitch_coef=0;
		}
      
		/*Compute "real" excitation*/
		// FIXME: memory copy
		SPEEX_COPY(st->exc, st->winBuf, diff);
		SPEEX_COPY(st->exc+diff, in, NB_FRAME_SIZE-diff);

		fir_mem16(st->exc, enc_mmu._interp_lpc, st->exc, NB_FRAME_SIZE, NB_LPC_SIZE, st->mem_exc, NULL);

		/* Compute open-loop excitation gain */
		{
			spx_word16_t g = compute_rms16(st->exc, NB_FRAME_SIZE);
			if (st->submodeID!=1 && ol_pitch>0)
			{
				ol_gain = MULT16_16(g, MULT16_16_Q14(QCONST16(1.1,14),
									spx_sqrt(QCONST32(1.,28)-MULT16_32_Q15(QCONST16(.8,15),SHL32(MULT16_16(ol_pitch_coef,ol_pitch_coef),16)))));
			}
			else
			{
				ol_gain = SHL32(EXTEND32(g),SIG_SHIFT);
			}
		}
	}

	if (st->encode_submode)
	{
		/* First, transmit a zero for narrowband */
		speex_bits_pack(bits, 0, 1);

		/* Transmit the sub-mode we use for this frame */
		speex_bits_pack(bits, st->submodeID, NB_SUBMODE_BITS);

	}
    
	/* LSP Quantization */
	if (st->first)
	{
		// FIXME: memory copy
		for (i=0;i<NB_LPC_SIZE;i++) st->old_lsp[i] = enc_mmu._lsp[i];
	}


   /*Quantize LSPs*/
   SUBMODE(lsp_quant)(enc_mmu._lsp, enc_mmu._qlsp, NB_LPC_SIZE, bits);

   /*Quantize and transmit open-loop excitation gain*/
   {
      int qe = scal_quant32(ol_gain, ol_gain_table, 32);

      ol_gain = MULT16_32_Q15(28406,ol_gain_table[qe]);
      speex_bits_pack(bits, qe, 5);
   }

	/* Special case for first frame */
	if (st->first)
	{
	   	// FIXME: memory copy
		for (i=0;i<NB_LPC_SIZE;i++) st->old_qlsp[i] = enc_mmu._qlsp[i];
	}

	/* Loop on sub-frames */
	for (sub=0;sub<NB_TOTAL_SUBFRAMES;sub++)
	{
		int   offset;
		spx_word16_t *sw;
		spx_word16_t *exc;
		int pitch;
		int response_bound = NB_SUBFRAME_SIZE;

/* 0.45 ms */

		/* Offset relative to start of frame */
		offset = NB_SUBFRAME_SIZE*sub;
		/* Excitation */
		exc=st->exc+offset;
		/* Weighted signal */
		sw=st->sw+offset;
	      
		/* LSP interpolation (quantized and unquantized) */
		lsp_interpolate(st->old_lsp, enc_mmu._lsp, enc_mmu._interp_lsp, NB_LPC_SIZE, sub, NB_TOTAL_SUBFRAMES);
		lsp_interpolate(st->old_qlsp, enc_mmu._qlsp, enc_mmu._interp_qlsp, NB_LPC_SIZE, sub, NB_TOTAL_SUBFRAMES);

		/* Make sure the filters are stable */
		lsp_enforce_margin(enc_mmu._interp_lsp, NB_LPC_SIZE, LSP_MARGIN);
		lsp_enforce_margin(enc_mmu._interp_qlsp, NB_LPC_SIZE, LSP_MARGIN);

		/* Compute interpolated LPCs (quantized and unquantized) */
		lsp_to_lpc(enc_mmu._interp_lsp, enc_mmu._interp_lpc, NB_LPC_SIZE, NULL);
		lsp_to_lpc(enc_mmu._interp_qlsp, enc_mmu._interp_qlpc, NB_LPC_SIZE, NULL);

		/* Compute analysis filter gain at w=pi (for use in SB-CELP) */
		{
			spx_word32_t pi_g=LPC_SCALING;
			for (i=0;i<NB_LPC_SIZE;i+=2)
			{
				/*pi_g += -st->interp_qlpc[i] +  st->interp_qlpc[i+1];*/
				pi_g = ADD32(pi_g, SUB32(EXTEND32(enc_mmu._interp_qlpc[i+1]),EXTEND32(enc_mmu._interp_qlpc[i])));
			}
			st->pi_gain[sub] = pi_g;
		}

		/* Compute bandwidth-expanded (unquantized) LPCs for perceptual weighting */
		bw_lpc(NB_GAMA_1, enc_mmu._interp_lpc, enc_mmu._bw_lpc1, NB_LPC_SIZE);
		bw_lpc(NB_GAMA_2, enc_mmu._interp_lpc, enc_mmu._bw_lpc2, NB_LPC_SIZE);

		/*FIXME: This will break if we change the window size */
		if (sub==0)
		{
			for (i=0;i<NB_SUBFRAME_SIZE;i++) enc_mmu._real_exc[i] = sw[i] = st->winBuf[i];
		} 
		else 
		{
			for (i=0;i<NB_SUBFRAME_SIZE;i++) enc_mmu._real_exc[i] = sw[i] = in[i+((sub-1)*NB_SUBFRAME_SIZE)];
		}

		fir_mem16(enc_mmu._real_exc, enc_mmu._interp_qlpc, enc_mmu._real_exc, NB_SUBFRAME_SIZE, NB_LPC_SIZE, st->mem_exc2, NULL);
	      
		if (st->complexity==0) response_bound >>= 1;

		compute_impulse_response(enc_mmu._interp_qlpc, enc_mmu._bw_lpc1, enc_mmu._bw_lpc2, enc_mmu._syn_resp, response_bound, NB_LPC_SIZE, NULL);
	      
		for (i=response_bound;i<NB_SUBFRAME_SIZE;i++) enc_mmu._syn_resp[i]=VERY_SMALL;
	      
		/* Compute zero response of A(z/g1) / ( A(z/g2) * A(z) ) */
		for (i=0;i<NB_LPC_SIZE;i++) enc_mmu._mem[i]=SHL32(st->mem_sp[i],1);
		for (i=0;i<NB_SUBFRAME_SIZE;i++) enc_mmu._ringing[i] = VERY_SMALL;

		iir_mem16(enc_mmu._ringing, enc_mmu._interp_qlpc, enc_mmu._ringing, NB_SUBFRAME_SIZE, NB_LPC_SIZE, enc_mmu._mem);
		// iir_mem16_40_10(enc_mmu._ringing, enc_mmu._interp_qlpc, enc_mmu._ringing, enc_mmu._mem);
		for (i=0;i<NB_LPC_SIZE;i++) enc_mmu._mem[i]=SHL32(st->mem_sw[i],1);
		filter_mem16(enc_mmu._ringing, enc_mmu._bw_lpc1, enc_mmu._bw_lpc2, enc_mmu._ringing, NB_SUBFRAME_SIZE, NB_LPC_SIZE, enc_mmu._mem, NULL);
      
		/* Compute weighted signal */
		for (i=0;i<NB_LPC_SIZE;i++) enc_mmu._mem[i]=st->mem_sw[i];
		filter_mem16(sw, enc_mmu._bw_lpc1, enc_mmu._bw_lpc2, sw, NB_SUBFRAME_SIZE, NB_LPC_SIZE, enc_mmu._mem, NULL);
	      
		if (st->complexity==0)
		{
			for (i=0;i<NB_LPC_SIZE;i++) st->mem_sw[i]=enc_mmu._mem[i];
		}
      
		/* Compute target signal (saturation prevents overflows on clipped input speech) */
		for (i=0;i<NB_SUBFRAME_SIZE;i++) enc_mmu._target[i]=EXTRACT16(SATURATE(SUB32(sw[i],PSHR32(enc_mmu._ringing[i],1)),32767));

		/* Reset excitation */
		SPEEX_MEMSET(exc, 0, NB_SUBFRAME_SIZE);
        
/* 1.44 ms */

		/* If we have a long-term predictor (otherwise, something's wrong) - 1.35 ms */
		{
			int pit_min, pit_max;
			/* Long-term prediction */
			pit_min = NB_PITCH_START;
			pit_max = NB_PITCH_END;
         
			/* Force pitch to use only the current frame if needed */
			if (st->bounded_pitch && pit_max>offset) pit_max=offset;

			/* Perform pitch search */
			pitch = SUBMODE(ltp_quant)(enc_mmu._target, sw, enc_mmu._interp_qlpc, enc_mmu._bw_lpc1, enc_mmu._bw_lpc2,
										enc_mmu._exc32, SUBMODE(ltp_params), pit_min, pit_max, ol_pitch_coef,
										NB_LPC_SIZE, NB_SUBFRAME_SIZE, bits, NULL, 
										exc, enc_mmu._syn_resp, st->complexity, 0, st->plc_tuning, &st->cumul_gain);

			/*
			pitch = pitch_search_3tap(enc_mmu._target, sw, enc_mmu._interp_qlpc, enc_mmu._bw_lpc1, enc_mmu._bw_lpc2,
										enc_mmu._exc32, SUBMODE(ltp_params), pit_min, pit_max, ol_pitch_coef,
										NB_LPC_SIZE, NB_SUBFRAME_SIZE, bits, NULL, 
										exc, enc_mmu._syn_resp, st->complexity, 0, st->plc_tuning, &st->cumul_gain);
										*/
			st->pitch[sub]=pitch;
		}
        
		/* Quantization of innovation */
		SPEEX_MEMSET(enc_mmu._innov, 0, NB_SUBFRAME_SIZE);
	      
		/* Make sure this is save from overflows (so far so good) */
		// FIXME: memory copy
		for (i=0;i<NB_SUBFRAME_SIZE;i++)
			enc_mmu._real_exc[i] = EXTRACT16(SUB32(EXTEND32(enc_mmu._real_exc[i]), PSHR32(enc_mmu._exc32[i],SIG_SHIFT-1)));
      
		ener = SHL32(EXTEND32(compute_rms16(enc_mmu._real_exc, NB_SUBFRAME_SIZE)),SIG_SHIFT);
      
		/*FIXME: Should use DIV32_16 and make sure result fits in 16 bits */
		{
			spx_word32_t f = PDIV32(ener,PSHR32(ol_gain,SIG_SHIFT));

			if (f<=32767) fine_gain = f;
			else fine_gain = 32767;
		}

		/* Calculate gain correction for the sub-frame (if any) */
        {
           int qe;
           qe = scal_quant(fine_gain, exc_gain_quant_scal1_bound, 2);
           speex_bits_pack(bits, qe, 1);
           ener=MULT16_32_Q14(exc_gain_quant_scal1[qe],ol_gain);               
		}

/* 0.73 ms */      	      

		/* Normalize innovation */
		signal_div(enc_mmu._target, enc_mmu._target, ener, NB_SUBFRAME_SIZE);
	      
		/* Quantize innovation */
		/* Codebook search */

		SUBMODE(innovation_quant)(enc_mmu._target, enc_mmu._interp_qlpc, enc_mmu._bw_lpc1, enc_mmu._bw_lpc2, 
				SUBMODE(innovation_params), NB_LPC_SIZE, NB_SUBFRAME_SIZE, 
				enc_mmu._innov, enc_mmu._syn_resp, bits, NULL, st->complexity, SUBMODE(double_codebook));

		/*
		split_cb_search_shape_sign(enc_mmu._target, enc_mmu._interp_qlpc, enc_mmu._bw_lpc1, enc_mmu._bw_lpc2, 
				SUBMODE(innovation_params), NB_LPC_SIZE, NB_SUBFRAME_SIZE, 
				enc_mmu._innov, enc_mmu._syn_resp, bits, NULL, st->complexity, SUBMODE(double_codebook));
        */
		/* De-normalize innovation and update excitation */
		signal_mul(enc_mmu._innov, enc_mmu._innov, ener, NB_SUBFRAME_SIZE);
     
		// FIXME: optimization
		for (i=0;i<NB_SUBFRAME_SIZE;i++)
			exc[i] = EXTRACT16(SATURATE32(PSHR32(ADD32(SHL32(enc_mmu._exc32[i],1),enc_mmu._innov[i]),SIG_SHIFT),32767));

        if (st->innov_rms_save) st->innov_rms_save[sub] = compute_rms(enc_mmu._innov, NB_SUBFRAME_SIZE);

		/* Final signal synthesis from excitation */
		iir_mem16(exc, enc_mmu._interp_qlpc, sw, NB_SUBFRAME_SIZE, NB_LPC_SIZE, st->mem_sp);
        // iir_mem16_40_10(exc, enc_mmu._interp_qlpc, sw, st->mem_sp);

		/* Compute weighted signal again, from synthesized speech (not sure it's the right thing) */
		if (st->complexity!=0) filter_mem16(sw, enc_mmu._bw_lpc1, enc_mmu._bw_lpc2, sw, NB_SUBFRAME_SIZE, NB_LPC_SIZE, st->mem_sw, NULL);
        
/******/

	}

	/* Store the LSPs for interpolation in the next frame */
	// FIXME: memory copy
	for (i=0;i<NB_LPC_SIZE;i++) 
	{
		st->old_lsp[i] = enc_mmu._lsp[i];
		st->old_qlsp[i] = enc_mmu._qlsp[i];
	}

	// if (st->submodeID==1) speex_bits_pack(bits, 0, 4);

	/* The next frame will not be the first (Duh!) */
	st->first = 0;
	// FIXME: memory copy
	SPEEX_COPY(st->winBuf, in+2*NB_FRAME_SIZE-NB_WINDOW_SIZE, NB_SUBFRAME_SIZE);

	if (SUBMODE(innovation_quant) == noise_codebook_quant || st->submodeID==0)
		st->bounded_pitch = 1;
	else
		st->bounded_pitch = 0;

	return 1;
}

void *nb_decoder_init(const SpeexMode *m)
{
   DecState *st;
   const SpeexNBMode *mode;
   int i;

   memset( &dec_mmu, 0x00, sizeof( tDecodeMMU ) );

   mode=(const SpeexNBMode *)m->mode;
   st =  &dec_mmu._local_st;

   dec_mmu._local_st.mode=m;
   dec_mmu._local_st.encode_submode = 1;
   dec_mmu._local_st.first=1;
   
   /* Codec parameters, should eventually have several "modes"*/
   dec_mmu._local_st.submodes = mode->submodes;
   dec_mmu._local_st.submodeID = mode->defaultSubmode;

   dec_mmu._local_st.lpc_enh_enabled=1;

   dec_mmu._local_st.exc = dec_mmu._local_st.excBuf + ( 2 * NB_PITCH_END ) + NB_SUBFRAME_SIZE + 6;
   SPEEX_MEMSET(dec_mmu._local_st.excBuf, 0, NB_FRAME_SIZE + NB_PITCH_END);

   dec_mmu._local_st.last_pitch = 40;
   dec_mmu._local_st.count_lost=0;
   dec_mmu._local_st.pitch_gain_buf[0] = dec_mmu._local_st.pitch_gain_buf[1] = dec_mmu._local_st.pitch_gain_buf[2] = 0;
   dec_mmu._local_st.pitch_gain_buf_idx = 0;
   dec_mmu._local_st.seed = 1000;
   
   dec_mmu._local_st.sampling_rate=8000;
   dec_mmu._local_st.last_ol_gain = 0;

   dec_mmu._local_st.user_callback.func = &speex_default_user_handler;
   dec_mmu._local_st.user_callback.data = NULL;

   for (i=0;i<SPEEX_MAX_CALLBACKS;i++) dec_mmu._local_st.speex_callbacks[i].func = NULL;

   dec_mmu._local_st.voc_m1 = dec_mmu._local_st.voc_m2 = dec_mmu._local_st.voc_mean=0;
   dec_mmu._local_st.voc_offset = 0;
   dec_mmu._local_st.dtx_enabled = 0;

   return st;
}

void nb_decoder_destroy(void *state)
{
}

/* Just so we don't need to carry the complete wideband mode information */
static const int wb_skip_table[8] = {0, 36, 112, 192, 352, 0, 0, 0};
   
int nb_decode(SpeexBits *bits, void *vout)
{
   // DecState *st;
   int i, sub;
   int pitch;
   spx_word16_t pitch_gain[3];
   spx_word32_t ol_gain=0;
   int ol_pitch=0;
   spx_word16_t ol_pitch_coef=0;
   int best_pitch=40;
   spx_word16_t best_pitch_gain=0;
   int wideband;
   int m;
   int offset;
   
   spx_word16_t pitch_average=0;
   
   spx_word16_t *out = (spx_word16_t*)vout;

   // st=(DecState*)state;
   // st=(DecState*)&dec_mmu._local_st;
   
   /* Check if we're in DTX mode - less than 1 ms */
   if (!bits && dec_mmu._local_st.dtx_enabled)
   {
      dec_mmu._local_st.submodeID=0;
   }
   else 
   {
      if (dec_mmu._local_st.encode_submode)
      {
      /* Search for next narrowband block (handle requests, skip wideband blocks) */
      do {
         if (speex_bits_remaining(bits)<5) return -1;
         wideband = speex_bits_unpack_unsigned(bits, 1);
         if (wideband) /* Skip wideband block (for compatibility) */
         {
            int submode;
            int advance;
            advance = submode = speex_bits_unpack_unsigned(bits, SB_SUBMODE_BITS);
            advance = wb_skip_table[submode];
            if (advance < 0)
            {
               // speex_notify("Invalid mode encountered. The stream is corrupted.");
               return -2;
            } 
            advance -= (SB_SUBMODE_BITS+1);
            speex_bits_advance(bits, advance);
            
            if (speex_bits_remaining(bits)<5) return -1;
            wideband = speex_bits_unpack_unsigned(bits, 1);
            if (wideband)
            {
               advance = submode = speex_bits_unpack_unsigned(bits, SB_SUBMODE_BITS);
               advance = wb_skip_table[submode];
               if (advance < 0)
               {
                  // speex_notify("Invalid mode encountered. The stream is corrupted.");
                  return -2;
               } 
               advance -= (SB_SUBMODE_BITS+1);
               speex_bits_advance(bits, advance);
               wideband = speex_bits_unpack_unsigned(bits, 1);
               if (wideband)
               {
                  // speex_notify("More than two wideband layers found. The stream is corrupted.");
                  return -2;
               }

            }
         }
         if (speex_bits_remaining(bits)<4) return -1;
         /* FIXME: Check for overflow */
         m = speex_bits_unpack_unsigned(bits, 4);
         if (m==15) /* We found a terminator */
         {
            return -1;
         } 
		 else if (m==14) /* Speex in-band request */
         {
            int ret = speex_inband_handler(bits, dec_mmu._local_st.speex_callbacks, &dec_mmu._local_st);
            if (ret) return ret;
         } 
		 else if (m==13) /* User in-band request */
         {
            int ret = dec_mmu._local_st.user_callback.func(bits, &dec_mmu._local_st, dec_mmu._local_st.user_callback.data);
            if (ret) return ret;
         } 
		 else if (m>8) /* Invalid mode */
         {
            // speex_notify("Invalid mode encountered. The stream is corrupted.");
            return -2;
         }
      
      } while (m>8);

      /* Get the sub-mode that was used */
      dec_mmu._local_st.submodeID = m;

      }

   }
   
	// start section - around 1 ms

   /* Shift all buffers by one frame */
   SPEEX_MOVE(dec_mmu._local_st.excBuf, dec_mmu._local_st.excBuf+NB_FRAME_SIZE, 2*NB_PITCH_END + NB_SUBFRAME_SIZE + 12);

   /* If null mode (no transmission), just set a couple things to zero - not executed*/
   if (dec_mmu._local_st.submodes[dec_mmu._local_st.submodeID] == NULL)
   {
      bw_lpc(QCONST16(0.93f,15), dec_mmu._local_st.interp_qlpc, dec_mmu._lpc, NB_LPC_SIZE);
      {
         spx_word16_t innov_gain=0;
         /* FIXME: This was innov, not exc */
         innov_gain = compute_rms16(dec_mmu._local_st.exc, NB_FRAME_SIZE);
         for (i=0;i<NB_FRAME_SIZE;i++) dec_mmu._local_st.exc[i]=speex_rand(innov_gain, &dec_mmu._local_st.seed);
      }


      dec_mmu._local_st.first=1;

      /* Final signal synthesis from excitation */
      // iir_mem16(st->exc, dec_mmu._lpc, out, NB_FRAME_SIZE, NB_LPC_SIZE, st->mem_sp);
	  iir_mem16_160_10(dec_mmu._local_st.exc, dec_mmu._lpc, out, dec_mmu._local_st.mem_sp);
	  
      dec_mmu._local_st.count_lost=0;
      return 0;
   }

   /* Unquantize LSPs */
   DEC_SUBMODE(lsp_unquant)(dec_mmu._qlsp, NB_LPC_SIZE, bits);

   /*Damp memory if a frame was lost and the LSP changed too much - not executed*/
   if (dec_mmu._local_st.count_lost)
   {
      spx_word16_t fact;
      spx_word32_t lsp_dist=0;
      for (i=0;i<NB_LPC_SIZE;i++) lsp_dist = ADD32(lsp_dist, EXTEND32(ABS(dec_mmu._local_st.old_qlsp[i] - dec_mmu._qlsp[i])));
      fact = SHR16(19661,SHR32(lsp_dist,LSP_SHIFT+2));      
      for (i=0;i<NB_LPC_SIZE;i++) dec_mmu._local_st.mem_sp[i] = MULT16_32_Q15(fact,dec_mmu._local_st.mem_sp[i]);
   }


   /* Handle first frame and lost-packet case */
   if (dec_mmu._local_st.first || dec_mmu._local_st.count_lost)
   {
      // for (i=0;i<NB_LPC_SIZE;i++) st->old_qlsp[i] = dec_mmu._qlsp[i];
      SPEEX_COPY( dec_mmu._local_st.old_qlsp, dec_mmu._qlsp, NB_LPC_SIZE );
   }

   /* Get open-loop pitch estimation for low bit-rate pitch coding - 6 kbps and below*/
   if (DEC_SUBMODE(lbr_pitch)!=-1)
   {
      ol_pitch = NB_PITCH_START+speex_bits_unpack_unsigned(bits, 7);
   } 
   
   /* 5 kbps and below */
   if (DEC_SUBMODE(forced_pitch_gain))
   {
      int quant;
      quant = speex_bits_unpack_unsigned(bits, 4);
      ol_pitch_coef=MULT16_16_P15(QCONST16(0.066667,15),SHL16(quant,GAIN_SHIFT));
   }
   
   /* Get global excitation gain */
   {
      int qe;
      qe = speex_bits_unpack_unsigned(bits, 5);
      /* FIXME: Perhaps we could slightly lower the gain here when the output is going to saturate? */
      ol_gain = MULT16_32_Q15(28406,ol_gain_table[qe]);
   }

   if (dec_mmu._local_st.submodeID==1)
   {
      int extra;
      extra = speex_bits_unpack_unsigned(bits, 4);

      if (extra==15) dec_mmu._local_st.dtx_enabled=1;
      else dec_mmu._local_st.dtx_enabled=0;
   }
   if (dec_mmu._local_st.submodeID>1)  dec_mmu._local_st.dtx_enabled=0;

   offset = 0;

   /*Loop on subframes time = 11-12 ms */
   for (sub=0;sub<NB_TOTAL_SUBFRAMES;sub++)
   {
      spx_word16_t *exc;
      spx_word16_t *sp;
      spx_word16_t *innov_save = NULL;
      spx_word16_t tmp;

      /* Offset relative to start of frame */
      // offset = NB_SUBFRAME_SIZE*sub;

      /* Excitation */
      exc=dec_mmu._local_st.exc+offset;

      /* Original signal */
      sp=out+offset;
      if (dec_mmu._local_st.innov_save) innov_save = dec_mmu._local_st.innov_save+offset;

      /* Reset excitation */
      SPEEX_MEMSET(exc, 0, NB_SUBFRAME_SIZE);

      /*Adaptive codebook contribution*/
      speex_assert (DEC_SUBMODE(ltp_unquant));
      {
         int pit_min, pit_max;
         /* Handle pitch constraints if any */
         if (DEC_SUBMODE(lbr_pitch) != -1)
         {
		 	// not executed for 8kpbs and higher
            int margin;
            margin = DEC_SUBMODE(lbr_pitch);
            if (margin)
            {
/* GT - need optimization?
               if (ol_pitch < NB_PITCH_START+margin-1)
                  ol_pitch=NB_PITCH_START+margin-1;
               if (ol_pitch > NB_PITCH_END-margin)
                  ol_pitch=NB_PITCH_END-margin;
               pit_min = ol_pitch-margin+1;
               pit_max = ol_pitch+margin;
*/
               pit_min = ol_pitch-margin+1;
               if (pit_min < NB_PITCH_START) pit_min = NB_PITCH_START;
               pit_max = ol_pitch+margin;
               if (pit_max > NB_PITCH_END) pit_max = NB_PITCH_END;
            } 
			else 
			{
               pit_min = pit_max = ol_pitch;
            }
         } 
		 else 
		 {
            pit_min = NB_PITCH_START;
            pit_max = NB_PITCH_END;
         }

         DEC_SUBMODE(ltp_unquant)(	exc, 
		 							dec_mmu._exc32, 
		 							pit_min, 
		 							pit_max, 
		 							ol_pitch_coef, 
		 							DEC_SUBMODE(ltp_params), 
                 					NB_SUBFRAME_SIZE, 
                 					&pitch, 
                 					&pitch_gain[0], 
                 					bits, 
                 					NULL, 
                 					dec_mmu._local_st.count_lost, 
                 					offset, 
                 					dec_mmu._local_st.last_pitch_gain, 
                 					0);

         /* Ensuring that things aren't blowing up as would happen if e.g. an encoder is 
         crafting packets to make us produce NaNs and slow down the decoder (vague DoS threat).
         We can probably be even more aggressive and limit to 15000 or so. */
         sanitize_values32(	dec_mmu._exc32, 
         					NEG32(QCONST32(32000,SIG_SHIFT-1)), 
         					QCONST32(32000,SIG_SHIFT-1), 
         					NB_SUBFRAME_SIZE);
         
         tmp = gain_3tap_to_1tap(pitch_gain);

         pitch_average += tmp;
         if (((tmp>best_pitch_gain)&&
		 	  (ABS(2*best_pitch-pitch)>=3)&&
		 	  (ABS(3*best_pitch-pitch)>=4)&&
		 	  (ABS(4*best_pitch-pitch)>=5)) ||
             ((tmp>MULT16_16_Q15(QCONST16(.6,15),best_pitch_gain))&&
              ((ABS(best_pitch-2*pitch)<3) || 
               (ABS(best_pitch-3*pitch)<4) || 
               (ABS(best_pitch-4*pitch)<5))) ||
             ((MULT16_16_Q15(QCONST16(.67,15),tmp)>best_pitch_gain)&&
              (ABS(2*best_pitch-pitch)<3)||
              (ABS(3*best_pitch-pitch)<4)||
              (ABS(4*best_pitch-pitch)<5)))
         {
            best_pitch = pitch;
            if (tmp > best_pitch_gain) best_pitch_gain = tmp;
         }
      }
      
      /* Unquantize the innovation */
      {
         int q_energy;
         spx_word32_t ener;
         
         SPEEX_MEMSET(dec_mmu._innov, 0, NB_SUBFRAME_SIZE);

         /* Decode sub-frame gain correction */
         if (DEC_SUBMODE(have_subframe_gain)==3)
         {
		 	// for bitrates of 15kbps and higher
            q_energy = speex_bits_unpack_unsigned(bits, 3);
            ener = MULT16_32_Q14(exc_gain_quant_scal3[q_energy],ol_gain);
         } 
		 else if (DEC_SUBMODE(have_subframe_gain)==1)
         {
		 	// 5-8 kbps
            q_energy = speex_bits_unpack_unsigned(bits, 1);
            ener = MULT16_32_Q14(exc_gain_quant_scal1[q_energy],ol_gain);
         } 
		 else 
		 {
		 	// below 5 kbps
            ener = ol_gain;
         }
                  
         speex_assert (DEC_SUBMODE(innovation_unquant));
         {
            /*Fixed codebook contribution*/
            DEC_SUBMODE(innovation_unquant)(dec_mmu._innov, 
            								DEC_SUBMODE(innovation_params), 
            								NB_SUBFRAME_SIZE, 
            								bits, 
            								NULL, 
            								&dec_mmu._local_st.seed);
			
            /* De-normalize innovation and update excitation */

            signal_mul(dec_mmu._innov, dec_mmu._innov, ener, NB_SUBFRAME_SIZE);
			// signal_mul_asm(dec_mmu._innov, dec_mmu._innov, ener, NB_SUBFRAME_SIZE);

            /* Decode second codebook (only for some modes) - only for 24 kpbs */
            if (DEC_SUBMODE(double_codebook))
            {
               char *tmp_stack=NULL;

			   SPEEX_MEMSET(dec_mmu._innov2, 0, NB_SUBFRAME_SIZE);
			   
               DEC_SUBMODE(innovation_unquant)(dec_mmu._innov2, DEC_SUBMODE(innovation_params), NB_SUBFRAME_SIZE, bits, NULL, &dec_mmu._local_st.seed);
			   
               signal_mul(dec_mmu._innov2, dec_mmu._innov2, MULT16_32_Q15(QCONST16(0.454545f,15),ener), NB_SUBFRAME_SIZE);

               for (i=0;i<NB_SUBFRAME_SIZE;i++) 
			      dec_mmu._innov[i] = ADD32(dec_mmu._innov[i], dec_mmu._innov2[i]);
               // stack = tmp_stack;
            }
			/************************************************/
			
            for (i=0;i<NB_SUBFRAME_SIZE;i++)
               exc[i]=EXTRACT16(SATURATE32(PSHR32(ADD32(SHL32(dec_mmu._exc32[i],1),dec_mmu._innov[i]),SIG_SHIFT),32767));
			
            if (innov_save)
            {
               for (i=0;i<NB_SUBFRAME_SIZE;i++)
			   	   innov_save[i] = EXTRACT16(PSHR32(dec_mmu._innov[i], SIG_SHIFT));
            }
         }

         /*Vocoder mode*/
         if (dec_mmu._local_st.submodeID==1) 
         {
		 	#if 0
		 	SPEEX_MEMSET(exc, 0, NB_SUBFRAME_SIZE);
			nb_decode_vocoder_submode1( exc, ol_pitch, ol_pitch_coef, ol_gain );
			#else
            spx_word16_t g=ol_pitch_coef;
            g=MULT16_16_P14(QCONST16(1.5f,14),(g-QCONST16(.2f,6)));
            if (g<0) g=0;
            if (g>GAIN_SCALING) g=GAIN_SCALING;
            
            SPEEX_MEMSET(exc, 0, NB_SUBFRAME_SIZE);
            while (dec_mmu._local_st.voc_offset<NB_SUBFRAME_SIZE)
            {
               /* exc[st->voc_offset]= g*sqrt(2*ol_pitch)*ol_gain;
                  Not quite sure why we need the factor of two in the sqrt */
               if (dec_mmu._local_st.voc_offset>=0)
                  exc[dec_mmu._local_st.voc_offset]=MULT16_16(spx_sqrt(MULT16_16_16(2,ol_pitch)),EXTRACT16(PSHR32(MULT16_16(g,PSHR32(ol_gain,SIG_SHIFT)),6)));
               dec_mmu._local_st.voc_offset+=ol_pitch;
            }
            dec_mmu._local_st.voc_offset -= NB_SUBFRAME_SIZE;
            
            for (i=0;i<NB_SUBFRAME_SIZE;i++)
            {
               spx_word16_t exci=exc[i];
               exc[i]= ADD16(ADD16(MULT16_16_Q15(QCONST16(.7f,15),exc[i]) , MULT16_16_Q15(QCONST16(.3f,15),dec_mmu._local_st.voc_m1)),
                             SUB16(MULT16_16_Q15(Q15_ONE-MULT16_16_16(QCONST16(.85f,9),g),EXTRACT16(PSHR32(dec_mmu._innov[i],SIG_SHIFT))),
                                   MULT16_16_Q15(MULT16_16_16(QCONST16(.15f,9),g),EXTRACT16(PSHR32(dec_mmu._local_st.voc_m2,SIG_SHIFT)))
                                  ));
               dec_mmu._local_st.voc_m1 = exci;
               dec_mmu._local_st.voc_m2=dec_mmu._innov[i];
               dec_mmu._local_st.voc_mean = EXTRACT16(PSHR32(ADD32(MULT16_16(QCONST16(.8f,15),dec_mmu._local_st.voc_mean), MULT16_16(QCONST16(.2f,15),exc[i])), 15));
               exc[i]-=dec_mmu._local_st.voc_mean;
            }

			#endif
         }
      }

	  offset += NB_SUBFRAME_SIZE;
   }

   #if 0
   // this little piece of code takes 39-56 ms
   if (st->lpc_enh_enabled && SUBMODE(comb_gain)>0 && !st->count_lost)
   {   	
      multicomb(st->exc-NB_SUBFRAME_SIZE, out,                    st->interp_qlpc, NB_LPC_SIZE, 2*NB_SUBFRAME_SIZE, best_pitch, 40, SUBMODE(comb_gain), NULL);
      multicomb(st->exc+NB_SUBFRAME_SIZE, out+2*NB_SUBFRAME_SIZE, st->interp_qlpc, NB_LPC_SIZE, 2*NB_SUBFRAME_SIZE, best_pitch, 40, SUBMODE(comb_gain), NULL);
   } 
   else 
   {
      SPEEX_COPY(out, &dec_mmu._local_st.exc[-NB_SUBFRAME_SIZE], NB_FRAME_SIZE);
   }
   #endif
   SPEEX_COPY(out, &dec_mmu._local_st.exc[-NB_SUBFRAME_SIZE], NB_FRAME_SIZE);

   /* If the last packet was lost, re-scale the excitation to obtain the same energy as encoded in ol_gain - not executed*/
   if (dec_mmu._local_st.count_lost) 
   {
      spx_word16_t exc_ener;
      spx_word32_t gain32;
      spx_word16_t gain;

      exc_ener = compute_rms16 (dec_mmu._local_st.exc, NB_FRAME_SIZE);
      gain32 = PDIV32(ol_gain, ADD16(exc_ener,1));

      if (gain32 > 32767) gain32 = 32767;
      gain = EXTRACT16(gain32);

      for (i=0;i<NB_FRAME_SIZE;i++)
      {
         dec_mmu._local_st.exc[i] = MULT16_16_Q14(gain, dec_mmu._local_st.exc[i]);
         out[i]=dec_mmu._local_st.exc[i-NB_SUBFRAME_SIZE];
      }
   }

   /*Loop on subframes - 15-16 ms, 4 per loop */
   for (sub=0;sub<NB_TOTAL_SUBFRAMES;sub++)
   {
      int offset;
      spx_word16_t *sp;
      spx_word16_t *exc;
	  
      /* Offset relative to start of frame */
      offset = NB_SUBFRAME_SIZE*sub;
	  
      /* Original signal */
      sp=out+offset;
	  
      /* Excitation */
      exc=dec_mmu._local_st.exc+offset;

      /* LSP interpolation (quantized and unquantized) */
      lsp_interpolate(dec_mmu._local_st.old_qlsp, dec_mmu._qlsp, dec_mmu._interp_qlsp, NB_LPC_SIZE, sub, NB_TOTAL_SUBFRAMES);

      /* Make sure the LSP's are stable */
      lsp_enforce_margin(dec_mmu._interp_qlsp, NB_LPC_SIZE, LSP_MARGIN);

      /* Compute interpolated LPCs (unquantized) */
      lsp_to_lpc(dec_mmu._interp_qlsp, dec_mmu._ak, NB_LPC_SIZE, NULL);

      /* Compute analysis filter at w=pi */
      {
         spx_word32_t pi_g=LPC_SCALING;
		 
         for (i=0;i<NB_LPC_SIZE;i+=2)
         {
            /*pi_g += -st->interp_qlpc[i] +  st->interp_qlpc[i+1];*/
            pi_g = ADD32(pi_g, SUB32(EXTEND32(dec_mmu._ak[i+1]),EXTEND32(dec_mmu._ak[i])));
         }
         dec_mmu._local_st.pi_gain[sub] = pi_g;
      }

	  // iir_mem16(sp, st->interp_qlpc, sp, NB_SUBFRAME_SIZE, NB_LPC_SIZE, st->mem_sp);
      iir_mem16_40_10(sp, dec_mmu._local_st.interp_qlpc, sp, dec_mmu._local_st.mem_sp);
      
      // for (i=0;i<NB_LPC_SIZE;i++) dec_mmu._local_st.interp_qlpc[i] = dec_mmu._ak[i];
      SPEEX_COPY( dec_mmu._local_st.interp_qlpc, dec_mmu._ak, NB_LPC_SIZE );

   }


   // highpass filter takes 8 ms
   // highpass(out, out, NB_FRAME_SIZE, HIGHPASS_NARROWBAND|HIGHPASS_OUTPUT, st->mem_hp);
   /*for (i=0;i<NB_FRAME_SIZE;i++)
     printf ("%d\n", (int)st->frame[i]);*/
     
	// final section, less than 1 ms

   /* Tracking output level */
   dec_mmu._local_st.level = 1+PSHR32(ol_gain,SIG_SHIFT);
   dec_mmu._local_st.max_level = MAX16(MULT16_16_Q15(QCONST16(.99f,15), dec_mmu._local_st.max_level), dec_mmu._local_st.level);
   dec_mmu._local_st.min_level = MIN16(ADD16(1,MULT16_16_Q14(QCONST16(1.01f,14), dec_mmu._local_st.min_level)), dec_mmu._local_st.level);

   if (dec_mmu._local_st.max_level < dec_mmu._local_st.min_level+1) 
   		dec_mmu._local_st.max_level = dec_mmu._local_st.min_level+1;
   /*printf ("%f %f %f %d\n", og, st->min_level, st->max_level, update);*/
   
   /* Store the LSPs for interpolation in the next frame */
   // for (i=0;i<NB_LPC_SIZE;i++) st->old_qlsp[i] = dec_mmu._qlsp[i];
   SPEEX_COPY( dec_mmu._local_st.old_qlsp, dec_mmu._qlsp, NB_LPC_SIZE );

   /* The next frame will not be the first (Duh!) */
   dec_mmu._local_st.first = 0;
   dec_mmu._local_st.count_lost=0;
   dec_mmu._local_st.last_pitch = best_pitch;
   dec_mmu._local_st.last_pitch_gain = PSHR16(pitch_average,2);
   dec_mmu._local_st.pitch_gain_buf[dec_mmu._local_st.pitch_gain_buf_idx++] = dec_mmu._local_st.last_pitch_gain;

   if (dec_mmu._local_st.pitch_gain_buf_idx > 2) dec_mmu._local_st.pitch_gain_buf_idx = 0;

   dec_mmu._local_st.last_ol_gain = ol_gain;

   return 0;
}

int nb_encoder_ctl(void *state, int request, void *ptr)
{
   EncState *st;
   st=(EncState*)state;     
   switch(request)
   {
   case SPEEX_GET_FRAME_SIZE:
      (*(spx_int32_t*)ptr) = NB_FRAME_SIZE;
      break;

   case SPEEX_SET_QUALITY:
      {
         int quality = (*(spx_int32_t*)ptr);
         if (quality < 0) quality = 0;
         if (quality > 10) quality = 10;
         st->submodeSelect = st->submodeID = ((const SpeexNBMode*)(st->mode->mode))->quality_map[quality];
      }
      break;

   case SPEEX_SET_BITRATE:
      {
         spx_int32_t i=10;
         spx_int32_t rate, target;
         target = (*(spx_int32_t*)ptr);
         while (i>=0)
         {
            nb_encoder_ctl(st, SPEEX_SET_QUALITY, &i);
            nb_encoder_ctl(st, SPEEX_GET_BITRATE, &rate);
            if (rate <= target)
               break;
            i--;
         }
      }
      break;
   case SPEEX_GET_BITRATE:
      if (st->submodes[st->submodeID])
         (*(spx_int32_t*)ptr) = st->sampling_rate*SUBMODE(bits_per_frame)/NB_FRAME_SIZE;
      else
         (*(spx_int32_t*)ptr) = st->sampling_rate*(NB_SUBMODE_BITS+1)/NB_FRAME_SIZE;
      break;
   default:
      return -1;
   }
   return 0;
}

int nb_decoder_ctl(void *state, int request, void *ptr)
{
   DecState *st;
   st=(DecState*)state;
   switch(request)
   {
   case SPEEX_GET_FRAME_SIZE:
      (*(spx_int32_t*)ptr) = NB_FRAME_SIZE;
      break;
   case SPEEX_GET_BITRATE:
      if (st->submodes[st->submodeID])
         (*(spx_int32_t*)ptr) = st->sampling_rate*SUBMODE(bits_per_frame)/NB_FRAME_SIZE;
      else
         (*(spx_int32_t*)ptr) = st->sampling_rate*(NB_SUBMODE_BITS+1)/NB_FRAME_SIZE;
      break;
   default:
      return -1;
   }
   return 0;
}

int speex_inband_handler(SpeexBits *bits, SpeexCallback *callback_list, void *state)
{
   int id;
   SpeexCallback *callback;
   /*speex_bits_advance(bits, 5);*/
   id=speex_bits_unpack_unsigned(bits, 4);
   callback = callback_list+id;

   if (callback->func)
   {
      return callback->func(bits, state, callback->data);
   } 
   else
   {
      /*If callback is not registered, skip the right number of bits*/
      int adv;
      
	  if (id<2)			adv = 1;
      else if (id<8)	adv = 4;
      else if (id<10)   adv = 8;
      else if (id<12)   adv = 16;
      else if (id<14)   adv = 32;
      else              adv = 64;

      speex_bits_advance(bits, adv);
   }
   return 0;
}

/* Default handler for user callbacks: skip it */
int speex_default_user_handler(SpeexBits *bits, void *state, void *data)
{
   int req_size = speex_bits_unpack_unsigned(bits, 4);
   speex_bits_advance(bits, 5+8*req_size);
   return 0;
}


void nb_decode_vocoder_submode1( spx_word16_t * exc, int ol_pitch, spx_word16_t ol_pitch_coef, spx_word32_t ol_gain )
{
	int i;
	
	spx_word16_t exci;
    spx_word16_t g=ol_pitch_coef;

	spx_word16_t tmp1;
	spx_word16_t tmp2;
	spx_word16_t tmp3;
	spx_word16_t tmp4;

	spx_sig_t * ptr_inov = dec_mmu._innov;
    
    tmp1 = ol_pitch_coef - 1;
	tmp1 = 21 * tmp1;
	tmp1 = 8192 + tmp1;
	g = tmp1 >> 14;
	
    if (g<0) g=0;
    if (g>GAIN_SCALING) g=GAIN_SCALING;
    
    while (1)
    {
       /* exc[st->voc_offset]= g*sqrt(2*ol_pitch)*ol_gain;
          Not quite sure why we need the factor of two in the sqrt */
          
       if (dec_mmu._local_st.voc_offset>=0)
       {
			tmp1 = PSHR32(ol_gain,14);	// SIG_SHIFT
			tmp1 = g * tmp1;
			tmp1 = PSHR32( tmp1, 6 );
			tmp1 = tmp1 & 0x0FFFF;
			tmp2 = 2 * ol_pitch;
			
			exc[dec_mmu._local_st.voc_offset] = spx_sqrt( tmp2 ) * tmp1;
       }
	   
       dec_mmu._local_st.voc_offset+=ol_pitch;

	   if( dec_mmu._local_st.voc_offset >= NB_SUBFRAME_SIZE ) break;
    }
	
    dec_mmu._local_st.voc_offset -= NB_SUBFRAME_SIZE;

    i = 0;
    while( 1 )
    {
	   
	   tmp1 = ( 435 * g );                                     		   // Q15_ONE - ( QCONST16(.85f,9) * g );
	   tmp1 = 32767 - tmp1;
	   tmp2 = ( spx_word16_t )PSHR32( (*ptr_inov), 14 );         // SIG_SHIFT
	   tmp3 = ( tmp1 * tmp2 ) >> 15;

	   tmp1 = ( 77 * g ) >> 15;  									   // ( QCONST16(.15f,9) * g ) >> 15;
	   tmp2 = ( spx_word16_t )PSHR32( dec_mmu._local_st.voc_m2, 14 );  // SIG_SHIFT
	   tmp4 = ( tmp1 * tmp2 ); //  >> 15;

	   tmp3 = tmp3 - ( tmp4 >> 5 );

	   tmp1 = ( 229381 * (*exc)      ) >> 15; 				    // QCONST16(.7f,15)
	   tmp2 = ( 9830   * dec_mmu._local_st.voc_m1 );//>> 15; 	// QCONST16(.3f,15)

	   tmp4 = tmp1 - ( tmp2 >> 15 );

       exci   = (*exc);
	   (*exc) = tmp3 + tmp4;
	   

       dec_mmu._local_st.voc_m1 = exci;
       dec_mmu._local_st.voc_m2 = (*ptr_inov);

	   tmp1 = ( 12 * dec_mmu._local_st.voc_mean 	); // QCONST16(.8f,15)
	   tmp2 = ( 3  * (*exc)       				    ); // QCONST16(.2f,15)
	   tmp3 = tmp1 + tmp2;
	   
	   dec_mmu._local_st.voc_mean = ( spx_word16_t )PSHR32( tmp3, 15 );
	   
       (*exc) -= dec_mmu._local_st.voc_mean;

	   i++;
	   exc++;
	   ptr_inov++;
	   
	   if( i >= NB_SUBFRAME_SIZE ) break;
	   
    }
}



