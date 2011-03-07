/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Conjunctions: Power Operator ^: and Associates                          */

#include "j.h"


static DF1(jtpowseqlim){PROLOG;A x,y,z,*zv;I i,n;
 RZ(w);
 RZ(z=exta(BOX,1L,1L,20L)); zv=AAV(z); *zv++=x=w;
 i=1; n=AN(z);
 while(1){
  if(n==i){RZ(z=ext(0,z)); zv=i+AAV(z); n=AN(z);}
  RZ(*zv++=x=df1(y=x,self));
  if(equ(x,y)){AN(z)=*AS(z)=i; break;}
  ++i;
 }
 EPILOG(ope(z));
}    /* f^:(<_) w */

static F2(jttclosure){A z;B b;I an,*av,c,d,i,wn,wr,wt,*wv,*zu,*zv,*zz;
 RZ(a&&w);
 wt=AT(w); wn=AN(w); wr=AR(w);
 if(B01&wt)RZ(w=cvt(INT,w)); wv=AV(w);
 av=AV(a); an=AN(a);
 RZ(z=exta(INT,1+wr,wn,20L)); 
 zv=AV(z); zz=zv+AN(z);
 if(1==wn){
  *zv++=c=*wv; d=1+c;
  while(c!=d){
   if(zv==zz){i=zv-AV(z); RZ(z=ext(0,z)); zv=AV(z)+i; zz=AV(z)+AN(z);}
   d=c; if(0>c)c+=an; ASSERT(0<=c&&c<an,EVINDEX); *zv++=c=av[c];
 }}else{
  ICPY(zv,wv,wn); zu=zv; zv+=wn;
  while(1){
   if(zv==zz){i=zv-AV(z); RZ(z=ext(0,z)); zv=AV(z)+i; zz=AV(z)+AN(z); zu=zv-wn;}
   b=1; DO(wn, d=c=*zu++; if(0>c)c+=an; ASSERT(0<=c&&c<an,EVINDEX); *zv++=c=av[c]; if(c!=d)b=0;);
   if(b)break;
 }}
 i=zv-AV(z); *AS(z)=d=i/wn-1; AN(z)=d*wn; ICPY(1+AS(z),AS(w),wr); 
 R z;
}    /* {&a^:(<_) w */

static DF1(jtindexseqlim1){A fs;
 RZ(w); 
 fs=VAV(self)->f;
 R AT(w)&B01+INT?tclosure(VAV(fs)->g,w):powseqlim(w,fs);
}    /* {&x^:(<_) w */

static DF2(jtindexseqlim2){
 RZ(a&&w);
 R 1==AR(a)&&AT(a)&INT&&AT(w)&B01+INT?tclosure(a,w):powseqlim(w,amp(ds(CFROM),a));
}    /* a {~^:(<_) w */

static DF1(jtpowseq){A fs,gs,x;I n=IMAX;V*sv;
 RZ(w);
 sv=VAV(self); fs=sv->f; gs=sv->g;
 ASSERT(!AR(gs),EVRANK);
 ASSERT(BOX&AT(gs),EVDOMAIN);
 x=*AAV(gs); if(!AR(x))RE(n=i0(vib(x)));
 if(0>n){RZ(fs=inv(fs)); n=-n;}
 if(n==IMAX||1==AR(x)&&!AN(x))R powseqlim(w,fs);
 R df1(w,powop(fs,IX(n)));
}    /* f^:(<n) w */

static DF1(jtfpown){A fs,z;AF f1;I n,old;V*sv;
 RZ(w);
 sv=VAV(self); 
 switch(n=*AV(sv->h)){
  case 0:  R ca(w);
  case 1:  fs=sv->f; R CALL1(VAV(fs)->f1,w,fs);
  default: 
   fs=sv->f; f1=VAV(fs)->f1;
   z=w; 
   old=jt->tbase+jt->ttop; 
   DO(n, RZ(z=CALL1(f1,z,fs)); gc(z,old);); 
   R z;
}}   /* single positive finite exponent */

static DF1(jtply1){PROLOG;DECLFG;A b,hs,j,x,*xv,y,z;B*bv,q;I i,k,m,n,*nv,old,p=0;
 hs=sv->h; m=AN(hs); 
 RZ(x=ravel(hs)); RZ(y=from(j=grade1(x),x)); nv=AV(y);
 GA(x,BOX,m,1,0); xv=AAV(x);
 while(p<m&&0>nv[p])p++;
 if(p<m){
  RZ(z=ca(w));
  n=nv[m-1]; k=p;
  while(k<m&&!nv[k]){xv[k]=z; ++k;}
  RZ(b=eq(ainf,from(j,ravel(gs)))); bv=BAV(b); q=k<m?bv[k]:0;
  old=jt->tbase+jt->ttop;
  for(i=1;i<=n;++i){
   RZ(z=CALL1(f1,y=z,fs));
   if(q&&equ(y,z)){DO(m-k, xv[k]=z; ++k;); break;}
   while(k<m&&i==nv[k]){xv[k]=z; ++k; q=k<m?bv[k]:0;}
   if(!(i%10))gc3(x,z,0L,old);
 }}
 if(0<p){
  RZ(fs=inv(fs)); f1=VAV(fs)->f1;
  RZ(z=ca(w));
  n=nv[0]; k=p-1;
  RZ(b=eq(scf(-inf),from(j,ravel(gs)))); bv=BAV(b); q=bv[k];
  old=jt->tbase+jt->ttop;
  for(i=-1;i>=n;--i){
   RZ(z=CALL1(f1,y=z,fs));
   if(q&&equ(y,z)){DO(1+k, xv[k]=z; --k;); break;}
   while(0<=k&&i==nv[k]){xv[k]=z; --k; q=0<=k?bv[k]:0;}
   if(!(i%10))gc3(x,z,0L,old);
 }}
 z=ope(reshape(shape(hs),from(grade1(j),x))); EPILOG(z);
}

