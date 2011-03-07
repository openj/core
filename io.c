/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* Input/Output                                                            */

#ifdef _WIN32
#include <windows.h>
#include <winbase.h>
#else
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#define _stdcall
#endif

#include "j.h"
#include "d.h"

void jtwri(J jt,I type,C*p,I m,C*s){C buf[1024],*t=jt->outseq,*v=buf;I c,d,e,n;
 if(jt->tostdout){
  c=strlen(p);            /* prompt      */
  e=strlen(t);            /* end-of-line */
  n=sizeof(buf)-(c+e+1);  /* main text   */
  d=m>n?n-3:m;
  memcpy(v,p,c); v+=c;
  memcpy(v,s,d); v+=d; if(m>n){memcpy(v,"...",3L); v+=3;}
  memcpy(v,t,e); v+=e; 
  *v=0;
  jsto(jt,type,buf);
}}

static void jtwrf(J jt,I n,C*v,F f){C*u,*x;I j=0,m;
 while(n>j){
  u=j+v; 
  m=(x=memchr(u,CLF,n-j))?1+x-u:n-j; 
  fwrite(u,sizeof(C),m,f);
  j+=m;
}}

A jtinpl(J jt,B b,I n,C*s){C c;I k=0;
 if(n&&(c=*(s+n-1),CLF==c||CCR==c))--n;
 ASSERT(!*jt->adbreak,EVINPRUPT);
 if(!b){ /* 1==b means literal input */
  if(n&&COFF==*(s+n-1))joff(zero);
  c=jt->bx[9]; if(c<0)DO(n, if(' '!=s[i]&&c!=s[i]){k=i; break;});
 }
 R str(n-k,s+k);
}

static I advl(I j,I n,C*s){B b;C c,*v;
 v=j+s; 
 DO(n-j, c=*v++; b=c==CCR; if(b||c==CLF)R j+1+i+(b&&CLF==*v););
 R n;
}    /* advance one line on CR, CRLF, or LF */

void breakclose(J jt);

static C* nfeinput(J jt,C* s){A y;
 jt->breakignore=1;
 y=exec1(cstr(s));
 jt->breakignore=0;
 if(!y){breakclose(jt);exit(2);} /* J input verb failed */
 jtwri(jt,MTYOLOG,"",strlen(CAV(y)),CAV(y));
 return CAV(y); /* don't combine with previous line! CAV runs (x) 2 times! */
}

A jtjgets(J jt,C*p){A y;B b;C*v;I j,k,m,n;UC*s;
 *jt->adbreak=0;
 if(b=1==*p)p=""; /* 1 means literal input */
 if(jt->dcs){
  ++jt->dcs->dcn; j=jt->dcs->dci; 
  y=jt->dcs->dcy; n=AN(y); s=UAV(y);
  RZ(j<n);
  jt->dcs->dcj=k=j;
  jt->dcs->dci=j=advl(j,n,s);
  m=j-k; if(m&&32>s[k+m-1])--m; if(m&&32>s[k+m-1])--m;
  jtwri(jt,MTYOLOG,p,m,k+s);
  R inpl(b,m,k+s);
 }
 /* J calls for input in 3 cases:
    debug suspension for normal input
    n : 0 input lines up to terminating )
    1!:1[1 read from keyboard */
 showerr();
 if(jt->nfe)
  v=nfeinput(jt,*p?"input_jfe_'      '":"input_jfe_''");
 else{
  ASSERT(jt->sminput,EVBREAK); 
  v=((inputtype)(jt->sminput))(jt,p);
 }
 R inpl(b,(I)strlen(v),v);
}

extern C breakdata;

#if SYS&SYS_UNIX
void breakclose(J jt)
{
 if(jt->adbreak==&breakdata) return;
 munmap(jt->adbreak,1);
 jt->adbreak=&breakdata;
 close(jt->breakfh);
 jt->breakfh=0;
 unlink(jt->breakfn);
 *jt->breakfn=0;
}
#else
void breakclose(J jt)
{
 if(jt->adbreak==&breakdata) return;
 UnmapViewOfFile(jt->adbreak);
 jt->adbreak=&breakdata;
 CloseHandle(jt->breakmh);
 jt->breakmh=0;
 CloseHandle(jt->breakfh);
 jt->breakfh=0;
#if SY_WINCE
 DeleteFile(tounibuf(jt->breakfn));
#else
 DeleteFile(jt->breakfn);
#endif
 *jt->breakfn=0;
}
#endif

F1(jtjoff){I x;
 RZ(w);
 x=i0(w);
 breakclose(jt);
 if(jt->sesm)jsto(jt, MTYOEXIT,(C*)x);
 exit((int)x);
 R 0;
}

#if (SYS & SYS_SESM)

