/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Xenos: Scripts                                                          */

#ifdef _WIN32
#include <windows.h>
#include <winbase.h>
#endif

#include "j.h"
#include "x.h"


B jtxsinit(J jt){A x;
 GA(x,BOX,10,1,0); memset(AV(x),C0,AN(x)*SZI); ra(x); jt->slist=x;
 jt->slisti=-1;
 R 1;
}

F1(jtsnl){ASSERTMTV(w); R vec(BOX,jt->slistn,AAV(jt->slist));}
     /* 4!:3  list of script names */

#if (SYS & SYS_MACINTOSH)
void setftype(C*v,OSType type,OSType crea){C p[256];FInfo f;
 __c2p(v,p);
 GetFInfo(p,0,&f);
 f.fdType=type; f.fdCreator=crea;
 SetFInfo(p,0,&f);
}
#endif

/* line/linf arguments:                         */
/* a:   left argument for unlock                */
/* w:   input file or lines; 1 means keyboard   */
/* si:  script index                            */
/* ce:  0 stop on error                         */ 
/*      1 continue on error                     */
/*      2 stop on error or nonunit result       */
/*      3 ditto, but return 0 or 1 result and   */
/*        do not display error                  */
/* tso: echo to stdout                          */

static A jtline(J jt,A w,I si,C ce,B tso){A x=mtv,z;B xt=jt->tostdout;DC d,xd=jt->dcs;I old;
 if(equ(w,one))R mtm;
 RZ(w=vs(w));
 FDEPINC(1);
 RZ(d=deba(DCSCRIPT,0L,w,(A)si));
 jt->dcs=d; jt->tostdout=tso&&!jt->seclev;
 old=jt->tbase+jt->ttop;
 switch(ce){
  case 0: while(x&&!jt->jerr){jt->etxn=0;                           immex(x=jgets("   ")); tpop(old);} break;
  case 1: while(x           ){if(!jt->seclev)showerr(); jt->jerr=0; immex(x=jgets("   ")); tpop(old);} break;
  case 2:
  case 3: while(x&&!jt->jerr){jt->etxn=0;                           immea(x=jgets("   ")); tpop(old);}
          jt->asgn=0;
 }
 jt->dcs=xd; jt->tostdout=xt;
 debz();
 FDEPDEC(1);
 if(3==ce){z=jt->jerr?zero:one; RESETERR; R z;}else RNE(mtm);
}

static A jtlinf(J jt,A a,A w,C ce,B tso){A x,y,z;B lk=0;C*s;I i=-1,n,oldi=jt->slisti,oldk=jt->glock;
 RZ(a&&w);
 ASSERT(AT(w)&BOX,EVDOMAIN);
 if(jt->seclev){
  y=AAV0(w); n=AN(y); s=CAV(y); 
  ASSERT(LIT&AT(y),EVDOMAIN); 
  ASSERT(3<n&&!memcmp(s+n-3,".js",3L)||4<n&&!memcmp(s+n-4,".ijs",4L),EVSECURE);
 }
 RZ(x=jfread(w));
 if(a!=mark||AN(x)&&CFF==*CAV(x)){
  RZ(x=unlock2(a,x));
  ASSERT(CFF!=*CAV(x),EVDOMAIN);
  lk=1;
 }
 RZ(y=fullname(AAV0(w)));
 RE(i=i0(indexof(vec(BOX,jt->slistn,AAV(jt->slist)),box(y))));
 if(jt->slistn==i){
  if(jt->slistn==AN(jt->slist))RZ(jt->slist=ext(1,jt->slist)); 
  RZ(*(jt->slistn+AAV(jt->slist))=ra(y)); 
  ++jt->slistn;
 }
 jt->slisti=i;    jt->glock=1==jt->glock?1:lk?2:0;
 z=line(x,jt->glock?-1L:i,ce,(B)(jt->glock?0:tso)); 
 jt->slisti=oldi; jt->glock=1==jt->glock?1:oldk;
#if SYS & SYS_PCWIN
 if(lk)memset(AV(x),C0,AN(x));  /* security paranoia */
#endif
 R z;
}

F1(jtscm00 ){I r; RZ(w);    r=1&&AT(w)&LIT+C2T; F1RANK(     r,jtscm00, 0); R r?line(w,-1L,0,0):linf(mark,w,0,0);}
F1(jtscm01 ){I r; RZ(w);    r=1&&AT(w)&LIT+C2T; F1RANK(     r,jtscm01, 0); R r?line(w,-1L,0,1):linf(mark,w,0,1);}
F1(jtscm10 ){I r; RZ(w);    r=1&&AT(w)&LIT+C2T; F1RANK(     r,jtscm10, 0); R r?line(w,-1L,1,0):linf(mark,w,1,0);}
F1(jtscm11 ){I r; RZ(w);    r=1&&AT(w)&LIT+C2T; F1RANK(     r,jtscm11, 0); R r?line(w,-1L,1,1):linf(mark,w,1,1);}
F1(jtsct1  ){I r; RZ(w);    r=1&&AT(w)&LIT+C2T; F1RANK(     r,jtsct1,  0); R r?line(w,-1L,2,1):linf(mark,w,2,1);}
F1(jtscz1  ){I r; RZ(w);    r=1&&AT(w)&LIT+C2T; F1RANK(     r,jtscz1,  0); R r?line(w,-1L,3,0):linf(mark,w,3,0);}

F2(jtscm002){I r; RZ(a&&w); r=1&&AT(w)&LIT+C2T; F2RANK(RMAX,r,jtscm002,0); R r?line(w,-1L,0,0):linf(a,   w,0,0);}
F2(jtscm012){I r; RZ(a&&w); r=1&&AT(w)&LIT+C2T; F2RANK(RMAX,r,jtscm012,0); R r?line(w,-1L,0,1):linf(a,   w,0,1);}
F2(jtscm102){I r; RZ(a&&w); r=1&&AT(w)&LIT+C2T; F2RANK(RMAX,r,jtscm102,0); R r?line(w,-1L,1,0):linf(a,   w,1,0);}
F2(jtscm112){I r; RZ(a&&w); r=1&&AT(w)&LIT+C2T; F2RANK(RMAX,r,jtscm112,0); R r?line(w,-1L,1,1):linf(a,   w,1,1);}
F2(jtsct2  ){I r; RZ(a&&w); r=1&&AT(w)&LIT+C2T; F2RANK(RMAX,r,jtsct2,  0); R r?line(w,-1L,2,1):linf(a,   w,2,1);}
F2(jtscz2  ){I r; RZ(a&&w); r=1&&AT(w)&LIT+C2T; F2RANK(RMAX,r,jtscz2,  0); R r?line(w,-1L,3,0):linf(a,   w,3,0);}
