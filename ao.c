/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Adverbs: Oblique and Key                                                */

#include "j.h"


static DF1(jtoblique){A x,y;I m,n,r,*u,*v;
 RZ(w);
 r=AR(w);
 RZ(y=gah(MAX(r-1,1),w));
 u=AS(w); v=AS(y);
 if(1>=r){*v=m=AN(w); n=1;}else{m=*u++; n=*u++; *v++=m*n; ICPY(v,u,r-2);}
 RZ(x=irs2(IX(m),IX(n),0L,0L,1L,jtplus)); AR(x)=1; *AS(x)=AN(x);
 R df2(x,y,sldot(VAV(self)->f));
}


#define OBQCASE(id,t)    ((id)+(256*(t)))

#define OBQLOOP(Tw,Tz,zt,init,expr)  \
 {Tw*u,*v,*ww=(Tw*)wv;Tz x,*zz;                  \
  b=1; k=n1;                                     \
  GA(z,zt,d*c,r-1,1+s); *AS(z)=d; zz=(Tz*)AV(z); \
  DO(n,  v=ww+i;      u=v+n1*MIN(i,m1);     init; while(v<=(u-=n1))expr; *zz++=x;);  \
  DO(m1, v=ww+(k+=n); u=v+n1*MIN(m-i-2,n1); init; while(v<=(u-=n1))expr; *zz++=x;);  \
 }

static DF1(jtobqfslash){A y,z;B b=0,p;C er,id,*wv;I c,d,k,m,m1,mn,n,n1,r,*s,wt;
 RZ(w);
 r=AR(w); s=AS(w); wt=AT(w); wv=CAV(w);
 if(!(AN(w)&&1<r&&DENSE&wt))R oblique(w,self);
 y=VAV(self)->f; y=VAV(y)->f; id=vaid(y);
 m=s[0]; m1=m-1;
 n=s[1]; n1=n-1; mn=m*n; d=m+n-1; c=prod(r-2,2+s);
 if(1==m||1==n){GA(z,wt,AN(w),r-1,1+s); *AS(z)=d; MC(AV(z),wv,AN(w)*bp(wt)); R z;}
 if(wt&FL+CMPX)NAN0;
 if(1==c)switch(OBQCASE(wt,id)){
  case OBQCASE(B01, CNE     ): OBQLOOP(B,B,wt,x=*u, x^=*u        ); break;
  case OBQCASE(B01, CEQ     ): OBQLOOP(B,B,wt,x=*u, x=x==*u      ); break;
  case OBQCASE(B01, CMAX    ):
  case OBQCASE(B01, CPLUSDOT): OBQLOOP(B,B,wt,x=*u, x|=*u        ); break;
  case OBQCASE(B01, CMIN    ):
  case OBQCASE(B01, CSTAR   ):
  case OBQCASE(B01, CSTARDOT): OBQLOOP(B,B,wt,x=*u, x&=*u        ); break;
  case OBQCASE(B01, CLT     ): OBQLOOP(B,B,wt,x=*u, x=*u< x      ); break;
  case OBQCASE(B01, CLE     ): OBQLOOP(B,B,wt,x=*u, x=*u<=x      ); break;
  case OBQCASE(B01, CGT     ): OBQLOOP(B,B,wt,x=*u, x=*u> x      ); break;
  case OBQCASE(B01, CGE     ): OBQLOOP(B,B,wt,x=*u, x=*u>=x      ); break;
  case OBQCASE(B01, CPLUS   ): OBQLOOP(B,I,INT,x=*u, x+=*u        ); break;
  case OBQCASE(FL,  CMAX    ): OBQLOOP(D,D,wt,x=*u, x=MAX(x,*u)  ); break;
  case OBQCASE(FL,  CMIN    ): OBQLOOP(D,D,wt,x=*u, x=MIN(x,*u)  ); break;
  case OBQCASE(FL,  CPLUS   ): OBQLOOP(D,D,wt,x=*u, x+=*u        ); break;
  case OBQCASE(CMPX,CPLUS   ): OBQLOOP(Z,Z,wt,x=*u, x=zplus(x,*u)); break;
  case OBQCASE(XNUM,CMAX    ): OBQLOOP(X,X,wt,x=*u, x=1==xcompare(x,*u)? x:*u); break;
  case OBQCASE(XNUM,CMIN    ): OBQLOOP(X,X,wt,x=*u, x=1==xcompare(x,*u)?*u: x); break;
  case OBQCASE(XNUM,CPLUS   ): OBQLOOP(X,X,wt,x=*u, x=xplus(x,*u)); break;
  case OBQCASE(RAT, CMAX    ): OBQLOOP(Q,Q,wt,x=*u, x=1==QCOMP(x,*u)? x:*u); break;
  case OBQCASE(RAT, CMIN    ): OBQLOOP(Q,Q,wt,x=*u, x=1==QCOMP(x,*u)?*u: x); break;
  case OBQCASE(RAT, CPLUS   ): OBQLOOP(Q,Q,wt,x=*u, x=qplus(x,*u)); break;
  case OBQCASE(INT, CBW0001 ): OBQLOOP(I,I,wt,x=*u, x&=*u        ); break;
  case OBQCASE(INT, CBW0110 ): OBQLOOP(I,I,wt,x=*u, x^=*u        ); break;
  case OBQCASE(INT, CBW0111 ): OBQLOOP(I,I,wt,x=*u, x|=*u        ); break;
  case OBQCASE(INT, CMAX    ): OBQLOOP(I,I,wt,x=*u, x=MAX(x,*u)  ); break;
  case OBQCASE(INT, CMIN    ): OBQLOOP(I,I,wt,x=*u, x=MIN(x,*u)  ); break;
  case OBQCASE(INT, CPLUS   ): 
   er=0; OBQLOOP(I,I,wt,x=*u, {p=0>x; x+=*u; BOV(p==0>*u&&p!=0>x);}); 
   if(er==EWOV)OBQLOOP(I,D,FL,x=(D)*u, x+=*u);
 }
 if(wt&FL+CMPX)NAN1; RE(0);
 R b?z:oblique(w,self);
}    /* f//.y for atomic f */


