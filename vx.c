/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Verbs: Extended Precision Integers                                      */

#include "j.h"
#include "ve.h"


X jtxev1(J jt,A w,C*s){A y; 
 RZ(y=df1(cvt(XNUM,w),eval(s)));
 ASSERTSYS(!AR(y),"xev1");
 if(!(XNUM&AT(y)))RZ(y=cvt(XNUM,y)); 
 R*XAV(y);
}

X jtxev2(J jt,A a,A w,C*s){A y; 
 RZ(y=df2(cvt(XNUM,a),cvt(XNUM,w),eval(s))); 
 ASSERTSYS(!AR(y),"xev2");
 if(!(XNUM&AT(y)))RZ(y=cvt(XNUM,y)); 
 R*XAV(y);
}

X jtxc(J jt,I n){I m=1,p,*zv;X z; 
 p=n; while(p/=XBASE)++m;
 GA(z,INT,m,1,0); zv=AV(z);
 p=n; DO(m, zv[i]=p%XBASE; p/=XBASE;);
 R z;
}    /* n is non-negative */

D xdouble(X w){D z=0;I c,n,*v;
 n=AN(w); v=n+AV(w); c=*--v;
 if(c==XPINF)R inf; else if(c==XNINF)R infm;
 DO(n, z=*v--+z*XBASE;);
 R z;   
}

I jtxint(J jt,X w){I c,n,*v,z;
 n=AN(w); v=AV(w); v+=n; c=z=*--v;
 ASSERT(n<=XIDIG&&c!=XPINF&&c!=XNINF,EVDOMAIN);
 DO(n-1, z=*--v+z*XBASE;);
 ASSERT((c<0)==(z<0),EVDOMAIN);
 R z;
}

XF1(jtxstd){A z;B b;I c=0,d,i,j,k,m=XBASE,n,*zv;
 RZ(w);
 n=AN(w); RZ(z=ca(w)); zv=AV(z);
 b=0; j=n; DO(n, --j; if(zv[j]){b=0<zv[j]; break;});
 if(b) for(i=0;i<n;++i){
  k=zv[i]+=c; 
  if     (0>  k){c=-1-(-k)/m; zv[i]=d=m-(-k)%m; if(d== m){zv[i]=0; ++c;}}
  else if(m<= k){c=k/m;       zv[i]=k%m;}
  else          c=0;
 }else for(i=0;i<n;++i){
  k=zv[i]+=c; 
  if     (0<  k){c=1+k/m;     zv[i]=d=(k%m)-m;  if(d==-m){zv[i]=0; --c;}}
  else if(m<=-k){c=-(-k)/m;   zv[i]=-(-k)%m;}
  else          c=0;
 }
 if(c)R over(z,sc(c));
 j=n-1; while(j&&!zv[j])--j; ++j;
 R j==n?z:vec(INT,j,zv);
}    /* convert to standard form */

int jtxcompare(J jt,X a,X w){I*av,j,m,n,x,y,*wv;int s,t;
 RE(1);
 m=AN(a); av=AV(a); x=av[m-1]; s=SGN(x);
 n=AN(w); wv=AV(w); y=wv[n-1]; t=SGN(y);
 if(s!=t)R s?s:-t;
 if(1==m&&(x==XPINF||x==XNINF))R 0<x? !(1==n&&y==XPINF):-!(1==n&&y==XNINF);
 if(1==n&&(y==XPINF||y==XNINF))R 0<y?-!(1==m&&x==XPINF): !(1==m&&x==XNINF);
 if(m!=n)R m>n?s:-s;
 j=m; DO(m, --j; if(av[j]!=wv[j])R av[j]>wv[j]?1:-1;);
 R 0;
}    /* _1 0 1 depending on whether a<w, a=w, a>w */


XF1(jtxsgn){I x=XDIG(w); R xc(SGN(x));}

