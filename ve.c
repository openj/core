/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Verbs: Elementary Functions (Arithmetic, etc.)                          */

#include "j.h"
#include "vasm.h"

#define DIVI(u,v)     (u||v ? u/(D)v : 0.0) 
#define DIVBB(u,v)    (v?u:u?inf:0.0)

#define TYMESBX(u,v)  (u?v:0)
#define TYMESXB(u,v)  (v?u:0)
#define TYMESID(u,v)  (u   ?u*v:0)
#define TYMESDI(u,v)  (   v?u*v:0)
#define TYMESDD(u,v)  (u&&v?u*v:0)

AOVF( plusII, I,I,I,  PLUSVV, PLUS1V, PLUSV1)
AOVF(minusII, I,I,I, MINUSVV,MINUS1V,MINUSV1)   
AOVF(tymesII, I,I,I, TYMESVV,TYMES1V,TYMESV1)

APFX( plusIO, D,I,I,  PLUSO)
APFX(minusIO, D,I,I, MINUSO)
APFX(tymesIO, D,I,I, TYMESO)

AIFX( plusBB, I,B,B, +     )    /* plusII */                AIFX( plusBD, D,B,D, +   )
   /* plusII */                 /* plusII */                AIFX( plusID, D,I,D, +   )
AIFX( plusDB, D,D,B, +     )  AIFX( plusDI, D,D,I, +)       ANAN( plusDD, D,D,D, PLUS)
ANAN( plusZZ, Z,Z,Z, zplus )

AIFX(minusBB, I,B,B, -     )    /* minusII */               AIFX(minusBD, D,B,D, -    )
  /* minusII */                 /* minusII */               AIFX(minusID, D,I,D, -    )
AIFX(minusDB, D,D,B, -     )  AIFX(minusDI, D,D,I, -)       ANAN(minusDD, D,D,D, MINUS)
ANAN(minusZZ, Z,Z,Z, zminus)

    /* andBB */               APFX(tymesBI, I,B,I, TYMESBX) APFX(tymesBD, D,B,D, TYMESBX) 
APFX(tymesIB, I,I,B, TYMESXB)   /* tymesII */               APFX(tymesID, D,I,D, TYMESID)  
APFX(tymesDB, D,D,B, TYMESXB) APFX(tymesDI, D,D,I, TYMESDI) APFX(tymesDD, D,D,D, TYMESDD) 
ANAN(tymesZZ, Z,Z,Z, ztymes )

APFX(  divBB, D,B,B, DIVBB)   APFX(  divBI, D,B,I, DIVI)    APFX(  divBD, D,B,D, DIV)
APFX(  divIB, D,I,B, DIVI )   APFX(  divII, D,I,I, DIVI)    APFX(  divID, D,I,D, DIV)
APFX(  divDB, D,D,B, DIVI )   APFX(  divDI, D,D,I, DIVI)    ANAN(  divDD, D,D,D, DIV)
ANAN(  divZZ, Z,Z,Z, zdiv )

     /* orBB */               APFX(  minBI, I,B,I, MIN)     APFX(  minBD, D,B,D, MIN)    
APFX(  minIB, I,I,B, MIN)     APFX(  minII, I,I,I, MIN)     APFX(  minID, D,I,D, MIN)  
APFX(  minDB, D,D,B, MIN)     APFX(  minDI, D,D,I, MIN)     APFX(  minDD, D,D,D, MIN)
APFX(  minSS, SB,SB,SB, SBMIN)

    /* andBB */               APFX(  maxBI, I,B,I, MAX)     APFX(  maxBD, D,B,D, MAX)    
APFX(  maxIB, I,I,B, MAX)     APFX(  maxII, I,I,I, MAX)     APFX(  maxID, D,I,D, MAX)  
APFX(  maxDB, D,D,B, MAX)     APFX(  maxDI, D,D,I, MAX)     APFX(  maxDD, D,D,D, MAX)
APFX(  maxSS, SB,SB,SB, SBMAX)


