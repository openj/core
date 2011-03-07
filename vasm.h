/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Verbs: Assembly Routines for Integer + * - with Overflow                */

/* fvv  zv=.xv+yv     0<n */
/* fv1  zv=.xv+y      0<n */
/* f1v  zv=.x +yv     0<n */
/* frv  zv=.xv+zv     0<n */
/* fr   z =.+/  xv    1<n */
/* fp   zv=.+/\ xv    1<n */
/* fs   zv=.+/\.xv    1<n */

#ifndef NOASM /* builder defines NOASM to do I overflow in C instead of asm */

#if SY_WIN32 && !SY_64 && !SY_WINCE
#define OVF

#define PLUSVV(m,z,x,y)                 \
{                                       \
__asm        mov  ecx,m                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        mov  edx,y                 \
__asm        sub  edi,4                 \
__asm        sub  esi,4                 \
__asm        sub  edx,4                 \
__asm pvv20: mov  eax,[esi+ecx*4]       \
__asm        add  eax,[edx+ecx*4]       \
__asm        jo   pvv30                 \
__asm        mov  [edi+ecx*4],eax       \
__asm        loop pvv20                 \
__asm        jmp  pvv40                 \
__asm pvv30: mov  er,EWOV               \
__asm pvv40:                            \
}   

#define PLUS1V(n,z,u,y)                 \
{                                       \
__asm        mov  ecx,n                 \
__asm        mov  edi,z                 \
__asm        mov  edx,u                 \
__asm        mov  esi,y                 \
__asm        sub  edi,4                 \
__asm        sub  esi,4                 \
__asm p1v20: mov  eax,[esi+ecx*4]       \
__asm        add  eax,edx               \
__asm        jo   p1v30                 \
__asm        mov  [edi+ecx*4],eax       \
__asm        loop p1v20                 \
__asm        jmp  p1v40                 \
__asm p1v30: mov  er,EWOV               \
__asm p1v40:                            \
}

#define PLUSV1(n,z,x,v)                 \
{                                       \
__asm        mov  ecx,n                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        mov  edx,v                 \
__asm        mov  esi,x                 \
__asm        sub  edi,4                 \
__asm        sub  esi,4                 \
__asm pv120: mov  eax,[esi+ecx*4]       \
__asm        add  eax,edx               \
__asm        jo   pv130                 \
__asm        mov  [edi+ecx*4],eax       \
__asm        loop pv120                 \
__asm        jmp  pv140                 \
__asm pv130: mov  er,EWOV               \
__asm pv140:                            \
}

#define PLUSRV(d,z,x)                   \
{                                       \
__asm        mov  ecx,d                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        sub  edi,4                 \
__asm        sub  esi,4                 \
__asm prv20: mov  eax,[esi+ecx*4]       \
__asm        add  eax,[edi+ecx*4]       \
__asm        jo   prv30                 \
__asm        mov  [edi+ecx*4],eax       \
__asm        loop prv20                 \
__asm        jmp  prv40                 \
__asm prv30: mov  er,EWOV               \
__asm prv40:                            \
}

#define PLUSR(n,z,x)                    \
{                                       \
__asm        mov  ecx,n                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        sub  esi,4                 \
__asm        xor  eax,eax               \
__asm  pr20: add  eax,[esi+ecx*4]       \
__asm        jo   pr30                  \
__asm        loop pr20                  \
__asm        mov  [edi],eax             \
__asm        jmp  pr40                  \
__asm  pr30: mov  er,EWOV               \
__asm  pr40:                            \
}

#define PLUSP(n,z,x)                    \
{                                       \
__asm        mov  ecx,n                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        xor  edx,edx               \
__asm        xor  eax,eax               \
__asm        mov  ebx,ecx               \
__asm        sar  ecx,1                 \
__asm  pp20: add  eax,[esi+edx*4]       \
__asm        jo   pp30                  \
__asm        mov  [edi+edx*4],eax       \
__asm        inc  edx                   \
__asm        add  eax,[esi+edx*4]       \
__asm        jo   pp30                  \
__asm        mov  [edi+edx*4],eax       \
__asm        inc  edx                   \
__asm        loop pp20                  \
__asm        and  ebx,1                 \
__asm        jz   pp40                  \
__asm        add  eax,[esi+edx*4]       \
__asm        jo   pp30                  \
__asm        mov  [edi+edx*4],eax       \
__asm        jmp  pp40                  \
__asm  pp30: mov  er,EWOV               \
__asm  pp40:                            \
}

