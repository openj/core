/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Words: Spelling                                                         */

#include "j.h"
#include "w.h"


static C spell[3][70]={
 '=',     '<',     '>',     '_',     '+',     '*',     '-',     '%',
 '^',     '$',     '~',     '|',     '.',     ':',     ',',     ';',
 '#',     '@',     '/',     CBSLASH, '[',     ']',     '{',     '}',
 '`',     CQQ,     '&',     '!',     '?',     'a',     'A',     'b',
 'c',     'C',     'd',     'D',     'e',     'E',     'f',     'H',
 'i',     'I',     'j',     'L',     'm',     'M',     'n',     'o',
 'p',     'q',     'r',     's',     'S',     't',     'T',     'u',
 'v',     'x',     'y',     '0',     '1',     '2',     '3',     '4',
 '5',     '6',     '7',     '8',     '9',     0,

 CASGN,   CFLOOR,  CCEIL,   1,       CPLUSDOT,CSTARDOT,CNOT,    CDOMINO,
 CLOG,    CSPARSE, CNUB,    CREV,    CEVEN,   COBVERSE,CCOMDOT, CCUT,
 CBASE,   CATDOT,  CSLDOT,  CBSDOT,  CLEV,    CDEX,    CTAKE,   CDROP,
 CGRDOT,  CEXEC,   CUNDER,  CFIT,    CQRYDOT, CALP,    CATOMIC, CBDOT,
 CCDOT,   CCYCLE,  CDDOT,   CDCAP,   CEPS,    CEBAR,   CFIX,    CHGEOM,
 CIOTA,   CICAP,   CJDOT,   CLDOT,   CMDOT,   CMCAP,   CNDOT,   CCIRCLE,
 CPOLY,   1,       CRDOT,   1,       1,       CTDOT,   CTCAP,   CUDOT,
 CVDOT,   CXDOT,   CYDOT,   1,       1,       1,       1,       1,
 1,       1,       1,       1,       1,       0,

 CGASGN,  CLE,     CGE,     CFCONS,  CPLUSCO, CSTARCO, CMATCH,  CROOT,
 CPOWOP,  CSELF,   CNE,     CCANT,   CODD,    CADVERSE,CLAMIN,  CWORDS,
 CABASE,  CATCO,   CGRADE,  CDGRADE, CCAP,    CIDA,    CTAIL,   CCTAIL,
 CGRCO,   CTHORN,  CAMPCO,  CIBEAM,  CQRYCO,  CACE,    1,       1,
 1,       1,       1,       CDCAPCO, 1,       1,       1,       1,       
 CICO,    1,       1,       CLCAPCO, 1,       1,       1,       1,
 CPCO,    CQCO,    1,       CSCO,    CSCAPCO, CTCO,    1,       CUCO,    
 1,       CXCO,    1,       CFCONS,  CFCONS,  CFCONS,  CFCONS,  CFCONS,  
 CFCONS,  CFCONS,  CFCONS,  CFCONS,  CFCONS,  0,
};

static C sp3[4][5]={
 CFETCH, CEMEND, CPDERIV, CUNDCO, 0,
 '{',    '}',    'p',     '&',    0,
 CESC2,  CESC2,  CESC1,   CESC1,  0,
 CESC2,  CESC2,  CESC1,   CESC2,  0,
};   /* trigraphs */

C spellin(I n,C*s){C c,d,p=*s,*t;I j;
 switch(n){
  case 1:
   R p;
  case 2:
   c=s[1]; j=c==CESC1?1:c==CESC2?2:0;
   R j&&(t=(C*)strchr(spell[0],p)) ? spell[j][t-spell[0]] : 0;
  case 3:
   c=s[1]; d=s[2];
   if(p==CSIGN&&d==CESC2&&'1'<=c&&c<='9')R CFCONS;
   if(t=(C*)strchr(sp3[1],p)){j=t-sp3[1]; R c==sp3[2][j]&&d==sp3[3][j]?sp3[0][j]:0;}
  default:  /* note: fall through */
   R 0;
}}

void spellit(C c,C*s){C*q;I k;
 s[1]=s[2]=0;
 if(0<=c&&(UC)c<=127) s[0]=c;
 else if(q=(C*)strchr(spell[1],c)){k=q-spell[1]; s[0]=spell[0][k]; s[1]=CESC1;}
 else if(q=(C*)strchr(spell[2],c)){k=q-spell[2]; s[0]=spell[0][k]; s[1]=CESC2;}
 else if(q=(C*)strchr(sp3[0],  c)){k=q-sp3[0];   s[0]=sp3[1][k];   s[1]=sp3[2][k]; s[2]=sp3[3][k];}
 else if(CAMIP==c)s[0]='}';
 else if(CAPIP==c)s[0]=',';
}    /* spell out ID c in s */

A jtspella(J jt,A w){C c,s[3];V*v;
 RZ(w);
 v=VAV(w); c=v->id;
 if(c==CFCONS)R over(thorn1(v->h),chr[':']); 
 spellit(c,s); 
 R str(s[2]?3L:s[1]?2L:1L,s);
}

A jtspellout(J jt,C c){C s[3]; spellit(c,s); R str(s[2]?3L:s[1]?2L:1L,s);}
