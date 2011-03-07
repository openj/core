/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Representations: Linear and Paren                                       */

#include "j.h"

#if !SY_WINCE
extern int isdigit(int);
#endif

static F1(jtlnoun);
static F1(jtlnum);
static F1(jtlrr);

#define NUMV(c)  (c==C9||c==CD||c==CA||c==CS)


static B jtlp(J jt,A w){B b=1,p=0;C c,d,q=CQUOTE,*v;I j=0,n;
 RZ(w);
 n=AN(w); v=CAV(w); c=*v; d=*(v+n-1);
 if(1==n||(2==n||3>=n&&' '==c)&&(d==CESC1||d==CESC2)||vnm(n,v))R 0;
 if(C9==ctype[c])DO(n-1, d=c; c=ctype[*++v]; if(b=!NUMV(c)||d==CS&&c!=C9)break;)
 else if(c==q)   DO(n-1, c=*v++; if(c==q)p=!p; if(b=p?0:c!=q)break;)
 else if(c=='(') DO(n-1, c=*v++; j+=c=='('?1:c==')'?-1:0; if(b=!j)break;)
 R b;
}    /* 1 iff put parens around w */

static A jtlcpa(J jt,B b,A w){A z=w;C*zv;I n;
 RZ(w);
 if(b){n=AN(w); GA(z,LIT,2+n,1,0); zv=CAV(z); *zv='('; MC(1+zv,AV(w),n); zv[1+n]=')';}
 R z;
}    /* if b then (w) otherwise just w */

static A jtlcpb(J jt,B b,A w){A z=w;B p;C c,*v,*wv,*zv;I n;
 RZ(w);
 n=AN(w); wv=CAV(w); 
 if(!b){
  c=ctype[*wv]; v=wv; p=0;
  if     (c==CQ)DO(n-1, c=ctype[*++v]; if(c==CQ)p=!p; else if(p){b=1; break;})
  else if(c==C9)DO(n-1, c=ctype[*++v]; if(!(c==C9   ||c==CS   )){b=1; break;})
  else          DO(n-1, c=      *++v ; if(!(c==CESC1||c==CESC2)){b=1; break;});
  if(b&&vnm(n,wv))b=0;
 }
 if(b){GA(z,LIT,2+n,1,0); zv=CAV(z); *zv='('; MC(1+zv,wv,n); zv[1+n]=')';}
 R z;
}

static A jtlcpx(J jt,A w){RZ(w); R CALL2(jt->lcp,lp(w),w,0);}

static F1(jtltiea){A t,*v,*wv,x,y;B b;C c;I n,wd;
 RZ(w);
 n=AN(w); wv=AAV(w); wd=(I)w*ARELATIVE(w); RZ(t=spellout(CGRAVE));
 GA(y,BOX,n+n,1,0); v=AAV(y);
 DO(n, *v++=i?t:mtv; x=WVR(i); c=ID(x); RZ(x=lrr(x)); 
     b=c==CHOOK||c==CFORK||i&&lp(x); RZ(*v++=CALL2(jt->lcp,b,x,0)););
 R raze(y);
}

static F1(jtltieb){A pt,t,*v,*wv,x,y;B b;C c,*s;I wd,n;
 RZ(w);
 n=AN(w); wv=AAV(w); wd=(I)w*ARELATIVE(w); RZ(t=spellout(CGRAVE)); RZ(pt=over(scc(')'),t));
 GA(y,BOX,n+n,1,0); v=AAV(y);
 if(1>=n)x=mtv; else{GA(x,LIT,n-2,1,0); s=CAV(x); DO(n-2, *s++='(';);}
 DO(n, *v++=0==i?x:1==i?t:pt; x=WVR(i); c=ID(x); RZ(x=lrr(x)); 
     b=c==CHOOK||c==CFORK||i&&lp(x); RZ(*v++=CALL2(jt->lcp,b,x,0)););
 R raze(y);
}

