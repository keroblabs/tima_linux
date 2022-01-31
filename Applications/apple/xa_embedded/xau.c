/* xa65 - 65xx/65816 cross-assembler and utility suite
 *
 * Copyright (C) 1989-1997 André Fachat (a.fachat@physik.tu-chemnitz.de)
 *
 * Undefined label tracking module (also see xal.c)
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
#include "xau.h"
#include "xah.h"
#include "xal.h"

/*
static int *ulist = NULL;
static int un = 0;
static int um = 0;
*/

int u_label(int labnr) {
	int i;
/*printf("u_label: %d\n",labnr);*/
	if(!afile->ud.ulist) {
	  afile->ud.ulist = (int*)malloc(200*sizeof(int));
	  if(afile->ud.ulist) afile->ud.um=200;
	}

	for(i=0;i<afile->ud.un;i++) {
	  if(afile->ud.ulist[i] == labnr) return i;
	}
	if(afile->ud.un>=afile->ud.um) {
	  afile->ud.um *= 15;
	  afile->ud.um /= 10;
	  afile->ud.ulist = ( int * )realloc(afile->ud.ulist, afile->ud.um * sizeof(int));
	  if(!afile->ud.ulist) {
	    return -1;
	  }
	}
	afile->ud.ulist[afile->ud.un] = labnr;
	return afile->ud.un++;
}
