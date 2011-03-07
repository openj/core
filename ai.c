/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Adverbs: Inverse & Identity Functions                                   */

#include "j.h"


static F1(jtinvamp);

static B ip(A w,C c,C d){A f,g;V*v;
 v=VAV(w); f=v->f; g=v->g;
 R CSLASH==ID(f)&&c==ID(VAV(f)->f)&&d==ID(g);
}

static B consf(A w){A f;C c;
 c=ID(w);
 if(c==CFCONS||c==CQQ&&(f=VAV(w)->f,NOUN&AT(f)))R 1;
 R 0;
}    /* 1 iff w is a constant function */

static F2(jtfong){A f;C c;V*v;
 RZ(a&&w);
 v=VAV(a); c=v->id; f=v->f;
 R c==CRIGHT ? w : c==CFORK&&(NOUN&AT(f)||CCAP==ID(f)) ? folk(f,v->g,fong(v->h,w)) : folk(ds(CCAP),a,w);
}    /* [: f g  with simplifications */

static F1(jtinvfork){A f,fi,g,gi,h,k;B b,c;V*v;
 RZ(w);
 v=VAV(w); RZ(f=unname(v->f)); g=v->g; RZ(h=unname(v->h));
 if(CCAP==ID(f))R fong(inv(h),inv(g));
 c=1&&NOUN&AT(f); b=c||consf(f);
 ASSERT(b!=consf(h),EVDOMAIN);
 RZ(k=c?f:df1(zero,b?f:h));
 RZ(gi=inv(b?amp(k,g):amp(g,k)));
 RZ(fi=inv(b?h:f));
 if(CAMP==ID(gi)){
  v=VAV(gi); 
  if     (NOUN&AT(v->f))RZ(gi=folk(v->f,     v->g, ds(CRIGHT)))
  else if(NOUN&AT(v->g))RZ(gi=folk(v->g,swap(v->f),ds(CRIGHT)));
 }
 R fong(fi,gi);
}

static DF1(jtexpandf){A f; RZ(w&&self); f=VAV(self)->f; R expand(VAV(f)->f,w);}

static DF1(jtexpandg){A f,g,z;V*v;
 RZ(w&&self);
 f=VAV(self)->f; v=VAV(f); g=v->g;
 jt->fill=VAV(g)->g; z=expand(v->f,w); jt->fill=0; 
 R z;
}

static F2(jtdiag){I d,k,m,p,r,t,*v;
 RZ(a&&w);
 r=AR(w); t=AT(w); k=bp(t);
 v=AS(w);   m=0;      DO(r, m=MIN(m,v[i]););
 v=AS(w)+r; p=1; d=0; DO(r, d+=p; p*=*--v;);
 if(t!=AT(a))RZ(a=cvt(t,a));
 if(AR(a)){
  ASSERT(m==AN(a),EVLENGTH);
  ASSERT(0,EVNONCE);
 }else{
  ASSERT(0,EVNONCE);
}}