#define DIST(i,x)  if(i==e){v=CAV(x); \
                     while(k<m&&i==(e=nv[jv[k]])){MC(zv+c*jv[k],v,c); ++k;}}

static DF1(jtply1s){DECLFG;A hs,j,y,y1,z;C*v,*zv;I c,e,i,*jv,k,m,n,*nv,r,*s,t,zn;
 RZ(w);
 hs=sv->h; m=AN(hs); nv=AV(hs); 
 RZ(j=grade1(ravel(hs))); jv=AV(j); e=nv[*jv];
 if(!e&&!nv[jv[m-1]])R reshape(over(shape(hs),shape(w)),w);
 RZ(y=y1=CALL1(f1,w,fs)); t=AT(y); r=AR(y);
 if(0>e||t==BOX)R ply1(w,self);
 if(!e){
  if(HOMO(t,AT(w)))RZ(w=pcvt(t,w));
  if(!(t==AT(w)&&AN(y)==AN(w)&&(r==AR(w)||1>=r&&1>=AR(w))))R ply1(w,self);
 }
 k=AR(hs); RE(zn=mult(m,AN(y)));
 GA(z,AT(y),zn,k+AR(y),0); zv=CAV(z);
 s=AS(z); ICPY(s,AS(hs),k); ICPY(k+s,AS(y),r);
 n=nv[jv[m-1]]; c=AN(y)*bp(t); s=AS(y);
 k=0; DIST(0,w); DIST(1,y);
 for(i=2;i<=n;++i){
  RZ(y=CALL1(f1,y,fs));
  if(t!=AT(y)||r!=AR(y)||ICMP(AS(y),s,r))R ply1(w,self);
  DIST(i,y);
 }
 R z;
}    /* f^:n w, non-negative finite n, well-behaved f */

static DF1(jtinv1){DECLFG;A z; RZ(w);    FDEPINC(1); z=df1(w,inv(fs));        FDEPDEC(1); R z;}
static DF2(jtinv2){DECLFG;A z; RZ(a&&w); FDEPINC(1); z=df1(w,inv(amp(a,fs))); FDEPDEC(1); R z;}

static CS2(jtply2,  df1(w,powop(amp(a,fs),gs)))

static DF1(jtpowg1){A h=VAV(self)->h; R df1(  w,*AAV(h));}
static DF2(jtpowg2){A h=VAV(self)->h; R df2(a,w,*AAV(h));}

static CS1(jtpowv1,  df1(  w,powop(fs,        CALL1(g1,  w,gs))))
static CS2(jtpowv2,  df2(a,w,powop(fs,        CALL2(g2,a,w,gs))))
static CS2(jtpowv2a, df1(  w,powop(VAV(fs)->f,CALL2(g2,a,w,gs))))

F2(jtpowop){A hs;B b,r;I m,n;V*v;
 RZ(a&&w);
 switch(CONJCASE(a,w)){
  default: ASSERTSYS(0,"powop");
  case NV: ASSERT(0,EVDOMAIN);
  case NN: ASSERT(-1==i0(w),EVDOMAIN); R vger2(CPOWOP,a,w);
  case VV:
   v=VAV(a); b=(v->id==CAT||v->id==CATCO)&&ID(v->g)==CRIGHT;
   R CDERIV(CPOWOP,jtpowv1,b?jtpowv2a:jtpowv2,RMAX,RMAX,RMAX);
  case VN:
   if(BOX&AT(w)){A x,y;AF f1,f2;
    if(ARELATIVE(w))RZ(w=car(w));
    if(!AR(w)&&(x=*AAV(w),!AR(x)&&NUMERIC&AT(x)||1==AR(x)&&!AN(x))){
     f1=jtpowseq; f2=jtply2; v=VAV(a);
     if((!AN(x)||FL&AT(x)&&inf==*DAV(x))&&
         CAMP==v->id&&(CFROM==ID(v->f)&&(y=v->g,INT&AT(y)&&1==AR(y))))f1=jtindexseqlim1;
     if(CTILDE==v->id&&CFROM==ID(v->f))f2=jtindexseqlim2;
     R CDERIV(CPOWOP,f1,f2,RMAX,RMAX,RMAX);
    }
    R gconj(a,w,CPOWOP);
   }
   RZ(hs=vib(w));
   b=0; m=AN(hs); n=m?*AV(hs):0; r=0<AR(hs);
   if(!r&&-1==n)R CDERIV(CPOWOP,jtinv1,jtinv2,RMAX,RMAX,RMAX);
   if(m&&AT(w)&FL+CMPX)RE(b=!all0(eps(w,over(ainf,scf(infm)))));
   R fdef(CPOWOP,VERB, b||!m?jtply1:!r&&0<=n?jtfpown:jtply1s,jtply2, a,w,hs,  
      0L,RMAX,RMAX,RMAX);
}}
