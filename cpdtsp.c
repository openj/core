/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Conjunctions: Dyad +/ .* on Sparse Arguments                            */

#include "j.h"


F1(jtbtreetest){ASSERT(0,EVDOMAIN);}
F1(jtbtreedft){ASSERT(0,EVDOMAIN);}


/*
vm=: 4 : 0     NB. vector +/ .* sparse matrix
 if. dense x do. yy=.   5$.y [ 'i j'=. |:   4$.y
 else.           yy=. b#5$.y [ 'i j'=. |: b#4$.y [ b=. ({."1 ]4$.y) e. ,4$.x end.
 1 $. (}.$y);0;0;(,.~.j);j +//. (i{x) * yy
)

mv=: 4 : 0     NB. sparse matrix +/ .* vector
 if. dense y do. xx=.   5$.x [ 'i j'=. |:   4$.x
 else.           xx=. b#5$.x [ 'i j'=. |: b#4$.x [ b=. ({:"1 ]4$.x) e. ,4$.y end.
 1 $. (#x);0;0;(,.~.i);i +//. xx*j{y
)
*/

static F2(jtpdtspvv){A x;D*av,s,t,*wv,z;I i,*u,*u0,*uu,*v,*v0,*vv;P*ap,*wp;
 RZ(a&&w);
 ap=PAV(a); x=SPA(ap,i); u=u0=AV(x); uu=u+AN(x); x=SPA(ap,x); av=DAV(x);
 wp=PAV(w); x=SPA(wp,i); v=v0=AV(x); vv=v+AN(x); x=SPA(wp,x); wv=DAV(x);
 z=0.0;
 NAN0;
 while(1){
  i=*u; while(i>*v&&v<vv)++v; if(v==vv)break;
  if(i==*v){s=av[u-u0]; t=wv[v-v0]; z+=s&&t?s*t:0; ++u; ++v; continue;}
  i=*v; while(i>*u&&u<uu)++u; if(u==uu)break;
  if(i==*u){s=av[u-u0]; t=wv[v-v0]; z+=s&&t?s*t:0; ++u; ++v; continue;}
 }
 NAN1;
 R scf(z);
}

static F2(jtpdtspmv){A ax,b,g,x,wx,y,yi,yj,z;B*bv;I m,n,s[2],*u,*v,*yv;P*ap,*wp,*zp;
 RZ(a&&w);
 ap=PAV(a); y=SPA(ap,i); yv=AV(y); s[0]=n=*AS(y); s[1]=1;
 GA(yj,INT,n,2,s);
 if(DENSE&AT(w)){
  GA(yi,INT,n,2,s); u=AV(yi); AR(yj)=1; v=AV(yj);
  DO(n, *u++=*yv++; *v++=*yv++;);
  ax=SPA(ap,x); RZ(wx=from(yj,w));
 }else{
  v=AV(yj);
  DO(n, yv++; *v++=*yv++;);
  wp=PAV(w); RZ(b=eps(yj,SPA(wp,i))); bv=BAV(b); 
  AN(yj)=*AS(yj)=*s=m=bsum(n,bv); v=AV(yj); yv=AV(y);
  GA(yi,INT,m,2,s); u=AV(yi);
  DO(n, if(*bv++){*u++=*yv++; *v++=*yv++;}else yv+=2;);
  RZ(ax=repeat(b,SPA(ap,x))); RZ(wx=from(indexof(SPA(wp,i),yj),SPA(wp,x))); 
 }
 RZ(x=df2(yi,tymes(ax,wx),sldot(slash(ds(CPLUS)))));
 RZ(y=nub(yi));
 RZ(g=grade1(y));
 GA(z,STYPE(AT(x)),1,1,AS(a)); zp=PAV(z);
 SPB(zp,a,iv0);
 SPB(zp,e,scf(0.0));
 SPB(zp,i,from(g,y));
 SPB(zp,x,from(g,x));
 R z;
}    /* (sparse matrix) +/ .* vector; non-complex */