XF2(jtxplus){PROLOG;A z;I an,*av,c,d,m,n,wn,*wv,*zv;
 RZ(a&&w);
 an=AN(a); av=AV(a); c=av[an-1];
 wn=AN(w); wv=AV(w); d=wv[wn-1];
 if(c==XPINF||c==XNINF||d==XPINF||d==XNINF){
  ASSERT(!(c==XPINF&&d==XNINF||c==XNINF&&d==XPINF),EVNAN);
  R vci(c==XPINF||d==XPINF?XPINF:XNINF);
 }
 m=MAX(an,wn); n=MIN(an,wn);
 GA(z,INT,m,1,0); zv=AV(z);
 DO(n, *zv++=*av+++*wv++;);
 if(m>n)ICPY(zv,an>wn?av:wv,m-n);
 EPILOG(xstd(z));
}

XF2(jtxminus){PROLOG;A z;I an,*av,c,d,m,n,wn,*wv,*zv;
 RZ(a&&w);
 an=AN(a); av=AV(a); c=av[an-1];
 wn=AN(w); wv=AV(w); d=wv[wn-1];
 if(c==XPINF||c==XNINF||d==XPINF||d==XNINF){
  ASSERT(c!=d,EVNAN);
  R vci(c==XPINF||d==XNINF?XPINF:XNINF);
 }
 m=MAX(an,wn); n=MIN(an,wn);
 GA(z,INT,m,1,0); zv=AV(z);
 DO(n, *zv++=*av++-*wv++;);
 if(m>n){if(an>wn)ICPY(zv,av,m-n); else DO(m-n, *zv++=-*wv++;);}
 EPILOG(xstd(z));
}

XF2(jtxtymes){A z;I an,*av,c,d,e,i,j,m=XBASE,n,*v,wn,*wv,*zv;
 RZ(a&&w);
 an=AN(a); av=AV(a); c=av[an-1];
 wn=AN(w); wv=AV(w); d=wv[wn-1];
 if(!c||!d)R xzero;
 if(c==XPINF||c==XNINF||d==XPINF||d==XNINF)R vci(0<c*d?XPINF:XNINF);
 n=an+wn; GA(z,INT,n,1,0); zv=v=AV(z); memset(zv,C0,n*SZI);
 for(i=0;i<an;++i,++zv){
  if(c=av[i])for(j=0;j<wn;++j){
   d=zv[j]+=c*wv[j];
   if     (m<= d){e=  d /m; zv[j]-=e*m; zv[1+j]+=e;}
   else if(m<=-d){e=(-d)/m; zv[j]+=e*m; zv[1+j]-=e;}
 }}
 R v[n-1]?z:vec(INT,v[n-2]?n-1:1,v);
}

static X jtshift10(J jt,I e,X w){A z;I c,d,k,m,n,q,r,*wv,*zv;
 n=AN(w); wv=AV(w); c=wv[n-1];
 q=e/XBASEN; r=e%XBASEN; d=0==r?1:1==r?10:2==r?100:1000;
 m=n+q+(XBASE<=c*d);
 GA(z,INT,m,1,0); zv=AV(z);
 DO(q, *zv++=0;);
 if(r){c=0; DO(n, k=c+d**wv++; *zv++=k%XBASE; c=k/XBASE;); if(c)*zv=c;}
 else DO(n, *zv++=*wv++;);
 R z;
}    /* w*10^e, positive w */

B jtxdivrem(J jt,X a,X w,X*qz,X*rz){B b,c;I*av,d,j,n,*qv,r,y;X q;
 j=n=AN(a); av=AV(a); b=0<=av[n-1];
 y=*AV(w); c=0<=y; if(!c)y=-y; r=0;
 GA(q,INT,n,1,0); qv=AV(q);
 switch(2*b+c){
  case 0: DO(n, --j; d=r*XBASE-av[j]; r=d%y; qv[j]=  d/y ;); r=-r;      break;
  case 1: DO(n, --j; d=r*XBASE-av[j]; r=d%y; qv[j]=-(d/y);); r=r?y-r:0; break;
  case 2: DO(n, --j; d=r*XBASE+av[j]; r=d%y; qv[j]=-(d/y);); r=r?r-y:0; break;
  case 3: DO(n, --j; d=r*XBASE+av[j]; r=d%y; qv[j]=  d/y ;);            break;
 }
 if(r&&b!=c){--qv[0]; DO(n-1, if(qv[i]>-XBASE)break; qv[i]=0; --qv[1+i];);}
 if(1<n&&!qv[n-1])AN(q)=*AS(q)=n-1;
 *qz=q; *rz=vec(INT,1L,&r); R 1;
}    /* (<.a%w),(w|a) where w has a single "digit" and is nonzero */
 