static F1(jtbminv){A*wv,x,z=w;I i,j,m,r,*s,t=0,*u,**v,*y,wn,wr,*ws,wd;
 RZ(w);
 ASSERT(0,EVNONCE);
 ASSERT(BOX&AT(w),EVDOMAIN);
 wn=AN(w); wr=AR(w); ws=AS(w); wv=AAV(w); wd=(I)w*ARELATIVE(w);
 if(1>=wr)R raze(w);
 if(!wn)R iota(reshape(sc(wr),zero));
 GA(x,INT,wr,1,0); u=AV(x); memset(u,C0,wr*SZI);
 GA(x,INT,wr,1,0); v=(I**)AV(x);
 DO(wr, m=ws[i]; GA(x,INT,m,1,0); memset(v[i]=AV(x),CFF,m*SZI););
 for(i=0;i<wn;++i){
  x=WVR(i); r=AR(x); s=AS(x);
  if(AN(x)){if(!t)t=AT(x); ASSERT(HOMO(t,AT(x)),EVDOMAIN);}
  ASSERT(2>r||r==wr,EVRANK);
  if(2>r)z=0;
  else DO(wr, y=v[i]+u[i]; if(0>*y)*y=s[i]; else ASSERT(*y==s[i],EVLENGTH););
  j=wr; while(1){--j; ++u[j]; if(ws[j]>u[j])break; u[j]=0;}
 }
 if(!z){A f,h,*zv;I*hv;
  GA(z,BOX,wn,2,ws); zv=AAV(z);
  GA(h,INT,wr,1,0); hv=AV(h);
  GA(f,t,1,1,0); RZ(f=filler(f)); memset(u,C0,wr*SZI);
  for(i=0;i<wn;++i){
   zv[i]=x=WVR(i);
   if(2>AR(x)){DO(wr, hv[i]=*(v[i]+u[i]);); RZ(zv[i]=diag(x,reshape(h,f)));}
   j=wr-1; while(1){--j; ++u[j]; if(ws[j]>u[j])break; u[j]=0;}
 }}
 DO(wr, RZ(z=df1(z,slash(under(qq(ds(CCOMMA),sc(wr-i)),ds(COPE))))););
 R ope(z);
}    /* <;.1 or <;.2 inverse on matrix argument */


