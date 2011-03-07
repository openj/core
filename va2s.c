/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Verbs: Atomic (Scalar) Dyadic Verbs on Sparse Arrays                    */

#include "j.h"
#include "ve.h"


static A jtvaspc(J jt,A a,A w,C id,VF ado,I cv,I t,I zt,I af,I acr,I wf,I wcr,I f,I r){A q;I*as,*v,*ws;
 as=AS(a);
 ws=AS(w);
 GA(q,INT,f+r,1,0); v=AV(q);
 if(r>acr){ICPY(v,wf+ws,r); RZ(a=irs2(vec(INT,r-acr,acr+v),a,0L,1L,0L,jtreshape));}
 if(r>wcr){ICPY(v,af+as,r); RZ(w=irs2(vec(INT,r-wcr,wcr+v),w,0L,1L,0L,jtreshape));}
 R vasp(a,w,id,ado,cv,t,zt,af,r,wf,r,f,r);
}    /* prefix agreement on cells */

F1(jtvaspz){A e,x,y;B c,*u,*xu,*xv;I j,n,*v,*yu,*yv,xc,yc;P*wp;
 if(!(SB01&AT(w)))R w;
 wp=PAV(w); 
 e=SPA(wp,e); c=!*BAV(e);
 x=SPA(wp,x); xv=xu=u=BAV(x); xc=aii(x); n=*AS(x); j=0;
 y=SPA(wp,i); yv=yu=   AV(y); yc=*(1+AS(y));
 if(!(n&&xc&&yc))R w;
 while(u=memchr(xv+xc*j,c,xc*(n-j))){
  j=(u-xv)/xc; v=yv+yc*j;
  if(v==yu){yu+=yc; xu+=xc;}
  else{DO(yc, *yu++=*v++;); if(1<xc){MC(xu,xv+xc*j,xc); xu+=xc;}}
  ++j;
 }
 n=(yu-yv)/yc;
 if(1==xc)memset(xv,c,n);
 *AS(y)=n; AN(y)=n*yc;
 *AS(x)=n; AN(x)=n*xc;
 R w;
}    /* post processing on result; modifies argument in place */

static A jtvasp0(J jt,A a,A w,VF ado,I cv,I t,I zt){A e,x,xx,y,z,ze,zx;B b;I n;P*p,*zp;
 if(b=1&&AR(a)){xx=a; y=w;}else{xx=w; y=a;}
 p=PAV(xx); e=SPA(p,e); x=SPA(p,x); n=AN(x);
 if(t){
  if(t!=AT(x)){RZ(x=cvt(t,x)); RZ(e=cvt(t,e));} 
  if(t!=AT(y)) RZ(y=cvt(t,y));
 }
 GA(ze,zt,1,0,    0    );      ado(jt, 0,1L,1L,AV(ze),b?AV(e):AV(y),b?AV(y):AV(e)); RE(0);
 GA(zx,zt,n,AR(x),AS(x)); if(n)ado(jt,!b,1L,n, AV(zx),b?AV(x):AV(y),b?AV(y):AV(x)); RE(0);
 if(cv&VRI+VRD){RZ(ze=cvz(cv,ze)); RZ(zx=cvz(cv,zx));}
 GA(z,STYPE(AT(zx)),1,AR(xx),AS(xx)); zp=PAV(z);
 SPB(zp,a,ca(SPA(p,a)));
 SPB(zp,i,ca(SPA(p,i)));
 SPB(zp,e,ze);
 SPB(zp,x,zx);
 R vaspz(z);
}    /* one argument is sparse and the other is scalar */

