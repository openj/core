/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Verbs: { on sparse arguments                                            */

#include "j.h"


static A jtfromis1(J jt,A ind,A w,A z,I wf){A a,a1,j1,p,q,x,x1,y,y1;C*xu,*xuu,*xv;I an,*av,c,d,
     h,i,*iv,j,*jv,k,m,n,*pv,*qu,*qv,r,s,*u,*v,xk,*yu,*yv;P*wp,*zp;
 zp=PAV(z); wp=PAV(w); r=AR(ind); n=AN(ind); 
 a=SPA(wp,a); an=AN(a); av=AV(a); DO(an, if(wf==av[i]){h=i; break;});
 y=SPA(wp,i); RZ(q=eps(fromr(sc(h),y),ravel(ind))); RZ(y=repeat(q,y)); RZ(x=repeat(q,SPA(wp,x)));
 GA(a1,INT,r+an-1,1,0); v=AV(a1); SPB(zp,a,a1);
 k=av[h]; u=av; DO(h, *v++=*u++;); DO(r, *v++=k++;); u++; DO(an-1-h, *v++=*u+++r-1;);
 if(!r) 
  if(AR(z)){GA(q,INT,an-1,1,0); v=AV(q); DO(an, if(i!=h)*v++=i;); SPB(zp,i,fromr(q,y)); SPB(zp,x,x); R z;}
  else R reshape(mtv,AN(x)?x:SPA(zp,e));
 if(h){q=grade1(fromr(sc(h),y)); RZ(y=ifrom(q,y)); RZ(x=ifrom(q,x));}
 RZ(q=odom(2L,r,AS(ind))); iv=AV(q);
 m=*AS(y); s=0; j=-1; u=h+AV(y); v=u+an;
 GA(p,INT,m,1,0); pv=AV(p); memset(pv,CFF,SZI*m);
 GA(q,INT,m,1,0); qu=AV(q);
 GA(q,INT,m,1,0); qv=AV(q);
 DO(m-1, if(*u!=*v){pv[s]=*u; qu[s]=1+j; qv[s++]=i-j; j=i;} u=v; v+=an;); 
 if(m){i=m-1;       pv[s]=*u; qu[s]=1+j; qv[s++]=i-j;}
 RZ(j1=indexof(p,ind)); jv=AV(j1);
 c=0; DO(n, if(s>jv[i])c+=qv[jv[i]];); i=aii(x); xk=i*bp(AT(x)); d=AN(a1);
 GA(y1,INT,  c*d,2,    0    ); v=AS(y1); v[0]=c; v[1]=d; yv= AV(y1); yu= AV(y);
 GA(x1,AT(x),c*i,AR(x),AS(x)); *AS(x1)=c;                xv=CAV(x1); xu=CAV(x);
 for(i=0;i<n;++i){
  k=jv[i]; 
  if(s>k){
   c=qu[k]; d=qv[k]; xuu=xu+c*xk; u=yu+c*an;
   for(j=0;j<d;++j){
    MC(xv,xuu,xk); xv+=xk; xuu+=xk;
    DO(h, *yv++=*u++;); DO(r, *yv++=iv[i];); u++; DO(an-1-h, *yv++=*u++;);
  }}
  iv+=r;
 }
 if(h){q=grade1(y1); RZ(y1=ifrom(q,y1)); RZ(x1=ifrom(q,x1));}
 SPB(zp,i,y1); SPB(zp,x,x1);
 R z;
}    /* ind{"r w along a sparse axis  */

F2(jtfromis){A ind,x,z;B*b;I acr,af,an,ar,*av,k,m,*v,wcr,wf,wn,wr,*ws,wt;P*wp,*zp;
 RZ(a&&w);
 ar=AR(a); acr=jt->rank?jt->rank[0]:ar; af=ar-acr;
 wr=AR(w); wcr=jt->rank?jt->rank[1]:wr; wf=wr-wcr; jt->rank=0;
 if(af)R rank2ex(a,w,0L,acr,wcr,jtfromis);
 wn=AN(w); ws=AS(w); wt=AT(w);
 RZ(ind=pind(wcr?*(ws+wf):1,a));
 GA(z,wt,1L,ar+wr-(0<wcr),ws); v=AS(z); ICPY(v+wf,AS(a),ar); if(wcr)ICPY(v+wf+ar,1+wf+ws,wcr-1);
 zp=PAV(z); wp=PAV(w); SPB(zp,e,ca(SPA(wp,e)));
 RZ(a=ca(SPA(wp,a))); av=AV(a); an=AN(a);
 RZ(b=bfi(wr,a,1));
 if(b[wf])R fromis1(ind,w,z,wf);
 m=wcr; DO(wcr, m-=b[wf+i];); RZ(x=irs2(ind,SPA(wp,x),0L,ar,m,jtifrom));
 if(k=ar-1)DO(an, if(av[i]>=wf)av[i]+=k;);
 if(AR(z)){SPB(zp,a,a); SPB(zp,x,x); SPB(zp,i,ca(SPA(wp,i))); R z;}
 else R AN(x)?reshape(mtv,x):ca(SPA(wp,e));
}    /* a{"r w for numeric a and sparse w */

static A jtaaxis(J jt,A w,I wf,A a,I r,I h,I*pp,I*qq,I*rr){A q;B*b,*c,*d;I wr,x,y,z,zr;
 wr=AR(w); zr=wr+r-h;
 RZ(b=bfi(wr,a,1));
 GA(q,B01,zr,1,0); c=BAV(q); 
 x=y=z=0; d=b; DO(wf, if(*d++)++x;); DO(h, if(*d++)++y;); DO(wr-wf-h, if(*d++)++z;);
 *pp=x; *qq=y; *rr=z;
 MC(c,b,wf); memset(c+wf,y?C1:C0,r); MC(c+wf+r,b+wf+h,wr-wf-h);
 R ifb(zr,c);
}

A jtfrombsn(J jt,A ind,A w,I wf){A a,j1,p,q,x,x1,y,y1,ys,z;C*xu,*xuu,*xv;
     I an,c,d,h,i,*iv,j,*jv,k,m,n,pp,*pv,qq,*qv,r,rr,s,*u,*v,wr,*ws,xk,*yu,*yv;P*wp,*zp;
 RZ(ind&&w);    /* need to handle 1==n */
 wr=AR(w); ws=AS(w); 
 r=AR(ind)-1; v=AS(ind); h=v[r]; n=AN(ind)/h;
 RZ(q=odom(2L,r,v)); iv=AV(q)-r;
 GA(z,AT(w),1,wr+r-h,0); u=AS(z); ICPY(u,ws,wf); ICPY(u+wf,v,r); ICPY(u+wf+r,ws+wf+h,wr-wf-h);
 zp=PAV(z); wp=PAV(w); 
 SPB(zp,e,ca(SPA(wp,e))); x=SPA(wp,x); y=SPA(wp,i); 
 a=SPA(wp,a); an=AN(a); SPB(zp,a,aaxis(w,wf,a,r,h,&pp,&qq,&rr));
 if( !qq){SPB(zp,i,ca(y)); SPB(zp,x,frombu(ind,x,AR(x)-(wr-wf-rr))); R z;}
 if(h>qq){q=nub(over(a,apv(h,wf,1L))); R frombsn(ind,reaxis(grade2(q,q),w),wf);}
 if(1<r)RZ(ind=reshape(v2(n,h),ind)); 
 RZ(ys=fromr(indexof(a,apv(h,wf,1L)),y));
 RZ(q=eps(ys,ind)); 
 if(!all1(q)){RZ(ys=repeat(q,ys)); RZ(y=repeat(q,y)); RZ(x=repeat(q,x));}
 if(wf){q=grade1(ys); RZ(ys=ifrom(q,ys)); RZ(y=ifrom(q,y)); RZ(x=ifrom(q,x));}
 m=*AS(y);
 GA(p,INT,m,1,0); pv=AV(p);
 GA(q,INT,m,1,0); qv=AV(q);
 s=0; j=-1; u=AV(ys); v=u+h;
 DO(m-1, if(ICMP(u,v,h)){pv[s]=1+j; qv[s++]=i-j; j=i;} u=v; v+=h;); if(m){pv[s]=1+j; qv[s++]=m-1-j;}
 RZ(j1=indexof(ifrom(vec(INT,s,pv),ys),ind)); jv=AV(j1);
 c=0; DO(n, if(s>jv[i])c+=qv[jv[i]];); 
 i=aii(x); j=AN(SPA(zp,a)); xk=i*bp(AT(x));
 GA(y1,INT,  c*j,2,    0    ); v=AS(y1); v[0]=c; v[1]=j; yv= AV(y1); yu= AV(y);
 GA(x1,AT(x),c*i,AR(x),AS(x)); *AS(x1)=c;                xv=CAV(x1); xu=CAV(x);
 for(i=0;i<n;++i){
  k=jv[i]; iv+=r;
  if(s>k){
   c=pv[k]; d=qv[k]; xuu=xu+c*xk; u=yu+c*an;
   for(j=0;j<d;++j){
    MC(xv,xuu,xk); xv+=xk; xuu+=xk;
    DO(pp, *yv++=*u++;); DO(r, *yv++=iv[i];); u+=qq; DO(rr, *yv++=*u++;);
 }}}
 if(wf){q=grade1(y1); RZ(y1=ifrom(q,y1)); RZ(x1=ifrom(q,x1));}
 SPB(zp,i,y1); SPB(zp,x,x1); 
 R z;
}    /* (<"1 ind){w, sparse w and integer array ind */

static A jtfrombs1(J jt,A ind,A w,I wf){A*iv,x,y,z;I id,j,m,n,old,wr,wcr;
 RZ(ind&&w);
 if(!(BOX&AT(ind))){ASSERT(!AN(ind)||NUMERIC&AT(ind),EVINDEX); RZ(ind=every(ind,0L,jtright1));}
 n=AN(ind); iv=AAV(ind); id=(I)ind*ARELATIVE(ind); wr=AR(w); wcr=wr-wf;
 ASSERT(1>=AR(ind),EVRANK);
 ASSERT(n<=wr-wf,EVLENGTH);
 j=n; DO(n, --j; x=AADR(id,iv[j]); if(BOX&AT(x)&&!AR(x)&&(y=AAV0(x),!AN(y)&&1==AR(y)))--n; else break;);
 z=w; old=jt->tbase+jt->ttop;
 for(j=0;j<n;++j){
  x=AADR(id,iv[j]); 
  if(BOX&AT(x)){
   ASSERT(!AR(x),EVINDEX);
   x=AAV0(x); m=*(wf+j+AS(w));
   if(!AN(x))continue;
   RZ(x=less(IX(m),pind(m,x)));
  }
  RZ(z=irs2(x,z,0L,RMAX,wcr-j,jtfromis)); gc(z,old);
 }
 R z;
}    /* (<ind){"r w, sparse w */

F2(jtfrombs){A ind;I acr,af,ar,wcr,wf,wr;
 RZ(a&&w);
 ar=AR(a); acr=jt->rank?jt->rank[0]:ar; af=ar-acr;
 wr=AR(w); wcr=jt->rank?jt->rank[1]:wr; wf=wr-wcr; jt->rank=0;
 ASSERT(!af,EVNONCE);
 if(ar){RE(aindex(a,w,wf,&ind)); ASSERT(ind,EVNONCE); R frombsn(ind,w,wf);}
 else R frombs1(AAV0(a),w,wf);
}    /* a{"r w for boxed a and sparse w */

F2(jtfromsd){A e,x,z;I acr,af,ar,*v,wcr,wf,wr,*ws;P*ap,*zp;
 RZ(a&&w);
 ar=AR(a); acr=jt->rank?jt->rank[0]:ar; af=ar-acr;
 wr=AR(w); wcr=jt->rank?jt->rank[1]:wr; wf=wr-wcr; jt->rank=0;
 if(af)R sprank2(a,w,0L,acr,wcr,jtfrom);
 ASSERT(AT(w)&B01+INT+FL+CMPX,EVNONCE);
 ap=PAV(a); ws=AS(w);
 GA(z,STYPE(AT(w)),1L,ar+wr-(0<wcr),ws); zp=PAV(z);
 v=AS(z); ICPY(v+wf,AS(a),ar); if(wcr)ICPY(v+wf+ar,1+wf+ws,wcr-1);
 RZ(x=irs2(SPA(ap,e),w,0L,0L,wcr,jtifrom)); RZ(e=reshape(mtv,x));
 ASSERT(all1(eq(e,x)),EVSPARSE);
 SPB(zp,e,e);
 SPB(zp,a,wf?plus(sc(wf),SPA(ap,a)):SPA(ap,a));
 SPB(zp,i,SPA(ap,i));
 if(wf){
  RZ(x=irs2(SPA(ap,x),w,0L,RMAX,wcr,jtifrom));
  RZ(x=cant2(less(IX(AR(x)),sc(wf)),x));
  SPB(zp,x,x);
 }else SPB(zp,x,ifrom(SPA(ap,x),w));
 R z;
}    /* a{"r w, sparse a, dense w */

F2(jtfromss){A e,x,y,z;B*b;I acr,af,ar,c,d,k,m,n,p,*u,*v,wcr,wf,wr,*ws,*yv;P*ap,*wp,*xp,*zp;
 RZ(a&&w);
 ar=AR(a); acr=jt->rank?jt->rank[0]:ar; af=ar-acr;
 wr=AR(w); wcr=jt->rank?jt->rank[1]:wr; wf=wr-wcr; jt->rank=0;
 if(af)R sprank2(a,w,0L,acr,wcr,jtfrom);
 ASSERT(DTYPE(AT(w))&B01+INT+FL+CMPX,EVNONCE);
 ap=PAV(a); wp=PAV(w); ws=AS(w);
 GA(z,AT(w),1L,ar+wr-(0<wcr),ws); zp=PAV(z);
 v=AS(z); ICPY(v+wf,AS(a),ar); if(wcr)ICPY(v+wf+ar,1+wf+ws,wcr-1);
 RZ(x=irs2(SPA(ap,e),w,0L,0L,wcr,jtfrom)); RZ(e=reshape(mtv,x));
 ASSERT(all1(denseit(eq(e,x))),EVSPARSE);
 SPB(zp,e,e);
 x=SPA(ap,a); if(ar>AN(x)){RZ(a=reaxis(IX(ar),a)); ap=PAV(a);}
 x=SPA(wp,a); n=AN(x); RZ(b=bfi(wr,x,1));
 if(wcr&&!b[wf]){b[wf]=1; ++n; RZ(w=reaxis(ifb(wr,b),w)); wp=PAV(w);}
 GA(x,INT,ar+n-!!wcr,1,0); v=AV(x);
 DO(wf, if(b[i])*v++=i;); DO(ar, *v++=wf+i;); DO(wcr-1, if(b[i+wf+1])*v++=wf+ar+i;);
 SPB(zp,a,x);
 RZ(x=irs2(SPA(ap,x),w,0L,RMAX,wcr,jtfrom)); xp=PAV(x); 
 y=SPA(xp,i); u=AV(y); c=*(1+AS(y)); m=*AS(y); k=0; DO(wf, if(b[i])++k;);
 y=SPA(ap,i); v=AV(y); d=*(1+AS(y)); n=c+d-1; p=c-(1+k);
 GA(y,INT,m*n,2,0); *AS(y)=m; *(1+AS(y))=n; yv=AV(y);
 DO(m, if(k)ICPY(yv,u,k); ICPY(yv+k,v+d*u[k],d); if(p)ICPY(yv+k+d,u+1+k,p); yv+=n; u+=c;);
 SPB(zp,i,y);
 SPB(zp,x,SPA(xp,x));
 R z;
}    /* a{"r w, sparse a, sparse w */