static F1(jtinvamp){A f,ff,g,h,*q,x,y;B nf,ng;C c,d,*yv;I n;V*u,*v;
 RZ(w);
 v=VAV(w);
 f=v->f; nf=!!(NOUN&AT(f));
 g=v->g; ng=!!(NOUN&AT(g));
 h=nf?g:f; x=nf?f:g; c=ID(h); u=VAV(h);   
 switch(c){
  case CPLUS:    R amp(negate(x),h);
  case CSTAR:    R amp(recip(x), h);
  case CMINUS:   R nf?w:amp(x,ds(CPLUS));
  case CDIV:     R nf?w:amp(x,ds(CSTAR));
  case CROOT:    R amp(ds(nf?CEXP:CLOG),x);
  case CEXP:     R ng&&equ(x,num[2])?ds(CROOT):amp(x,ds(nf?CLOG:CROOT));
  case CLOG:     R nf?amp(x,ds(CEXP)):amp(ds(CROOT),x);
  case CJDOT:    R nf?atop(inv(ds(CJDOT)),amp(ds(CMINUS),x)):amp(ds(CMINUS),jdot1(x));
  case CRDOT:    R nf?atop(inv(ds(CRDOT)),amp(ds(CDIV  ),x)):amp(ds(CDIV  ),rdot1(x));
  case CLBRACE:  R nf?amp(pinv(x),h):amp(x,ds(CIOTA));
  case COBVERSE: ff=VAV(h)->g; R amp(nf?x:ff,nf?ff:x);
  case CPDERIV:  if(!AR(h))R ds(CPDERIV);
  case CXCO:     RE(n=i0(x)); ASSERT(n&&-3<n&&n<3,EVDOMAIN);
  case CROT:
  case CCIRCLE:  
  case CSPARSE:  if(nf)R amp(negate(x),h);   break;
  case CABASE:   if(nf)R amp(x,ds(CBASE));   break;
  case CIOTA:    if(nf)R amp(ds(CLBRACE),x); break;
  case CTHORN:   if(nf)R ds(CEXEC);          break;
  case CTILDE:   
   if(ff=VAV(h)->f,VERB&AT(ff))R invamp(amp(nf?ff:x,nf?x:ff));
   else{ff=unname(h); R invamp(amp(nf?x:ff,nf?ff:x));}
  case CSCO:     
   ASSERT(nf,EVDOMAIN); 
   RE(n=i0(x)); ASSERT(n&&-6<=n&&n<=6,EVDOMAIN);
   R amp(sc(-n),h);
  case CUCO:
   ASSERT(nf,EVDOMAIN); 
   RE(n=i0(x)); ASSERT(1<=n&&n<=4||7<=n&&n<=8,EVDOMAIN);
   R amp(sc(1==n?2L:2==n?1L:3==n?4L:4==n?3L:7==n?8L:7L),h);
  case CCANT:    
   ASSERT(nf,EVDOMAIN); 
   R obverse(eva(x,"] |:~ x C.^:_1 i.@#@$"),w);
  case CPCO:
   if(nf){
    RE(n=i0(x));
    switch(n){
     case -4: case 4: R amp(negate(x),h);
     case -1:         R ds(CPCO);
     case  2:         R obverse(eval("*/@(^/)\"2"),w);
     case  3:         R eval("*/");
   }}
   break;
  case CQCO:     
   if(nf){
    ASSERT(!AR(x),EVRANK);
    R obverse(eval(all1(lt(x,zero))?"*/@(^/)\"2":"(p:@i.@# */ .^ ])\"1"),w);
   }
   break;
  case CFIT:
   ASSERT(nf&&(CPOUND==ID(VAV(g)->f)),EVDOMAIN);
   ASSERT(1==AR(x),EVRANK);
   R fdef(CPOWOP,VERB, jtexpandg,0L, w,num[-1],0L, 0L, RMAX,0L,0L);
  case CPOUND:
   ASSERT(nf,EVDOMAIN);
   ASSERT(1==AR(x),EVRANK);
   R fdef(CPOWOP,VERB, jtexpandf,0L, w,num[-1],0L, 0L, RMAX,0L,0L);
   break;
  case CPOWOP:
   if(VGERL&u->flag){ff=*(1+AAV(u->h)); R amp(nf?x:ff,nf?ff:x);} 
   break;
  case CCOMMA:  
   n=IC(x); 
   R obverse(1==n?ds(nf?CDROP:CCTAIL):amp(sc(nf?n:-n),ds(CDROP)),w);
  case CBASE:   
   if(!nf)break;
   R AR(x) ? amp(x,ds(CABASE)) : 
    obverse(evc(x,mag(x),"$&x@>:@(y&(<.@^.))@(1&>.)@(>./)@:|@, #: ]"),w);
  case CBANG:
   ASSERT(!AR(x),EVRANK);
   ASSERT(all1(lt(zero,x)),EVDOMAIN);
   GA(y,BOX,9,1,0); q=AAV(y);
   q[0]=cstr("3 :'(-("); q[1]=q[3]=lrep(w);
   q[2]=cstr("-y\"_)%1e_3&* "); q[4]=cstr("\"0 D:1 ])^:_[");
   h=lrep(x);
   if(nf){q[5]=over(over(h,cstr("&<@|@{:}")),over(h,cstr(",:"))); q[6]=over(h,cstr("%:y*!")); q[7]=h;}
   else  {q[5]=cstr("1>.{.@/:\"1|y-/(i.!])"); q[6]=h; q[7]=mtv;}
   RE(q[8]=cstr("'")); RZ(y=raze(y));
   R obverse(eval(CAV(y)),w);
  case CATOMIC:
   if(ng){ASSERT(equ(x,nub(x)),EVDOMAIN); R obverse(atop(f,amp(x,ds(CIOTA))),w);}
  case CCYCLE:
   if(nf&&AR(x)<=(c==CCYCLE))R obverse(eva(w,"/:@x@(i.@#) { ]"),w); break;
  case CDROP:
   if(!(nf&&1>=AR(x)))break;
   RZ(x=cvt(INT,x));
   RZ(y=eps(v2(-1L,1L),signum(x))); yv=CAV(y);
   f=amp(mag(x),ds(CPLUS));
   g=1==AN(x)?ds(CPOUND):atop(amp(tally(x),ds(CTAKE)),ds(CDOLLAR));
   h=!yv[1]?f:atop(!yv[0]?ds(CMINUS):amp(negate(signum(x)),ds(CSTAR)),f);
   R obverse(hook(swap(ds(CTAKE)),atop(h,g)),w);
  case CDOMINO:
   if(!(2==AR(x)&&*AS(x)==*(1+AS(x))))break;
   ff=eval("+/ .*");
   R nf?atop(h,amp(ff,minv(x))):amp(x,ff);
  case CDOT:
   if(ip(h,CPLUS,CSTAR)){
    ASSERT(2==AR(x),EVRANK);
    ASSERT(*AS(x)==*(1+AS(x)),EVLENGTH);
    R nf?amp(ds(CDOMINO),x):amp(h,minv(x));
   }
   break;
  case CQQ:
   if(ng&&equ(x,one)&&equ(f,eval("i.\"1")))R hook(ds(CFROM),ds(CEQ));
   break;
  case CBSLASH:
   if(nf&&(n=i0(x),0>n)&&(d=ID(u->f),d==CLEFT||d==CRIGHT))R slash(ds(CCOMMA));
   break;
  case CIBEAM:
   x=VAV(h)->f; y=VAV(h)->g;
   if(NOUN&AT(x)&&equ(x,num[3])&&NOUN&AT(y)){
    RE(n=i0(f));
    if(all1(eps(y,v2(4L,5L)))){ASSERT(n&&-2<=n&&n<=2,EVDOMAIN); R amp(sc(-n),g);}
    if(all1(eps(y,v2(1L,3L)))){ASSERT(0==n||1==n||10==n||11==n,EVDOMAIN); R foreign(x,num[2]);}
   }
   break;
  case CBDOT:
   RE(n=i0(x));
   switch(i0(VAV(h)->f)){
    case 22: case 25:          R w;
    case 19: case 28:          if(ng)R w; break;
    case 21: case 26:          if(nf)R w; break;
    case 32: case 33: case 34: ASSERT(nf,EVDOMAIN); R amp(negate(x),h);
   }
   break;
  case CPOLY:
   if(nf&&1==AR(x)&&2==AN(x)&&NUMERIC&AT(x)&&!equ(zero,tail(x))){
    RZ(y=recip(tail(x)));
    R amp(over(tymes(y,negate(head(x))),y),h);
 }}
 ASSERT(0,EVDOMAIN);
}

