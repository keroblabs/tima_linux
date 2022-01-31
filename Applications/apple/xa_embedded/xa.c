/* xa65 - 65xx/65816 cross-assembler and utility suite
 *
 * Copyright (C) 1989-1997 André Fachat (a.fachat@physik.tu-chemnitz.de)
 * maintained by Cameron Kaiser (ckaiser@floodgap.com)
 *
 * Main program
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

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef _MSC_VER
#include <unistd.h>
#endif

/* macros */
#include "xad.h"

/* structs and defs */
#include "xah.h"
#include "xah2.h"

/* exported functions are defined here */
#include "xa.h"
#include "xal.h"
#include "xao.h"
#include "xap.h"
#include "xar.h"
#include "xat.h"
#include "xacharset.h"
#include "embedded.h"

/* ANZERR: total number of errors */
/* ANZWARN: total number of warnings */

#define ANZERR		64
#define ANZWARN		13

/* exported globals */
int ncmos, cmosfl, w65816, n65816;
int masm = 0;
int nolink = 0;
int romable = 0;
int romaddr = 0;
int noglob = 0;
int showblk = 0;
int crossref = 0;
char altppchar;

/* local variables */
static char out[MAXLINE];
static int ner = 0;

static int align = 1;

static int setfext(char *, char *);
static int x_init(void);
static int pass1(void);
static int pass2(void);
static int puttmp(int);
static int puttmps(signed char *, int);
static void chrput(int);
static int _xa_getline(char *);
static void lineout(void);
static long ga_p1(void);
static long gm_p1(void);

/* text */
int memode,xmode;
int segment;
int tlen=0, tbase=0x1000;
int dlen=0, dbase=0x0400;
int blen=0, bbase=0x4000;
int zlen=0, zbase=4;
int fmode=0;
int relmode=0;

int pc[SEG_MAX];	/* segments */

file_hdl_t * file_hdl;
logout_hdl_t logout_hdl;

int assembler_embedded( const char ** filename, int nifiles, void * p_file, void * p_logout, void * p_stats )
{
	int er=1,i;
	char *ifile;
	stats_t * stats;

	file_hdl = ( file_hdl_t * )p_file;
	logout_hdl = ( logout_hdl_t )p_logout;
	stats = ( stats_t * )p_stats;

	altppchar = '#' ; /* i.e., NO alternate char */
	ncmos=0;
	n65816=0;
	cmosfl=1;
	w65816=0;	/* default: 6502 only */

	set_charset("ASCII");
	afile = alloc_file();

	if( afile == NULL )
	{
		return Asm_ErrorAFile;
	}

	if(pp_init())
	{
		return Asm_ErrorPPMemory;
	}
	if(b_init()) 
	{
		return Asm_ErrorBMemory;
	}
	if(l_init()) 
	{
		return Asm_ErrorLMemory;
	}

	if(!x_init())
	{
		/* Pass 1 */
		pc[SEG_ABS]= 0;		/* abs addressing */
		pc[SEG_BASE] = -1;
		seg_start(fmode, tbase, dbase, bbase, zbase, 0, relmode);

		r_mode(RMODE_ABS);

		nolink = 0;

		for (i=0; i<nifiles; i++)
		{
			ifile = ( char * )filename[i]; 
			
			sprintf(out, "Asm65: Pass 1 %s\n", ifile);
			logout_asm(out);

			er=pp_open(ifile);
			if( er == -1 )
			{
				return Asm_ErrorPPFile;
			}
			else if( er == 1 )
			{
				return Asm_ErrorSrcFile;
			}

			puttmp(0);
			puttmp(T_FILE);
			puttmp(0);
			puttmp(0);
			puttmps((signed char*)&ifile, sizeof(filep->fname));

			er=pass1();
			pp_close();
		}

		if((er=b_depth())) {
			sprintf(out,"Still %d blocks open at end of file!\n",er);
			logout_hdl(out);
		}

		if(tbase & (align-1)) {
			sprintf(out,"Warning: text segment ($%04x) start address doesn't align to %d!\n", tbase, align);
			logout_hdl(out);
		}
		if(dbase & (align-1)) {
			sprintf(out,"Warning: data segment ($%04x) start address doesn't align to %d!\n", dbase, align);
			logout_hdl(out);
		}
		if(bbase & (align-1)) {
			sprintf(out,"Warning: bss segment ($%04x) start address doesn't align to %d!\n", bbase, align);
			logout_hdl(out);
		}
		if(zbase & (align-1)) {
			sprintf(out,"Warning: zero segment ($%04x) start address doesn't align to %d!\n", zbase, align);
			logout_hdl(out);
		}
		if (n65816>0)
			fmode |= 0x8000;

		switch(align) {
			case 1: break;
			case 2: fmode |= 1; break;
			case 4: fmode |= 2; break;
			case 256: fmode |=3; break;
		}

		if(!er)
		{
			logout_asm("Asm65: Pass 2\n");
			pc[SEG_BASE] = -1;
			seg_pass2();

			if(!relmode) {
				r_mode(RMODE_ABS);
			} else {
				r_mode(RMODE_RELOC);
				segment = SEG_TEXT;
			}

			er=pass2();
			if( er == Asm_ErrorPass2 )
			{
				return er;
			}
		} 

		// prepare statistics
		if( stats != NULL )
		{
			stats->labels[0] =		ga_lab();	stats->labels[1] =		gm_lab(); 
			stats->label_mem[0] =	(int)ga_labm();	stats->label_mem[1] =	(int)gm_labm();
			stats->pp_defs[0] =		ga_pp();	stats->pp_defs[1] =		gm_pp(); 
			stats->pp_mem[0] =		(int)ga_ppm();	stats->pp_mem[1] =		(int)gm_ppm();
			stats->byte_mem[0] =	(int)ga_p1();	stats->byte_mem[1] =	(int)gm_p1();
			stats->blocks[0] =		ga_blk();	stats->blocks[1] =		0; 
		}
	}

	return Asm_NoError;
}

