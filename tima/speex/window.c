/* Copyright (C) 2006 Jean-Marc Valin 
   File: window.c

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
#include "arch.h"

const spx_word16_t lag_window[11] = {
   16384, 16337, 16199, 15970, 15656, 15260, 14790, 14254, 13659, 13015, 12330
};

const spx_word16_t lpc_window[200] = {
1310, 1313, 1321, 1333, 1352, 1375, 1403, 1436,
1475, 1518, 1567, 1621, 1679, 1743, 1811, 1884,
1962, 2044, 2132, 2224, 2320, 2421, 2526, 2636,
2750, 2868, 2990, 3116, 3246, 3380, 3518, 3659,
3804, 3952, 4104, 4259, 4417, 4578, 4742, 4909,
5079, 5251, 5425, 5602, 5781, 5963, 6146, 6331,
6518, 6706, 6896, 7087, 7280, 7473, 7668, 7863,
8059, 8256, 8452, 8650, 8847, 9044, 9241, 9438,
9635, 9831, 10026, 10220, 10414, 10606, 10797, 10987,
11176, 11363, 11548, 11731, 11912, 12091, 12268, 12443,
12615, 12785, 12952, 13116, 13277, 13435, 13590, 13742,
13890, 14035, 14176, 14314, 14448, 14578, 14704, 14826,
14944, 15058, 15168, 15273, 15374, 15470, 15562, 15649,
15732, 15810, 15883, 15951, 16015, 16073, 16127, 16175,
16219, 16257, 16291, 16319, 16342, 16360, 16373, 16381,
16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384,
16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384,
16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384,
16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384,
16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384,
16384, 16384, 16384, 16384, 16384, 16384, 16384, 16384,
16384, 16384, 16384, 16361, 16294, 16183, 16028, 15830,
15588, 15304, 14979, 14613, 14207, 13763, 13282, 12766,
12215, 11631, 11016, 10373, 9702, 9007, 8289, 7551,
6797, 6028, 5251, 4470, 3695, 2943, 2248, 1696
};

