/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
// utilities for JFE to load JE, initiallize, and run profile sentence
// JFEs are jconsole, jwdw, and jwdp
#define PLEN 1000 // path length
#include <unistd.h>
#ifdef _WIN32
 #include <windows.h>

#ifdef UNDER_CE
 #define GETPROCADDRESS(h,p) GetProcAddress(h,_T(p))
#else
 #define GETPROCADDRESS(h,p) GetProcAddress(h,p)
#endif
 #define JDLLNAME "j.dll"
 #define filesep '\\'
 #define filesepx "\\"
// setfocus e required for pocketpc and doesn't hurt others
#define ijx "11!:0'pc ijx closeok;xywh 0 0 300 200;cc e editijx rightmove bottommove ws_vscroll ws_hscroll;setfont e \"Courier New\" 12;setfocus e;pas 0 0;pgroup jijx;pshow;'[18!:4<'base'"

#else
 #include <dlfcn.h>
 #define GETPROCADDRESS(h,p)	dlsym(h,p)
 #define _stdcall
 #define filesep '/'
 #define filesepx "/"
 #define ijx "11!:0'pc ijx closeok;xywh 0 0 300 200;cc e editijx rightmove bottommove ws_vscroll ws_hscroll;setfont e monospaced 12;pas 0 0;pgroup jijx;pshow;'[18!:4<'base'"
 #ifdef __MACH__ 
  #define JDLLNAME "libj.dylib"
 #else
  #define JDLLNAME "libj.so"
 #endif
#endif
#include "j.h"

static void* hjdll;
static J jt;
static JDoType jdo;
static JFreeType jfree;
static JgaType jga;
static JGetLocaleType jgetlocale;
static char path[PLEN];    //directory holding the exe
static char pathdll[PLEN]; //filename of the j library (DLL/so)

int jedo(char* sentence)
{
	return jdo(jt,sentence);
}

void jefree(){jfree(jt);}
char* jegetlocale(){return jgetlocale(jt);}
A jega(I t, I n, I r, I*s){return jga(jt,t,n,r,s);}
void* jehjdll(){return hjdll;}

static void* dlload(char*path)
{
#ifdef _WIN32
 WCHAR wpath[PLEN];
 MultiByteToWideChar(CP_UTF8,0,path,1+(int)strlen(path),wpath,PLEN);
 return LoadLibraryW(wpath);
#else
 return dlopen(path,RTLD_LAZY);
#endif
}
// load JE, Jinit, getprocaddresses, JSM
J jeload(void* callbacks)
{
 char*search[]={pathdll,JDLLNAME,0};int path=0;
 for(hjdll=0;!hjdll&&search[path];path++)
  if(hjdll=dlload(search[path]))
   strcpy(pathdll,search[path]);
 if(!hjdll) return 0;
 jt=((JInitType)GETPROCADDRESS(hjdll,"JInit"))();
 if(!jt) return 0;
 ((JSMType)GETPROCADDRESS(hjdll,"JSM"))(jt,callbacks);
 jdo=(JDoType)GETPROCADDRESS(hjdll,"JDo");
 jfree=(JFreeType)GETPROCADDRESS(hjdll,"JFree");
 jga=(JgaType)GETPROCADDRESS(hjdll,"Jga");
 jgetlocale=(JGetLocaleType)GETPROCADDRESS(hjdll,"JGetLocale");
 return jt;
}