I jdo(J jt, C* lp){I e,old;A x;
 jt->jerr=0; jt->etxn=0; /* clear old errors */
 old=jt->tbase+jt->ttop;
 *jt->adbreak=0;
 x=inpl(0,(I)strlen(lp),lp);
 while(jt->iepdo&&jt->iep){jt->iepdo=0; immex(jt->iep); jt->jerr=0; tpop(old);}
 if(!jt->jerr)immex(x);
 e=jt->jerr;
 jt->jerr=0;
 if(e&&DBERRCAP==jt->db&&jt->dbtrap){
  jt->db=0;
  immex(jt->dbtrap);
  jt->jerr=0;
 }
 while(jt->iepdo&&jt->iep){jt->iepdo=0; immex(jt->iep); jt->jerr=0; tpop(old);}
 showerr();
 spfree();
 tpop(old);
 R e;
}

#define SZINT             ((I)sizeof(int))

DF1(jtwd){A z=0;C*p=0;D*pd;I e,*pi,t;V*sv;
 F1RANK(1,jtwd,self);
 RZ(w);
 ASSERT(2>AR(w),EVRANK);
 sv=VAV(self);
 t=i0(sv->g);
 if(t>=2000 && t<3000 && AN(w) && LIT!=AT(w) && C2T!=AT(w) && INT!=AT(w))
 {
	 switch(AT(w))
	 {
	 case B01:
		RZ(w=vi(w));break;
	 case FL:
		pd=DAV(w);
		GA(w,INT,AN(w),AR(w),0);
		pi=AV(w);
		DO(AN(w),*pi++=(I)(jfloor(0.5+*pd++));); 
		break;
	 default:
		 ASSERT(0,EVDOMAIN);
	 }
 }
 // t is 11!:t and w is wd argument
 e=jt->smdowd ? ((dowdtype)(jt->smdowd))(jt, (int)t, w, &z) : EVDOMAIN;
 if(!e) R mtm;   // e==0 is MTM
 if(e==-1) R z;  // e---1 is zp
 ASSERT(e<=0,e); // e>=0 is EVDOMAIN etc
 RZ(z=df1(z,cut(ds(CBOX),num[-2]))); // e==-2 is lit pairs
 R reshape(v2(AN(z)/2,2L),z);
}

C* getlocale(J jt){A y=locname(mtv); y=*AAV(y); R CAV(y);}

static char breaknone=0;

B jtsesminit(J jt){jt->adbreak=&breakdata; R 1;}
#endif

int _stdcall JDo(J jt, char* lp){int r;
 r=(int)jdo(jt,lp);
 while(jt->nfe)
  r=(int)jdo(jt,nfeinput(jt,"input_jfe_'   '"));
 R r;
} 

/* socket protocol CMDGET name */
A _stdcall JGetA(J jt, I n, C* name){A x;
 jt->jerr=0;
 RZ(x=symbrdlock(nfs(n,name)));
 ASSERT(!(FUNC&AT(x)),EVDOMAIN);
 R binrep1(x);
}

/* socket protocol CMDSET */
I _stdcall JSetA(J jt,I n,C* name,I dlen,C* d){I old;
 jt->jerr=0;
 if(!vnm(n,name)) R EVILNAME;
 old=jt->tbase+jt->ttop;
 symbis(nfs(n,name),jtunbin(jt,str(dlen,d)),jt->global);
 tpop(old);
 R jt->jerr;
}

/* set jclient callbacks */
void _stdcall JSM(J jt, void* callbacks[])
{
	jt->smoutput = (outputtype)callbacks[0];
	jt->smdowd = (dowdtype)callbacks[1];
	jt->sminput = (inputtype)callbacks[2];
	jt->sm = (I)callbacks[4];
}

C* _stdcall JGetLocale(J jt){return getlocale(jt);}

A _stdcall Jga(J jt, I t, I n, I r, I*s){
 return ga(t, n, r, s);
}

void oleoutput(J jt, I n, char* s);	/* SY_WIN32 only */

/* jsto - display output in output window */
void jsto(J jt,I type,C*s){C e;I ex;
 if(jt->nfe)
 {
  C q[]="0 output_jfe_ (15!:18)0";
  q[0]+=(C)type;
  jt->mtyostr=s;
  e=jt->jerr; ex=jt->etxn;
  jt->jerr=0; jt->etxn=0;
  jt->breakignore=1;exec1(cstr(q));jt->breakignore=0;
  jt->jerr=e; jt->etxn=ex; 
 }else{
  if(jt->smoutput) ((outputtype)(jt->smoutput))(jt,(int)type,s);
#if SY_WIN32 && !SY_WINCE
  if(type & MTYOFM) oleoutput(jt,strlen(s),s);	/* save output for ole */
#endif
}}

#if SYS&SYS_UNIX