X jtxdiv(J jt,X a,X w,I mode){PROLOG;B di;I an,*av,c,c0,d,e,k,s,u[2],u1,wn,*wv,yn;X q,r,y;
 RZ(a&&w&&!jt->jerr);
 an=AN(a); av=AV(a); c=c0=av[an-1];
 wn=AN(w); wv=AV(w); d=   wv[wn-1]; di=d==XPINF||d==XNINF;
 if(c&&!d)R vci(0<c?XPINF:XNINF);
 if(c==XPINF||c==XNINF){ASSERT(!di,EVNAN); R vci(0<c*d?XPINF:XNINF);}
 if(di)R xzero;
 if(1==wn&&d){I*v;
  RZ(xdivrem(a,w,&q,&r));
  if(!*AV(r)||mode==XMFLR)R q;
  ASSERT(mode==XMCEIL,EWRAT);
  v=AV(q); ++*v; 
  R XBASE>*v?q:xstd(q);
 }
 switch((0<=c?2:0)+(0<=d)){
  case 0: R xdiv(negate(a),negate(w),mode);
  case 1: R negate(xdiv(negate(a),w,mode==XMFLR?XMCEIL:mode==XMCEIL?XMFLR:mode));
  case 2: R negate(xdiv(a,negate(w),mode==XMFLR?XMCEIL:mode==XMCEIL?XMFLR:mode));
  default:
   if(1!=(e=xcompare(a,w))){
    ASSERT(!(c&&e&&mode==XMEXACT),EWRAT); 
    d=c&&(mode||!e); 
    R vec(INT,1L,&d);
   }
   if(1<an)c=av[an-2]+c*XBASE;
   if(1<wn)d=wv[wn-2]+d*XBASE;
   e=c>=d?c/d:(I)((XBASE*(D)c)/d); u[0]=e%XBASE; u[1]=u1=e/XBASE; 
   RZ(q=vec(INT,u1?2L:1L,u)); 
   RZ(y=xtymes(w,q)); yn=AN(y); e=*(AV(y)+yn-1);
   k=c0>=e?c0/e:e/c0; 
   k=k<=3?0:k>3162?4:3<k&&k<=32?1:32<k&&k<=316?2:3;
   s=XBASEN*(an-yn)+(c0>=e?k:-k); 
   if(s){q=shift10(s,q); y=shift10(s,y);}
   EPILOG(xplus(q,xdiv(xminus(a,y),w,mode)));
}}   /* <.a%w (mode=XMFLR) or >.a%w (mode=XMCEIL) or a%w (mode=XMEXACT) */

XF2(jtxrem){I c,d,e;X q,r,y;
 RZ(a&&w);
 c=XDIG(a); d=XDIG(w);
 if(!c)R w;
 ASSERT(!(d==XPINF||d==XNINF),EVNAN);
 if(c==XPINF)R 0<=d?w:a;
 if(c==XNINF)R 0>=d?w:a;
 if(1==AN(a)&&c){RZ(xdivrem(w,a,&q,&r)); R r;}
 switch((0<=c?2:0)+(0<=d)){
  case 0:  R negate(xrem(negate(a),negate(w)));
  case 1:  y=xrem(negate(a),w); R xcompare(y,xzero)? xplus(a,y):y;
  case 2:  y=xrem(a,negate(w)); R xcompare(y,xzero)?xminus(a,y):y;
  default: R 0<=(e=xcompare(a,w)) ? (e?w:xzero) : xminus(w,xtymes(a,xdiv(w,a,XMFLR)));
}}
                                             
XF2(jtxgcd){I c,d,old;X p,q,t;
 RZ(a&&w);
 c=XDIG(a); if(0>c)RZ(a=negate(a)); 
 d=XDIG(w); if(0>d)RZ(w=negate(w));
 ASSERT(!(c==XPINF||c==XNINF||d==XPINF||d==XNINF),EVNAN);
 if(!c)R w;
 if(!d)R a;
 p=a; q=w; old=jt->tbase+jt->ttop;
 while(XDIG(p)){
  t=p;
  RZ(p=xrem(p,q));
  q=t;
  gc3(p,q,0L,old);
 }
 R q;
}