static F1(jtlsh){R over(thorn1(shape(w)),spellout(CDOLLAR));}

static F1(jtlshape){I r,*s;
 RZ(w);
 r=AR(w); s=AS(w);
 R 2==r&&(1==s[0]||1==s[1]) ? spellout((C)(1==s[1]?CCOMDOT:CLAMIN)) : !r ? mtv :
     1<r ? lsh(w) : 1<AN(w) ? mtv : spellout(CCOMMA);
}

static F1(jtlchar){A y;B b,p=1,r1;C c,d,*u,*v;I j,k,m,n;
 RZ(w);
 m=AN(alp); n=AN(w); j=n-m; r1=1==AR(w); u=v=CAV(w); d=*v;
 if(0<=j&&r1&&!memcmp(v+j,AV(alp),m)){ 
  if(!j)R cstr("a.");
  RZ(y=lchar(1==j?scc(*v):str(j,v)));
  R lp(y)?over(cstr("a.,~"),y):over(y,cstr(",a."));
 }
 if(r1&&m==n&&(y=icap(ne(w,alp)))&&m>AN(y)){
  if(1==AN(y))RZ(y=head(y));
  R over(over(cstr("a. "),lcpx(lnum(y))),over(cstr("}~"),lchar(from(y,w))));
 }
 j=2; b=7<n||1<n&&1<AR(w);
 DO(n, c=*v++; if(c==CQUOTE)++j; b&=c==d; p&=31<c&&c<127;); 
 if(b){n=1; j=MIN(3,j);}
 if(!p){
  k=(UC)d; RZ(y=indexof(alp,w));
  if(r1&&n<m&&(!k||k==m-n)&&equ(y,apv(n,k,1L)))R over(thorn1(sc(d?-n:n)),cstr("{.a."));
  RZ(y=lnum(y));
  R lp(y)?over(cstr("a.{~"),y):over(y,cstr("{a.")); 
 }
 GA(y,LIT,n+j,1,0); v=CAV(y);
 *v=*(v+n+j-1)=CQUOTE; ++v;
 if(2==j)MC(v,u,n); else DO(n, *v++=c=*u++; if(c==CQUOTE)*v++=c;);
 R over(b?lsh(w):lshape(w),y);
}    /* non-empty character array */

static F1(jtlbox){A p,*v,*vv,*wv,x,y;B b=0;I n,wd;
 RZ(w);
 if(equ(ace,w)&&B01==AT(AAV0(w)))R cstr("a:");
 n=AN(w); wv=AAV(w); wd=(I)w*ARELATIVE(w);
 DO(n, x=WVR(i); if(BOX&AT(x)){b=1; break;}); b=b||1==n;
 GA(y,BOX,n+n-!b,1,0); v=vv=AAV(y);
 if(b){
  RZ(p=cstr("),(<"));
  DO(n, x=WVR(i); *v++=p; RZ(*v++=lnoun(x)););
  RZ(*vv=cstr(1==n?"<":"(<")); if(1<n)RZ(vv[n+n-2]=cstr("),<"));
  R over(lshape(w),raze(y));
 }
 DO(n, x=WVR(i); if(b=1!=AR(x)||!(LIT&AT(x)))break;);
 if(!b){C c[256],d,*t;UC*s;
  DO(256,c[i]=1;); 
  RZ(x=raze(w)); s=UAV(x);
  DO(AN(x), c[*s++]=0;);
  if(c[CQUOTE]&&equ(w,words(x)))R over(cstr(";:"),lchar(x));
  if(c[d=' ']||c[d='|']||c[d='/']||c[d=',']||c[d=';']){
   GA(y,LIT,n+AN(x),1,0); t=CAV(y);
   DO(n, x=WVR(i); *t++=d; MC(t,AV(x),AN(x)); t+=AN(x););
   RZ(y=lchar(y));
   R over(lshape(w),over(cstr(isdigit(*CAV(y))?"<;.(_1) ":"<;._1 "),y));
 }}
 RZ(p=cstr(";"));
 DO(n-1, RZ(*v++=lcpx(lnoun(WVR(i)))); *v++=p;);
 RZ(*v=lnoun(WVR(n-1)));
 R over(lshape(w),raze(y));
}    /* non-empty boxed array */