#if SY_64
#define TYMESF(x)       {LD t=*u--*(LD)*v++; x=(I)t; BOV(t<IMIN||IMAX<t);}
#else
#define TYMESF(x)       {D  t=*u--*( D)*v++; x=(I)t; BOV(t<IMIN||IMAX<t);}
#endif
#define ACCUMF          {B p;I y; TYMESF(y); p=0>x; x+=y; BOV(p==0>y&&p!=0>x);}

#define PMCASE(t,c,d)   (65536*(c)+256*(d)+(t))

#define PMLOOP(Tw,Tz,zt,expr0,expr)  \
 {Tw*aa=(Tw*)av,*u,*v,*ww=(Tw*)wv;Tz x,*zv;  \
  b=1; GA(z,zt,zn,1,0); zv=(Tz*)AV(z);       \
  for(i=0;i<zn;++i){                         \
   j=MIN(i,m1); u=aa+j; v=ww+i-j;            \
   p=MIN(1+i,zn-i); p=MIN(p,k);              \
   expr0; DO(p-1, expr;); *zv++=x;           \
 }}

DF2(jtpolymult){A f,g,y,z;B b=0;C*av,c,d,*wv;I at,i,j,k,m,m1,n,p,t,wt,zn;V*v;
 RZ(a&&w&&self);
 m=AN(a); n=AN(w); m1=m-1; zn=m+n-1; k=MIN(m,n);
 at=AT(a); wt=AT(w); t=maxtype(at,wt);
 if(t!=at)RZ(a=cvt(t,a)); at=AT(a); av=CAV(a);
 if(t!=wt)RZ(w=cvt(t,w)); wt=AT(w); wv=CAV(w);
 v=VAV(self); 
 f=v->f; y=VAV(f)->f; y=VAV(y)->f; c=vaid(y);
 g=v->g; y=VAV(g)->f;              d=vaid(y);
 if(!(m&&1==AR(a)&&n&&1==AR(w)))R obqfslash(df2(a,w,g),f);
 if(t&FL+CMPX)NAN0;
 switch(PMCASE(t,c,d)){
  case PMCASE(B01, CNE,    CMAX    ): 
  case PMCASE(B01, CNE,    CPLUSDOT): PMLOOP(B,B,B01,  x=*u--|*v++, x^=*u--|*v++); break;
  case PMCASE(B01, CNE,    CSTAR   ): 
  case PMCASE(B01, CNE,    CMIN    ): 
  case PMCASE(B01, CNE,    CSTARDOT): PMLOOP(B,B,B01,  x=*u--&*v++, x^=*u--&*v++); break;
  case PMCASE(B01, CPLUS,  CMAX    ): 
  case PMCASE(B01, CPLUS,  CPLUSDOT): PMLOOP(B,I,INT,  x=*u--|*v++, x+=*u--|*v++); break;
  case PMCASE(B01, CPLUS,  CSTAR   ): 
  case PMCASE(B01, CPLUS,  CMIN    ): 
  case PMCASE(B01, CPLUS,  CSTARDOT): PMLOOP(B,I,INT,  x=*u--&*v++, x+=*u--&*v++); break;
  case PMCASE(FL,  CPLUS,  CSTAR   ): PMLOOP(D,D,FL,   x=*u--**v++, x+=*u--**v++); break;
  case PMCASE(CMPX,CPLUS,  CSTAR   ): PMLOOP(Z,Z,CMPX, x=ztymes(*u--,*v++), x=zplus(x,ztymes(*u--,*v++))); break;
  case PMCASE(XNUM,CPLUS,  CSTAR   ): PMLOOP(X,X,XNUM, x=xtymes(*u--,*v++), x=xplus(x,xtymes(*u--,*v++))); break;
  case PMCASE(RAT, CPLUS,  CSTAR   ): PMLOOP(Q,Q,RAT,  x=qtymes(*u--,*v++), x=qplus(x,qtymes(*u--,*v++))); break;
  case PMCASE(INT, CBW0110,CBW0001 ): PMLOOP(I,I,INT,  x=*u--&*v++, x^=*u--&*v++); break;
  case PMCASE(INT, CPLUS,  CSTAR   ): 
/*
   er=0; PMLOOP(I,I,INT, TYMESF(x), ACCUMF);
*/
  {A a1,y;I*aa,i,*u,*ww=(I*)wv,*v,*yv,*zv;VF adotymes,adosum;
   b=1;
   RZ(var(CSTAR,a,w,at,wt,&adotymes,&i)); vains(CPLUS,wt,&adosum,&i);
   GA(a1,INT,m,1,0); aa=AV(a1); u=m+(I*)av; DO(m, aa[i]=*--u;);
   GA(y,INT,MIN(m,n),1,0); yv=AV(y);
   GA(z,INT,zn,1,0); zv=AV(z);
   for(i=0;i<zn;++i){
    j=MIN(i,m1); u=aa+m1-j; v=ww+i-j;
    p=MIN(1+i,zn-i); p=MIN(p,k);
    adotymes(jt,1,p,1,yv,u,v); adosum(jt,1,p,p,zv,yv);
    ++zv;
   }
   if(EWOV==jt->jerr){RESETERR; fa(z); PMLOOP(I,D,FL, x=*u--*(D)*v++, x+=*u--*(D)*v++);}
 }}
 if(t&FL+CMPX)NAN1; RE(0);
 if(!b)R obqfslash(df2(a,w,g),f);
 R z;
}    /* f//.@(g/) for atomic f, g */


