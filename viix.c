/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Verbs: Interval Index, mostly by Binary Search                          */

#include "j.h"


#define BXLOOP(T)  \
 {T*wv=(T*)AV(w),x;                                                  \
  switch((4*descend)+(0<=p?2:0)+(0<=q)){                             \
   case 1: DO(m, *zv++=n*(1<*wv++););              break; /*   q */  \
   case 2: DO(m, *zv++=n*(0<*wv++););              break; /* p   */  \
   case 3: DO(m, x=*wv++; *zv++=x<=0?0:x<=1?q:n;); break; /* p q */  \
   case 7: DO(m, x=*wv++; *zv++=x>=1?0:x>=0?p:n;);        /* p q */  \
 }}

static B jtiixBX(J jt,I n,I m,A a,A w,I*zv){B*av,*b,descend;I p,q;
 av=BAV(a); descend=av[0]>av[n-1];
 b=memchr(av,C0,n); p=b?b-av:-1;
 b=memchr(av,C1,n); q=b?b-av:-1;
 switch(AT(w)){
  case INT: BXLOOP(I); break;
  case FL:  BXLOOP(D); break;
  case B01:
   b=BAV(w);
   switch((4*descend)+(0<=p?2:0)+(0<=q)){
    case 1: memset(zv,C0,m*SZI);   break;  /*   q */
    case 2: DO(m, *zv++=n* *b++;); break;  /* p   */
    case 3: DO(m, *zv++=q* *b++;); break;  /* p q */
    case 7: DO(m, *zv++=p*!*b++;);         /* p q */
 }}
 R 1;
}    /* a I."r w where a is a boolean list */

static B jtiixI(J jt,I n,I m,A a,A w,I*zv){A t;B ascend;I*av,j,p,q,*tv,*u,*v,*vv,*wv,x,y;
 av=AV(a); wv=AV(w);
 p=av[0]; q=av[n-1]; ascend=p<=q; if(!ascend){x=p; p=q; q=x;}
 GA(t,INT,1+q-p,1,0); v=AV(t); tv=v-p; vv=v+AN(t);
 if(ascend){u=av;     x=*u++; *v++=j=0; DO(n-1, ++j; y=*u++; ASSERT(p<=y&&y<=q&&vv>=v+y-x,EVDOMAIN); DO(y-x, *v++=j;); x=y;);}
 else      {u=av+n-1; x=*u--;      j=n; DO(n-1, --j; y=*u--; ASSERT(p<=y&&y<=q&&vv>=v+y-x,EVDOMAIN); DO(y-x, *v++=j;); x=y;);}
 if(ascend)DO(m, x=*wv++; *zv++=x<=p?0:q<x?n:tv[x];)
 else      DO(m, x=*wv++; *zv++=x>=q?0:p>x?n:tv[x];);
 R 1;
}    /* a I. w where a is a list of small range integers */

#define COMPVLOOP(T,c)       \
 {T*u=(T*)uu,*v=(T*)vv; DO(c, if(*u!=*v){cc=*u<*v?-1:1; break;} ++u; ++v;);}
#define COMPVLOOF(T,c,COMP)  \
 {T*u=(T*)uu,*v=(T*)vv; DO(c, if(cc=COMP(*u,*v))break;          ++u; ++v;);}

#define MID(k,p,q)   k=(UI)(p+q)>>1  /* beware integer overflow */

#define BSLOOP1(CMP)           \
  p=0; q=n-1; y=*wv++;         \
  while(p<=q){MID(k,p,q); CMP; \
      if(b)q=k-1; else p=k+1;}
#define BSLOOPN(NE,CMP)        \
  p=0; q=n-1;                  \
  while(p<=q){MID(k,p,q); u=av+c*k; v=wv; b=1; DO(c, x=*u++; y=*v++; if(NE){CMP; break;});  \
      if(b)q=k-1; else p=k+1;}

#define BSLOOP(Ta,Tw)       \
 {Ta*av=(Ta*)AV(a),*u,x;                                              \
  Tw*wv=(Tw*)AV(w),*v,y;                                              \
  switch((1==c?0:2)+(1==ge)){                                         \
   case 0: DO(m, BSLOOP1(b=av[k]>=y); *zv++=1+q;       ); break;      \
   case 1: DO(m, BSLOOP1(b=av[k]<=y); *zv++=1+q;       ); break;      \
   case 2: DO(m, BSLOOPN(x!=y,b=x>y); *zv++=1+q; wv+=c;); break;      \
   case 3: DO(m, BSLOOPN(x!=y,b=x<y); *zv++=1+q; wv+=c;); break;      \
 }}

#define BSLOOF(Ta,Tw,COMP)  \
 {Ta*av=(Ta*)AV(a),*u,x;                                              \
  Tw*wv=(Tw*)AV(w),*v,y;                                              \
  if(1==c) DO(m, BSLOOP1(b=ge!=COMP(av[k],y));   *zv++=1+q;       )   \
  else     DO(m, BSLOOPN(cc=COMP(x,y),b=gt==cc); *zv++=1+q; wv+=c;);  \
 }

