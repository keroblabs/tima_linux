/* xa65 - 65xx/65816 cross-assembler and utility suite
 *
 * Copyright (C) 1989-1997 André Fachat (a.fachat@physik.tu-chemnitz.de)
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

#include "xah.h"
#include "xa.h"
#include "xar.h"
#include "embedded.h"

/*
static relocateInfo *rlist = NULL;
static int mlist = 0, nlist = 0;
static int first = -1;
*/

/* int rmode; */
 
int rd_set(int pc, int afl, int l, int lab) {
	int p,pp;

/*	if(!rmode) return 0; */

	/*printf("set relocation @$%04x, l=%d, afl=%04x\n",pc, l, afl);*/

	if(l==2 && ((afl & A_MASK)!=A_ADR)) {
	  errout(W_BYTRELOC);
	  /*printf("Warning: byte relocation in word value at PC=$%04x!\n",pc);*/
	}
	if(l==1 && ((afl&A_MASK)==A_ADR)) {
	  if((afl & A_FMASK) != (SEG_ZERO<<8)) errout(W_ADRRELOC);
	  /*printf("Warning: cutting address relocation in byte value at PC=$%04x!\n",pc);*/
	  afl = (afl & (~A_MASK)) | A_LOW;
	}
	
	if(afile->rd.nlist>=afile->rd.mlist) {
	  afile->rd.mlist+=500;
	  afile->rd.rlist=realloc(afile->rd.rlist, afile->rd.mlist*sizeof(relocateInfo));
	}
	if(!afile->rd.rlist) {
	  return Asm_ErrorOutOfMemory;
	}

	afile->rd.rlist[afile->rd.nlist].adr = pc;
	afile->rd.rlist[afile->rd.nlist].afl = afl;
	afile->rd.rlist[afile->rd.nlist].lab = lab;
	afile->rd.rlist[afile->rd.nlist].next= -1;

	/* sorting this into the list is not optimized, to be honest... */
	if(afile->rd.first<0) {
	  afile->rd.first = afile->rd.nlist;
	} else {
	  p=afile->rd.first; pp=-1;
	  while(afile->rd.rlist[p].adr<pc && afile->rd.rlist[p].next>=0) { 
	    pp=p; 
	    p=afile->rd.rlist[p].next; 
	  }
/*
printf("endloop: p=%d(%04x), pp=%d(%04x), nlist=%d(%04x)\n",
		p,p<0?0:afile->rd.rlist[p].adr,pp,pp<0?0:afile->rd.rlist[pp].adr,afile->rd.nlist,afile->rd.nlist<0?0:afile->rd.rlist[afile->rd.nlist].adr);
*/
	  if(afile->rd.rlist[p].next<0 && afile->rd.rlist[p].adr<pc) {
	    afile->rd.rlist[p].next=afile->rd.nlist;
	  } else
	  if(pp==-1) {
	    afile->rd.rlist[afile->rd.nlist].next = afile->rd.first;
	    afile->rd.first = afile->rd.nlist;
	  } else {
	    afile->rd.rlist[afile->rd.nlist].next = p;
	    afile->rd.rlist[pp].next = afile->rd.nlist;
	  }
	}
	afile->rd.nlist++;

	return 0;
}