int h_length(void) {
	return 26+(int)o_length();
}

static int setfext(char *s, char *ext)
{
     int j,i=(int)strlen(s);

     if(i>MAXLINE-5)
          return(-1);
          
     for(j=i-1;j>=0;j--)
     {
          if(s[j]==DIRCHAR)
          {
               strcpy(s+i,ext);
               break;
          }
          if(s[j]=='.')
          {
               strcpy(s+j,ext);
               break;
          }
     }
     if(!j)
          strcpy(s+i,ext);

     return(0);
}

static long ga_p1(void)
{
	return(afile->mn.tmpz);
}
static long gm_p1(void)
{
	return(TMPMEM);
}

static int pass2(void)
{
     int c,er,l,ll,i,al;
     Datei datei;
     signed char *dataseg=NULL;
     signed char *datap=NULL;

     memode=0;
     xmode=0;
     if((dataseg=(signed char*)malloc(dlen))) {
       if(!dataseg) {
		   return Asm_ErrorPass2;
       }
       datap=dataseg;
     }
     filep=&datei;
     afile->mn.tmpe=0L;

     while(ner<20 && afile->mn.tmpe<afile->mn.tmpz)
     {
          l=afile->mn.tmp[afile->mn.tmpe++];
          ll=l;

          if(!l)
          {
               if(afile->mn.tmp[afile->mn.tmpe]==T_LINE)
               {
                    datei.fline=(afile->mn.tmp[afile->mn.tmpe+1]&255)+(afile->mn.tmp[afile->mn.tmpe+2]<<8);
                    afile->mn.tmpe+=3;
               } else
               if(afile->mn.tmp[afile->mn.tmpe]==T_FILE)
               {
                    datei.fline=(afile->mn.tmp[afile->mn.tmpe+1]&255)+(afile->mn.tmp[afile->mn.tmpe+2]<<8);

		    memcpy(&datei.fname, afile->mn.tmp+afile->mn.tmpe+3, sizeof(datei.fname));
                    afile->mn.tmpe+=3+sizeof(datei.fname);
               }
          } else
          {
/* do not attempt address mode optimization on pass 2 */
               er=t_p2(afile->mn.tmp+afile->mn.tmpe,&ll,1,&al);

               if(er==E_NOLINE)
               {
               } else
               if(er==E_OK)
               {
		  if(segment<SEG_DATA) { 
                    for(i=0;i<ll;i++)
                         chrput(afile->mn.tmp[afile->mn.tmpe+i]);
		  } else if (segment==SEG_DATA && datap) {
		    memcpy(datap,afile->mn.tmp+afile->mn.tmpe,ll);
		    datap+=ll;
		  }
               } else
               if(er==E_DSB)
               {
                  c=afile->mn.tmp[afile->mn.tmpe];
		  if(segment<SEG_DATA) {
                    /*printf("E_DSB, ll=%d, l=%d, c=%c\n",ll,l,afile->mn.tmp[afile->mn.tmpe]);*/
                    for(i=0;i<ll;i++)
                         chrput(c);
		  } else if (segment==SEG_DATA && datap) {
		    memset(datap, c, ll);
		    datap+=ll;
		  }
		} else {
                    errout(er);
               }
          }
          afile->mn.tmpe+=abs(l);
     }

     return(ner);
}     
     