XF2(jtxlcm){R xtymes(a,xdiv(w,xgcd(a,w),XMEXACT));}

static X jtxexp(J jt,X w,I mode){I k,m;X s,y;
 RZ(w);
 k=XDIG(w);
 ASSERT(!k||mode!=XMEXACT,EWIRR);
 if(0>k)R xc(mode);
 m=(I)(2.71828*xint(w)); k=2; s=xplus(xone,w); y=w;
 DO(m, y=xtymes(y,w); s=xplus(xtymes(s,xc(k)),y); ++k;);
 R xdiv(s,xev1(apv(1+m,1L,1L),"*/"),mode);
}

XF2(jtxpow){PROLOG;I c,d,e,r;X m,t,z;
 RZ(a&&w);
 c=XDIG(a); d=XDIG(w); e=*AV(w);
 if(c==XPINF||c==XNINF){
  ASSERT(0<c||d!=XPINF,EVDOMAIN); 
  R vci(!d?1L:0>d?0L:0<c?c:1&e?XNINF:XPINF);
 }
 if(d==XPINF||d==XNINF){
  ASSERT(0<=c||d==XNINF,EVDOMAIN); 
  R vci(1==c&&1==AN(a)?1L:!c&&0>d||c&&0<d?XPINF:0L);
 }
 if(1==AN(a)&&(1==c||-1==c))R 1==c||0==e%2?xone:xc(-1L); 
 if(!c){ASSERT(0<=d,EWRAT); R d?xzero:xone;}
 if(0>d){
  ASSERT(!jt->xmod,EVDOMAIN); 
  ASSERT(jt->xmode!=XMEXACT,EWRAT); 
  r=jt->xmode==XMCEIL; R xc(0<c?r:1&e?r-1:r);
 }
 t=a; z=xone; m=jt->xmod?*XAV(jt->xmod):0;
 if(!m||1>xcompare(w,xc(IMAX))){
  ASSERT(m||2>=AN(w),EVLIMIT);
  RE(e=xint(w));
  if(m)while(e){if(1&e)RZ(z=xrem(m,xtymes(z,t))); RZ(t=xrem(m,xsq(t))); e>>=1;}
  else while(e){if(1&e)RZ(z=       xtymes(z,t) ); RZ(t=       xsq(t) ); e>>=1;}
 }else{B b;I n,*u,*v;X e;
  RZ(e=ca(w)); n=AN(e); v=AV(e);
  while(n){
   if(1&*v)RZ(z=xrem(m,xtymes(z,t))); 
   RZ(t=xrem(m,xtymes(t,t))); 
   b=1; c=0; u=v+n;
   DO(n, d=c+*--u; c=1&d?XBASE:0; *u=d>>1; if(b&=!*u)--n;);  /* e=.<.e%2 */
 }}
 EPILOG(z);
}

XF1(jtxsq){R xtymes(w,w);}

XF1(jtxsqrt){I c,m,n,p,q,*wv;X e,x;
 RZ(w);
 n=AN(w); wv=AV(w); c=wv[n-1];
 ASSERT(0<=c,EWIMAG);
 if(!(1&n))c=wv[n-2]+c*XBASE;
 m=(1+n)/2; RZ(x=apv(m,0L,0L)); *(AV(x)+m-1)=(I)sqrt((D)c);
 RZ(e=xc(2L));
 p=m*XBASEN; q=0; while(p){++q; p>>=1;} 
 DO(1+q, RZ(x=xdiv(xplus(x,xdiv(w,x,XMFLR)),e,XMFLR)););
 p=xcompare(w,xsq(x));
 switch(jt->xmode){
  default:     ASSERTSYS(0,"xsqrt");
  case XMFLR:  if(-1==p){--*AV(x); R xstd(x);}else R x;
  case XMCEIL: if( 1==p){++*AV(x); R xstd(x);}else R x;
  case XMEXACT: 
   if(!p)R x; 
   *AV(x)+=p; RZ(x=xstd(x));
   ASSERT(!xcompare(w,xsq(x)),EWIRR);
   R x;
}}