static D jtremdd(J jt,D a,D b){D q,x,y;
 if(!a)R b;
 ASSERT(!INF(b),EVNAN);
 if(a==inf )R 0<=b?b:a;
 if(a==infm)R 0>=b?b:a;
 q=b/a; x=tfloor(q); y=tceil(q); R teq(x,y)?0:b-a*x;
}

ANAN(remDD, D,D,D, remdd)
ANAN(remZZ, Z,Z,Z, zrem )

static I jtremid(J jt,I a,D b){D r;I k;
 ASSERT(a&&-9e15<b&&b<9e15,EWOV);
 r=b-a*floor(b/a); k=(I)r;
 ASSERT(k==r,EWOV); 
 R k;
}

APFX(remID, I,I,D, remid)

static I remii(I a,I b){I r; R!a?b:(r=b%a,0<a?r+a*(0>r):r+a*(0<r));}

AHDR2(remII,I,I,I){I u,v;
 if(1==n)  DO(m,               *z++=remii(*x,*y); x++; y++; )
 else if(b)DO(m, u=*x++; if(0<=u&&!(u&(u-1))){--u; DO(n, *z++=u&*y++;);}
                    else DO(n, *z++=remii( u,*y);      y++;))
 else      DO(m, v=*y++; DO(n, *z++=remii(*x, v); x++;     ));
}


static I igcd1(I a,I b){R a?igcd1(b%a,a):b;}

static I jtigcd(J jt,I a,I b){
 if(a>IMIN&&b>IMIN){a=ABS(a); b=ABS(b);}
 else{
  if(a==b||!a||!b){jt->jerr=EWOV; R 0;}
  if(a==IMIN){b=ABS(b); a=-(a+b);}else{a=ABS(a); b=-(a+b);}
 }
 R a?igcd1(b%a,a):b;
}

D jtdgcd(J jt,D a,D b){D a1,b1,t;
 a=ABS(a); b=ABS(b); if(a>b){t=a; a=b; b=t;}
 ASSERT(inf!=b,EVNAN);
 if(!a)R b;
 a1=a; b1=b;
 while(remdd(a1/jfloor(0.5+a1/a),b1)){t=a; a=remdd(a,b); b=t;}
 R a;
}    /* D.L. Forkes 1984; E.E. McDonnell 1992 */
#if SY_64
#if SY_WIN32
static I jtilcm(J jt,I a,I b){C er=0;I b1,d,z;
 if(a&&b){RZ(d=igcd(a,b)); b1=b/d; TYMESVV(1L,&z,&a,&b1); if(er)jt->jerr=EWOV; R    z;}else R 0;
}
#else
static I jtilcm(J jt,I a,I b){LD z;I b1,d;
 if(a&&b){RZ(d=igcd(a,b)); b1=b/d; z=a*(LD)b1; if(z<IMIN||IMAX<z)jt->jerr=EWOV; R (I)z;}else R 0;
}
#endif
#else
static I jtilcm(J jt,I a,I b){D z;I b1,d;
 if(a&&b){RZ(d=igcd(a,b)); b1=b/d; z=a*(D)b1; if(z<IMIN||IMAX<z)jt->jerr=EWOV; R (I)z;}else R 0;
}
#endif

#define GCDIO(u,v)      (dgcd((D)u,(D)v))
#define LCMIO(u,v)      (dlcm((D)u,(D)v))

static D jtdlcm(J jt,D a,D b){ASSERT(!(INF(a)||INF(b)),EVNAN); R a&&b?a*(b/dgcd(a,b)):0;}

APFX(gcdIO, D,I,I, GCDIO)
APFX(gcdII, I,I,I, igcd )
APFX(gcdDD, D,D,D, dgcd )
APFX(gcdZZ, Z,Z,Z, zgcd )

APFX(lcmII, I,I,I, ilcm )
APFX(lcmIO, D,I,I, LCMIO)
APFX(lcmDD, D,D,D, dlcm )
APFX(lcmZZ, Z,Z,Z, zlcm )


