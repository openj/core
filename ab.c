/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Adverbs: b. bitwise functions                                           */

#include "j.h"
#include "ve.h"
#include "ar.h"


APFX(bw0000II, UI,UI,UI, BW0000)       static APFX(bw0000CC, UC,UC,UC, BW0000)
APFX(bw0001II, UI,UI,UI, BW0001)       static APFX(bw0001CC, UC,UC,UC, BW0001)
APFX(bw0010II, UI,UI,UI, BW0010)       static APFX(bw0010CC, UC,UC,UC, BW0010)
APFX(bw0011II, UI,UI,UI, BW0011)       static APFX(bw0011CC, UC,UC,UC, BW0011)
APFX(bw0100II, UI,UI,UI, BW0100)       static APFX(bw0100CC, UC,UC,UC, BW0100)
APFX(bw0101II, UI,UI,UI, BW0101)       static APFX(bw0101CC, UC,UC,UC, BW0101)
APFX(bw0110II, UI,UI,UI, BW0110)       static APFX(bw0110CC, UC,UC,UC, BW0110)
APFX(bw0111II, UI,UI,UI, BW0111)       static APFX(bw0111CC, UC,UC,UC, BW0111)
APFX(bw1000II, UI,UI,UI, BW1000)       static APFX(bw1000CC, UC,UC,UC, BW1000)
APFX(bw1001II, UI,UI,UI, BW1001)       static APFX(bw1001CC, UC,UC,UC, BW1001)
APFX(bw1010II, UI,UI,UI, BW1010)       static APFX(bw1010CC, UC,UC,UC, BW1010)
APFX(bw1011II, UI,UI,UI, BW1011)       static APFX(bw1011CC, UC,UC,UC, BW1011)
APFX(bw1100II, UI,UI,UI, BW1100)       static APFX(bw1100CC, UC,UC,UC, BW1100)
APFX(bw1101II, UI,UI,UI, BW1101)       static APFX(bw1101CC, UC,UC,UC, BW1101)
APFX(bw1110II, UI,UI,UI, BW1110)       static APFX(bw1110CC, UC,UC,UC, BW1110)
APFX(bw1111II, UI,UI,UI, BW1111)       static APFX(bw1111CC, UC,UC,UC, BW1111)

/* see below */                        /* see below */
REDUCEPFX(bw0001insI, UI,UI, BW0001)   static REDUCEPFX(bw0001insC, UC,UC, BW0001)
REDUCEPFX(bw0010insI, UI,UI, BW0010)   static REDUCEPFX(bw0010insC, UC,UC, BW0010)
/* see below */                        /* see below */
REDUCEPFX(bw0100insI, UI,UI, BW0100)   static REDUCEPFX(bw0100insC, UC,UC, BW0100)  
/* see below */                        /* see below */
REDUCEPFX(bw0110insI, UI,UI, BW0110)   static REDUCEPFX(bw0110insC, UC,UC, BW0110)
REDUCEPFX(bw0111insI, UI,UI, BW0111)   static REDUCEPFX(bw0111insC, UC,UC, BW0111)
REDUCEPFX(bw1000insI, UI,UI, BW1000)   static REDUCEPFX(bw1000insC, UC,UC, BW1000)
REDUCEPFX(bw1001insI, UI,UI, BW1001)   static REDUCEPFX(bw1001insC, UC,UC, BW1001)
/* see below */                        /* see below */
REDUCEPFX(bw1011insI, UI,UI, BW1011)   static REDUCEPFX(bw1011insC, UC,UC, BW1011)
/* see below */                        /* see below */
REDUCEPFX(bw1101insI, UI,UI, BW1101)   static REDUCEPFX(bw1101insC, UC,UC, BW1101)
REDUCEPFX(bw1110insI, UI,UI, BW1110)   static REDUCEPFX(bw1110insC, UC,UC, BW1110)
/* see below */                        /* see below */

       AHDRR(bw0000insI,UI,UI){I k=SZI*m*c/n; if(1<n)memset(z,C0 ,k); else MC(z,x,k);}
static AHDRR(bw0000insC,UC,UC){I k=    m*c/n; if(1<n)memset(z,C0 ,k); else MC(z,x,k);}

       AHDRR(bw1111insI,UI,UI){I k=SZI*m*c/n; if(1<n)memset(z,CFF,k); else MC(z,x,k);}
static AHDRR(bw1111insC,UC,UC){I k=    m*c/n; if(1<n)memset(z,CFF,k); else MC(z,x,k);}

       AHDRR(bw0011insI,UI,UI){I d=c/n,k=c-d;                        DO(m, DO(d, *z++=  *x++;); x+=k;);}