static XF2(jtxroot){A q;D x;I an,*av,c,d,r,wn,*wv;X n,n1,p,t,z;
 an=AN(a); av=AV(a); c=av[an-1];
 wn=AN(w); wv=AV(w); d=wv[wn-1]; 
 ASSERT(0<=d,EWIMAG);
 if(1==wn&&(0==d||1==d))R 1==d?xone:0<=c?xzero:vci(XPINF);
 if(!c&&0<d)R vci(XPINF);
 r=xint(a); if(jt->jerr){RESETERR; R xone;}
 if(2==r)R xsqrt(w);
 x=xlogabs(w)/r;
 if(x<709.78){RZ(q=ceil1(cvt(RAT,scf(exp(x))))); z=*XAV(q);}
 else        {RZ(q=cvt(XNUM,scf(ceil(x)))); z=xexp(*XAV(q),XMCEIL);}
 RZ(n=xc(r)); RZ(n1=xc(r-1));
 RZ(t=xdiv(w,p=xpow(z,n1),XMFLR));
 RZ(z=xdiv(xplus(t,xtymes(z,n1)),n,XMFLR))
 while(1){
  RZ(t=xdiv(w,p=xpow(z,n1),XMFLR));
  if(1>xcompare(z,t))break;
  RZ(z=xdiv(xplus(t,xtymes(z,n1)),n,XMFLR))
 }
 if(XMFLR==jt->xmode||!xcompare(w,xtymes(z,p)))R z;
 if(XMCEIL==jt->xmode)R xplus(z,xone);
 ASSERT(0,EWIRR);
}

D jtxlogabs(J jt,X w){D c;I m,n,*v;
 n=AN(w); m=MIN(n,20/XBASEN); v=n+AV(w);
 c=0.0; DO(m, c=c*XBASE+(D)*--v;);
 R log(ABS(c))+XBASEN*(n-m)*2.3025850929940457;
}

static XF1(jtxlog1){B b;I c;
 c=XDIG(w); b=1==c&&1==AN(w);
 ASSERT(0<=c,EWIMAG);
 ASSERT(b||jt->xmode!=XMEXACT,EWIRR);
 R xc((I)xlogabs(w)+(!b&&jt->xmode==XMCEIL));
}

static D jtxlogd1(J jt,X w){ASSERT(0<=XDIG(w),EWIMAG); R xlogabs(w);}

static Z jtxlogz1(J jt,X w){Z z; z.re=xlogabs(w); z.im=0>XDIG(w)?PI:0.0; R z;}


static XF2(jtxlog2sub){ASSERT(0,EVNONCE);}

static XF2(jtxlog2){D c,d,x,y;I an,*av,j,k,m,n,wn,*wv;X p,q;
 RZ(a&&w);
 an=AN(a); av=AV(a); c=(D)av[an-1]; if(1<an)c=av[an-2]+c*XBASE;
 wn=AN(w); wv=AV(w); d=(D)wv[wn-1]; if(1<wn)d=wv[wn-2]+d*XBASE;
 if(2<an)R xlog2sub(a,w);
 ASSERT(0<=c,EWIMAG);
 if(!c){ASSERT(d,EVDOMAIN); R xzero;}
 if(!d){ASSERT(0<c,EVDOMAIN); R vci(XNINF);}
 ASSERT(0<d,EVDOMAIN);
 if(1==c)R 1==d?xzero:vci(XPINF);
 x=log(c)+XBASEN*(2<an?an-2:0)*2.3025850929940457;
 y=log(d)+XBASEN*(2<wn?wn-2:0)*2.3025850929940457;
 m=n=(I)(y/x+(an<wn));
 RZ(p=q=xpow(a,xc(m))); j=k=xcompare(p,w);
 if     (0<j){--m; RZ(p=xdiv(p,a,XMEXACT)); j=xcompare(p,w); if(0<j)R xlog2sub(a,w);}
 else if(0>j){++n; RZ(q=xtymes(p,a));       k=xcompare(q,w); if(0>k)R xlog2sub(a,w);}
 ASSERT(jt->xmode!=XMEXACT||!j||!k,EWIRR); 
 R xc(!j?m:!k?n:jt->xmode==XMCEIL?n:m);
}

