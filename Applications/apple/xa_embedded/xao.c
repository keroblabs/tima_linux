/* xa65 - 65xx/65816 cross-assembler and utility suite
 *
 * Copyright (C) 1989-1997 André Fachat (a.fachat@physik.tu-chemnitz.de)
 *
 * Options module (handles pass options and writing them out to disk)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xah.h"
#include "xar.h"
#include "xa.h"
#include "xat.h"
#include "xao.h"
#include "embedded.h"

/*
static Fopt 	*olist =NULL;
static int 	mlist  =0;
static int 	nlist  =0;
*/

/* sets file option after pass 1 */
int set_fopt(int l, signed char *buf, int reallen) {
/*printf("set_fopt(%s, l=%d\n",buf,l);*/
	while(afile->fo.mlist<=afile->fo.nlist) {
	  afile->fo.mlist +=5;
	  afile->fo.olist = ( Fopt * )realloc(afile->fo.olist, afile->fo.mlist*sizeof(Fopt));
	  if(!afile->fo.olist) {	
		  return Asm_ErrorOutOfMemory;
	  }
	}
	afile->fo.olist[afile->fo.nlist].text=(signed char *)malloc(l);
	if(!afile->fo.olist[afile->fo.nlist].text) {
		  return Asm_ErrorOutOfMemory;
	}
	memcpy(afile->fo.olist[afile->fo.nlist].text, buf, l);
	afile->fo.olist[afile->fo.nlist++].len = reallen;

	return 0;
}

size_t o_length(void) {
	int i;
	size_t n = 0;
	for(i=0;i<afile->fo.nlist;i++) {
/*printf("found option: %s, len=%d, n=%d\n", afile->fo.olist[i].text, afile->fo.olist[i].len,n);*/
	  n += afile->fo.olist[i].len +1;
	}
	return ++n;
}

