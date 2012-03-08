/* Copyright 1990-2011, Jsoftware Inc.  All rights reserved. */
/* License in license.txt.                                   */
/*                                                                         */
/* SYS_ and friends                                                        */

#ifndef SYS                                 /* only include once (dtoa.c)  */

/* Inclusion of a system herein does not necessarily mean that the source  */
/* compiles or works under that system.                                    */

#define SYS_AMIGA           1L              /* DICE                        */
#define SYS_ARCHIMEDES      2L
#define SYS_ATARIST         4L              /* GCC                         */
#define SYS_ATT3B1          8L              /* System V C                  */
#define SYS_DEC5500         16L             /* GCC                         */
#define SYS_IBMRS6000       32L             /* AIX XL C                    */
#define SYS_MACINTOSH       64L             /* Think C                     */
#define SYS_MIPS            128L            /* GCC                         */
#define SYS_NEXT            256L            /* GCC                         */
#define SYS_OS2             512L
#define SYS_PC              1024L           /* Turbo C                     */
#define SYS_PCWIN           2048L           /* Watcom C 386                */
#define SYS_PC386           4096L           /* Watcom C 386                */
#define SYS_SGI             8192L           /* GCC                         */
#define SYS_SUN3            16384L          /* GCC                         */
#define SYS_SUN4            32768L          /* GCC                         */
#define SYS_VAX             65536L          /* GCC                         */
#define SYS_HPUX            131072L         /* C89                         */
#define SYS_LINUX           262144L         /* GCC                         */
#define SYS_FREEBSD         524288L         /* x86 only                    */
#define SYS_NETBSD          1048576L        /* GCC                         */
#define SYS_SUNSOL2         2097152L        /* GCC                         */
#define SYS_MACOSX          4194304L        /* GCC (CC)                    */

#define SY_64               0    /* 64-bit systems                         */

#define SY_WIN32            0    /* any windows intel version              */
#define SY_WINCE            0    /* any windows ce versions                */
#define SY_LINUX            0    /* any linux intel version                */
#define SY_MAC              0    /* any macosx intel or powerpc version    */
#define SY_MACPPC           0    /* macosx powerpc                         */

#define SY_GETTOD           0    /* gettimeofday on unix                   */

#define SYS_DOS             (SYS_PC + SYS_PC386 + SYS_PCWIN)

#define SYS_UNIX            (SYS_ATT3B1 + SYS_DEC5500 + SYS_IBMRS6000 + \
                             SYS_MIPS + SYS_NEXT + SYS_SGI + SYS_SUN3 + \
                             SYS_SUN4 + SYS_VAX + SYS_LINUX + SYS_MACOSX + \
                             SYS_FREEBSD + SYS_NETBSD + SYS_SUNSOL2 + SYS_HPUX)

#define SYS_ANSILIB         (SYS_AMIGA + SYS_ARCHIMEDES + SYS_DOS + \
                             SYS_MACINTOSH +  SYS_OS2 + SYS_UNIX)

#define SYS_SESM            (SYS_ARCHIMEDES + SYS_DOS + SYS_MACINTOSH + \
                             SYS_OS2 + SYS_UNIX)

#define SYS_LILENDIAN       (SYS_ARCHIMEDES + SYS_DEC5500 + SYS_DOS + \
                             SYS_OS2 + SYS_LINUX + SYS_FREEBSD + \
                             SYS_NETBSD)

#if defined(__FreeBSD__)
#define SYS SYS_FREEBSD
#endif

#if defined(__NetBSD__)
#define SYS SYS_NETBSD
#endif

#if defined(sparc) && ! defined(__svr4__)
#define SYS SYS_SUN4
#endif

#if defined(sparc) && defined(__svr4__)
#define SYS SYS_SUNSOL2
#endif

#if defined(__sgi__)
#define SYS SYS_SGI
#endif

#if defined (_AIX)
#define SYS SYS_IBMRS6000
#endif

#ifdef __linux__
#define SYS SYS_LINUX
#undef SY_LINUX
#define SY_LINUX 1
#endif

#if defined _PA_RISC1_1
#define SYS SYS_HPUX
#endif

#ifdef __MACH__
#ifdef __ppc__
#ifdef __GNUC__
#define SYS SYS_MACOSX // powerpc
#undef SY_MAC
#define SY_MAC 1
#undef SY_MACPPC
#def SY_MACPPC 1
#endif
#endif
#endif

#ifdef __MACH__
#ifndef __ppc__
#ifdef __GNUC__
#define SYS SYS_MACOSX // intel
#undef SY_MAC
#define SY_MAC 1
#undef SYS_LILENDIAN
#define SYS_LILENDIAN SYS_MACOSX

#endif
#endif
#endif


#ifdef _WIN32
#define SYS                 SYS_PCWIN
#undef  SY_WIN32
#define SY_WIN32            1
#endif

#if SYS & SYS_UNIX
#undef  SY_GETTOD
#define SY_GETTOD 1
#endif

#ifdef UNDER_CE
#undef  SY_WINCE
#define SY_WINCE            1
#endif

#define SY_ALIGN            (!(SY_WIN32 || SYS&SYS_LINUX) || SY_WINCE)
/* SY_ALIGN    should be 1 for compilers requiring strict alignment        */
/*             e.g. if (I*)av is not allowed for arbitrary av of type C*   */

/* Windows CE target autoconfiguration: */
#if SY_WINCE
#ifdef SH3
#define SY_WINCE_SH         1
#else
#define SY_WINCE_SH         0
#endif
#ifdef MIPS
#define SY_WINCE_MIPS       1
#else
#define SY_WINCE_MIPS       0
#endif
#ifdef ARM
#define SY_WINCE_ARM        1
#else
#define SY_WINCE_ARM        0
#endif
#endif

/* _WIN64 defined by VC++ and _UNIX64 defined in makefile */
#if defined(_WIN64) || defined(_UNIX64)
#undef SY_64
#define SY_64               1
#endif

#ifndef SYS     /* must be defined */
 error: "SYS must be defined"
#endif

#if 1!=SY_WIN32+SY_LINUX+SY_MAC
 error: "one and only one of SY_WIN32, SY_LINUX, SY_MAC must be 1"
#endif 

#endif /* only include once */