static F1(jtlnum1){A z;I t;
 RZ(w);
 t=AT(w);
 RZ(z=t&FL+CMPX?df1(w,fit(ds(CTHORN),sc((I)18))):thorn1(w));
 R t&XNUM+RAT&&!memchr(CAV(z),t&XNUM?'x':'r',AN(z))?over(z,scc('x')):z;
}    /* dense non-empty numeric vector */

static F1(jtlnum){A b,d,t,*v,y;B p;I n;
 RZ(t=ravel(w));
 n=AN(w);
 if(7<n||1<n&&1<AR(w)){
  d=minus(from(one,t),b=from(zero,t)); if(jt->jerr)RESETERR;
  p=equ(t,plus(b,tymes(d,IX(n)))); if(jt->jerr)RESETERR;
  if(p){
   if(equ(d,zero))R over(lsh(w),lnum1(b));
   GA(y,BOX,6,1,0); v=AAV(y); v[0]=v[1]=v[2]=v[3]=mtv;
   if(p=!(equ(b,sc(n-1))&&equ(d,num[-1]))){
    if     (!equ(b,zero   )){v[0]=lnum1(b); v[1]=spellout(CPLUS);}
    if     ( equ(d,num[-1])) v[1]=spellout(CMINUS);
    else if(!equ(d,one    )){v[2]=lnum1(d); v[3]=spellout(CSTAR);}
   }
   v[4]=spellout(CIOTA); v[5]=thorn1(p?shape(w):negate(shape(w)));
   RE(y); R raze(y);
 }}
 R over(lshape(w),lnum1(t));
}    /* dense numeric non-empty array */

static F1(jtlsparse){A a,e,q,t,x,y,z;B ba,be,bn;I j,r,*v;P*p;
 RZ(w);
 r=AR(w); p=PAV(w); a=SPA(p,a); e=SPA(p,e); y=SPA(p,i); x=SPA(p,x);
 bn=0; v=AS(w); DO(r, if(!*v++){bn=1; break;});
 ba=0; if(r==AR(a)){v=AV(a); DO(r, if(i!=*v++){ba=1; break;});}
 be=!(AT(w)&SFL&&0==*DAV(e));
 if(be)RZ(z=over(lnoun(e),cstr(SB01&AT(w)?"":SINT&AT(w)?"+-~2":SFL&AT(w)?"+-~2.1":"+-~2j1")));
 if(be||ba){
  RZ(z=be?over(lcpx(lnoun(a)),       over(scc(';'),z)):lnoun(a));
  RZ(z=   over(lcpx(lnoun(shape(w))),over(scc(';'),z))         );
 }else RZ(z=lnoun(shape(w))); 
 RZ(z=over(cstr("1$."),z));
 if(bn||!*AS(y))R z;
 if(AN(a)){
  RZ(x=lcpx(lnoun(x)));
  RZ(y=1==r?lnoun(ravel(y)):over(cstr("(<\"1)"),lnoun(y)));
  RZ(t=over(x,over(cstr(" ("),over(y,cstr(")}"))))); 
 }else RZ(t=over(lcpx(lnoun(head(x))),cstr(" a:}"))); 
 ba=0; v=AV(a); DO(AN(a), if(i!=*v++){ba=1; break;});
 if(!ba)R over(t,z);
 RZ(q=less(IX(r),a));
 RZ(z=over(over(lcpx(lnoun(q)),cstr("|:")),z));
 RZ(z=over(t,z));
 RZ(q=grade1(over(less(IX(r),q),q)));
 j=r; v=AV(q); DO(r, if(i!=*v++){j=i; break;});
 R over(lcpx(lnoun(drop(sc(j),q))),over(cstr("|:"),z));
}    /* sparse array */