#define GETD          {d=*wv++; if(!d){z=0; break;}}
#define INTDIVF(c,d)  (0>c==0>d?c/d:c%d?c/d-1:c/d)
#define INTDIVC(c,d)  (0>c!=0>d?c/d:c%d?c/d+1:c/d)

F2(jtintdiv){A z;B b,flr;I an,ar,*as,*av,c,d,j,k,m,n,p,p1,r,*s,wn,wr,*ws,*wv,*zv;
 RZ(a&&w);
 an=AN(a); ar=AR(a); as=AS(a); av=AV(a);
 wn=AN(w); wr=AR(w); ws=AS(w); wv=AV(w); b=ar>=wr; r=b?wr:ar; s=b?as:ws;
 ASSERT(!ICMP(as,ws,r),EVLENGTH);
 if(an&&wn){m=prod(r,s); n=prod(b?ar-r:wr-r,r+s);}else m=n=0; 
 GA(z,INT,b?an:wn,b?ar:wr,s); zv=AV(z);
 d=wn?*wv:0; p=0<d?d:-d; p1=d==IMIN?p:p-1; flr=XMFLR==jt->xmode;
 if(!wr&&p&&!(p&p1)){
  k=0; j=1; while(p>j){++k; j<<=1;}
  switch((0<d?0:2)+(flr?0:1)){
   case 0: DO(n,          *zv++=*av++>>k;);                    break;
   case 1: DO(n, c=*av++; *zv++=0< c?1+((c-1)>>k):(c+p1)>>k;); break;
   case 2: DO(n, c=*av++; *zv++=c>IMIN?-c>>k:-(-c>>k););       break;
   case 3: DO(n, c=*av++; *zv++=0<=c?-(c>>k):1+(-(1+c)>>k););
 }}else if(flr){
  if(1==n)    DO(m, c=*av++; GETD;                *zv++=INTDIVF(c,d);  )
  else   if(b)DO(m,          GETD; DO(n, c=*av++; *zv++=INTDIVF(c,d););)
  else        DO(m, c=*av++;       DO(n, GETD;    *zv++=INTDIVF(c,d););)
 }else{
  if(1==n)    DO(m, c=*av++; GETD;                *zv++=INTDIVC(c,d);  )
  else   if(b)DO(m,          GETD; DO(n, c=*av++; *zv++=INTDIVC(c,d););)
  else        DO(m, c=*av++;       DO(n, GETD;    *zv++=INTDIVC(c,d););)
 }
 R z?z:flr?floor1(divide(a,w)):ceil1(divide(a,w));
}    /* <.@% or >.@% on integers */


static F2(jtweight){RZ(a&&w); R df1(behead(over(AR(w)?w:reshape(a,w),one)),bsdot(slash(ds(CSTAR))));}

F1(jtbase1){A z;B*v;I c,d,m,n,p,r,*s,t,*x;
 RZ(w);
 n=AN(w); t=AT(w); r=AR(w); s=AS(w); c=r?*(s+r-1):1;
 ASSERT(t&DENSE,EVNONCE);
 if(c>(SY_64?63:31)||!(t&B01))R pdt(w,weight(sc(c),t&RAT+XNUM?cvt(XNUM,num[2]):num[2]));
 if(c)m=n/c; else RE(m=prod(r-1,s));
 GA(z,INT,m,r?r-1:0,s); x=m+AV(z); v=n+BAV(w);
 if(c)DO(m, p=0; d=1; DO(c, if(*--v)p+=d; d+=d;); *--x=p;)
 else memset(x-m,C0,m*SZI);
 R z;
}

F2(jtbase2){I ar,*as,at,c,t,wr,*ws,wt;
 RZ(a&&w);
 at=AT(a); ar=AR(a); as=AS(a);
 wt=AT(w); wr=AR(w); ws=AS(w); c=wr?*(ws+wr-1):1; t=maxtype(at,wt);
 ASSERT(at&DENSE&&wt&DENSE,EVNONCE);
 if(!(t&at))RZ(a=cvt(t,a));
 if(!(t&wt))RZ(w=cvt(t,w));
 R 1>=ar?pdt(w,weight(sc(c),a)):rank2ex(w,rank2ex(sc(c),a,0L,0L,1L,jtweight),0L,1L,1L,jtpdt);
}