/*
static B jtvaspprep(J jt,A a,A w,I t,I af,I acr,I wf,I wcr,I f,I r,A*ae,A*ay,A*ax,A*we,A*wy,A*wx,A*za){
     A aa,e,x,wa;B*b,sa,sw;I c,d,m,n,*u,*v;P*ap,*wp;
 sa=1&&AT(a)&SPARSE; 
 sw=1&&AT(w)&SPARSE;
 GA(x,B01,f+r,1,0); b=BAV(x); memset(b,C1,f); memset(b+f,C0,r);
 if(sa){ap=PAV(a); aa=SPA(ap,a); u=AV(aa); d=f-af; DO(AN(aa), c=u[i]; if(af<=c)b[c+d]=1;);}
 if(sw){wp=PAV(w); wa=SPA(wp,a); v=AV(wa); d=f-wf; DO(AN(wa), c=v[i]; if(wf<=c)b[c+d]=1;);}
 GA(x,INT,f+r,1,0); u=AV(x); m=0; DO(af, if(b[i])u[m++]=i;); DO(acr, if(b[f+i])u[m++]=af+i;); 
 GA(x,INT,f+r,1,0); v=AV(x); n=0; DO(wf, if(b[i])v[n++]=i;); DO(wcr, if(b[f+i])v[n++]=wf+i;); 
 if(!sa||m!=AN(aa)||memcmp(u,AV(aa),m*SZI))RZ(a=reaxis(vec(INT,m,u),a));
 if(!sw||n!=AN(wa)||memcmp(v,AV(wa),n*SZI))RZ(w=reaxis(vec(INT,n,v),w));
 ap=PAV(a); *ae=e=SPA(ap,e); *ay=SPA(ap,i); *ax=x=SPA(ap,x); if(t&&t!=AT(x)){RZ(*ae=cvt(t,e)); RZ(*ax=cvt(t,x));}
 wp=PAV(w); *we=e=SPA(wp,e); *wy=SPA(wp,i); *wx=x=SPA(wp,x); if(t&&t!=AT(x)){RZ(*we=cvt(t,e)); RZ(*wx=cvt(t,x));}
 RZ(*za=ifb(f+r,b));
 R 1;
}
*/

static B jtvaspeqprep(J jt,A a,A w,I t,I f,I r,A*ae,A*ay,A*ax,A*we,A*wy,A*wx,A*za){
     A aa,e,q,x,wa;B*b,sa,sw;I n,*v;P*p;
 sa=1&&AT(a)&SPARSE; 
 sw=1&&AT(w)&SPARSE; n=f+r;
 GA(x,B01,n,1,0); b=BAV(x); memset(b,C0,n);
 if(sa){p=PAV(a); aa=SPA(p,a); v=AV(aa); DO(AN(aa), b[v[i]]=1;);}
 if(sw){p=PAV(w); wa=SPA(p,a); v=AV(wa); DO(AN(wa), b[v[i]]=1;);}
 RZ(*za=q=ifb(n,b));
 if(!sa||!equ(q,aa))RZ(a=reaxis(q,a));
 if(!sw||!equ(q,wa))RZ(w=reaxis(q,w));
 p=PAV(a); *ae=e=SPA(p,e); *ay=SPA(p,i); *ax=x=SPA(p,x); if(t&&t!=AT(x)){RZ(*ae=cvt(t,e)); RZ(*ax=cvt(t,x));}
 p=PAV(w); *we=e=SPA(p,e); *wy=SPA(p,i); *wx=x=SPA(p,x); if(t&&t!=AT(x)){RZ(*we=cvt(t,e)); RZ(*wx=cvt(t,x));}
 R 1;
}

static I zcount(A ay,A wy,B ab,B wb){I c,d,i,j,m,n,*u,*v,yc;
 v=AS(ay); m=v[0]; yc=v[1]; n=*AS(wy);
 i=j=d=0; u=AV(ay); v=AV(wy);
 while(m>i&&n>j){
  c=0; DO(yc, if(c=u[i]-v[i])break;);
  if(0>c)   {u+=yc; ++i;             if(wb)++d;}
  else if(c){            v+=yc; ++j; if(ab)++d;}
  else      {u+=yc; ++i; v+=yc; ++j;       ++d;}
 } 
 R d+wb*(m-i)+ab*(n-j);
}    /* item count for sparse result */