static C invf[2][29] = {
 CDIV,   CPLUS,  CMINUS,  CLEFT,   CRIGHT,  CREV,    CCANT,   CPOLY, 
 CNOT,   CGRADE, CCYCLE,  CDOMINO, COPE,    CBOX,    CLOG,    CEXP,
 CGE,    CLE,    CHALVE,  CPLUSCO, CSQRT,   CSTARCO, CHEAD,   CLAMIN,
 CABASE, CBASE,  CTHORN,  CEXEC,   0,
 CDIV,   CPLUS,  CMINUS,  CLEFT,   CRIGHT,  CREV,    CCANT,   CPOLY,
 CNOT,   CGRADE, CCYCLE,  CDOMINO, CBOX,    COPE,    CEXP,    CLOG,
 CLE,    CGE,    CPLUSCO, CHALVE,  CSTARCO, CSQRT,   CLAMIN,  CHEAD,  
 CBASE,  CABASE, CEXEC,   CTHORN,  0 
};

F1(jtinv){A f,ff,g;B b,nf,ng,vf,vg;C id,*s;I p,q;V*v;
 RZ(w);
 ASSERT(VERB&AT(w),EVDOMAIN); 
 id=ID(w); v=VAV(w);
 if(s=strchr(invf[0],id))R ds(invf[1][s-invf[0]]);
 f=v->f; nf=f&&AT(f)&NOUN+NAME; vf=f&&!nf;
 g=v->g; ng=g&&AT(g)&NOUN+NAME; vg=g&&!ng;
 switch(id){
  case CCIRCLE:  R eval("1p_1&*");
  case CJDOT:    R eval("0j_1&*");
  case CRDOT:    R eval("%&0j1@^.");
  case CPLUSDOT: R eval("j./\"1\"_ :. +.");
  case CSTARDOT: R eval("r./\"1\"_ :. *.");
  case CDGRADE:  R eval("/:@|.");
  case CWORDS:   R eval("}:@;@(,&' '&.>\"1) :. ;:");
  case CBANG:    R eval("3 :'(-(!-y\"_)%1e_3&* !\"0 D:1 ])^:_ <.&170^:(-:+)^.y' :. !");
  case CXCO:     R amp(num[-1],w);
  case CSPARSE:  R fdef(CPOWOP,VERB,jtdenseit,0L, w,num[-1],0L, 0L, RMAX,RMAX,RMAX);
  case CPCO:     R fdef(CPOWOP,VERB,jtplt,    0L, w,num[-1],0L, 0L, 0L,  0L,  0L  );
  case CQCO:     R eval("*/");
  case CUCO:     R amp(num[3],w);
  case CUNDER:   R under(inv(f),g);
  case CFORK:    R invfork(w);
  case CAMP:     if(nf!=ng)R invamp(w);  /* fall thru */
  case CAT:      if(vf&&vg)R atop(inv(g),inv(f));   break;
  case CAMPCO:
  case CATCO:    if(vf&&vg)R atco(inv(g),inv(f));   break;
  case CSLASH:   if(CSTAR==ID(f))R ds(CQCO);        break;
  case CQQ:      if(vf)R qq(inv(f),g);              break;
  case COBVERSE: if(vf&&vg)R obverse(g,f);          break;
  case CSCO:     R amp(num[5],w);
  case CPOWOP:   
   if(vf&&ng){RE(p=i0(g)); R -1==p?f:1==p?inv(f):powop(0>p?f:inv(f),sc(ABS(p)));}
   if(VGERL&v->flag)R*(1+AAV(v->h));
   break;
  case CTILDE:
   if(nf)R inv(symbrd(f));
   switch(ID(f)){
    case CPLUS:  R ds(CHALVE);
    case CSTAR:  R ds(CSQRT);
    case CJDOT:  R eval("0.5j_0.5&*");
    case CLAMIN: R eval("{. :. (,:~)");
    case CSEMICO:R eval(">@{. :. (;~)");
    case CCOMMA: R eval("<.@-:@# {. ] :. (,~)");
    case CEXP:   R eval("3 : '(- -&b@(*^.) % >:@^.)^:_ ]1>.b=.^.y' \" 0 :. (^~)");
   }
   break;
  case CBSLASH:
  case CBSDOT:
   if(CSLASH==ID(f)&&(ff=VAV(f)->f,ff&&VERB&AT(ff))){
    b=id==CBSDOT;
    switch(ID(ff)){
     case CPLUS: R obverse(eval(b?"- 1&(|.!.0)":" - |.!.0"),w);
     case CSTAR: R obverse(eval(b?"% 1&(|.!.1)":" % |.!.1"),w);
     case CEQ:   R obverse(eval(b?"= 1&(|.!.1)":" = |.!.1"),w);
     case CNE:   R obverse(eval(b?"~:1&(|.!.0)":" ~:|.!.0"),w);
     case CMINUS:R obverse(eval(b?"+ 1&(|.!.0)":"(- |.!.0) *\"_1 $&1 _1@#"),w);
     case CDIV:  R obverse(eval(b?"* 1&(|.!.1)":"(% |.!.1) ^\"_1 $&1 _1@#"),w);
   }}
   break;
  case CCUT:
   if(CBOX==ID(f)&&ng&&(p=i0(g),1==p||2==p))R fdef(CPOWOP,VERB, jtbminv,0L, w,num[-1], 0L,0L, RMAX,RMAX,RMAX);
   break;
  case CIBEAM:
   p=i0(f); q=i0(g);
   if(3==p&&1==q)R foreign(f,num[2]);
   if(3==p&&2==q)R foreign(f,one   );
   if(3==p&&3==q)R foreign(f,num[2]);
   break;
  case CHOOK:
   if(CFROM==ID(f)&&CEQ==ID(g))R eval("i.\"1&1");
   break;
 }
 if(!nameless(w))R inv(fix(w));
 ASSERT(0,EVDOMAIN);
}

