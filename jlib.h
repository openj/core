/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */

J _stdcall JInit();                         /* init instance */
void _stdcall JSM(J jt, void*callbacks[]);  /* set callbacks */ 
int _stdcall JDo(J jt,C*);                  /* run sentence */
C* _stdcall JGetLocale(J jt);               /* get locale */			
int _stdcall JFree(J jt);                   /* free instance */
A _stdcall JGetA(J jt,I n,C* name);         /* get 3!:1 from name */
I _stdcall JSetA(J jt,I n,C* name,I x,C* d);/* name=:3!:2 data */

typedef void* (_stdcall *JInitType)     ();
typedef int   (_stdcall *JDoType)       (void*, C*);
typedef C*    (_stdcall *JGetLocaleType)(void*);    
typedef void  (_stdcall *JSMType)       (void*, void*);
typedef void  (_stdcall *JFreeType)     (void*);
typedef A     (_stdcall *JgaType)       (J jt, I t, I n, I r, I*s);

/*  void* callbacks[] = {Joutput, Jwd, Jinput, unused, smoptions}; */

typedef void  (_stdcall * outputtype)(J,int,C*);
typedef int   (_stdcall * dowdtype)  (J,int, A, A*);
typedef C* (_stdcall * inputtype) (J,C*);

void _stdcall Joutput(J jt, int type, C* s);
int _stdcall Jwd(J jt, int x, A parg, A* pres);
C* _stdcall Jinput(J jt, C*);

// output type
#define MTYOFM		1	/* formatted result array output */
#define MTYOER		2	/* error output */
#define MTYOLOG		3	/* output log */
#define MTYOSYS		4	/* system assertion failure */
#define MTYOEXIT	5	/* exit */
#define MTYOFILE	6	/* output 1!:2[2 */

// smoptions
#define SMWIN    0  /* j.exe    Jwdw (Windows) front end */
#define SMJAVA   2  /* j.jar    Jwdp (Java) front end */
#define SMCON    3  /* jconsole */

