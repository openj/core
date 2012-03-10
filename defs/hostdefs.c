#include <stdio.h>
#ifndef _WIN32
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <regex.h>
#include <sys/time.h>
#include <sys/types.h>
#else

#include <winsock.h>
#include "winregex\rxposix.h"
#endif
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#define offset(r,f) (((char*)&((r*)0)->f)-((char*)((r*)0)))
main(){
	printf ("NB. do not edit -- created by sym2ijs\n\n");
	printf ("cocurrent <'jdefs'\n\n");
#ifndef _WIN32
	printf ("F_OK=: %d\n",(int)F_OK);
	printf ("R_OK=: %d\n",(int)R_OK);
	printf ("W_OK=: %d\n",(int)W_OK);
	printf ("X_OK=: %d\n",(int)X_OK);
	printf ("STDIN_FILENO=: %d\n",(int)STDIN_FILENO);
	printf ("STDOUT_FILENO=: %d\n",(int)STDOUT_FILENO);
	printf ("STDERR_FILENO=: %d\n",(int)STDERR_FILENO);
#else
	puts ("F_OK=:0");
	puts ("R_OK=:4");
	puts ("W_OK=:2");
	puts ("X_OK=:1");
#endif
	printf ("SEEK_CUR=: %d\n",(int)SEEK_CUR);
	printf ("SEEK_END=: %d\n",(int)SEEK_END);
	printf ("SEEK_SET=: %d\n",(int)SEEK_SET);
	puts("");
	printf ("O_APPEND=: %d\n",(int)O_APPEND);
	printf ("O_CREAT=: %d\n",(int)O_CREAT);
	printf ("O_EXCL=: %d\n",(int)O_EXCL);
	printf ("O_RDONLY=: %d\n",(int)O_RDONLY);
	printf ("O_RDWR=: %d\n",(int)O_RDWR);
	printf ("O_TRUNC=: %d\n",(int)O_TRUNC);
	printf ("O_WRONLY=: %d\n",(int)O_WRONLY);
	puts("");
#ifndef _WIN32
	printf ("O_ACCMODE=: %d\n",(int)O_ACCMODE);
	printf ("O_NOCTTY=: %d\n",(int)O_NOCTTY);
	printf ("O_NONBLOCK=: %d\n",(int)O_NONBLOCK);
	printf ("FD_CLOEXEC=: %d\n",(int)FD_CLOEXEC);
	printf ("F_DUPFD=: %d\n",(int)F_DUPFD);
	printf ("F_GETFD=: %d\n",(int)F_GETFD);
	printf ("F_SETFD=: %d\n",(int)F_SETFD);
	printf ("F_GETFL=: %d\n",(int)F_GETFL);
	printf ("F_SETFL=: %d\n",(int)F_SETFL);
	printf ("F_SETLK=: %d\n",(int)F_SETLK);
	printf ("F_SETLKW=: %d\n",(int)F_SETLKW);
	printf ("F_GETLK=: %d\n",(int)F_GETLK);
	printf ("F_UNLCK=: %d\n",(int)F_UNLCK);
	printf ("F_WRLCK=: %d\n",(int)F_WRLCK);
	printf ("flock_sz=: %d\n",(int)sizeof (struct flock));
	printf ("l_len_off=: %d\n",(int)offset(struct flock,l_len));
	printf ("l_len_sz=: %d\n",(int)sizeof(((struct flock*)0)->l_len));
	printf ("l_pid_off=: %d\n",(int)offset(struct flock,l_pid));
	printf ("l_pid_sz=: %d\n",(int)sizeof(((struct flock*)0)->l_pid));
	printf ("l_start_off=: %d\n",(int)offset(struct flock,l_start));
	printf ("l_start_sz=: %d\n",(int)sizeof(((struct flock*)0)->l_start));
	printf ("l_type_off=: %d\n",(int)offset(struct flock,l_type));
	printf ("l_type_sz=: %d\n",(int)sizeof(((struct flock*)0)->l_type));
	printf ("l_whence_off=: %d\n",(int)offset(struct flock,l_whence));
	printf ("l_whence_sz=: %d\n",(int)sizeof(((struct flock*)0)->l_whence));
	puts("");
	printf ("PROT_READ=: %d\n",(int)PROT_READ);
	printf ("PROT_WRITE=: %d\n",(int)PROT_WRITE);
	printf ("PROT_EXEC=: %d\n",(int)PROT_EXEC);
	printf ("PROT_NONE=: %d\n",(int)PROT_NONE);
	printf ("MAP_SHARED=: %d\n",(int)MAP_SHARED);
	printf ("MAP_PRIVATE=: %d\n",(int)MAP_PRIVATE);
	printf ("MAP_FIXED=: %d\n",(int)MAP_FIXED);
#endif
	puts("");
	printf ("REG_EXTENDED=: %d\n",(int)REG_EXTENDED);
	printf ("REG_ICASE=: %d\n",(int)REG_ICASE);
	printf ("REG_NOSUB=: %d\n",(int)REG_NOSUB);
	printf ("REG_NEWLINE=: %d\n",(int)REG_NEWLINE);
	puts("");
	printf ("regex_t_sz=: %d\n",(int)sizeof (regex_t));
	printf ("re_nsub_off=: %d\n",(int)offset(regex_t,re_nsub));
	printf ("re_nsub_sz=: %d\n",(int)sizeof(((regex_t*)0)->re_nsub));
	printf ("regmatch_t_sz=: %d\n",(int)sizeof (regmatch_t));
	printf ("rm_so_off=: %d\n",(int)offset(regmatch_t,rm_so));
	printf ("rm_so_sz=: %d\n",(int)sizeof(((regmatch_t*)0)->rm_so));
	printf ("rm_eo_off=: %d\n",(int)offset(regmatch_t,rm_eo));
	printf ("rm_eo_sz=: %d\n",(int)sizeof(((regmatch_t*)0)->rm_eo));
	puts("");
#if defined(linux) && ! defined(ANDROID)
#define fds_bits __fds_bits
#endif
	puts("");
#ifndef _WIN32
	printf ("fd_set_sz=: %d\n",(int)sizeof (fd_set));
	printf ("fds_bits_off=: %d\n",(int)offset(fd_set,fds_bits));
	printf ("fds_bits_sz=: %d\n",(int)sizeof(((fd_set*)0)->fds_bits));
#endif
	printf ("FD_SETSIZE=: %d\n",(int)FD_SETSIZE);
	printf ("timeval_sz=: %d\n",(int)sizeof (struct timeval));
	printf ("tv_sec_off=: %d\n",(int)offset(struct timeval,tv_sec));
	printf ("tv_sec_sz=: %d\n",(int)sizeof(((struct timeval*)0)->tv_sec));
	printf ("tv_usec_off=: %d\n",(int)offset(struct timeval,tv_usec));
	printf ("tv_usec_sz=: %d\n",(int)sizeof(((struct timeval*)0)->tv_usec));
	puts("");
	printf ("E2BIG=: %d\n",(int)E2BIG);
	printf ("EFAULT=: %d\n",(int)EFAULT);
	printf ("ENFILE=: %d\n",(int)ENFILE);
	printf ("ENOTTY=: %d\n",(int)ENOTTY);
	printf ("EACCES=: %d\n",(int)EACCES);
	printf ("EFBIG=: %d\n",(int)EFBIG);
	printf ("ENODEV=: %d\n",(int)ENODEV);
	printf ("ENXIO=: %d\n",(int)ENXIO);
	printf ("EAGAIN=: %d\n",(int)EAGAIN);
	printf ("ENOENT=: %d\n",(int)ENOENT);
	printf ("EPERM=: %d\n",(int)EPERM);
	printf ("EBADF=: %d\n",(int)EBADF);
	printf ("EINTR=: %d\n",(int)EINTR);
	printf ("ENOEXEC=: %d\n",(int)ENOEXEC);
	printf ("EPIPE=: %d\n",(int)EPIPE);
	printf ("EINVAL=: %d\n",(int)EINVAL);
	printf ("ENOLCK=: %d\n",(int)ENOLCK);
	printf ("ERANGE=: %d\n",(int)ERANGE);
	printf ("EBUSY=: %d\n",(int)EBUSY);
	printf ("EIO=: %d\n",(int)EIO);
	printf ("ENOMEM=: %d\n",(int)ENOMEM);
	printf ("EROFS=: %d\n",(int)EROFS);
	printf ("EISDIR=: %d\n",(int)EISDIR);
	printf ("ENOSPC=: %d\n",(int)ENOSPC);
	printf ("ESPIPE=: %d\n",(int)ESPIPE);
	printf ("ECHILD=: %d\n",(int)ECHILD);
	printf ("EMFILE=: %d\n",(int)EMFILE);
	printf ("ENOSYS=: %d\n",(int)ENOSYS);
	printf ("ESRCH=: %d\n",(int)ESRCH);
	printf ("EDEADLK=: %d\n",(int)EDEADLK);
	printf ("EMLINK=: %d\n",(int)EMLINK);
	printf ("ENOTDIR=: %d\n",(int)ENOTDIR);
	printf ("EDOM=: %d\n",(int)EDOM);
	printf ("ENOTEMPTY=: %d\n",(int)ENOTEMPTY);
	printf ("EXDEV=: %d\n",(int)EXDEV);
	printf ("EEXIST=: %d\n",(int)EEXIST);
	printf ("ENAMETOOLONG=: %d\n",(int)ENAMETOOLONG);
	puts("");
#ifndef _WIN32
	printf ("EINPROGRESS=: %d\n",(int)EINPROGRESS);
	printf ("ECANCELED=: %d\n",(int)ECANCELED);
	printf ("ETIMEDOUT=: %d\n",(int)ETIMEDOUT);
	printf ("EMSGSIZE=: %d\n",(int)EMSGSIZE);
	printf ("ENOTSUP=: %d\n",(int)ENOTSUP);
#endif
	exit (0);
}