#define PLUSS(n,z,x)                    \
{                                       \
__asm        mov  ecx,n                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        sub  esi,4                 \
__asm        sub  edi,4                 \
__asm        xor  eax,eax               \
__asm  ps20: add  eax,[esi+ecx*4]       \
__asm        jo   ps30                  \
__asm        mov  [edi+ecx*4],eax       \
__asm        loop ps20                  \
__asm        jmp  ps40                  \
__asm  ps30: mov  er,EWOV               \
__asm  ps40:                            \
}


#define MINUSVV(m,z,x,y)                \
{                                       \
__asm        mov  ecx,m                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        mov  edx,y                 \
__asm        sub  edi,4                 \
__asm        sub  esi,4                 \
__asm        sub  edx,4                 \
__asm mvv20: mov  eax,[esi+ecx*4]       \
__asm        sub  eax,[edx+ecx*4]       \
__asm        jo   mvv30                 \
__asm        mov  [edi+ecx*4],eax       \
__asm        loop mvv20                 \
__asm        jmp  mvv40                 \
__asm mvv30: mov  er,EWOV               \
__asm mvv40:                            \
}

#define MINUS1V(n,z,u,y)                \
{                                       \
__asm        mov  ecx,n                 \
__asm        mov  edi,z                 \
__asm        sub  edi,4                 \
__asm        mov  edx,u                 \
__asm        mov  esi,y                 \
__asm        sub  esi,4                 \
__asm m1v20: mov  eax,edx               \
__asm        sub  eax,[esi+ecx*4]       \
__asm        jo   m1v30                 \
__asm        mov  [edi+ecx*4],eax       \
__asm        loop m1v20                 \
__asm        jmp  m1v40                 \
__asm m1v30: mov  er,EWOV               \
__asm m1v40:                            \
}

#define MINUSV1(n,z,x,v)                \
{                                       \
__asm        mov  ecx,n                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        mov  edx,v                 \
__asm        sub  edi,4                 \
__asm        sub  esi,4                 \
__asm mv120: mov  eax,[esi+ecx*4]       \
__asm        sub  eax,edx               \
__asm        jo   mv130                 \
__asm        mov  [edi+ecx*4],eax       \
__asm        loop mv120                 \
__asm        jmp  mv140                 \
__asm mv130: mov  er,EWOV               \
__asm mv140:                            \
}

#define MINUSRV(d,z,x)                  \
{                                       \
__asm        mov  ecx,d                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        sub  edi,4                 \
__asm        sub  esi,4                 \
__asm mrv20: mov  eax,[esi+ecx*4]       \
__asm        sub  eax,[edi+ecx*4]       \
__asm        jo   mrv30                 \
__asm        mov  [edi+ecx*4],eax       \
__asm        loop mrv20                 \
__asm        jmp  mrv40                 \
__asm mrv30: mov  er,EWOV               \
__asm mrv40:                            \
}

#define MINUSR(n,z,x)                   \
{                                       \
__asm        mov  ecx,n                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        sub  esi,4                 \
__asm        xor  eax,eax               \
__asm  mr20: mov  edx,[esi+ecx*4]       \
__asm        sub  edx,eax               \
__asm        jo   mr30                  \
__asm        mov  eax,edx               \
__asm        loop mr20                  \
__asm        mov  [edi],eax             \
__asm        jmp  mr40                  \
__asm  mr30: mov  er,EWOV               \
__asm  mr40:                            \
}