F1(jtabase1){A d,z;B*zv;I c,n,p,r,t,*v,x;
 RZ(w);
 n=AN(w); r=AR(w); t=AT(w);
 ASSERT(t&DENSE,EVNONCE);
 if(!n||t&B01)R reshape(over(shape(w),n?one:zero),w);
 if(!(t&INT)){
  d=df2(num[2],maximum(one,aslash(CMAX,mag(ravel(w)))),atop(ds(CFLOOR),ds(CLOG)));
  RZ(z=abase2(reshape(increm(d),num[2]),w));
  R t&FL&&equ(irs1(z,0L,1L,jthead),lt(w,zero))?irs1(z,0L,1L,jtbehead):z;
 }
 c=x=0; v=AV(w);
 DO(n, p=*v++; if(p==IMIN){c=SY_64?64:32; break;} x=x<p?p:x<-p?-p:x;);
 if(!c)while(x){x>>=1; ++c;}
 c=MAX(1,c);
 GA(z,B01,n*c,1+r,AS(w)); *(r+AS(z))=c;
 v=n+AV(w); zv=AN(z)+BAV(z);
 DO(n, x=*--v; DO(c, *--zv=(B)(x&1); x>>=1;));
 R z;
}

F2(jtabase2){A z;I an,ar,at,wn,wr,wt,zn;
 RZ(a&&w);
 an=AN(a); ar=AR(a); at=AT(a);
 wn=AN(w); wr=AR(w); wt=AT(w);
 ASSERT(at&DENSE&&wt&DENSE,EVNONCE);
 if(!ar)R residue(a,w);
 if(1==ar&&at&B01+INT&&wt&B01+INT){I*av,d,r,*u,*wv,x,*zv;
  RZ(coerce2(&a,&w,INT));
  RE(zn=mult(an,wn)); GA(z,INT,zn,1+wr,AS(w)); *(wr+AS(z))=an;
  av=an+AV(a); wv=wn+AV(w); zv=zn+AV(z);
  if(2==an&&!av[-2]&&0<(d=av[-1])){I d1,j,k;
   k=0; j=1; while(d>j){++k; j<<=1;} d1=d-1;
   if(d==j)DO(wn, x=*--wv; *--zv=x&d1; *--zv=x>>k;)
   else    DO(wn, x=*--wv; if(0<=x){*--zv=x%d; *--zv=x/d;}else{*--zv=d+x%d; *--zv=-1+x/d;})
  }else DO(wn, x=*--wv; u=av; DO(an, d=*--u; *--zv=r=remii(d,x); x=d?(x-r)/d:0;););
  R z;
 }else{PROLOG;A y,*zv;C*u,*yv;I k;
  F2RANK(1,0,jtabase2,0);
  k=bp(at); u=an*k+CAV(a);
  GA(y,at, 1, 0,0); yv=CAV(y);
  GA(z,BOX,an,1,0); zv=an+AAV(z);
  DO(an, MC(yv,u-=k,k); RZ(w=divide(minus(w,*--zv=residue(y,w)),y)););
  EPILOG(ope(z));
}}

F1(jtintmod2){A z;B*b,*v;I k=SZI,mask,m,n,q,r,*u,*wi;
 RZ(w);
 n=AN(w); q=n/k; r=n%k; v=BAV(w)+!liln*(k-1);
 GA(z,B01,n,AR(w),AS(w)); u=AV(z);
 b=(B*)&mask; DO(k, b[i]=1;);
 b=(B*)&m; DO(q, DO(k, b[i]=*v; v+=k;); *u++=mask&m;)
 b=(B*)u; wi=AV(w)+q*k; DO(r, *b++=1&*wi++?1:0;);
 R z;
}