static int pass1(void)
{
     signed char o[MAXLINE];
     int l,er,temp_er,al;

     memode=0;
     xmode=0;
     tlen=0;
     ner=0;

	temp_er = 0;

/*FIXIT*/
     while(!(er=_xa_getline(s)))
     {         
          er=t_p1((signed char*)s,o,&l,&al);
	  switch(segment) {
	    case SEG_ABS:
	    case SEG_TEXT: tlen += al; break;
	    case SEG_DATA: dlen += al; break;
	    case SEG_BSS : blen += al; break;
	    case SEG_ZERO: zlen += al; break;
	  }

          /*printf(": er= %d, l=%d, tmpz=%d\n",er,l,tmpz); */

          if(l)
          {
            if(er)
            {
               if(er==E_OKDEF)
               {
                    if(!(er=puttmp(l)))
                         er=puttmps(o,l);
               } else
               if(er==E_NOLINE)
                    er=E_OK;
            } else
            {
               if(!(er=puttmp(-l)))
                    er=puttmps(o,l);
            }
          }
          if(er)
          {
               lineout();
               errout(er);
          }

/*          printf("tmpz =%d\n",afile->mn.tmpz);
*/
     } 

     if(er!=E_EOF) {
	fprintf(stderr, "foul through\n");
          errout(er);
	}

          

/*     { int i; printf("Pass 1 \n");
     for(i=0;i<afile->mn.tmpz;i++)
          fprintf(stderr, " %02x",255 & afile->mn.tmp[i]);
     getchar();}
*/
     return(ner);
}

/*
static char *ertxt[] = { "Syntax","Label definiert",
          "Label nicht definiert","Labeltabelle voll",
          "Label erwartet","Speicher voll","Illegaler Opcode",
          "Falsche Adressierungsart","Branch ausserhalb des Bereichs",
          "Ueberlauf","Division durch Null","Pseudo-Opcode erwartet",
          "Block-Stack-Ueberlauf","Datei nicht gefunden",
          "End of File","Block-Struktur nicht abgeschlossen",
          "NoBlk","NoKey","NoLine","OKDef","DSB","NewLine",
          "NewFile","CMOS-Befehl","pp:Falsche Anzahl Parameter" };
*/
static char *ertxt[] = {
	"Syntax",
	"Label already defined",
        "Label not defined",
	"Label table full",
        "Label expected",
	"Out of memory",
	"Illegal opcode",
        "Wrong addressing mode",
	"Branch out of range",
        "Overflow",
	"Division by zero",
	"Pseudo-opcode expected",
        "Block stack overflow",
	"File not found",
        "End of file",
	"Unmatched block close",
        "NoBlk",
	"NoKey",
	"NoLine",
	"OKDef",
	"DSB",
	"NewLine",
        "NewFile",
	"CMOS-Befehl",
	"pp:Wrong parameter count",
	"Illegal pointer arithmetic", 
	"Illegal segment",
	"File header option too long",
	"File option not at file start (when ROM-able)",
	"Illegal align value",
        "65816 mode used/required",
	"Exceeded recursion limit for label evaluation",
	"Unresolved preprocessor directive at end of file",
	"Data underflow",
	"Illegal quantity",
	".bin",
/* placeholders for future fatal errors */
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
		"",
/* warnings */
	  "Cutting word relocation in byte value",
	  "Byte relocation in word value",
	  "Illegal pointer arithmetic",
	  "Address access to low or high byte pointer",
	  "High byte access to low byte pointer",
	  "Low byte access to high byte pointer",
	  "Can't optimize forward-defined label; using absolute addressing",
	  "Open preprocessor directive at end of file (intentional?)",
	  "Included binary data exceeds 64KB",
	  "Included binary data exceeds 16MB",
/* more placeholders */
		"",
		"",
		"",

 };

