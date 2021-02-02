/* Copyright (C) 2002-2006 Jean-Marc Valin*/
/**
  @file speex.h
  @brief Describes the different modes of the codec
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

#ifndef SPEEX_H
#define SPEEX_H
/** @defgroup Codec Speex encoder and decoder
 *  This is the Speex codec itself.
 *  @{
 */

#include "speex_bits.h"
#include "speex_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Values allowed for *ctl() requests */

/** Set enhancement on/off (decoder only) */
#define SPEEX_SET_ENH 0
/** Get enhancement state (decoder only) */
#define SPEEX_GET_ENH 1

/*Would be SPEEX_SET_FRAME_SIZE, but it's (currently) invalid*/
/** Obtain frame size used by encoder/decoder */
#define SPEEX_GET_FRAME_SIZE 3

/** Set quality value */
#define SPEEX_SET_QUALITY 4
/** Get current quality setting */
/* #define SPEEX_GET_QUALITY 5 -- Doesn't make much sense, does it? */

/** Set sub-mode to use */
#define SPEEX_SET_MODE 6
/** Get current sub-mode in use */
#define SPEEX_GET_MODE 7

/** Set low-band sub-mode to use (wideband only)*/
#define SPEEX_SET_LOW_MODE 8
/** Get current low-band mode in use (wideband only)*/
#define SPEEX_GET_LOW_MODE 9

/** Set high-band sub-mode to use (wideband only)*/
#define SPEEX_SET_HIGH_MODE 10
/** Get current high-band mode in use (wideband only)*/
#define SPEEX_GET_HIGH_MODE 11

/** Set VBR on (1) or off (0) */
#define SPEEX_SET_VBR 12
/** Get VBR status (1 for on, 0 for off) */
#define SPEEX_GET_VBR 13

/** Set quality value for VBR encoding (0-10) */
#define SPEEX_SET_VBR_QUALITY 14
/** Get current quality value for VBR encoding (0-10) */
#define SPEEX_GET_VBR_QUALITY 15

/** Set complexity of the encoder (0-10) */
#define SPEEX_SET_COMPLEXITY 16
/** Get current complexity of the encoder (0-10) */
#define SPEEX_GET_COMPLEXITY 17

/** Set bit-rate used by the encoder (or lower) */
#define SPEEX_SET_BITRATE 18
/** Get current bit-rate used by the encoder or decoder */
#define SPEEX_GET_BITRATE 19

/** Define a handler function for in-band Speex request*/
#define SPEEX_SET_HANDLER 20

/** Define a handler function for in-band user-defined request*/
#define SPEEX_SET_USER_HANDLER 22

/** Set sampling rate used in bit-rate computation */
#define SPEEX_SET_SAMPLING_RATE 24
/** Get sampling rate used in bit-rate computation */
#define SPEEX_GET_SAMPLING_RATE 25

/** Reset the encoder/decoder memories to zero*/
#define SPEEX_RESET_STATE 26

/** Get VBR info (mostly used internally) */
#define SPEEX_GET_RELATIVE_QUALITY 29

/** Set VAD status (1 for on, 0 for off) */
#define SPEEX_SET_VAD 30

/** Get VAD status (1 for on, 0 for off) */
#define SPEEX_GET_VAD 31

/** Set Average Bit-Rate (ABR) to n bits per seconds */
#define SPEEX_SET_ABR 32
/** Get Average Bit-Rate (ABR) setting (in bps) */
#define SPEEX_GET_ABR 33

/** Set DTX status (1 for on, 0 for off) */
#define SPEEX_SET_DTX 34
/** Get DTX status (1 for on, 0 for off) */
#define SPEEX_GET_DTX 35

/** Set submode encoding in each frame (1 for yes, 0 for no, setting to no breaks the standard) */
#define SPEEX_SET_SUBMODE_ENCODING 36
/** Get submode encoding in each frame */
#define SPEEX_GET_SUBMODE_ENCODING 37

/*#define SPEEX_SET_LOOKAHEAD 38*/
/** Returns the lookahead used by Speex */
#define SPEEX_GET_LOOKAHEAD 39

/** Sets tuning for packet-loss concealment (expected loss rate) */
#define SPEEX_SET_PLC_TUNING 40
/** Gets tuning for PLC */
#define SPEEX_GET_PLC_TUNING 41