static F1(jtneutral){A x,y;B b;V*v;
 RZ(w);
 v=VAV(w);
 ASSERT(!v->lr&&!v->rr,EVDOMAIN);
 RZ(y=v2(0L,1L));
 RZ(x=scf(infm)); b=equ(y,CALL2(v->f2,x,y,w)); RESETERR; if(b)R x;
 x=ainf;          b=equ(y,CALL2(v->f2,x,y,w)); RESETERR; if(b)R x;
 x=zero;          b=equ(y,CALL2(v->f2,x,y,w)); RESETERR; if(b)R x; 
 x=one;           b=equ(y,CALL2(v->f2,x,y,w)); RESETERR; if(b)R x;
 RZ(x=scf(infm)); b=equ(y,CALL2(v->f2,y,x,w)); RESETERR; if(b)R x;
 x=ainf;          b=equ(y,CALL2(v->f2,y,x,w)); RESETERR; if(b)R x;
 x=zero;          b=equ(y,CALL2(v->f2,y,x,w)); RESETERR; if(b)R x;
 x=one;           b=equ(y,CALL2(v->f2,y,x,w)); RESETERR; if(b)R x;
 ASSERT(0,EVDOMAIN);
}    /* neutral of arbitrary rank-0 function */

F1(jtiden){A f,g,x=0;V*u,*v;
 RZ(w=fix(w)); ASSERT(VERB&AT(w),EVDOMAIN);
 v=VAV(w); f=v->f; g=v->g;
 switch(v->id){
  default:      RZ(x=neutral(w)); break;
  case CCOMMA:  R eval("i.@(0&,)@(2&}.)@$");
  case CDOT:    if(!(ip(w,CPLUS,CSTAR)||ip(w,CPLUSDOT,CSTARDOT)||ip(w,CNE,CSTARDOT)))break;
  case CDOMINO: R atop(atop(ds(CEQ),ds(CGRADE)),ds(CHEAD));
  case CCYCLE:
  case CLBRACE: R atop(ds(CGRADE),ds(CHEAD));
  case CSLASH:  if(VERB&AT(f))R atop(iden(f),ds(CPOUND)); break;
  case CPLUS: case CMINUS: case CSTILE:   case CNE:
  case CGT:   case CLT:    case CPLUSDOT: case CJDOT:   case CRDOT:
                x=zero; break;
  case CSTAR: case CDIV:   case CEXP:     case CROOT:   case CBANG:
  case CEQ:   case CGE:    case CLE:      case CSTARDOT:
                x=one; break;
  case CMAX:    x=scf(infm); break;
  case CMIN:    x=ainf; break;
  case CUNDER:  x=df1(df1(mtv,iden(f)),inv(g)); break;
  case CAT:
   if(CAMP==ID(f)&&(u=VAV(f),NOUN&AT(u->f)&&!AR(u->f)&&CSTILE==ID(u->g)))switch(ID(g)){
    case CSTAR: case CEXP: x=one;  break;
    case CPLUS:            x=zero;
   }
   break;
  case CBDOT:
   switch(i0(f)){
    case 25:    x=num[-1]; break;
    case  2: case  4: case  5: case  6: case  7:
    case 18: case 20: case 21: case 22: case 23:
                x=zero; break;
    case  1: case  9: case 11: case 13: case 17: 
    case 27: case 29:
                x=one;
 }}
 ASSERT(x,EVDOMAIN);
 R folk(x,swap(ds(CDOLLAR)),atop(ds(CBEHEAD),ds(CDOLLAR)));
}