static int gl;
static int gf;  

static int x_init(void)
{
	return 0;
#if 0
     int er=0;
     /*er=m_alloc(TMPMEM,&tmp);*/
     afile->mn.tmp=malloc(TMPMEM);
     if(!afile->mn.tmp) er=E_NOMEM;
     afile->mn.tmpz=0L;
     return(er);
#endif
}

static int puttmp(int c)
{
     int er=E_NOMEM;
/*printf("puttmp: afile=%p, tmp=%p, tmpz=%d\n",afile, afile?afile->mn.tmp:0, afile?afile->mn.tmpz:0);*/
     if(afile->mn.tmpz<TMPMEM)
     {
          afile->mn.tmp[afile->mn.tmpz++]=c;
          er=E_OK;
     }
     return(er);
}

static int puttmps(signed char *s, int l)
{
     int i=0,er=E_NOMEM;
     
     if(afile->mn.tmpz+l<TMPMEM)
     {
          while(i<l)
               afile->mn.tmp[afile->mn.tmpz++]=s[i++];

          er=E_OK;
     }
     return(er);
}

static char l[MAXLINE];

static int _xa_getline(char *s)
{
     static int ec;

     static int i,c;
     int hkfl,j,comcom;

     j=hkfl=comcom=0;
     ec=E_OK;

     if(!gl)
     {
          do
          {
               ec=pgetline(l);
               i=0;
               while(l[i]==' ')
                    i++;
               while(l[i]!='\0' && isdigit(l[i]))
                    i++;
               gf=1;

               if(ec==E_NEWLINE)
               {
                    puttmp(0);
                    puttmp(T_LINE);
                    puttmp((filep->fline)&255);
                    puttmp(((filep->fline)>>8)&255);
		ec=E_OK;

               }
		else
               if(ec==E_NEWFILE)
               {
                    puttmp(0);
                    puttmp(T_FILE);
                    puttmp((filep->fline)&255);
                    puttmp(((filep->fline)>>8)&255);
		    puttmps((signed char*)&(filep->fname), sizeof(filep->fname));
/*
                    puttmps((signed char*)filep->fname,
					1+(int)strlen(filep->fname));
*/
                    ec=E_OK;
               }
          } while(!ec && l[i]=='\0');
     }

     gl=0;
     if(!ec || ec==E_EOF)
     {
          do {
               c=s[j]=l[i++];

               if (c=='\"')
                    hkfl^=1;
		if (c==';' && !hkfl)
			comcom = 1;
               if (c=='\0') 
                    break;	/* hkfl = comcom = 0 */
		if (c==':' && !hkfl && (!comcom || !masm)) {
                    		gl=1;
                    		break;
               }
               j++;
          } while (c!='\0' && j<MAXLINE-1 && i<MAXLINE-1);
     
          s[j]='\0';
     } else
          s[0]='\0';

     return(ec);
}

void set_align(int a) {
	align = (a>align)?a:align;
}

static void lineout(void)
{
     if(gf)
     {
          logout_asm(filep->flinep);
          logout_asm("\n");
          gf=0;
     }
}

void errout(int er)
{
     if (er<-ANZERR || er>-1) {
	if(er>=-(ANZERR+ANZWARN) && er < -ANZERR) {
	  sprintf(out,"%s:line %d: %04x: Warning - %s\n",
		filep->fname, filep->fline, pc[segment], ertxt[(-er)-1]);
	} else {
          /* sprintf(out,"%s:Zeile %d: %04x:Unbekannter Fehler Nr.: %d\n",*/
          sprintf(out,"%s:line %d: %04x: Unknown error # %d\n",
               filep->fname,filep->fline,pc[segment],er);
	  ner++;
	}
     } else {
       if (er==E_NODEF)
          sprintf(out,"%s:line %d: %04x:Label '%s' not defined\n",
               filep->fname,filep->fline,pc[segment],lz);
       else  
          sprintf(out,"%s:line %d: %04x:%s error\n",
               filep->fname,filep->fline,pc[segment],ertxt[(-er)-1]);

       ner++;
     }
     logout_asm(out);
}

static void chrput(int c)
{
	file_hdl->write_file( ( unsigned char )( c & 0x0FF ) );
     /*     printf(" %02x",c&255);*/
}

void logout_asm(char *s)
{
	logout_hdl(s);
}