static DF2(jtkey);

static DF2(jtkeysp){PROLOG;A b,by,e,q,x,y,z;I j,k,n,*u,*v;P*p;
 RZ(a&&w);
 n=IC(a); 
 RZ(q=indexof(a,a)); p=PAV(q); 
 x=SPA(p,x); u=AV(x);
 y=SPA(p,i); v=AV(y);
 e=SPA(p,e); k=i0(e); 
 j=0; DO(AN(x), if(k<=u[i])break; if(u[i]==v[i])++j;);
 RZ(b=ne(e,x));
 RZ(by=repeat(b,y));
 RZ(x=key(repeat(b,x),from(ravel(by),w),self));
 GA(q,SB01,1,1,0); *AS(q)=n;  /* q=: 0 by}1$.n;0;1 */
 p=PAV(q); SPB(p,a,iv0); SPB(p,e,one); SPB(p,i,by); SPB(p,x,reshape(tally(by),zero));
 RZ(z=over(df1(repeat(q,w),VAV(self)->f),x));
 EPILOG(j?cdot2(box(IX(1+j)),z):z);
}

static DF2(jtkeyi){PROLOG;A j,p;B*pv;I*av,c,d=-1,n,*jv;
 RZ(a&&w);
 n=IC(a); av=AV(a);
 RZ(j=grade1(a)); jv=AV(j);
 GA(p,B01,n,1,0); pv=BAV(p);
 DO(n, c=d; d=av[*jv++]; *pv++=c<d;);
 EPILOG(df2(p,from(j,w),cut(VAV(self)->f,one)));
}    /* a f/. w where a is i.~x for dense x & w */