static AHDRR(bw0011insC,UC,UC){I d=c/n,k=c-d;                        DO(m, DO(d, *z++=  *x++;); x+=k;);}

       AHDRR(bw1100insI,UI,UI){I d=c/n,k=c-d;                 if(1<n)DO(m, DO(d, *z++= ~*x++;); x+=k;) else MC(z,x,SZI*m*c/n);}
static AHDRR(bw1100insC,UC,UC){I d=c/n,k=c-d;                 if(1<n)DO(m, DO(d, *z++= ~*x++;); x+=k;) else MC(z,x,    m*c/n);}

       AHDRR(bw0101insI,UI,UI){I d=c/n,k=c-d;                  x+=k; DO(m, DO(d, *z++=  *x++;); x+=k;);}
static AHDRR(bw0101insC,UC,UC){I d=c/n,k=c-d;                  x+=k; DO(m, DO(d, *z++=  *x++;); x+=k;);}

       AHDRR(bw1010insI,UI,UI){I d=c/n,k=c-d;UI t=     n%2-1 ; x+=k; DO(m, DO(d, *z++=t^*x++;); x+=k;);}
static AHDRR(bw1010insC,UC,UC){I d=c/n,k=c-d;UC t=(UC)(n%2-1); x+=k; DO(m, DO(d, *z++=t^*x++;); x+=k;);}



#define BITWISE(f,T,op)  \
 F2(f){A z;B b;I an,ar,*as,*av,k=0,wn,wr,*ws,x;T*wv,y,*zv;             \
  RZ(a&&w);                                                            \
  if(!(INT&AT(a)))RZ(a=cvt(INT,a));                                    \
  if(!(INT&AT(w)))RZ(w=cvt(INT,w));                                    \
  an=AN(a); ar=AR(a); as=AS(a); av=(I*)AV(a);                          \
  wn=AN(w); wr=AR(w); ws=AS(w); wv=(T*)AV(w); b=ar>wr;                 \
  DO(MIN(ar,wr), ASSERT(as[i]==ws[i],EVLENGTH););                      \
  GA(z,INT,b?an:wn,MAX(ar,wr),b?as:ws); zv=(T*)AV(z);                  \
  if(!AN(z))R z;                                                       \
  if     (ar==wr)DO(an, x=*av++;           y=*wv++; *zv++=op(x,y);  )  \
  else if(ar< wr)DO(an, x=*av++; DO(wn/an, y=*wv++; *zv++=op(x,y););)  \
  else           DO(wn, y=*wv++; DO(an/wn, x=*av++; *zv++=op(x,y););); \
  RE(0); R z;                                                          \
 }

#if SY_64
#define WLEN    64
#else
#define WLEN    32
#endif

#define BWROT(x,y)      (0>x ? (y>>(-x%WLEN))|(y<<(WLEN+(x%WLEN))) : (y<<(x%WLEN))|(y>>(WLEN-(x%WLEN))) )
#define BWSHIFT(x,y)    (0>x ? (x<=-WLEN?0:y>>-x)           : (x>=WLEN?0:y<<x)            )
#define BWSHIFTA(x,y)   (0>x ? (x<=-WLEN?(y<0?-1:0):y>>-x)  : (x>=WLEN?0:y<<x)            )

BITWISE(jtbitwiserotate,UI,BWROT   )
BITWISE(jtbitwiseshift, UI,BWSHIFT )
BITWISE(jtbitwiseshifta,I, BWSHIFTA)

DF1(jtbitwise1){R CALL2(VAV(self)->f2,zero,w,self);}


static VF bwC[16]={bw0000CC,bw0001CC,bw0010CC,bw0011CC, bw0100CC,bw0101CC,bw0110CC,bw0111CC,
                   bw1000CC,bw1001CC,bw1010CC,bw1011CC, bw1100CC,bw1101CC,bw1110CC,bw1111CC};

static VF bwI[16]={bw0000II,bw0001II,bw0010II,bw0011II, bw0100II,bw0101II,bw0110II,bw0111II,
                   bw1000II,bw1001II,bw1010II,bw1011II, bw1100II,bw1101II,bw1110II,bw1111II};

/* a m b.&.(a.&i.) w */
/* a m b.&.(a.i.]) w */
/* m e. 16+i.16      */