static F2(jtpdtspvm){A ax,b,g,x,wx,y,yi,yj,z;B*bv;D*av,c,d,*wv,*xv;I m,n,s[2],*u,*v,*yv;P*ap,*wp,*zp;
 RZ(a&&w);
 wp=PAV(w); y=SPA(wp,i); yv=AV(y); s[0]=n=*AS(y); s[1]=1;
 if(DENSE&AT(a)){
  GA(yj,INT,n,2,s); v=AV(yj); 
  av=DAV(a); x=SPA(wp,x); wv=DAV(x);
  GA(x,FL,n,1,0); xv=DAV(x);
  DO(n, c=av[*yv++]; *v++=*yv++; d=*wv++; *xv++=c&&d?c*d:0;);
 }else{
  GA(yi,INT,n,2,s); u=AV(yi);
  DO(n, *u++=*yv++; yv++;);
  ap=PAV(a); RZ(b=eps(yi,SPA(ap,i))); bv=BAV(b); 
  AN(yi)=*AS(yi)=*s=m=bsum(n,bv); u=AV(yi); yv=AV(y);
  GA(yj,INT,m,2,s); v=AV(yj);
  DO(n, if(*bv++){*u++=*yv++; *v++=*yv++;}else yv+=2;);
  RZ(ax=from(indexof(SPA(ap,i),yi),SPA(ap,x))); RZ(wx=repeat(b,SPA(wp,x)));
  RZ(x=tymes(ax,wx));
 }
 RZ(x=df2(yj,x,sldot(slash(ds(CPLUS)))));
 RZ(y=nub(yj));
 RZ(g=grade1(y));
 GA(z,STYPE(AT(x)),1,1,1+AS(w)); zp=PAV(z);
 SPB(zp,a,iv0);
 SPB(zp,e,scf(0.0));
 SPB(zp,i,from(g,y));
 SPB(zp,x,from(g,x));
 R z;
}    /* vector +/ .* (sparse matrix); non-complex */

/* p  - ptr to sparse array value part   */
/* n  - # elements in index array        */
/* iv - ptr to index array (row,column)  */
/* m  - length of nv                     */
/* nv - row boundaries in iv             */
/* xv - ptr to data values               */
static B jtmmprep(J jt,P*p,I*n,I**iv,I*m,I**nv,D**xv){A x;I j,k,q,*u,*v;
 x=SPA(p,x); if(!(FL&AT(x)))RZ(x=cvt(FL,x)); *xv=DAV(x);
 x=SPA(p,i); *iv=u=AV(x); *n=AN(x);
 if(m&&nv){
  q=*AS(x); k=q?2+u[(q-1)<<1]-*u:1;
  GA(x,INT,k,1,0); *nv=v=AV(x);
  k=-1; DO(q, j=*u++; u++; if(j>k){*v++=i; k=j;});
  *v++=q; AN(x)=*AS(x)=k=v-*nv; *m=k-1;
 }
 R 1;
}

/* ii  - row index in result                  */
/* zjn - # temp result values to be harvested */
/* zj  - temp result column indices           */
/* zyv - ptr to temp result values            */
/* n   - # result values so far               */
/* zi  - ptr to result index array            */
/* zx  - ptr to result value array            */
static B jtmmharvest(J jt,I ii,I zjn,A zj,D*zyv,I*n,A*zi,A*zx){A x;D*zxv,*zxv0;I j,m,p,*v,*ziv;
 m=MIN(*AS(*zi),*AS(*zx));
 while(m<*n+zjn){RZ(*zi=ext(0,*zi)); RZ(*zx=ext(0,*zx)); m=MIN(*AS(*zi),*AS(*zx));}
 m=AN(zj); AN(zj)=*AS(zj)=zjn; RZ(x=grade2(zj,zj)); AN(zj)=*AS(zj)=m; 
 p=-1; v=AV(x); ziv=AV(*zi)+(*n<<1); zxv=zxv0=DAV(*zx)+*n;
 DO(zjn, if(p<(j=*v++)){p=j; *ziv++=ii; *ziv++=j; *zxv++=zyv[j]; zyv[j]=0;});
 *n+=zxv-zxv0;
 R 1;
}    /* collect accumulated values for row ii */