/** Sets the max bit-rate allowed in VBR mode */
#define SPEEX_SET_VBR_MAX_BITRATE 42
/** Gets the max bit-rate allowed in VBR mode */
#define SPEEX_GET_VBR_MAX_BITRATE 43

/** Turn on/off input/output high-pass filtering */
#define SPEEX_SET_HIGHPASS 44
/** Get status of input/output high-pass filtering */
#define SPEEX_GET_HIGHPASS 45

/** Get "activity level" of the last decoded frame, i.e.
    how much damage we cause if we remove the frame */
#define SPEEX_GET_ACTIVITY 47

/* Preserving compatibility:*/
/** Equivalent to SPEEX_SET_ENH */
#define SPEEX_SET_PF 0
/** Equivalent to SPEEX_GET_ENH */
#define SPEEX_GET_PF 1

/* Values allowed for mode queries */
/** Query the frame size of a mode */
#define SPEEX_MODE_FRAME_SIZE 0

/** Query the size of an encoded frame for a particular sub-mode */
#define SPEEX_SUBMODE_BITS_PER_FRAME 1

/** Get major Speex version */
#define SPEEX_LIB_GET_MAJOR_VERSION 1
/** Get minor Speex version */
#define SPEEX_LIB_GET_MINOR_VERSION 3
/** Get micro Speex version */
#define SPEEX_LIB_GET_MICRO_VERSION 5
/** Get extra Speex version */
#define SPEEX_LIB_GET_EXTRA_VERSION 7
/** Get Speex version string */
#define SPEEX_LIB_GET_VERSION_STRING 9

/** Total number of callbacks */
#define SPEEX_MAX_CALLBACKS 16

/* Describes all the in-band requests */

/*These are 1-bit requests*/
/** Request for perceptual enhancement (1 for on, 0 for off) */
#define SPEEX_INBAND_ENH_REQUEST         0
/** Reserved */
#define SPEEX_INBAND_RESERVED1           1

/*These are 4-bit requests*/
/** Request for a mode change */
#define SPEEX_INBAND_MODE_REQUEST        2
/** Request for a low mode change */
#define SPEEX_INBAND_LOW_MODE_REQUEST    3
/** Request for a high mode change */
#define SPEEX_INBAND_HIGH_MODE_REQUEST   4
/** Request for VBR (1 on, 0 off) */
#define SPEEX_INBAND_VBR_QUALITY_REQUEST 5
/** Request to be sent acknowledge */
#define SPEEX_INBAND_ACKNOWLEDGE_REQUEST 6
/** Request for VBR (1 for on, 0 for off) */
#define SPEEX_INBAND_VBR_REQUEST         7

/*These are 8-bit requests*/
/** Send a character in-band */
#define SPEEX_INBAND_CHAR                8
/** Intensity stereo information */
#define SPEEX_INBAND_STEREO              9

/*These are 16-bit requests*/
/** Transmit max bit-rate allowed */
#define SPEEX_INBAND_MAX_BITRATE         10

/*These are 32-bit requests*/
/** Acknowledge packet reception */
#define SPEEX_INBAND_ACKNOWLEDGE         12

struct SpeexMode;


/* Prototypes for mode function pointers */

/** Callback function type */
typedef int (*speex_callback_func)(SpeexBits *bits, void *state, void *data);

/** Struct defining a Speex mode */ 
typedef struct SpeexMode {
   /** Pointer to the low-level mode data */
   const void *mode;

   /** The name of the mode (you should not rely on this to identify the mode)*/
   const char *modeName;

   /**ID of the mode*/
   int modeID;

   /**Version number of the bitstream (incremented every time we break
    bitstream compatibility*/
   int bitstream_version;

} SpeexMode;

/** Callback information */
typedef struct SpeexCallback {
   int callback_id;             /**< ID associated to the callback */
   speex_callback_func func;    /**< Callback handler function */
   void *data;                  /**< Data that will be sent to the handler */
   void *reserved1;             /**< Reserved for future use */
   int   reserved2;             /**< Reserved for future use */
} SpeexCallback;

/** Obtain one of the modes available */
const SpeexMode * speex_lib_get_mode( void );

#ifdef __cplusplus
}
#endif

/** @}*/
#endif