static DF2(jtkeybox){PROLOG;B b;I*wv;
 RZ(a&&w);
 ASSERT(IC(a)==IC(w),EVLENGTH);
 if(SPARSE&AT(a))R keysp(a,w,self);
 if(b=INT&AT(w)&&1==AR(w)){wv=AV(w); DO(AN(w), if(i!=*wv++){b=0; break;});}
 if(b)R group(a);
 EPILOG(keyi(indexof(a,a),w,self));
}    /* a </. w */

static DF2(jtkey){PROLOG;
 RZ(a&&w);
 ASSERT(IC(a)==IC(w),EVLENGTH);
 if(SPARSE&AT(a))R keysp(a,w,self);
 EPILOG(keyi(indexof(a,a),w,self));
}    /* a f/. w */

static I jtkeyrs(J jt,A a,I*zr,I*zs){I ac,at,r=0,s=0;
 at=AT(a); ac=aii(a);
 if(2>=ac)switch(at){
  case C2T: if(1==ac)s=65536;                      break;
  case B01: if(1==ac)s=2;   else{s=258;   at=C2T;} break;
  case LIT: if(1==ac)s=256; else{s=65536; at=C2T;} break;
  case INT: if(1==ac)irange(AN(a),AV(a),&r,&s);    break;
  case SBT: if(1==ac){at=INT; s=jt->sbun; if(65536<s)irange(AN(a),AV(a),&r,&s);}
 }
 *zr=r; *zs=s;
 R at;
}

#define KCASE(d,t)          (t+17*d)
#define KACC1(F,Ta)  \
 {Ta*u;                                                          \
  if(1==c){                                                      \
   u=(Ta*)av0; DO(n, v=qv+  *u++;       y=*wv++; *v=F;       );  \
   u=(Ta*)av0; DO(n, if(bv[j=*u++]){*zv++=qv[j];                  bv[j]=0; if(s==++m)break;});  \
  }else{                                                         \
   u=(Ta*)av0; DO(n, v=qv+c**u++; DO(c, y=*wv++; *v=F; ++v;););  \
   u=(Ta*)av0; DO(n, if(bv[j=*u++]){v=qv+c*j; DO(c, *zv++=*v++;); bv[j]=0; if(s==++m)break;});  \
 }}
#define KACC(F,Tz,Tw,v0)   \
 {Tw*wv=(Tw*)wv0,y;Tz*qv=(Tz*)qv0,*v,*zv=(Tz*)zv0;               \
  if(bb){                                                        \
   m=0; v=qv; DO(AN(q), *v++=v0;); qv-=r*c;                      \
   switch(at){                                                   \
    case B01: KACC1(F,B ); break;                                \
    case LIT: KACC1(F,UC); break;                                \
    case C2T: KACC1(F,US); break;                                \
    case INT: KACC1(F,I );                                       \
  }}else{                                                        \
   v=zv; DO(m*c, *v++=v0;);                                      \
   if(1==c)DO(n, v=zv+  *xv++;       y=*wv++; *v=F;       )      \
   else    DO(n, v=zv+c**xv++; DO(c, y=*wv++; *v=F; ++v;););     \
 }}