#define MINUSP(n,z,x)                   \
{                                       \
__asm        mov  ecx,n                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        xor  edx,edx               \
__asm        xor  eax,eax               \
__asm        mov  ebx,ecx               \
__asm        sar  ecx,1                 \
__asm  mp20: add  eax,[esi+edx*4]       \
__asm        jo   mp30                  \
__asm        mov  [edi+edx*4],eax       \
__asm        inc  edx                   \
__asm        sub  eax,[esi+edx*4]       \
__asm        jo   mp30                  \
__asm        mov  [edi+edx*4],eax       \
__asm        inc  edx                   \
__asm        loop mp20                  \
__asm        and  ebx,1                 \
__asm        jz   mp40                  \
__asm        add  eax,[esi+edx*4]       \
__asm        jo   mp30                  \
__asm        mov  [edi+edx*4],eax       \
__asm        jmp  mp40                  \
__asm  mp30: mov  er,EWOV               \
__asm  mp40:                            \
}

#define MINUSS(n,z,x)                   \
{                                       \
__asm        mov  ecx,n                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        sub  esi,4                 \
__asm        sub  edi,4                 \
__asm        xor  eax,eax               \
__asm  ms20: mov  edx,[esi+ecx*4]       \
__asm        sub  edx,eax               \
__asm        jo   ms30                  \
__asm        mov  eax,edx               \
__asm        mov  [edi+ecx*4],eax       \
__asm        loop ms20                  \
__asm        jmp  ms40                  \
__asm  ms30: mov  er,EWOV               \
__asm  ms40:                            \
}


#define TYMESVV(m,z,x,y)                \
{                                       \
__asm        mov  ecx,m                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        mov  edx,y                 \
__asm        sub  edi,4                 \
__asm        sub  esi,4                 \
__asm        sub  edx,4                 \
__asm tvv20: mov  eax,[esi+ecx*4]       \
__asm        imul eax,[edx+ecx*4]       \
__asm        jo   tvv30                 \
__asm        mov  [edi+ecx*4],eax       \
__asm        loop tvv20                 \
__asm        jmp  tvv40                 \
__asm tvv30: mov  er,EWOV               \
__asm tvv40:                            \
}

#define TYMES1V(n,z,u,y)                \
{                                       \
__asm        mov  ecx,n                 \
__asm        mov  edi,z                 \
__asm        mov  edx,u                 \
__asm        mov  esi,y                 \
__asm        sub  edi,4                 \
__asm        sub  esi,4                 \
__asm t1v20: mov  eax,[esi+ecx*4]       \
__asm        imul eax,edx               \
__asm        jo   t1v30                 \
__asm        mov  [edi+ecx*4],eax       \
__asm        loop t1v20                 \
__asm        jmp  t1v40                 \
__asm t1v30: mov  er,EWOV               \
__asm t1v40:                            \
}

#define TYMESV1(n,z,x,v)                \
{                                       \
__asm        mov  ecx,n                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        mov  edx,v                 \
__asm        sub  edi,4                 \
__asm        sub  esi,4                 \
__asm tv120: mov  eax,[esi+ecx*4]       \
__asm        imul eax,edx               \
__asm        jo   tv130                 \
__asm        mov  [edi+ecx*4],eax       \
__asm        loop tv120                 \
__asm        jmp  tv140                 \
__asm tv130: mov  er,EWOV               \
__asm tv140:                            \
}

#define TYMESRV(d,z,x)                  \
{                                       \
__asm        mov  ecx,d                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        sub  edi,4                 \
__asm        sub  esi,4                 \
__asm trv20: mov  eax,[esi+ecx*4]       \
__asm        imul eax,[edi+ecx*4]       \
__asm        jo   trv30                 \
__asm        mov  [edi+ecx*4],eax       \
__asm        loop trv20                 \
__asm        jmp  trv40                 \
__asm trv30: mov  er,EWOV               \
__asm trv40:                            \
}

#define TYMESR(n,z,x)                   \
{                                       \
__asm        mov  ecx,n                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        sub  esi,4                 \
__asm        mov  eax,1                 \
__asm  tr20: imul eax,[esi+ecx*4]       \
__asm        jo   tr30                  \
__asm        loop tr20                  \
__asm        mov  [edi],eax             \
__asm        jmp  tr40                  \
__asm  tr30: mov  er,EWOV               \
__asm  tr40:                            \
}