static F1(jtlnoun0){A s,x;B r1;
 RZ(w);
 r1=1==AR(w); RZ(s=thorn1(shape(w)));
 switch(AT(w)){
  default:   R over(cstr("i."),s);
  case LIT:  x=cstr(   "''"); R r1?x:over(over(s,scc('$')),x);
  case C2T:  x=cstr("u: ''"); R r1?x:over(over(s,scc('$')),x);
  case BOX:  R over(s,cstr("$a:"    ));
  case B01:  R over(s,cstr("$0"     ));
  case FL:   R over(s,cstr("$0.5"   ));
  case CMPX: R over(s,cstr("$0j5"   ));
  case XNUM: R over(s,cstr("$0x"    ));
  case RAT:  R over(s,cstr("$1r2"   ));
  case SBT:  R over(s,cstr("$s: ' '"));
}}   /* empty dense array */

static F1(jtlnoun){I t;
 RZ(w);
 t=AT(w);
 if(t&SPARSE)R lsparse(w);
 if(!AN(w))R lnoun0(w);
 switch(t){
  case LIT: R lchar(w);
  case C2T: R over(cstr("u: "),lnum(uco2(num[3],w)));
  case BOX: R lbox(w);
  case SBT: R over(cstr("s: "),lbox(sb2(num[5],w)));
  default:  R lnum(w);
}}

static A jtlsymb(J jt,C c,A w){A t;C buf[20],d,*s;I*u;V*v=VAV(w);
 if(VDDOP&v->flag){
  u=AV(v->h); s=buf; 
  *s++=' '; *s++='('; s+=sprintf(s,FMTI,*u); spellit(CIBEAM,s); s+=2; s+=sprintf(s,FMTI,u[1]); *s++=')';
  RZ(t=str(s-buf,buf)); 
 }else RZ(t=spella(w));
 d=cf(t);
 R d==CESC1||d==CESC2?over(chr[' '],t):t;
}

static B laa(A a,A w){C c,d;
 RZ(a&&w);
 c=ctype[cl(a)]; d=ctype[cf(w)];
 R (c==C9||c==CA)&&(d==C9||d==CA);
}

static B lnn(A a,A w){C c; RZ(a&&w); c=cl(a); R ('x'==c||C9==ctype[c])&&C9==ctype[cf(w)];}

static F2(jtlinsert){A*av,f,g,h,t,t0,t1,t2,*u,y;B b,ft,gt,ht,vb;C c,id;I ad,n;V*v;
 RZ(a&&w);
 n=AN(a); av=AAV(a); ad=(I)w*ARELATIVE(a); 
 vb=VERB==AT(w); v=VAV(w); id=v->id;
 b=id==CCOLON&&VXOP&v->flag;
 if(1<=n){f=AVR(0); t=v->f; c=ID(t); ft=c==CHOOK||c==CFORK||c==CADVF||id==CFORK&&NOUN&AT(t)&&lp(f);}
 if(2<=n){g=AVR(1); t=v->g; c=ID(t); gt=vb    ?c==CHOOK||c==CFORK:lp(g);}
 if(3<=n){h=AVR(2); t=v->h; c=ID(t); ht=vb&&!b?c==CHOOK          :lp(h);}
 switch(!b?id:2==n?CHOOK:CFORK){
  case CADVF:
  case CHOOK:
   GA(y,BOX,3,1,0); u=AAV(y);
   u[0]=f=CALL2(jt->lcp,ft||lnn(f,g),f,0);
   u[2]=g=CALL2(jt->lcp,gt||b,       g,0);
   u[1]=str(' '==cf(g)||id==CADVF&&!laa(f,g)&&!(lp(f)&&lp(g))?0L:1L," ");
   RE(0); R raze(y);
  case CFORK:
   GA(y,BOX,5,1,0); u=AAV(y);
   RZ(u[0]=f=CALL2(jt->lcp,ft||lnn(f,g),   f,0));
   RZ(u[2]=g=CALL2(jt->lcp,gt||lnn(g,h)||b,g,0)); RZ(u[1]=str(' '==cf(g)?0L:1L," "));
   RZ(u[4]=h=CALL2(jt->lcp,ht,             h,0)); RZ(u[3]=str(' '==cf(h)?0L:1L," "));
   R raze(y);
  default:
   t0=CALL2(jt->lcp,ft||NOUN&AT(v->f)&&!(VGERL&v->flag)&&lp(f),f,0);
   t1=lsymb(id,w);
   y=over(t0,laa(t0,t1)?over(chr[' '],t1):t1);
   if(1==n)R y;
   t2=lcpx(g);
   R over(y,laa(y,t2)?over(chr[' '],t2):t2);
}}