static DF2(jtkeyslash){PROLOG;A b,q,x,z=0;B bb,*bv,pp=0;C d;I at,*av0,c,n,j,m,*qv0,r,s,*u,wr,wt,*wv0,*xv,zt,*zv0;
 RZ(a&&w);
 at=AT(a); av0=AV(a); n=IC(a); 
 wt=AT(w); wv0=AV(w); wr=AR(w);
 ASSERT(n==IC(w),EVLENGTH);
 x=VAV(self)->f; d=vaid(VAV(x)->f); if(B01&wt)d=d==CMAX?CPLUSDOT:d==CMIN||d==CSTAR?CSTARDOT:d;
 if(!(AN(a)&&AN(w)&&at&DENSE&&
     (wt&B01&&(d==CEQ||d==CPLUSDOT||d==CSTARDOT||d==CNE||d==CPLUS)||
     wt&INT&&(17<=d&&d<=25)||
     wt&INT+FL&&(d==CMIN||d==CMAX||d==CPLUS) )))R key(a,w,self);
 at=keyrs(a,&r,&s); c=aii(w); m=s;
 zt=d==CPLUS?(wt&B01?INT:wt&INT?FL:wt):wt; bb=s&&s<=MAX(2*n,65536);
 if(bb){
  GA(b,B01,s,  1,0); bv=BAV(b); memset(bv,C1,s); bv-=r;
  GA(q,zt, s*c,1,0); qv0=AV(q);
 }else{RZ(x=indexof(a,a)); xv=AV(x); m=0; u=xv; DO(n, *u=i==*u?m++:xv[*u]; ++u;);}
 GA(z,zt,m*c,wr,AS(w)); *AS(z)=m; zv0=AV(z);
 if(wt&FL)NAN0;
 switch(KCASE(d,wt)){
  case KCASE(CEQ,     B01): KACC(*v==y,    B, B, 1   ); break;
  case KCASE(CPLUSDOT,B01): KACC(*v||y,    B, B, 0   ); break;
  case KCASE(CSTARDOT,B01): KACC(*v&&y,    B, B, 1   ); break;
  case KCASE(CNE,     B01): KACC(*v!=y,    B, B, 0   ); break;
  case KCASE(CMIN,    INT): KACC(MIN(*v,y),I, I, IMAX); break;  
  case KCASE(CMIN,    FL ): KACC(MIN(*v,y),D, D, inf ); break;
  case KCASE(CMAX,    INT): KACC(MAX(*v,y),I, I, IMIN); break;
  case KCASE(CMAX,    FL ): KACC(MAX(*v,y),D, D, infm); break;
  case KCASE(CPLUS,   B01): KACC(*v+y,     I, B, 0   ); break;
  case KCASE(CPLUS,   INT): KACC(*v+y,     D, I, 0.0 ); pp=1; break;
  case KCASE(CPLUS,   FL ): KACC(*v+y,     D, D, 0.0 ); break;
  case KCASE(17,      INT): KACC(*v&y,     UI,UI,-1  ); break;
  case KCASE(22,      INT): KACC(*v^y,     UI,UI,0   ); break;
  case KCASE(23,      INT): KACC(*v|y,     UI,UI,0   ); break;
  case KCASE(25,      INT): KACC(~(*v^y),  UI,UI,-1  );
 }
 if(wt&FL)NAN1;
 *AS(z)=m; AN(z)=m*c; if(pp)RZ(z=pcvt(INT,z));
 EPILOG(z);
}    /* x f//.y */


#define KMCASE(ta,tw)  (ta+65536*tw)
#define KMACC(Ta,Tw) \
 {Ta*u=(Ta*)av;Tw*v=(Tw*)wv;                                        \
  if(1==c)DO(n, ++pv[*u];                   qv[*u]+=*v++;   ++u;)   \
  else    DO(n, ++pv[*u]; vv=qv+c**u; DO(c, *vv++ +=*v++;); ++u;);  \
 }
#define KMSET(Ta)    \
 {Ta*u=(Ta*)av;                                                                                           \
  if(1==c)DO(n, if(pv[j=*u++]){                             *zv++=qv[j]/pv[j]; pv[j]=0; if(s==++m)break;})   \
  else    DO(n, if(pv[j=*u++]){vv=qv+c*j; d=(D)pv[j]; DO(c, *zv++=*vv++/d;);   pv[j]=0; if(s==++m)break;});  \
 }
#define KMFUN(Tw)    \
 {Tw*v=(Tw*)wv;                                                      \
  if(1==c)DO(n, j=*xv++; ++pv[j]; zv[j]+=*v++;)                      \
  else    DO(n, j=*xv++; ++pv[j]; vv=zv+j*c; DO(c, *vv+++=*v++;););  \
 }

