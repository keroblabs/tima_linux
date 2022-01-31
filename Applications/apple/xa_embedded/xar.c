/* xa65 - 65xx/65816 cross-assembler and utility suite
 *
 * Copyright (C) 1989-1997 André Fachat (a.fachat@physik.tu-chemnitz.de)
 *
 * Relocation module (for relocatable objects)
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

#include "xad.h"
#include "xah.h"
#include "xar.h"
#include "xa.h"
#include "xal.h"
#include "xao.h"
#include "xau.h"
#include "embedded.h"

File *afile = NULL;

int rmode = RMODE_RELOC;

int u_set(int pc, int afl, int label, int l) {
/*printf("set relocation @$%04x, l=%d, afl=%04x, segment=%d, label=%d\n",
					pc, l, afl,segment, label);*/
	if((afl & A_FMASK) == (SEG_UNDEF<<8)) 
	{
		label = u_label(label);		/* set label as undefined */
		if( label == -1 ) return Asm_ErrorOutOfMemory;
	}
	if(segment==SEG_TEXT) return rt_set(pc,afl,l,label);
	if(segment==SEG_DATA) return rd_set(pc,afl,l,label);
	return 0;
}

void r_mode(int m) {
	static int old_segment = SEG_TEXT;
/*printf("setting mode to %s\n",(m==RMODE_RELOC)?"reloc":"abs");*/
	if(rmode!=m) {
	  if(m==RMODE_RELOC) {
	    segment = old_segment;
	  } else {	/* absolute mode */
	    old_segment = segment;
	    segment = SEG_ABS;
	  }
	}
	rmode = m;
}

int rt_set(int pc, int afl, int l, int lab) {
	int p,pp;
	
	if(!rmode) return 0;

	/*printf("set relocation @$%04x, l=%d, afl=%04x\n",pc, l, afl);*/

	if(l==2 && ((afl & A_MASK)!=A_ADR)) {
	  errout(W_BYTRELOC);
	  /*printf("Warning: byte relocation in word value at PC=$%04x!\n",pc);*/
	}
	if(l==1 && ((afl&A_MASK)==A_ADR)) {
	  if((afl & A_FMASK) != (SEG_ZERO<<8)) {
/*printf("afl=%04x\n",afl);*/
	    errout(W_ADRRELOC);
	  }
	  /*printf("Warning: cutting address relocation in byte value at PC=$%04x!\n",pc);*/
	  afl = (afl & (~A_MASK)) | A_LOW;
	}
	
	if(afile->rt.nlist>=afile->rt.mlist) {
	  afile->rt.mlist+=500;
	  afile->rt.rlist=realloc(afile->rt.rlist, afile->rt.mlist*sizeof(relocateInfo));
	}
	if(!afile->rt.rlist) {
	  return Asm_ErrorOutOfMemory;
	}

	afile->rt.rlist[afile->rt.nlist].adr = pc;
	afile->rt.rlist[afile->rt.nlist].afl = afl;
	afile->rt.rlist[afile->rt.nlist].lab = lab;
	afile->rt.rlist[afile->rt.nlist].next= -1;

	/* sorting this into the list is not optimized, to be honest... */
	if(afile->rt.first<0) {
	  afile->rt.first = afile->rt.nlist;
	} else {
	  p=afile->rt.first; pp=-1;
	  while(afile->rt.rlist[p].adr<pc && afile->rt.rlist[p].next>=0) { 
	    pp=p; 
	    p=afile->rt.rlist[p].next; 
	  }
/*
printf("endloop: p=%d(%04x), pp=%d(%04x), nlist=%d(%04x)\n",
		p,p<0?0:afile->rt.rlist[p].adr,pp,pp<0?0:afile->rt.rlist[pp].adr,afile->rt.nlist,afile->rt.nlist<0?0:afile->rt.rlist[afile->rt.nlist].adr);
*/
	  if(afile->rt.rlist[p].next<0 && afile->rt.rlist[p].adr<pc) {
	    afile->rt.rlist[p].next=afile->rt.nlist;
	  } else 
	  if(pp==-1) {
	    afile->rt.rlist[afile->rt.nlist].next = afile->rt.first;
	    afile->rt.first = afile->rt.nlist;
	  } else {
	    afile->rt.rlist[afile->rt.nlist].next = p;
	    afile->rt.rlist[pp].next = afile->rt.nlist;
	  }
	}
	afile->rt.nlist++;

	return 0;
}

void seg_start(int fmode, int t_base, int d_base, int b_base, int z_base,
						int slen, int relmode) {
	afile->fmode = fmode;
	afile->slen = slen;
	afile->relmode = relmode;

	pc[SEG_TEXT] = afile->base[SEG_TEXT] = t_base;
	pc[SEG_DATA] = afile->base[SEG_DATA] = d_base;
	pc[SEG_BSS]  = afile->base[SEG_BSS]  = b_base;
	pc[SEG_ZERO] = afile->base[SEG_ZERO] = z_base;

	afile->old_abspc = pc[SEG_ABS];
	pc[SEG_ABS]  = pc[SEG_TEXT];
}

File *alloc_file(void) {
	File *afile;
	int i;

	afile = (File*)malloc(sizeof(File));
	if(!afile) {
	  return NULL;
	}

	afile->mn.tmp = (signed char *)malloc(TMPMEM);
	if(!afile->mn.tmp) {
	  return NULL;
	}
	afile->mn.tmpz = 0;
	afile->mn.tmpe = 0;

	afile->ud.ulist = NULL; afile->ud.un = afile->ud.um = 0;
	afile->rt.rlist = NULL; afile->rt.first = -1;
	afile->rt.mlist = afile->rt.nlist = 0;
	afile->rd.rlist = NULL; afile->rd.first = -1;
	afile->rd.mlist = afile->rd.nlist = 0;
	afile->fo.olist = NULL;
	afile->fo.mlist = afile->fo.nlist = 0;

	for(i=0;i<256;i++) afile->la.hashindex[i]=0;
	afile->la.lt  = NULL;
	afile->la.lti = 0;
	afile->la.ltm = 0;

	afile->len[SEG_TEXT] = afile->len[SEG_DATA] = 
		afile->len[SEG_BSS] = afile->len[SEG_ZERO] = 0;

	return afile;
}

void seg_pass2(void) {

	pc[SEG_TEXT] = afile->base[SEG_TEXT];
	pc[SEG_DATA] = afile->base[SEG_DATA];
	pc[SEG_BSS]  = afile->base[SEG_BSS];
	pc[SEG_ZERO] = afile->base[SEG_ZERO];

	afile->old_abspc = pc[SEG_ABS];
	pc[SEG_ABS]  = pc[SEG_TEXT];
	//pc[SEG_BASE] = -1;
}