#define TYMESP(n,z,x)                   \
{                                       \
__asm        mov  ecx,n                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        xor  edx,edx               \
__asm        mov  eax,1                 \
__asm  tp20: imul eax,[esi+edx*4]       \
__asm        jo   tp30                  \
__asm        mov  [edi+edx*4],eax       \
__asm        inc  edx                   \
__asm        loop tp20                  \
__asm        jmp  tp40                  \
__asm  tp30: mov  er,EWOV               \
__asm  tp40:                            \
}

#define TYMESS(n,z,x)                   \
{                                       \
__asm        mov  ecx,n                 \
__asm        mov  edi,z                 \
__asm        mov  esi,x                 \
__asm        sub  esi,4                 \
__asm        sub  edi,4                 \
__asm        mov  eax,1                 \
__asm  ts20: imul eax,[esi+ecx*4]       \
__asm        jo   ts30                  \
__asm        mov  [edi+ecx*4],eax       \
__asm        loop ts20                  \
__asm        jmp  ts40                  \
__asm  ts30: mov  er,EWOV               \
__asm  ts40:                            \
}

#endif

#if SY_64 /* win64 and linux64 asm routines */
#define OVF

C asmplusvv(I,I*,I*,I*);
C asmminusvv(I,I*,I*,I*);
C asmtymesvv(I,I*,I*,I*);

C asmplus1v(I,I*,I,I*);
C asmminus1v(I,I*,I,I*);
C asmtymes1v(I,I*,I,I*);

C asmminusv1(I,I*,I*,I);

C asmplusr(I,I*,I*);
C asmminusr(I,I*,I*);
C asmtymesr(I,I*,I*);

C asmplusrv(I,I*,I*);
C asmminusrv(I,I*,I*);
C asmtymesrv(I,I*,I*);
 
C asmpluss(I,I*,I*);
C asmminuss(I,I*,I*);
C asmtymess(I,I*,I*);

C asmplusp(I,I*,I*);
C asmminusp(I,I*,I*);
C asmtymesp(I,I*,I*);

C asminnerprod(I,I*,I*,I*,I);
C asminnerprodx(I,I*,I,I*);

#define  PLUSVV(m,z,x,y) er=asmplusvv(m,z,x,y)
#define MINUSVV(m,z,x,y) er=asmminusvv(m,z,x,y)
#define TYMESVV(m,z,x,y) er=asmtymesvv(m,z,x,y)

#define  PLUSRV(d,z,x)   er=asmplusrv(d,z,x)
#define MINUSRV(d,z,x)   er=asmminusrv(d,z,x)
#define TYMESRV(d,z,x)   er=asmtymesrv(d,z,x)

#define  PLUS1V(n,z,u,y) er=asmplus1v(n,z,u,y)
#define MINUS1V(n,z,u,y) er=asmminus1v(n,z,u,y)
#define TYMES1V(n,z,u,y) er=asmtymes1v(n,z,u,y)

#define  PLUSV1(n,z,x,v) PLUS1V(n,z,v,x)
#define MINUSV1(n,z,x,v) er=asmminusv1(n,z,x,v)
#define TYMESV1(n,z,x,v) TYMES1V(n,z,v,x)

#define  PLUSR(n,z,x)    er=asmplusr(n,z,x) 
#define MINUSR(n,z,x)    er=asmminusr(n,z,x) 
#define TYMESR(n,z,x)    er=asmtymesr(n,z,x) 

#define  PLUSS(n,z,x)    er=asmpluss(n,z,x) 
#define MINUSS(n,z,x)    er=asmminuss(n,z,x) 
#define TYMESS(n,z,x)    er=asmtymess(n,z,x) 

#define  PLUSP(n,z,x)    er=asmplusp(n,z,x) 
#define MINUSP(n,z,x)    er=asmminusp(n,z,x) 
#define TYMESP(n,z,x)    er=asmtymesp(n,z,x) 

