/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Conjunctions: Rank Associates                                           */

#include "j.h"

#define DR(r)           (0>r?RMAX:r)


I mr(A w){R VAV(w)->mr;}
I lr(A w){R VAV(w)->lr;}
I rr(A w){R VAV(w)->rr;}

I efr(I ar,I r){R 0>r?MAX(0,r+ar):MIN(r,ar);}

#define NEWYA   {GA(ya,at,acn,acr,as+af); uu=CAV(ya);}
#define NEWYW   {GA(yw,wt,wcn,wcr,ws+wf); vv=CAV(yw);}
#define MOVEYA  {MC(uu,u+=ak,ak); if(ab)RZ(ya=relocate((I)a-(I)ya,ya));}
#define MOVEYW  {MC(vv,v+=wk,wk); if(wb)RZ(yw=relocate((I)w-(I)yw,yw));}

A jtrank1ex(J jt,A w,A fs,I mr,AF f1){PROLOG;A y,y0,yw,z;B wb;C*v,*vv;
    I k,mn,n=1,p,*s,wcn,wcr,wf,wk,wr,*ws,wt,yn,yr,*ys,yt;
 RZ(w);
 wt=AT(w);
 if(wt&SPARSE)R sprank1(w,fs,mr,f1);
 wr=AR(w); ws=AS(w); wcr=efr(wr,mr); wf=wr-wcr; wb=ARELATIVE(w);
 if(!wf)R CALL1(f1,w,fs);
 RE(wcn=prod(wcr,wf+ws)); wk=wcn*bp(wt); v=CAV(w)-wk; NEWYW;
 p=wf; s=ws; RE(mn=prod(wf,ws));
 if(AN(w))MOVEYW else RZ(yw=reshape(vec(INT,wcr,ws+wf),filler(w)));
#define VALENCE   1
#define TEMPLATE  0
#include "cr_t.h"
}

A jtrank2ex(J jt,A a,A w,A fs,I lr,I rr,AF f2){PROLOG;A y,y0,ya,yw,z;B ab,b,wb;
   C*u,*uu,*v,*vv;I acn,acr,af,ak,ar,*as,at,k,mn,n=1,p,q,*s,wcn,wcr,wf,wk,wr,*ws,wt,yn,yr,*ys,yt;
 RZ(a&&w);
 at=AT(a); wt=AT(w);
 if(at&SPARSE||wt&SPARSE)R sprank2(a,w,fs,lr,rr,f2);
 ar=AR(a); as=AS(a); acr=efr(ar,lr); af=ar-acr; ab=ARELATIVE(a);
 wr=AR(w); ws=AS(w); wcr=efr(wr,rr); wf=wr-wcr; wb=ARELATIVE(w);
 if(!af&&!wf)R CALL2(f2,a,w,fs);
 RE(acn=prod(acr,as+af)); ak=acn*bp(at); u=CAV(a)-ak; NEWYA;
 RE(wcn=prod(wcr,ws+wf)); wk=wcn*bp(wt); v=CAV(w)-wk; NEWYW;
 b=af<=wf; p=b?wf:af; q=b?af:wf; s=b?ws:as; RE(mn=prod(p,s)); RE(n=prod(p-q,s+q));
 ASSERT(!ICMP(as,ws,q),EVLENGTH);
 if(AN(a))MOVEYA else RZ(ya=reshape(vec(INT,acr,as+af),filler(a)));
 if(AN(w))MOVEYW else RZ(yw=reshape(vec(INT,wcr,ws+wf),filler(w)));
#define VALENCE  2
#define TEMPLATE 0
#include "cr_t.h"
}


/* Integrated Rank Support                              */
/* f knows how to compute f"r                           */
/* jt->rank points to a 2-element vector of             */
/* (left, right (monadic)) ranks                        */
/* 0=jt->rank means f is not being called from rank     */
/* jt->rank is guaranteed positive                      */
/* jt->rank is guaranteed <: argument ranks             */
/* frame agreement is verified before invoking f        */
/* frames either match, or one is empty                 */
/* (i.e. prefix agreement invokes general case)         */

A jtirs1(J jt,A w,A fs,I m,AF f1){A z;I*old=jt->rank,rv[2],wr; 
 RZ(w);
 wr=AR(w); rv[1]=m=efr(wr,m);
 if(m>=wr)R CALL1(f1,w,fs);
 rv[0]=0;
 jt->rank=rv; z=CALL1(f1,w,fs); jt->rank=old; 
 R z;
}

A jtirs2(J jt,A a,A w,A fs,I l,I r,AF f2){A z;I af,ar,*old=jt->rank,rv[2],wf,wr; 
 RZ(a&&w);
 ar=AR(a); rv[0]=l=efr(ar,l); af=ar-l;
 wr=AR(w); rv[1]=r=efr(wr,r); wf=wr-r;
 if(!(af||wf))R CALL2(f2,a,w,fs);
 ASSERT(!ICMP(AS(a),AS(w),MIN(af,wf)),EVLENGTH);
 /* if(af&&wf&&af!=wf)R rank2ex(a,w,fs,l,r,f2); */
 jt->rank=rv; z=CALL2(f2,a,w,fs); jt->rank=old; 
 R z;
}


static DF1(cons1a){R VAV(self)->f;}

static DF2(cons2a){R VAV(self)->f;}

static DF1(cons1){V*sv=VAV(self);
 RZ(w);
 R rank1ex(w,self,efr(AR(w),*AV(sv->h)),cons1a);
}