static F2(jtpdtspmm){A z,zi,zj,zx,zy;D*axv,c,d,*dv,*wxv,*zyv;
     I*aiv,*aivm,i,ii,j,k,k0,m,n=0,old,p,q,*v,wm,*wiv,*wnv,*zjv,*zjv0;P*zp;
 RZ(a&&w);
 RZ(mmprep(PAV(a),&m,&aiv,0L ,0L  ,&axv)); aivm=m+aiv;
 RZ(mmprep(PAV(w),&m,&wiv,&wm,&wnv,&wxv));
 GA(zy,FL,*(1+AS(w)),1,0); zyv=DAV(zy); memset(zyv,C0,AN(zy)*sizeof(D));
 old=jt->tbase+jt->ttop; 
 RZ(zj=exta(INT,1L,1L,1000L)); zjv0=AV(zj);
 RZ(zi=exta(INT,2L,2L,1000L));
 RZ(zx=exta(FL, 1L,1L,1000L));
 NAN0;
 if(wm&&aiv<aivm){
  i=*aiv++; zjv=zjv0; k=-1;
  while(aiv<aivm){                 /* run through aiv and axv exactly once */
   j=*aiv++; 
   if(c=*axv++){
    k0=k; p=k+1; q=wm; ii=-1;
    while(p<=q){ii=wiv[wnv[k=(p+q)>>1]<<1]; if(j==ii)break; if(j<ii)q=k-1; else p=k+1;}
    if(j==ii){
     p=wnv[1+k]-wnv[k]; dv=wxv+wnv[k]; v=1+wiv+(wnv[k]<<1);
     q=zjv-zjv0; while(AN(zj)<p+q){RZ(zj=ext(0,zj)); zjv0=AV(zj); zjv=q+zjv0;}
     DO(p, if(d=*dv++){if(!zyv[*v])*zjv++=*v; zyv[*v++]+=c*d; v++;});
    }else k=k0;
   }
   if(aiv>=aivm||i<(p=*aiv++)){    /* done with row i in a, emit row i in z */
    RZ(mmharvest(i,zjv-zjv0,zj,zyv,&n,&zi,&zx));
    gc3(zj,zi,zx,old);
    zjv=zjv0; k=-1; i=p;
 }}}
 NAN1;
 *AS(zx)=AN(zx)=*AS(zi)=n; AN(zi)=n<<1;
 GA(z,SFL,1,2,AS(a)); *(1+AS(z))=*(1+AS(w));
 zp=PAV(z); SPB(zp,a,IX(2)); SPB(zp,e,scf(0.0)); SPB(zp,i,zi); SPB(zp,x,zx);
 R z;
}


F2(jtpdtsp){A x;B ab=0,wb=0;P*p;
 RZ(a&&w);
 ASSERT(!AR(a)||!AR(w)||*(AS(a)+AR(a)-1)==*AS(w),EVLENGTH);
 if(AT(a)&FL+SFL&&AT(w)&FL+SFL){
  if(SPARSE&AT(a)){p=PAV(a); x=SPA(p,a); ab=AR(a)==AN(x)&&equ(zero,SPA(p,e));}
  if(SPARSE&AT(w)){p=PAV(w); x=SPA(p,a); wb=AR(w)==AN(x)&&equ(zero,SPA(p,e));}
 }
 if(ab&&1==AR(a)&&wb&&1==AR(w))R pdtspvv(a,w);
 if(ab&&2==AR(a)&&    1==AR(w))R pdtspmv(a,w);
 if(    1==AR(a)&&wb&&2==AR(w))R pdtspvm(a,w);
 if(ab&&2==AR(a)&&wb&&2==AR(w))R pdtspmm(a,w);
 R df2(a,w,atop(slash(ds(CPLUS)),qq(ds(CSTAR),v2(1L,AR(w)))));
}