J JInit(void){
  J jt;
  /* jtglobinit must be done once when dll is first loaded
     Windows does it in dll load routine  - thread safe
     Unix does it here once, but this is not thread safe */
  
  static J g_jt=0;
  if(!g_jt)
  {
    g_jt=malloc(sizeof(JST));
    if(!g_jt) R 0;
    memset(g_jt,0,sizeof(JST));
    if(!jtglobinit(g_jt)){free(g_jt);g_jt=0; R 0;}
  }
  RZ(jt=malloc(sizeof(JST)));
  memset(jt,0,sizeof(JST));
  if(!jtjinit2(jt,0,0)){free(jt); R 0;};
  R jt;
}

int JFree(J jt){return 0;}
#endif

F1(jtbreakfnq){
 ASSERTMTV(w);
 R cstr(jt->breakfn);
}

F1(jtbreakfns){A z;I *fh,*mh; void* ad;
 ASSERT(1>=AR(w),EVRANK);
 ASSERT(!AN(w)||AT(w)&LIT,EVDOMAIN);
 ASSERT(AN(w)<NPATH,EVDOMAIN);
 if(!strcmp(jt->breakfn,CAV(w))) R mtm;
 breakclose(jt);
#if SYS&SYS_UNIX
 fh=(I*)(I)open(CAV(w),O_RDWR);
 ASSERT(-1!=(I)fh,EVDOMAIN);
 ad=mmap(0,1,PROT_READ|PROT_WRITE,MAP_SHARED,(I)fh,0);
 if(0==ad){close(fh); ASSERT(0,EVDOMAIN);}
#else
 RZ(z=toutf16x(w));
 fh=CreateFileW(USAV(z),GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,0,OPEN_EXISTING,0,0);
 ASSERT(INVALID_HANDLE_VALUE!=fh,EVDOMAIN);
 mh=CreateFileMapping(fh,0,PAGE_READWRITE,0,1,0);
 if(0==mh){CloseHandle(fh); ASSERT(0,EVDOMAIN);}
 ad=MapViewOfFile(mh,FILE_MAP_WRITE,0,0,0);
 if(0==ad){CloseHandle(mh); CloseHandle(fh); ASSERT(0,EVDOMAIN);}
#endif
 strcpy(jt->breakfn,CAV(w));
 jt->breakfh=fh;
 jt->breakmh=mh;
 jt->adbreak=ad;
 R mtm;
}

int valid(C* psrc, C* psnk)
{
	while(*psrc == ' ') ++psrc;
	if(!isalpha(*psrc)) return EVILNAME;
	while(isalnum(*psrc) || *psrc=='_') *psnk++ = *psrc++;
	while(*psrc == ' ') ++psrc;
	if(*psrc) return EVILNAME;
	*psnk = 0;
	return 0;		
}

int _stdcall JGetM(J jt, C* name, I* jtype, I* jrank, I* jshape, I* jdata)
{
	A a; char gn[256];
	if(strlen(name) >= sizeof(gn)) return EVILNAME;
	if(valid(name, gn)) return EVILNAME;
	RZ(a=symbrdlock(nfs(strlen(gn),gn)));
    if(FUNC&AT(a))R EVDOMAIN;
	*jtype = AT(a);
	*jrank = AR(a);
	*jshape = (I)AS(a);
	*jdata = (I)AV(a);
	return 0;
}

static int setterm(J jt, C* name, I* jtype, I* jrank, I* jshape, I* jdata)
{
	A a;
	I k=1,i,n;
	char gn[256];

	switch(*jtype)
	{
	case LIT:
	case B01:
		n = sizeof(char);
		break;

	case INT:
		n = sizeof(I);
		break;
		
	case FL:
		n = sizeof(double);
		break;
		
	case CMPX:
		n = 2 * sizeof(double);
		break;
		
	default:
		return EVDOMAIN;	
	}

	// validate name
	if(strlen(name) >= sizeof(gn)) return EVILNAME;
	if(valid(name, gn)) return EVILNAME; 
	for(i=0; i<*jrank; ++i)	k *= ((I*)(*jshape))[i];
	a = ga(*jtype, k, *jrank, (I*)*jshape);
	if(!a) return EVWSFULL;
	memcpy(AV(a), (void*)*jdata, n*k);
	jset(gn, a);
	return jt->jerr;
}

int _stdcall JSetM(J jt, C* name, I* jtype, I* jrank, I* jshape, I* jdata)
{
	int er;

	PROLOG;
	er = setterm(jt, name, jtype, jrank, jshape, jdata);
	tpop(_ttop);
	return er;
}

#define EDCBUSY	-1
#define EDCEXE	-2

C* esub(J jt, I ec)
{
	if(!ec) return "";
	if(ec == EDCBUSY) return "busy with previous input";
	if(ec == EDCEXE) return "not supported in EXE server";
	if(ec > NEVM || ec < 0) return "unknown error";
	return (C*)AV(*(ec+AAV(jt->evm)));
}

int _stdcall JErrorTextM(J jt, I ec, I* p)
{
	*p = (I)esub(jt, ec);
	return 0;
}