#define ADVA   axv+=ak; u+=yc; ++i;
#define ADVW   wxv+=wk; v+=yc; ++j;
#define FLUSH  if(d){c=d*yc; ICPY(zyv,u-c,c); ado(jt,0,d*xc,1L,zxv,axv-d*ak,wxv-d*wk); \
                     zxv+=d*zk; zyv+=c; d=0;}

static A jtvaspeq(J jt,A a,A w,C id,VF ado,I cv,I t,I zt,I f,I r){A ae,ax,ay,we,wx,wy,z,za,ze,zx,zy;
     B ab=1,wb=1;C*aev,*axv,*wev,*wxv,*zxv;I ak,c,d,i,j,m,n,*u,*v,wk,xc,yc,zk,*zyv;P*zp;
 RZ(vaspeqprep(a,w,t,f,r,&ae,&ay,&ax,&we,&wy,&wx,&za));
 if(id==CSTAR||id==CSTARDOT){ab=!equ(ae,zero); wb=!equ(we,zero);} 
 v=AS(ay); m=v[0]; yc=v[1]; xc=aii(ax); n=*AS(wy);
 aev=CAV(ae); axv=CAV(ax); ak=xc*bp(AT(ax));
 wev=CAV(we); wxv=CAV(wx); wk=xc*bp(AT(wx));
 d=zcount(ay,wy,ab,wb);
 GA(zx,zt, d*xc,AR(ax),AS(ax)); *AS(zx)=d; zxv=CAV(zx); zk=xc*bp(zt);
 GA(zy,INT,d*yc,2,     AS(ay)); *AS(zy)=d; zyv= AV(zy);
 i=j=d=0; u=AV(ay); v=AV(wy);
 while(m>i&&n>j){
  c=0; DO(yc, if(c=u[i]-v[i])break;);
  if(0>c)   {FLUSH; if(wb){ICPY(zyv,u,yc); ado(jt,0,1L,xc,zxv,axv,wev); zxv+=zk; zyv+=yc;} ADVA;}
  else if(c){FLUSH; if(ab){ICPY(zyv,v,yc); ado(jt,1,1L,xc,zxv,aev,wxv); zxv+=zk; zyv+=yc;} ADVW;}
  else      {++d; ADVA; ADVW;}
 }
 FLUSH;
 if     (wb&&m>i){c=m-i; ICPY(zyv,u,c*yc); ado(jt,0,1L,c*xc,zxv,axv,wev);}
 else if(ab&&n>j){c=n-j; ICPY(zyv,v,c*yc); ado(jt,1,1L,c*xc,zxv,aev,wxv);}
 GA(ze,zt,1,0,0); ado(jt,0,1L,1L,AV(ze),aev,wev);
 RE(0);
 if(cv&VRI+VRD){A e,x; RZ(e=cvz(cv,ze)); RZ(x=cvz(cv,zx)); if(AT(e)==AT(x)){ze=e; zx=x;}}
 GA(z,STYPE(AT(zx)),1,AR(a),AS(a));
 zp=PAV(z); 
 SPB(zp,a,za); SPB(zp,e,ze); SPB(zp,i,zy); SPB(zp,x,zx);
 R vaspz(z);
}    /* frames and cell ranks equal */

A jtvasp(J jt,A a,A w,C id,VF ado,I cv,I t,I zt,I af,I acr,I wf,I wcr,I f,I r){A fs,z;
 if(!AR(a)||!AR(w))R vasp0(a,w,ado,cv,t,zt);
 if((SPARSE&AT(a)||SPARSE&AT(w))&&spmult(&z,a,w,id,af,acr,wf,wcr))R z;
 if(af!=wf){RZ(fs=ds(id)); R sprank2(a,w,0L,acr,wcr,VAV(fs)->f2);}
 if(acr!=wcr)R vaspc(a,w,id,ado,cv,t,zt,af,acr,wf,wcr,f,r);
 R vaspeq(a,w,id,ado,cv,t,zt,f,r);
}    /* scalar dyadic fns with one or both arguments sparse */