DF2(jtbitwisechar){DECLFG;A*p,x,y,z;B b;I an,ar,*as,at,d,j,m,n,wn,wr,*ws,wt,zn;VF f;
 RZ(a&&w);
 d=SZI;
 x=a; an=AN(a); ar=AR(a); as=AS(a); at=AT(a);
 y=w; wn=AN(w); wr=AR(w); ws=AS(w); wt=AT(a);
 if(!(an&&wn&&at&LIT&&wt&LIT))R from(df2(indexof(alp,a),indexof(alp,w),fs),alp);
 b=ar<=wr; zn=b?wn:an; m=b?an:wn; n=zn/m;
 ASSERT(!ICMP(as,ws,MIN(ar,wr)),EVLENGTH);
 j=i0(VAV(fs)->f)-16;
 GA(z,d==SZI?LIT:C2T,zn,MAX(ar,wr),b?ws:as); 
 if(1==n)                 {f=bwI[j]; m=(m+d-1)/d;}
 else if(!ar||!wr||0==n%d){f=bwI[j]; n=(n+d-1)/d; p=b?&x:&y; RZ(*p=irs2(sc(d),*p,0L,0L,0L,jtrepeat));}
 else                      f=bwC[j];
 f(jt,b,m,n,AV(z),AV(x),AV(y)); 
 *(zn+CAV(z))=0;
 R z;
}

/* compute z=: t{~ a.i.w if t=: c&(m b.) a.                             */
/* http://www.jsoftware.com/jwiki/Essays/Bitwise_Functions_on_Charcters */

B jtbitwisecharamp(J jt,UC*t,I n,UC*wv,UC*zv){I p;UC c,i,j,*pv,s[256];VF f;
 i=t[0]; j=t[255];
 if     (i==0    ){c=j; f=bw0001II;}
 else if(j==i    ){c=i; f=bw0011II;}
 else if(j==255  ){c=i; f=bw0111II;}
 else if(j==255-i){c=i; f=bw0110II;}
 else if(j==0    ){c=i; f=bw0010II;}
 else if(i==255  ){c=j; f=bw1011II;}
 else R 0;
 pv=(UC*)&p; DO(SZI, pv[i]=c;);
 f(jt,1,1L,256L/SZI,s,pv,AV(alp)); if(memcmp(s,t,256L))R 0;
 f(jt,1,1L,(n+SZI-1)/SZI,zv,pv,wv); zv[n]=0;
 R 1;
}


static VF bwinsC[16]={bw0000insC,bw0001insC,bw0010insC,bw0011insC, bw0100insC,bw0101insC,bw0110insC,bw0111insC,
                      bw1000insC,bw1001insC,bw1010insC,bw1011insC, bw1100insC,bw1101insC,bw1110insC,bw1111insC};

static VF bwinsI[16]={bw0000insI,bw0001insI,bw0010insI,bw0011insI, bw0100insI,bw0101insI,bw0110insI,bw0111insI,
                      bw1000insI,bw1001insI,bw1010insI,bw1011insI, bw1100insI,bw1101insI,bw1110insI,bw1111insI};

/* m b./&.(a.&i.) w */
/* m b./&.(a.i.]) w */
/* m e. 16+i.16     */

DF1(jtbitwiseinsertchar){A fs,z;I c,d=SZI,j,m,n,r,wn,wr;UC*u,*v,*wv,x,*zv;VF f;
 RZ(w&&self);
 wr=AR(w); c=wn=AN(w); n=wr?*AS(w):1; z=VAV(self)->f; fs=VAV(z)->f;
 if(!(wn&&d<n&&LIT&AT(w)))R from(df1(indexof(alp,w),fs),alp);
 m=wn/n; wv=CAV(w); j=i0(VAV(fs)->f)-16; f=bwinsC[j];
 if(1==wr)switch(j){
  case  0: R scc(0);
  case  3: R scc(*wv);
  case  5: R scc(*(wv+wn-1));
  case 10: x=*(wv+wn-1); R scc((UC)(wn%2?x:~x));
  case 12: R scc((UC)~*wv);
  case 15: R scc((UC)255);
  case  1: case 6: case 7: case 9: f=bwinsI[j]; c=n=n/d;
 }else if(0==m%d){f=bwinsI[j]; c/=d;}
 GA(z,LIT,m,wr-1,1+AS(w)); zv=CAV(z);
 f(jt,1L,c,n,zv,wv);
 if(1==wr){
  r=wn-n*d; u=wv+n*d; x=*zv; v=1+zv; 
  switch(j){
   case 1: DO(d-1, x=BW0001(x,*v); ++v;); DO(r, x=BW0001(x,*u); ++u;); break;
   case 6: DO(d-1, x=BW0110(x,*v); ++v;); DO(r, x=BW0110(x,*u); ++u;); break;
   case 7: DO(d-1, x=BW0111(x,*v); ++v;); DO(r, x=BW0111(x,*u); ++u;); break;
   case 9: DO(d-1, x=BW1001(x,*v); ++v;); DO(r, x=BW1001(x,*u); ++u;); break;
  }
  *(I*)zv=0; *zv=x;
 }
 R z;
}