F2(jtxlog2a){A z; GA(z,XNUM,1L,0L,0L); *XAV(z)=xlog2(*XAV(a),*XAV(w)); RNE(z);}
F2(jtxroota){A z; GA(z,XNUM,1L,0L,0L); *XAV(z)=xroot(*XAV(a),*XAV(w)); RNE(z);}

XF1(jtxfact){I n;
 n=*AV(w);
 if(n==XPINF||n==XNINF)R vci(XPINF);
 RE(n=xint(w)); 
 if(0>n)R vci(n%2?XPINF:XNINF);
 R xev1(apv(n,1L,1L),"*/");
}

static XF2(jtxbinp){PROLOG;D m;I i,n;X c,d,p,q,r,s;
 RZ(d=xminus(w,a)); s=1==xcompare(a,d)?d:a; RE(n=xint(s));
 m=xdouble(w);
 if(m<=IMAX){
  RZ(p=less(ravel(factor(apv(n,(I)m,-1L))),zero));
  RZ(q=less(ravel(factor(apv(n,1L,   1L))),zero));
  c=over(p,q);
  d=repeat(v2(AN(p),AN(q)),v2(1L,-1L));
  EPILOG(xev1(repeat(ev2(c,d,"+//."),nub(c)),"*/"));
 }else{
  p=q=xone; r=w;  
  for(i=0;i<n;++i){
   p=xtymes(p,r); r=xminus(r,xone);  
   q=xtymes(q,s); s=xminus(s,xone);
   d=xgcd(p,q); p=xdiv(p,d,XMEXACT); q=xdiv(q,d,XMEXACT);
   if(jt->jerr)R 0;
  }
  EPILOG(p);
}}   /* non-negative x,y; x<=y */

XF2(jtxbin){X d,z;
 RZ(d=xminus(w,a));
 switch(4*(0>XDIG(a))+2*(0>XDIG(w))+(0>XDIG(d))){
  default:             ASSERTSYS(0,"xbin");
  case 2: /* 0 1 0 */  /* Impossible */
  case 5: /* 1 0 1 */  /* Impossible */
  case 1: /* 0 0 1 */ 
  case 4: /* 1 0 0 */ 
  case 7: /* 1 1 1 */  R xzero;
  case 0: /* 0 0 0 */  R xbinp(a,w);
  case 3: /* 0 1 1 */  
   z=xbinp(a,xminus(a,xplus(w,xone)));           R*AV(a)%2?negate(z):z;
  case 6: /* 1 1 0 */  
   z=xbinp(xminus(xc(-1L),w),xminus(xc(-1L),a)); R*AV(d)%2?negate(z):z;
}}

static A jtpiev(J jt,I n,X b){A e;I ek,i,n1=n-1;X bi,e0,e1,*ev,t;
 GA(e,XNUM,n,1,0); ev=XAV(e);
 bi=e0=e1=xone;
 for(i=0,ek=1;i<n1;++i,ek+=3){
  ev[i]=xtymes(e0,xtymes(XCUBE(e1),bi));
  t=xtymes(xc(ek),xtymes(xc(1+ek),xc(2+ek)));
  e0=xtymes(e0,t);        /* e0 = ! 3*i */
  e1=xtymes(e1,xc(1+i));  /* e1 = ! i   */
  bi=xtymes(bi,b);        /* bi = b^i   */
 }
 ev[i]=xtymes(e0,xtymes(XCUBE(e1),bi));
 RE(e); R e;
}

