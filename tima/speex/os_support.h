/* Copyright (C) 2007 Jean-Marc Valin
      
   File: os_support.h
   This is the (tiny) OS abstraction layer. Aside from math.h, this is the
   only place where system headers are allowed.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:

   1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

   3. The name of the author may not be used to endorse or promote products
   derived from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
   OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
   INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
   HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
   STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef OS_SUPPORT_H
#define OS_SUPPORT_H

#include "types.h"
#include <stdio.h>
#include <stdlib.h>

#if defined( WIN32 ) || defined (__MACH__) || defined( ARM_STM32F103 ) || defined( ARM_S3C2410 )
#include <string.h>
#else
#include <strings.h>
#endif

#if defined( ARM_S3C2410 )
#include "heap.h"
#endif

#include "speex_config.h"
#ifdef OS_SUPPORT_CUSTOM
#include "os_support_custom.h"
#endif

#if defined( WIN32 )
#include <malloc.h>
#endif

#if !defined( ARM_STM32F103 ) && !defined( ARM_S3C2410 )
#include "memory.h"
#endif

#define ALLOC(var, size, type) var = (type * )alloca(sizeof(type)*(size))

/** Copy n bytes of memory from src to dst. The 0* term provides compile-time type checking  */
#ifndef OVERRIDE_SPEEX_COPY
#define SPEEX_COPY(dst, src, n) (memcpy((dst), (src), (n)*sizeof(*(dst)) + 0*((dst)-(src)) ))
#endif

/** Copy n bytes of memory from src to dst, allowing overlapping regions. The 0* term 
    provides compile-time type checking */
#ifndef OVERRIDE_SPEEX_MOVE
#define SPEEX_MOVE(dst, src, n) (memmove((dst), (src), (n)*sizeof(*(dst)) + 0*((dst)-(src)) ))
#endif

/** Set n bytes of memory to value of c, starting at address s */
#ifndef OVERRIDE_SPEEX_MEMSET
#define SPEEX_MEMSET(dst, c, n) (memset((dst), (c), (n)*sizeof(*(dst))))
#endif

// #define speex_fatal(str) _speex_fatal(str, __FILE__, __LINE__);
// #define speex_assert(cond) {if (!(cond)) {speex_fatal("assertion failed: " #cond);}}
#define speex_assert(cond)

#endif