#endif

#endif

/* C routines for platforms without asm support */
#ifndef OVF

#if SY_64
#define DI LD
#else
#define DI D
#endif

#define  PLUSVV(m,z,x,y)   {B p;  DO(m, p=0>*x; *z=*x+*y;     BOV(p==0>*y&&p!=0>*z); z++; x++; y++;);}
#define MINUSVV(m,z,x,y)   {B p;  DO(m, p=0>*x; *z=*x-*y;     BOV(p!=0>*y&&p!=0>*z); z++; x++; y++;);}
#define TYMESVV(m,z,x,y)   {DI t; DO(m, t=*x*(DI)*y; *z=(I)t; BOV(t<IMIN||IMAX<t  ); z++; x++; y++;);}

#define  PLUS1V(n,z,u,y)   {B p=0>u;  DO(n, z[i]=u+y[i];         BOV(p==0>y[i]&&p!=0>z[i]););}
#define MINUS1V(n,z,u,y)   {B p=0>u;  DO(n, z[i]=u-y[i];         BOV(p!=0>y[i]&&p!=0>z[i]););}
#define TYMES1V(n,z,u,y)   {DI d=u,t; DO(n, t=d*y[i]; z[i]=(I)t; BOV(t<IMIN||IMAX<t      ););}

#define  PLUSV1(n,z,x,v)   PLUS1V(n,z,v,x)
#define TYMESV1(n,z,x,v)   TYMES1V(n,z,v,x)
#define MINUSV1(n,z,x,v)   {B p=0>v; DO(n, z[i]=x[i]-v;   BOV(p!=0>x[i]&&p==0>z[i]););}

#define  PLUSP(n,z,x)      {B p;I s=0;   DO(n, p=0>s; *z=s+=*x;        BOV(p==0>*x&&p!=0>s); z++; x++;);}
#define MINUSP(n,z,x)      {B p=0;DI t=0; DO(n, t=p?t-*x:t+*x; *z=(I)t; BOV(t<IMIN||IMAX<t ); z++; x++; p=!p;);}
#define TYMESP(n,z,x)      {DI t=1;      DO(n, t*=*x;         *z=(I)t; BOV(t<IMIN||IMAX<t ); z++; x++;);}

#define  PLUSR(n,z,x)      {B p;I s=0;   DO(n, p=0>s; s+=*x;  BOV(p==0>*x&&p!=0>s); x++;      ); *z=s;}
#define MINUSR(n,z,x)      {B p=0;DI t=0; DO(n, t=p?t-*x:t+*x; BOV(t<IMIN||IMAX<t ); x++; p=!p;); *z=(I)t;}
#define TYMESR(n,z,x)      {DI t=1;      DO(n, t*=*x;         BOV(t<IMIN||IMAX<t ); x++;      ); *z=(I)t;}

#define  PLUSRV(d,z,x)     {B p;  DO(d, p=0>*z; *z+=*x;       BOV(p==0>*x&&p!=0>*z); x++; z++;);}
#define MINUSRV(d,z,x)     {DI t; DO(d, t=*x-(DI)*z; *z=(I)t; BOV(t<IMIN||IMAX<t  ); x++; z++;);}
#define TYMESRV(d,z,x)     {DI t; DO(d, t=*x*(DI)*z; *z=(I)t; BOV(t<IMIN||IMAX<t  ); x++; z++;);}

#define  PLUSS(n,z,x)      {B p;I s=0; x+=n; z+=n; DO(n, --x; p=0>s; *--z=s+=*x;       BOV(p==0>*x&&p!=0>s););}
#define MINUSS(n,z,x)      {B p;I s=0; x+=n; z+=n; DO(n, --x; p=0>s; *--z=s=*x-s;      BOV(p!=0>*x&&p==0>s););}
#define TYMESS(n,z,x)      {DI t=1;    x+=n; z+=n; DO(n, --x;        t*=*x; *--z=(I)t; BOV(t<IMIN||IMAX<t ););}

#endif
