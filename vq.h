/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Rational Numbers                                                        */


#define QF1(f)          Q f(J jt,   Q  w)
#define QF2(f)          Q f(J jt,Q a,Q w)
#define QASSERT(b,e)    {if(!(b)){jsignal(e); R zeroQ;}}
#define QEPILOG(q)      {Q z9; z9=(qstd(q)); gc3(z9.n,z9.d,0L,_ttop); R z9;}
#define QRE(exp)        {if((exp),jt->jerr)R zeroQ;}
#define QRZ(exp)        {if(!(exp))        R zeroQ;}
#define QX1(x)          (1==AN(x)&&1==XDIG(x))

#define QEQ(x,y)        (equ((x).n,(y).n)&&equ((x).d,(y).d))
#define QCOMP(x,y)      (xcompare(xtymes((x).n,(y).d),xtymes((y).n,(x).d)))
#define QLT(x,y)        (0> QCOMP(x,y))
#define QLE(x,y)        (0>=QCOMP(x,y))
#define QGT(x,y)        (0< QCOMP(x,y))
#define QGE(x,y)        (0<=QCOMP(x,y))
#define QMAX(x,y)       (QGE(x,y)?x:y)
#define QMIN(x,y)       (QLE(x,y)?x:y)

extern QF1(jtqstd);

extern QF2(jtqdiv);
extern QF2(jtqminus);
extern QF2(jtqplus);
extern QF2(jtqtymes);

extern Q zeroQ;
