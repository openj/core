/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Adverbs: Macros and Defined-Constants (for Adverbs and Conjunctions)    */


#define GAPPEND         (I)0
#define GINSERT         (I)3
#define GTRAIN          (I)6

#define COMPOSE(c)  ((c)==CAT||(c)==CATCO||(c)==CAMP||(c)==CAMPCO) 

#define CONJCASE(a,w)   (2*!(VERB&AT(a))+!(VERB&AT(w)))
#define NN              3               /* NOUN NOUN                       */
#define NV              2               /* NOUN VERB                       */
#define VN              1               /* VERB NOUN                       */
#define VV              0               /* VERB VERB                       */

#define DECLF           V*sv=VAV(self);A fs=sv->f;  \
                        AF f1=fs?VAV(fs)->f1:0,f2=fs?VAV(fs)->f2:0

#define DECLG           V*sv=VAV(self);A gs=sv->g;  \
                        AF g1=gs?VAV(gs)->f1:0,g2=gs?VAV(gs)->f2:0

#define DECLFG          DECLF;         A gs=sv->g;  \
                        AF g1=gs?VAV(gs)->f1:0,g2=gs?VAV(gs)->f2:0

#define DECLFGH         DECLFG;        A hs=sv->h;  \
                        AF h1=hs?VAV(hs)->f1:0,h2=hs?VAV(hs)->f2:0

#define PREF1(f)        {I m=mr(self);            F1RANK(  m,f,self);}
#define PREF2(f)        {I l=lr(self),r=rr(self); F2RANK(l,r,f,self);}

#define AS1(f,exp)      DF1(f){PROLOG;DECLF ;A z; PREF1(f); z=(exp); EPILOG(z);}
#define AS2(f,exp)      DF2(f){PROLOG;DECLF ;A z; PREF2(f); z=(exp); EPILOG(z);}
#define CS1(f,exp)      DF1(f){PROLOG;DECLFG;A z; PREF1(f); z=(exp); EPILOG(z);}
#define CS2(f,exp)      DF2(f){PROLOG;DECLFG;A z; PREF2(f); z=(exp); EPILOG(z);}

#define ADERIV(id,f1,f2,m,l,r)  fdef(id,VERB,(AF)(f1),(AF)(f2),w,0L,0L,0L,(I)(m),(I)(l),(I)(r))
#define CDERIV(id,f1,f2,m,l,r)  fdef(id,VERB,(AF)(f1),(AF)(f2),a,w ,0L,0L,(I)(m),(I)(l),(I)(r))

#define ASSERTVV(a,w)   RZ(a&&w); ASSERT(VERB&AT(a)&&VERB&AT(w),EVDOMAIN)
#define ASSERTVN(a,w)   RZ(a&&w); ASSERT(VERB&AT(a)&&NOUN&AT(w),EVDOMAIN)
#define ASSERTNN(a,w)   RZ(a&&w); ASSERT(NOUN&AT(a)&&NOUN&AT(w),EVDOMAIN)

#define SCALARFN(id,w)  (id==ID(w)&&!lr(w)&&!rr(w))

#define FIT0(c,v)       (CFIT==v->id&&c==ID(v->f)&&equ(zero,v->g))