static DF2(jtkeymean){PROLOG;A p,q,x,z;D d,*qv,*vv,*zv;I at,*av,c,j,m=0,n,*pv,r,s,*u,wr,wt,*wv,*xv;
 RZ(a&&w);
 at=AT(a); av=AV(a); n=IC(a); 
 wt=AT(w); wv=AV(w); wr=AR(w);
 ASSERT(n==IC(w),EVLENGTH);
 if(!(AN(a)&&AN(w)&&at&DENSE&&wt&B01+INT+FL))R df2(a,w,folk(sldot(slash(ds(CPLUS))),ds(CDIV),sldot(ds(CPOUND))));
 at=keyrs(a,&r,&s); c=aii(w);
 if(wt&FL)NAN0;
 if(s&&s<=MAX(2*n,65536)){
  GA(p,INT,s,  1, 0    ); pv= AV(p); memset(pv,C0,s*  SZI); pv-=r;
  GA(q,FL, s*c,1, 0    ); qv=DAV(q); memset(qv,C0,s*c*SZD); qv-=r*c;
  GA(z,FL, s*c,wr,AS(w)); zv=DAV(z);
  switch(KMCASE(at,wt)){
   case KMCASE(B01,B01): KMACC(B, B); break;
   case KMCASE(B01,INT): KMACC(B, I); break;
   case KMCASE(B01,FL ): KMACC(B, D); break;
   case KMCASE(LIT,B01): KMACC(UC,B); break;
   case KMCASE(LIT,INT): KMACC(UC,I); break;
   case KMCASE(LIT,FL ): KMACC(UC,D); break;
   case KMCASE(C2T,B01): KMACC(US,B); break;
   case KMCASE(C2T,INT): KMACC(US,I); break;
   case KMCASE(C2T,FL ): KMACC(US,D); break;
   case KMCASE(INT,B01): KMACC(I ,B); break;
   case KMCASE(INT,INT): KMACC(I ,I); break;
   case KMCASE(INT,FL ): KMACC(I ,D);
  }
  switch(at){
   case B01: KMSET(B ); break;
   case LIT: KMSET(UC); break;
   case C2T: KMSET(US); break;
   case INT: KMSET(I );
  }
  *AS(z)=m; AN(z)=m*c;
 }else{
  RZ(x=indexof(a,a)); xv=AV(x); m=0; u=xv; DO(n, *u=i==*u?m++:xv[*u]; ++u;);
  GA(p,INT,m,  1, 0    );           pv= AV(p); memset(pv,C0,m*  SZI);
  GA(z,FL, m*c,wr,AS(w)); *AS(z)=m; zv=DAV(z); memset(zv,C0,m*c*SZD);
  switch(wt){
   case B01: KMFUN(B); break;
   case INT: KMFUN(I); break;
   case FL:  KMFUN(D);
  }
  if(1==c)DO(m, *zv++/=*pv++;) else DO(m, d=(D)*pv++; DO(c, *zv++/=d;););
 }
 if(wt&FL)NAN1;
 EPILOG(z);
}    /* x (+/%#)/.y */


#define GRPCD(T)            {T*v=(T*)wv; DO(n, j=*v++; if(0<=dv[j])++cv[j]; else{dv[j]=i; cv[j]=1; ++zn;});}
#define GRPIX(T,asgn,j,k)   {T*v=(T*)wv; DO(n, j=asgn; if(m>=j)*cu[k]++=i; \
                                 else{GA(x,INT,cv[k],1,0); *zv++=x; u=AV(x); *u++=m=j; cu[k]=u;})}

F1(jtgroup){PROLOG;A c,d,x,z,*zv;B b;I**cu,*cv,*dv,j,k,m,n,p,q,t,*u,*v,*wv,zn=0;
 RZ(w);
 if(SPARSE&AT(w))RZ(w=denseit(w));
 n=IC(w); t=AT(w); p=q=0; b=0; k=n?aii(w)*bp(t):0;
 if(!AN(w)){GA(z,BOX,n?1:0,1,0); if(n)RZ(*AAV(z)=IX(n)); R z;}
 if(2>=k)q=t&B01?(1==k?2:258):t&LIT?(1==k?256:65536):t&C2T?65536:0;
 if(k==SZI&&t&INT+SBT)irange(n,AV(w),&p,&q);
 if(b=q&&(2>=k||q<=2*n)){
  GA(c,INT,q,1,0); cv=AV(c)-p;  /* counts  */
  GA(d,INT,q,1,0); dv=AV(d)-p;  /* indices */
  wv=AV(w); v=dv+p; DO(q, *v++=-1;);
  switch(k){
   case 1:   GRPCD(UC); break;
   case 2:   GRPCD(US); break;
   case SZI: GRPCD(I);
 }}else{
  RZ(w=indexof(w,w)); wv=AV(w);
  GA(c,INT,n,1,0); cv=AV(c);
  m=-1; v=wv; DO(n, j=*v++; if(m>=j)++cv[j]; else{m=j; cv[j]=1; ++zn;});
 }
 GA(z,BOX,zn,1,0); zv=AAV(z);
 m=-1; cu=(I**)cv;
 switch(b*k){
  case 1:   GRPIX(UC,dv[k=*v++],j,k); break;
  case 2:   GRPIX(US,dv[k=*v++],j,k); break;
  case SZI: GRPIX(I ,dv[k=*v++],j,k); break;
  default:  GRPIX(I ,     *v++ ,j,j);
 }
 EPILOG(z);
}    /* (</. i.@#) w */


