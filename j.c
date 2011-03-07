/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Global Variables                                                        */

#include "j.h"

A   a0j1=0;               /* 0j1                                  */
A   ace=0;                /* a:                                   */
A   ainf=0;               /* _                                    */
A   alp=0;                /* a.                                   */
A   aqq=0;                /* ''                                   */
UC  bit[8]={(UC)0x80, (UC)0x40, (UC)0x20, (UC)0x10, (UC)0x08, (UC)0x04, (UC)0x02, (UC)0x01};
UC  bitc[256]={0};        /* # 1 bits in each possible byte       */
C   bitdisp[256*16]={0};  /* display for each possible byte       */
C   breakdata=0;
A   chr[256]={0};         /* scalar for each character, or 0      */
D   inf=0;                /* _                                    */
D   infm=0;               /* __                                   */
A   iv0=0;                /* ,0                                   */
A   iv1=0;                /* ,1                                   */
D   jnan=0;               /* _.                                   */
I   liln=0;               /* 1 iff little endian                  */
A   mark=0;               /* parser marker                        */
C   minus0[8]={0};        /* the abominable minus 0               */
A   mdot=0;               /* m.                                   */
A   mnam=0;               /* m as a name                          */
I   msize[MLEN]={0};      /* m.c size of blocks in mfree[i]       */
A   mtm=0;                /* i. 0 0                               */
A   mtv=0;                /* i.0                                  */
A   ndot=0;               /* n.                                   */
A   nnam=0;               /* n as a name                          */
A*  num=0;                /* i=num[i]; see numinit()              */
A   numv[19]={0};
A   one=0;                /* 1                                    */
D   pf=0;                 /* performance frequency                */
A   pie=0;                /* o.1                                  */
A   pst[256]={0};
B   testb[256]={0};       /* 1 iff test block follows             */
A   udot=0;               /* u.                                   */
A   unam=0;               /* u as a name                          */
A   vdot=0;               /* v.                                   */
A   vnam=0;               /* v as a name                          */
C   wtype[256]={0};
A   xdot=0;               /* x.                                   */
A   xnam=0;               /* x as a name                          */
X   xone=0;               /* extended integer 1                   */
X   xzero=0;              /* extended integer 0                   */
A   ydot=0;               /* y.                                   */
A   ynam=0;               /* y as a name                          */
A   zero=0;               /* 0                                    */
Q   zeroQ={0,0};          /* 0r1                                  */
DX  zeroDX={0,0};         /* 0                                    */
Z   zeroZ={0,0};          /* 0j0                                  */
A   zpath=0;              /* default locale search path           */

/* version text up to first / is the J System ID and it */
/* identifies the J Front Ends, J Engine, and J Library */
/* and is used in Unix to find profile.ijs              */  

F1(jtversq){ASSERTMTV(w); R cstr("j701/2011-02-23/15:25");}
