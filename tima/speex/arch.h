/* Copyright (C) 2003 Jean-Marc Valin */
/**
   @file arch.h
   @brief Various architecture definitions Speex
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

#ifndef ARCH_H
#define ARCH_H

#ifndef SPEEX_VERSION
#define SPEEX_MAJOR_VERSION 1         /**< Major Speex version. */
#define SPEEX_MINOR_VERSION 1         /**< Minor Speex version. */
#define SPEEX_MICRO_VERSION 15        /**< Micro Speex version. */
#define SPEEX_EXTRA_VERSION ""        /**< Extra Speex version. */
#define SPEEX_VERSION "speex-1.2beta3"  /**< Speex version string. */
#endif

/* A couple test to catch stupid option combinations */

#ifdef FLOATING_POINT
#error You cannot compile as floating point and fixed point at the same time
#endif
#ifdef _USE_SSE
#error SSE is only for floating-point
#endif
#if ((defined (ARM4_ASM)||defined (ARM4_ASM)) && defined(BFIN_ASM)) || (defined (ARM4_ASM)&&defined(ARM5E_ASM))
#error Make up your mind. What CPU do you have?
#endif
#ifdef VORBIS_PSYCHO
#error Vorbis-psy model currently not implemented in fixed-point
#endif

#ifndef OUTSIDE_SPEEX
#include "speex_types.h"
#endif

#ifndef ABS
#define ABS(x) ((x) < 0 ? (-(x)) : (x))      /**< Absolute integer value. */
#endif

#define ABS16(x) ((x) < 0 ? (-(x)) : (x))    /**< Absolute 16-bit value.  */
#define MIN16(a,b) ((a) < (b) ? (a) : (b))   /**< Maximum 16-bit value.   */
#define MAX16(a,b) ((a) > (b) ? (a) : (b))   /**< Maximum 16-bit value.   */
#define ABS32(x) ((x) < 0 ? (-(x)) : (x))    /**< Absolute 32-bit value.  */
#define MIN32(a,b) ((a) < (b) ? (a) : (b))   /**< Maximum 32-bit value.   */
#define MAX32(a,b) ((a) > (b) ? (a) : (b))   /**< Maximum 32-bit value.   */

typedef spx_int16_t spx_word16_t;
typedef spx_int32_t   spx_word32_t;
typedef spx_word32_t spx_mem_t;
typedef spx_word16_t spx_coef_t;
typedef spx_word16_t spx_lsp_t;
typedef spx_word32_t spx_sig_t;

#define Q15ONE 32767

#define LPC_SCALING  8192
#define SIG_SCALING  16384
#define LSP_SCALING  8192.
#define GAMMA_SCALING 32768.
#define GAIN_SCALING 64
#define GAIN_SCALING_1 0.015625

#define LPC_SHIFT    13
#define LSP_SHIFT    13
#define SIG_SHIFT    14
#define GAIN_SHIFT   6

#define VERY_SMALL 0
#define VERY_LARGE32 ((spx_word32_t)2147483647)
#define VERY_LARGE16 ((spx_word16_t)32767)
#define Q15_ONE ((spx_word16_t)32767)


#ifdef FIXED_DEBUG
#include "fixed_debug.h"
#else

#include "fixed_generic.h"

#if 0
#ifdef ARM5E_ASM
#include "fixed_arm5e.h"
#elif defined (ARM4_ASM)
#include "fixed_arm4.h"
#elif defined (BFIN_ASM)
#include "fixed_bfin.h"
#endif
#endif

#endif

#if defined (CONFIG_TI_C54X) || defined (CONFIG_TI_C55X)

/* 2 on TI C5x DSP */
#define BYTES_PER_CHAR 2 
#define BITS_PER_CHAR 16
#define LOG2_BITS_PER_CHAR 4

#else 

#define BYTES_PER_CHAR 1
#define BITS_PER_CHAR 8
#define LOG2_BITS_PER_CHAR 3

#endif

#ifdef FIXED_DEBUG
extern long long spx_mips;
#endif

#endif