static DF2(jtkeytally);

static F1(jtkeytallysp){PROLOG;A b,e,q,x,y,z;I c,d,j,k,*u,*v;P*p;
 RZ(w);
 RZ(q=indexof(w,w));
 p=PAV(q); 
 x=SPA(p,x); u=AV(x); c=AN(x);
 y=SPA(p,i); v=AV(y);
 e=SPA(p,e); k=i0(e); 
 j=0; DO(c, if(k<=u[i])break; if(u[i]==v[i])++j;);
 RZ(b=ne(e,x));
 RZ(x=repeat(b,x)); RZ(x=keytally(x,x,mark)); u=AV(x); d=AN(x);
 GA(z,INT,1+d,1,0); v=AV(z);
 DO(j, *v++=*u++;); *v++=IC(w)-bsum(c,BAV(b)); DO(d-j, *v++=*u++;);
 EPILOG(z);
}    /* x #/.y , sparse x */

#define KEYTALLY(T)     {T*u;                             \
                         u=(T*)av; DO(n, ++*(qv+*u++););  \
                         u=(T*)av; DO(n, v=qv+*u++; if(*v){*zv++=*v; *v=0; if(s==++j)break;});}

static DF2(jtkeytally){PROLOG;A q;I at,*av,j=0,k,n,r=0,s=0,*qv,*u,*v;
 RZ(a&&w);
 n=IC(a); at=AT(a); av=AV(a);
 ASSERT(n==IC(w),EVLENGTH);
 if(!AN(a))R vec(INT,n?1:0,&n);
 if(at&SPARSE)R keytallysp(a);
 at=keyrs(a,&r,&s);
 if(n&&at&B01&&1>=AR(a)){B*b=(B*)av; k=bsum(n,b); R !k||n==k?vci(k?k:n):v2(*b?k:n-k,*b?n-k:k);}
 if(s&&s<=MAX(2*n,65536)){A z;I*zv;
  GA(z,INT,s,1,0); zv=AV(z);
  GA(q,INT,s,1,0); qv=AV(q)-r;
  u=qv+r; DO(s, *u++=0;);
  switch(at){
   case LIT: KEYTALLY(UC); break;
   case C2T: KEYTALLY(US); break;
   case INT: KEYTALLY(I );
  }
  AN(z)=*AS(z)=j;
  EPILOG(z);
 }
 RZ(q=indexof(a,a));
 if(!AR(q))R iv1; 
 v=qv=AV(q);
 u=qv; DO(n, ++*(qv+*u++););
 u=qv; DO(n, k=*u++; if(i<k){j+=*v++=k-i; if(n==j)break;});
 *AS(q)=AN(q)=v-qv;
 EPILOG(q);
}    /* x #/.y main control & dense x */


#define KEYHEADTALLY(Tz,Ta,Tw,exp0,exp1)  \
 {Ta*u;Tw*wv=(Tw*)AV(w);Tz*zz=(Tz*)zv;    \
  u=(Ta*)av; DO(n, ++*(qv+*u++););        \
  u=(Ta*)av; DO(n, v=qv+*u++; if(*v){*zz++=exp0; *zz++=exp1; k+=*v; if(n==k)break; *v=0;}); \
  AN(z)=zz-(Tz*)zv;                       \
 }