static int exepath(char* path,int z)//path buffer, z is buflen, returns strlen(path)
{
#ifdef _WIN32
 WCHAR wpath[PLEN];
 GetModuleFileNameW(0,wpath,_MAX_PATH);
 *(wcsrchr(wpath, '\\')) = 0;
 WideCharToMultiByte(CP_UTF8,0,wpath,1+(int)wcslen(wpath),path,z,0,0);
#else

#define sz 4000
 char arg2[sz],arg3[sz];
 char* src,*snk;int n,len=sz;
 // fprintf(stderr,"arg0 %s\n",arg);
 // try host dependent way to get path to executable
 // use arg if they fail (arg command in PATH won't work)
#ifdef __MACH__ 
 n=_NSGetExecutablePath(arg2,&len);
 if(0!=n) strcat(arg2,arg);
#else
 n=readlink("/proc/self/exe",arg2,sizeof(arg2));
 if(-1==n) strcpy(arg2,arg); else arg2[n]=0;
#endif
 // fprintf(stderr,"arg2 %s\n",arg2);
 // arg2 is path (abs or relative) to executable or soft link
 n=readlink(arg2,arg3,sz);
 if(-1==n) strcpy(arg3,arg2); else arg3[n]=0;
 // fprintf(stderr,"arg3 %s\n",arg3);
 if('/'==*arg3)
  strcpy(path,arg3);
 else
 {
  if(!getcwd(path,z))
   perror("getcwd");
  strcat(path,"/");
  strcat(path,arg3);
 }
 *(1+strrchr(path,'/'))=0;
 // remove ./ and backoff ../
 snk=src=path;
 while(*src)
 {
	 if('/'==*src&&'.'==*(1+src)&&'.'==*(2+src)&&'/'==*(3+src))
	 {
		 *snk=0;
		 snk=strrchr(path,'/');
		 snk=0==snk?path:snk;
		 src+=3;
	 }
	 else if('/'==*src&&'.'==*(1+src)&&'/'==*(2+src))
      src+=2;
	 else
	  *snk++=*src++;
 }
 *snk=0;
 snk=path+strlen(path)-1;
 if('/'==*snk) *snk=0;
#endif
 return strlen(path);
}

// set path and pathdll (wpath also set for win)
// WIN arg is 0, Unix arg is argv[0]
#define PSEP filesepx
void jepath(char* arg)
{
 char b[PLEN];
 exepath(path,PLEN);
 snprintf(b,PLEN,"%s/.libs/"JDLLNAME,path);
 if(!access(b,F_OK))
   strcpy(pathdll,b);
 else
   snprintf(pathdll,PLEN,"%s"PSEP JDLLNAME,path);
 // fprintf(stderr,"arg4 %s\n",path);
}
// called by jwdp (java jnative.c) to set path
void jesetpath(char* arg)
{
	strcpy(pathdll,arg); // jwdp gives path to j.dll
	strcpy(path,arg);
	*(strrchr(path,filesep)) = 0;
}

#define PIJS "profile.ijs"
static char* find_profile()
{
  if(!access(path,F_OK))
  { 
#define NSEARCH 4
    char* p,s[NSEARCH][PLEN];int i,n=0;
#define NSADD(fmt,a) snprintf(s[n++],PLEN,fmt,a)
    NSADD("%s",getenv("HOME"));
    NSADD("%s",path);
    NSADD("%s"PSEP"j"PSEP"bin",path);
    NSADD("%s"PSEP".."PSEP"share",path);
    p=malloc(PLEN);
    for(i=0;i<n;i++)
    { 
      snprintf(p,PLEN,"%s"PSEP"%s",s[i],PIJS);
      if(!access(p,F_OK)) return p;
    }
  }
  return 0;
}
// build and run first sentence to set BINPATH, ARGV, and run profile
// arg is command line ready to set in ARGV_z_
// type is 0 normal, 1 -jprofile xxx, 2 ijx basic, 3 nothing
// profile[ARGV_z_=:...[BINPATH=:....
// profile is from BINPATH, ARGV, ijx basic, or nothing
static int stmt(char*b,int z,char*e){snprintf(b,z,"(3 : '0!:0 y')%s",e);}
int jefirst(int type,char* arg)
{
	int r,z; char* p,*q;
	char* input=malloc(z=2000+strlen(arg));
	char buf[PLEN*2];
	*input=0;
	if(0==type)
	{
          char* p=find_profile();
          if(!p) return -1;
          sprintf(buf,"<'%s'",p);
          stmt(input,z,buf);
          free(p);
	}
	else if(1==type)
		stmt(input,z,"2{ARGV");
	else if(2==type)
		strcat(input,ijx);
	else
		strcat(input,"i.0 0");
	sprintf(buf,"[ARGV_z_=:%s[BINPATH_z_=:'",arg);
	strcat(input,buf);
	q=input+strlen(input);
	p=path;
	sprintf(buf,"%s/j/bin/profile.ijs",path);
	if(!access(buf,F_OK))
	  sprintf(buf,"%s/j/bin",path),p=buf;
	while(*p)
	{
		if(*p=='\'') *q++='\'';	// 's doubled
		*q++=*p++;
	}
	*q=0;
	strcat(input,"'");
	r=jedo(input);
	free(input);
	return r;
}

void jefail(char* msg)
{
	strcpy(msg, "Load library ");
	strcat(msg, pathdll);
	strcat(msg," failed.");
}
