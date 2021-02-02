// Microsoft version of 'inline'
#define inline __inline

#define FIXED_POINT

// Visual Studio support alloca(), but it always align variables to 16-bit
// boundary, while SSE need 128-bit alignment. So we disable alloca() when
// SSE is enabled.
#ifndef _USE_SSE
#  define USE_ALLOCA
#endif

/* Default to floating point */
#ifndef FIXED_POINT
#  define FLOATING_POINT
#  define USE_SMALLFT
#else
#  define USE_KISS_FFT
#endif

#define DISABLE_FLOAT_API
#define DISABLE_WIDEBAND
#define DISABLE_VBR