#define TT(s,t)     (7*(s)+(t))

F2(jticap2){A*av,*wv,z;B b;C*uu,*vv;I ad,ar,*as,at,c,ck,cm,ge,gt,j,k,m,n,p,q,r,t,*u,*v,wd,wr,*ws,wt,*zv;int cc;
 RZ(a&&w);
 ar=AR(a); at=AT(a); as=AS(a); n=ar?*as:1; r=ar?ar-1:0;
 wr=AR(w); wt=AT(w); ws=AS(w); b=!AN(a)||!AN(w);
 ASSERT(r<=wr,EVRANK);
 u=as+ar; v=ws+wr; DO(r, ASSERT(*--u==*--v,EVLENGTH););
 ASSERT(b||HOMO(at,wt),EVDOMAIN);
 ASSERT(b||at&DENSE&&wt&DENSE,EVNONCE);
 t=maxtype(at,wt);
 RE(m=prod(wr-r,ws)); RE(c=prod(r,ws+wr-r));
 GA(z,INT,m,wr-r,ws); zv=AV(z);
 if(!m||!n||!c){DO(m, *zv++=0;); R z;}
 if(1==c){
  if(at&B01&&wt&B01+INT+FL){RZ(iixBX(n,m,a,w,zv)); R z;}
  if(at&INT&&wt&INT){D r;
   v=AV(a); r=(D)v[n-1]-(D)v[0]; if(0>r)r=-r;
   if(m+r<1.4*m*log((D)n)){RZ(iixI(n,m,a,w,zv)); R z;}
 }}
 jt->complt=-1; jt->compgt=1; cc=0; uu=CAV(a); vv=CAV(a)+bp(at)*c*(n-1);
 switch(at){
  default:   ASSERT(0,EVNONCE);
  case B01:  COMPVLOOP(B, c);           break;
  case LIT:  COMPVLOOP(UC,c);           break;
  case INT:  COMPVLOOP(I, c);           break;
  case FL:   COMPVLOOP(D, c);           break;
  case CMPX: COMPVLOOP(D, c+c);         break;
  case C2T:  COMPVLOOP(US,c);           break;
  case XNUM: COMPVLOOF(X, c, xcompare); break;
  case RAT:  COMPVLOOF(Q, c, qcompare); break;
  case BOX:  
   av=AAV(a); ad=(I)a*ARELATIVE(a); 
   wv=AAV(w); wd=(I)w*ARELATIVE(w); 
   DO(c, if(cc=compare(AVR(i),AVR(i+c*(n-1))))break;);
 }
 ge=cc; gt=-ge;
 switch(TT(at,wt)){
  case TT(B01, B01 ): BSLOOP(C, C ); break;
  case TT(B01, INT ): BSLOOP(C, I ); break;
  case TT(B01, FL  ): BSLOOP(C, D ); break;
  case TT(LIT, C2T ): BSLOOP(UC,US); break;
#if SYS & SYS_LILENDIAN
  case TT(LIT, LIT ): BSLOOP(UC,UC); break;
#else
  case TT(LIT, LIT ): if(1&c){BSLOOP(UC,UC); break;}else c>>=1; /* fall thru */
#endif
  case TT(C2T, C2T ): BSLOOP(US,US); break;
  case TT(C2T, LIT ): BSLOOP(US,UC); break;
  case TT(INT, B01 ): BSLOOP(I, C ); break;
  case TT(INT, INT ): BSLOOP(I, I ); break;
  case TT(INT, FL  ): BSLOOP(I, D ); break;
  case TT(FL,  B01 ): BSLOOP(D, C ); break;
  case TT(FL,  INT ): BSLOOP(D, I ); break;
  case TT(CMPX,CMPX): c+=c;  /* fall thru */
  case TT(FL,  FL  ): BSLOOP(D, D ); break;
  case TT(XNUM,XNUM): BSLOOF(X, X, xcompare); break;
  case TT(RAT, RAT ): BSLOOF(Q, Q, qcompare); break;
  case TT(BOX, BOX ):
   for(j=0,cm=c*m;j<cm;j+=c){
    p=0; q=n-1;
    while(p<=q){
     MID(k,p,q); ck=c*k; b=1; 
     DO(c, if(cc=compare(AVR(i+ck),WVR(i+j))){b=gt==cc; break;});
     if(b)q=k-1; else p=k+1;
    } 
    *zv++=1+q;
   }
   break;
  default:
   ASSERT(at!=wt,EVNONCE);
   if(t!=at)RZ(a=cvt(t,a));
   if(t!=wt)RZ(w=cvt(t,w));
   switch(t){
    case CMPX: c+=c;  /* fall thru */ 
    case FL:   BSLOOP(D,D);           break;
    case XNUM: BSLOOF(X,X, xcompare); break;
    case RAT:  BSLOOF(Q,Q, qcompare); break;
    default:   ASSERT(0,EVNONCE);
 }}
 R z;
}    /* a I."r w */