static DF2(jtkeyheadtally){PROLOG;A f,q,x,y,z;B b;I at,*av,k,n,r=0,s=0,*qv,*u,*v,wt,*zv;
 RZ(a&&w);
 n=IC(a); wt=AT(w);
 ASSERT(n==IC(w),EVLENGTH);
 ASSERT(!n||wt&NUMERIC,EVDOMAIN);
 if(SPARSE&AT(a)||1<AR(w)||!n||!AN(a))R key(a,w,self);
 at=keyrs(a,&r,&s); av=AV(a); 
 f=VAV(self)->f; f=VAV(f)->f; b=CHEAD==ID(f);
 if(at&B01&&1>=AR(a)){B*c,*d,*p=(B*)av;I i,j,m;
  c=d=p;
  if(*p){i=0; d=(B*)memchr(p,C0,n); j=d?d-p:0;}
  else  {j=0; c=(B*)memchr(p,C1,n); i=c?c-p:0;}
  k=bsum(n,p); m=c&&d?2:1;
  GA(x,INT,m,1,0); v=AV(x); *v++=MIN(i,j);      if(c&&d)*v=MAX(i,j); 
  GA(y,INT,m,1,0); v=AV(y); *v++=i<j||!d?k:n-k; if(c&&d)*v=i<j?n-k:k;
  R stitch(b?from(x,w):y,b?y:from(x,w));
 }
 if(at&LIT+C2T+INT&&wt&B01+INT+FL&&s&&s<=MAX(2*n,65536)){
  GA(z,wt&FL?FL:INT,2*s,2,0); zv=AV(z);
  GA(q,INT,s,1,0); qv=AV(q)-r;
  u=qv+r; DO(s, *u++=0;); k=0;
  switch(9*b+(at&INT?6:at&C2T?3:0)+(wt&FL?2:wt&INT?1:0)){
   case  0: KEYHEADTALLY(I,UC,B,*v,   wv[i]); break;
   case  1: KEYHEADTALLY(I,UC,I,*v,   wv[i]); break;
   case  2: KEYHEADTALLY(D,UC,D,(D)*v,wv[i]); break;
   case  3: KEYHEADTALLY(I,US,B,*v,   wv[i]); break;
   case  4: KEYHEADTALLY(I,US,I,*v,   wv[i]); break;
   case  5: KEYHEADTALLY(D,US,D,(D)*v,wv[i]); break;
   case  6: KEYHEADTALLY(I,I ,B,*v,   wv[i]); break;
   case  7: KEYHEADTALLY(I,I ,I,*v,   wv[i]); break;
   case  8: KEYHEADTALLY(D,I ,D,(D)*v,wv[i]); break;
   case  9: KEYHEADTALLY(I,UC,B,wv[i],*v   ); break;
   case 10: KEYHEADTALLY(I,UC,I,wv[i],*v   ); break;
   case 11: KEYHEADTALLY(D,UC,D,wv[i],(D)*v); break;
   case 12: KEYHEADTALLY(I,US,B,wv[i],*v   ); break;
   case 13: KEYHEADTALLY(I,US,I,wv[i],*v   ); break;
   case 14: KEYHEADTALLY(D,US,D,wv[i],(D)*v); break;
   case 15: KEYHEADTALLY(I,I ,B,wv[i],*v   ); break;
   case 16: KEYHEADTALLY(I,I ,I,wv[i],*v   ); break;
   case 17: KEYHEADTALLY(D,I ,D,wv[i],(D)*v); break;
  }
  *AS(z)=AN(z)/2; *(1+AS(z))=2;
 }else{
  RZ(q=indexof(a,a));
  x=repeat(eq(q,IX(n)),w); y=keytally(q,q,0L); z=stitch(b?x:y,b?y:x);
 }
 EPILOG(z);
}    /* x ({.,#)/.y or x (#,{.)/.y */


F1(jtsldot){A h=0;AF f1=jtoblique,f2=jtkey;C c,d,e;I flag=0;V*v;
 RZ(w);
 if(NOUN&AT(w)){flag=VGERL; RZ(h=fxeachv(1L,w));}
 else{
  v=VAV(w);
  switch(ID(w)){
   case CPOUND: f2=jtkeytally; break;
   case CSLASH: f2=jtkeyslash; if(vaid(v->f))f1=jtobqfslash; break;
   case CBOX:   f2=jtkeybox;   break;
   case CFORK:  if(v->f1==(AF)jtmean){f2=jtkeymean; break;}
                c=ID(v->f); d=ID(v->g); e=ID(v->h); 
                if(d==CCOMMA&&(c==CHEAD&&e==CPOUND||c==CPOUND&&e==CHEAD))f2=jtkeyheadtally;
 }}
 R fdef(CSLDOT,VERB, f1,f2, w,0L,h, flag, RMAX,RMAX,RMAX);
}