static DF2(cons2){V*sv=VAV(self);I*v=AV(sv->h);
 RZ(a&&w);
 R rank2ex(a,w,self,efr(AR(a),v[1]),efr(AR(w),v[2]),cons2a);
}

static DF1(rank1i){DECLF;A h=sv->h;I*v=AV(h); R irs1(w,fs,*v,f1);}

static DF2(rank2i){DECLF;A h=sv->h;I*v=AV(h); R irs2(a,w,fs,v[1],v[2],f2);}

static DF1(rank1){DECLF;A h=sv->h;I m,*v=AV(h),wr;
 RZ(w);
 wr=AR(w); m=efr(wr,v[0]);
 R m<wr?rank1ex(w,fs,m,f1):CALL1(f1,w,fs);
}

static DF2(rank2){DECLF;A h=sv->h;I ar,l,r,*v=AV(h),wr;
 RZ(a&&w);
 ar=AR(a); l=efr(ar,v[1]);
 wr=AR(w); r=efr(wr,v[2]);
 R l<ar||r<wr?rank2ex(a,w,fs,l,r,f2):CALL2(f2,a,w,fs);
}

static void qqset(A a,AF*f1,AF*f2,I*flag){A f,g;C c,d,e,p,q;I m=0;V*v;
 static C at1[]={CFLOOR,CLE,CCEIL,CGE,CPLUS,CPLUSDOT,CPLUSCO, 
   CSTAR,CSTARDOT,CSTARCO,CMINUS,CNOT,CHALVE,CDIV,CSQRT,CEXP,CLOG, 
   CSTILE,CBANG,CLEFT,CRIGHT,CQUERY,CHGEOM,CJDOT,CCIRCLE, 
   CPCO,CQCO,CRDOT,CTDOT,CXCO,0};  /* f monad <-> f"r monad */
 static C ir1[]={CCOMMA,CLAMIN,CLEFT,CRIGHT,CCANT,CROT,CTAKE,CDROP,CGRADE,CDGRADE,
   CBOX,CNE,CTAIL,CCTAIL,CSLASH,CBSLASH,CBSDOT,CCOMDOT,CPCO,CATDOT,0};
 static C ir2[]={CCOMMA,CLAMIN,CLEFT,CRIGHT,CCANT,CROT,CTAKE,CDROP,CGRADE,CDGRADE,
   CDOLLAR,CPOUND,CIOTA,CICO,CEPS,CLBRACE,CMATCH,
   CEQ,CLT,CMIN,CLE,CGT,CMAX,CGE,CPLUS,CPLUSDOT,CPLUSCO,CSTAR,CSTARDOT,CSTARCO,
   CMINUS,CDIV,CEXP,CNE,CSTILE,CBANG,CCIRCLE,0};
 if(NOUN&AT(a)){*f1=cons1; *f2=cons2; *flag=0; R;}
 v=VAV(a); c=v->id;
 if(strchr(ir1,c))m+=VIRS1;
 if(strchr(ir2,c))m+=VIRS2;
 if(!(m&VIRS1)&&v->flag&VIRS1&&c!=CQQ)m+=VIRS1;
 if(!(m&VIRS2)&&v->flag&VIRS2&&c!=CQQ)m+=VIRS2;
 if(!m){
  p=0; if(f=v->f)p=VERB&AT(f)&&strchr(ir2,d=ID(f));
  q=0; if(g=v->g)q=VERB&AT(g)&&strchr(ir2,e=ID(g));
  switch(c){
   case CFIT:   if(p&&d!=CEXP)m+=VIRS2; if(d==CNE)m+=VIRS1; break;
   case CTILDE: if(p)m+=VIRS1+VIRS2; break;
   case CAMP:   if(p&&NOUN&AT(g)||q&&NOUN&AT(f))m+=VIRS1; break;
   case CFORK:  if(v->f1==(AF)jtmean)m+=VIRS1;
 }}
 *f1=strchr(at1,c) ? v->f1 : m&VIRS1 ? rank1i : rank1;
 *f2=                        m&VIRS2 ? rank2i : rank2; 
 *flag=m;
}

F2(jtqq){A h,t;AF f1,f2;D*d;I flag,*hv,n,r[3],*v;
 RZ(a&&w);
 GA(h,INT,3,1,0); hv=AV(h);
 if(VERB&AT(w)){
  GA(t,FL,3,1,0); d=DAV(t);
  n=r[0]=hv[0]=mr(w); d[0]=n<=-RMAX?-inf:RMAX<=n?inf:n;
  n=r[1]=hv[1]=lr(w); d[1]=n<=-RMAX?-inf:RMAX<=n?inf:n;
  n=r[2]=hv[2]=rr(w); d[2]=n<=-RMAX?-inf:RMAX<=n?inf:n;
  w=t;
 }else{
  n=AN(w);
  ASSERT(1>=AR(w),EVRANK);
  ASSERT(0<n&&n<4,EVLENGTH);
  RZ(t=vib(w)); v=AV(t);
  hv[0]=v[2==n]; r[0]=DR(hv[0]);
  hv[1]=v[3==n]; r[1]=DR(hv[1]);
  hv[2]=v[n-1];  r[2]=DR(hv[2]);
 }
 qqset(a,&f1,&f2,&flag);
 R fdef(CQQ,VERB, f1,f2, a,w,h, flag, r[0],r[1],r[2]);
}