static F1(jtlcolon){A*v,x,y;C*s,*s0;I m,n;
 RZ(y=unparsem(one,w));
 n=AN(y); v=AAV(y); RZ(x=lrr(VAV(w)->f));
 if(2>n||2==n&&1==AN(v[0])&&':'==*CAV(v[0])){
  if(!n)R over(x,str(5L," : \'\'"));
  y=lrr(v[2==n]);
  if(2==n)y=over(str(5L,"\':\'; "),y);
  R over(over(x,str(3L," : ")),lcpx(y));
 }
 m=0; DO(n, m+=AN(v[i]););
 GA(y,LIT,2+n+m,1,0);
 s=s0=CAV(y);
 DO(n, *s++=CLF; y=v[i]; m=AN(y); MC(s,CAV(y),m); s+=m;);
 *s++=CLF; *s++=')'; 
 RZ(y=str(s-s0,s0));
 jt->ltext=jt->ltext?over(jt->ltext,y):y;
 R over(x,str(4L," : 0"));
}

static F1(jtlrr){A fs,gs,hs,t,*tv;C id;I fl,m;V*v;
 RZ(w);
 if(AT(w)&NOUN)R lnoun(w);
 if(AT(w)&NAME)R sfn(0,w);
 v=VAV(w); id=v->id; fs=v->f; gs=v->g; hs=v->h; fl=v->flag;
 if(fl&VXOPCALL)R lrr(hs);
 m=!!fs+!!gs+(id==CFORK)+(hs&&id==CCOLON&&VXOP&fl);
 if(!m)R lsymb(id,w);
 if(evoke(w))R sfn(0,fs);
 if(!(VXOP&fl)&&hs&&BOX&AT(hs)&&id==CCOLON)R lcolon(w);
 GA(t,BOX,m,1,0); tv=AAV(t);
 if(2<m)RZ(tv[2]=lrr(hs));
 if(1<m)RZ(tv[1]=fl&VGERR?CALL1(jt->ltie,fxeach(gs),0L):lrr(gs));
 if(0<m)RZ(tv[0]=fl&VGERL?CALL1(jt->ltie,fxeach(fs),0L):lrr(fs));
 R linsert(t,w);
}

F1(jtlrep){PROLOG;A z;
 jt->ltext=0; jt->lcp=(AF)jtlcpa; jt->ltie=jtltiea;
 RE(z=lrr(w));
 if(jt->ltext)z=over(z,jt->ltext);
 jt->ltext=0;
 EPILOG(z);
}

F1(jtprep){PROLOG;A z;
 jt->ltext=0; jt->lcp=(AF)jtlcpb; jt->ltie=jtltieb;
 RE(z=lrr(w));
 if(jt->ltext)z=over(z,jt->ltext);
 jt->ltext=0;
 EPILOG(z);
}