static XF1(jtxpi){A e;B p;I i,n,n1,sk;X a,b,c,d,*ev,k,f,m,q,s,s0,t;
 RZ(w);
 if(!XDIG(w))R xzero;
 ASSERT(jt->xmode!=XMEXACT,EVDOMAIN);
 RZ(a=xc(545140134L));
 RZ(b=XCUBE(xc(640320L)));
 RZ(c=xc(13591409L));
 RZ(d=xplus(xc(541681608L),xtymes(xc(10L),xc(600000000L))));
 n1=(13+AN(w)*XBASEN)/14; n=1+n1;
 RZ(e=piev(n,b)); ev=XAV(e); m=ev[n1];
 f=xzero; s0=xone; sk=1;
 for(i=p=0;;++i,p=!p){
  s=xtymes(s0,xplus(c,xtymes(a,xc(i))));
  t=xdiv(xtymes(s,m),ev[i],XMEXACT);
  f=p?xminus(f,t):xplus(f,t);
  if(i==n1)break;
  DO(6, s0=xtymes(s0,xc(sk++));); RE(s0);  /* s0 = ! 6*i */
 }
 f=xtymes(d,f);
 q=xpow(xc(10L),xc(14*n1));
 k=xtymes(xtymes(a,m),xsqrt(xtymes(b,xsq(q))));
 R xdiv(xtymes(k,w),xtymes(f,q),jt->xmode);
}    /* Chudnovsky Bros. */

APFX( plusXX, X,X,X, xplus )
APFX(minusXX, X,X,X, xminus)
APFX(tymesXX, X,X,X, xtymes)
APFX(  divXX, X,X,X, XDIV  )
APFX(  remXX, X,X,X, xrem  )
APFX(  gcdXX, X,X,X, xgcd  )
APFX(  lcmXX, X,X,X, xlcm  )
APFX(  minXX, X,X,X, XMIN  )
APFX(  maxXX, X,X,X, XMAX  )
APFX(  powXX, X,X,X, xpow  )
APFX(  binXX, X,X,X, xbin  )

AMON( sgnX, X,X, *z=  xsgn(*x);)
AMON(sqrtX, X,X, *z= xsqrt(*x);)
AMON( expX, X,X, *z=  xexp(*x,jt->xmode);)
AMON( logX, X,X, *z= xlog1(*x);)
AMON(logXD, D,X, *z=xlogd1(*x);)
AMON(logXZ, Z,X, *z=xlogz1(*x);)
AMON( absX, X,X, *z=   mag(*x);)
AMON(factX, X,X, *z= xfact(*x);)
AMON( pixX, X,X, *z=   xpi(*x);)


F1(jtdigits10){A z;B b=0;I c,m,n,*v,*zv,*zv0;X x;
 RZ(w);
 if(!AR(w))switch(AT(w)){
  case INT:  b=0<=*AV(w); break;
  case XNUM: x=*XAV(w); n=AN(x); v=AV(x); b=0<=v[n-1]; break;
  case RAT:  x=*XAV(w); n=AN(x); v=AV(x); b=0<=v[n-1]&&equ(iv1,QAV(w)->d);
 }
 if(!b)R rank1ex(thorn1(w),0L,0L,jtexec1);
 m=INT&AT(w)?(SY_64?19:10):XBASEN*AN(x);
 GA(z,INT,m,1,0); zv=zv0=AV(z);
 if(INT&AT(w)){c=*AV(w); *zv++=c%10; while(c/=10)*zv++=c%10;}
 else{
  DO(n-1, c=*v++; DO(XBASEN, *zv++=c%10; c/=10;););
  c=*v++; if(c||1==n)*zv++=c%10; while(c/=10)*zv++=c%10;
 }
 AN(z)=*AS(z)=n=zv-zv0; 
 zv=zv0; v=zv0+n-1; DO(n/2, c=*zv; *zv++=*v; *v--=c;); /* reverse in place */
 R z;
}    /* "."0@": w */


#define DXBODY(exp)  DECLG;A y=sv->h,z;I m=jt->xmode; jt->xmode=XMFLR; z=exp; jt->xmode=m; R z
#define DX1(f,exp)   DF1(f){DXBODY(exp);} 
#define DX2(f,exp)   DF2(f){DXBODY(exp);}
#define XT(w)        tymes(y,w)

static DX1(postmult1, XT(CALL1(g1,  w,gs)))
static DX2(postmult2, XT(CALL2(g2,a,w,gs)))

static DX1(premult1, CALL1(g1,      XT(w),gs))
static DX2(premult2, CALL2(g2,XT(a),XT(w),gs))

static DX1(ydiv1, CALL2(g2,y,    w,gs))
static DX2(ydiv2, CALL2(g2,XT(a),w,gs))

static DX1(ysqrt, CALL1(g1,tymes(w,XT(y)),gs))
