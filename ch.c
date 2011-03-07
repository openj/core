/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Conjunctions: Hypergeometric Series                                     */

#include "j.h"


static A jthparm(J jt,A j,A f,A h){A z;
 if(!(VERB&AT(f)))R shift1(aslash(CSTAR,atab(CPLUS,h,j)));
 RZ(z=CALL1(VAV(f)->f1,j,f));
 ASSERT(1>=AR(z),EVRANK); 
 ASSERT(!AR(z)||AN(j)==AN(z),EVLENGTH);
 R z;
}

static A jthgv(J jt,B b,I n,A w,A self){A c,d,e,h,*hv,j,y;V*sv=VAV(self);
 RZ(j=IX(n)); h=sv->h; hv=AAV(h);
 c=hparm(j,sv->f,hv[0]);
 d=hparm(j,sv->g,hv[1]);
 e=shift1(divide(w,apv(n,1L,1L)));
 switch((VERB&AT(sv->f)?2:0)+(VERB&AT(sv->g)?1:0)){
  case 0: y=ascan(CSTAR,divide(tymes(c,e),d)); break;
  case 1: y=divide(ascan(CSTAR,tymes(c,e)),d); break;
  case 2: y=divide(tymes(c,ascan(CSTAR,e)),ascan(CSTAR,d)); break;
  case 3: y=divide(tymes(c,ascan(CSTAR,e)),d);
 }
 R b?over(zero,ascan(CPLUS,y)):aslash(CPLUS,y);
}    /* verb or complex cases */

static A jthgd(J jt,B b,I n,A w,A p,A q){A c,d,e,z;D r,s,t,*u,*v,x,*zv;I j,pn,qn;
 RZ(c=cvt(FL,p)); u=DAV(c); pn=AN(c);
 RZ(d=cvt(FL,q)); v=DAV(d); qn=AN(d);
 RZ(e=cvt(FL,w)); x=*DAV(e); r=s=1; t=0; z=0;
 if(b&&2000>n){GA(z,FL,1+n,1,0); zv=DAV(z); *zv++=0; *zv++=1;}
 NAN0;
 for(j=1;j<n&&t!=s&&!_isnan(s);++j){
  DO(pn, r*=u[i]; ++u[i];);  /* r*=u[i]++; compiler error on 3B1 */
  DO(qn, r/=v[i]; ++v[i];); 
  r*=x/j; t=s; s+=r; if(z)*zv++=s; JBREAK0;
 }
 NAN1;
 R !b?scf(s):z?take(sc(1+j),z):hgd(b,j,w,p,q);
}    /* real vector p,q; real scalar w; all terms (1=b) or last term (0=b) */

static DF2(jthgeom2){PROLOG;A h,*hv,t,z;B b;I an,*av,j,n;V*sv=VAV(self);
 RZ(a&&w);
 if(AR(w))R rank2ex(a,w,self,0L,0L,jthgeom2);
 RZ(a=AT(a)&FL+CMPX?vib(a):vi(a));
 an=AN(a); av=AV(a); n=0; DO(an, j=av[i]; ASSERT(0<=j,EVDOMAIN); if(n<j)n=j;);
 if(!n)R tymes(zero,a);
 h=sv->h; hv=AAV(h);
 b=VERB&(AT(sv->f)|AT(sv->g))||CMPX&(AT(w)|AT(hv[0])|AT(hv[1]));
 if(!b)z=hgd((B)(1<an),n,w,hv[0],hv[1]);
 else if(2000>n)z=hgv((B)(1<an),n,w,self);
 else{
  j=10; t=mtv; z=one;
  while(z&&!equ(z,t)){t=z; z=hgv(0,j,w,self); j+=j;} 
  RZ(z); if(1<an)z=hgv(1,j,w,self);
 }
 if(1<an)z=from(minimum(a,sc(IC(z)-1)),z);
 EPILOG(z);
}

static DF1(jthgeom1){R hgeom2(sc(IMAX),w,self);}

static F2(jtcancel){A c,d,f,x,y;
 f=eval("#/.~");
 a=ravel(a); x=nub(a); c=df1(a,f);
 w=ravel(w); y=nub(w); d=df1(w,f);
 a=repeat(maximum(zero,minus(c,from(indexof(y,x),over(d,zero)))),x);
 w=repeat(maximum(zero,minus(d,from(indexof(x,y),over(c,zero)))),y);
 R link(a,w);
}

F2(jthgeom){A c,d,h=0;B p,q;I at,wt;
 RZ(a&&w);
 at=AT(a); p=1&&at&NOUN; c=d=mtv;
 wt=AT(w); q=1&&wt&NOUN;
 if(p){c=a; ASSERT(!AN(a)||at&NUMERIC,EVDOMAIN); ASSERT(1>=AR(a),EVRANK);}
 if(q){d=w; ASSERT(!AN(w)||wt&NUMERIC,EVDOMAIN); ASSERT(1>=AR(w),EVRANK);}
 RZ(h=cancel(c,d));
 R fdef(CHGEOM,VERB, jthgeom1,jthgeom2, a,w,h, 0L, 0L,0L,0L);
}    /* a H. w */

F1(jthgdiff){A*hv,p,q,x,y;V*v=VAV(w);
 ASSERTNN(v->f,v->g);
 hv=AAV(v->h); 
 x=hv[0]; x=1==AN(x)?head(x):x;
 y=hv[1]; y=1==AN(y)?head(y):y;
 p=divide(aslash(CSTAR,x),aslash(CSTAR,y));
 q=hgeom(increm(x),increm(y));
 R equ(p,one)?q:folk(qq(p,zero),ds(CSTAR),q);
}    /* a H. w D. 1 */

DF1(jthgcoeff){PROLOG;A c,d,h,*hv,y,z;B b;I j,n,pn,qn,*v;V*sv=VAV(self);
 RZ(w=vi(w)); v=AV(w); 
 n=0; DO(AN(w), j=v[i]; ASSERT(0<=j,EVDOMAIN); if(n<j)n=j;);
 if(!n)R eq(w,w);
 h=sv->h; hv=AAV(h);
 b=VERB&(AT(sv->f)|AT(sv->g))||CMPX&(AT(w)|AT(hv[0])|AT(hv[1]));
 if(!b){D r=1.0,*u,*v,*yv;
  RZ(c=cvt(FL,hv[0])); u=DAV(c); pn=AN(c);
  RZ(d=cvt(FL,hv[1])); v=DAV(d); qn=AN(d);
  GA(y,FL,n,1,0); yv=DAV(y);
  DO(n, DO(pn, r*=u[i]; ++u[i];); DO(qn, r/=v[i]; ++v[i];); yv[i]=r;); 
 }else{A j;
  RZ(j=IX(n));
  c=hparm(j,sv->f,hv[0]);
  d=hparm(j,sv->g,hv[1]);
  switch((VERB&AT(sv->f)?2:0)+(VERB&AT(sv->g)?1:0)){
   case 0: y=ascan(CSTAR,divide(c,d)); break;
   case 1: y=divide(ascan(CSTAR,c),d); break;
   case 2: y=divide(c,ascan(CSTAR,d)); break;
   case 3: y=divide(c,d);
 }}
 RZ(z=from(w,over(one,y)));
 EPILOG(z);
}    /* coefficients indexed by w excluding !j */
