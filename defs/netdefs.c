#include <stdio.h>
#ifdef _WIN32
#include <winsock.h>
#else
#include <stdlib.h>
#include <sys/socket.h>
#ifdef sun
#include <inet/tcp.h>
#endif
#ifdef ANDROID
#include<linux/time.h>
#endif
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#endif
#include <sys/types.h>
#define offset(r,f) (((char*)&((r*)0)->f)-((char*)((r*)0)))
main(){
	printf ("NB. do not edit -- created by sym2ijs\n\n");
	printf ("cocurrent <'jdefs'\n\n");
	printf ("FIONBIO=: %d\n",(int)FIONBIO);
	printf ("FIONREAD=: %d\n",(int)FIONREAD);
	printf ("FD_SETSIZE=: %d\n",(int)FD_SETSIZE);
	puts("");
#ifdef _WIN32
	printf ("SD_RECEIVE=: %d\n",(int)SD_RECEIVE);
	printf ("SD_SEND=: %d\n",(int)SD_SEND);
	printf ("SD_BOTH=: %d\n",(int)SD_BOTH);
#endif
	puts("");
	printf ("sockaddr_sz=: %d\n",(int)sizeof (struct sockaddr));
	printf ("sa_family_off=: %d\n",(int)offset(struct sockaddr,sa_family));
	printf ("sa_family_sz=: %d\n",(int)sizeof(((struct sockaddr*)0)->sa_family));
	printf ("sa_data_off=: %d\n",(int)offset(struct sockaddr,sa_data));
	printf ("sa_data_sz=: %d\n",(int)sizeof(((struct sockaddr*)0)->sa_data));
	puts("");
	printf ("sockaddr_in_sz=: %d\n",(int)sizeof (struct sockaddr_in));
	printf ("sin_family_off=: %d\n",(int)offset(struct sockaddr_in,sin_family));
	printf ("sin_family_sz=: %d\n",(int)sizeof(((struct sockaddr_in*)0)->sin_family));
	printf ("sin_port_off=: %d\n",(int)offset(struct sockaddr_in,sin_port));
	printf ("sin_port_sz=: %d\n",(int)sizeof(((struct sockaddr_in*)0)->sin_port));
	printf ("sin_addr_off=: %d\n",(int)offset(struct sockaddr_in,sin_addr));
	printf ("sin_addr_sz=: %d\n",(int)sizeof(((struct sockaddr_in*)0)->sin_addr));
	puts("");
	printf ("in_addr_sz=: %d\n",(int)sizeof (struct in_addr));
	printf ("s_addr_off=: %d\n",(int)offset(struct in_addr,s_addr));
	printf ("s_addr_sz=: %d\n",(int)sizeof(((struct in_addr*)0)->s_addr));
	puts("");
	printf ("hostent_sz=: %d\n",(int)sizeof (struct hostent));
	printf ("h_name_off=: %d\n",(int)offset(struct hostent,h_name));
	printf ("h_name_sz=: %d\n",(int)sizeof(((struct hostent*)0)->h_name));
	printf ("h_aliases_off=: %d\n",(int)offset(struct hostent,h_aliases));
	printf ("h_aliases_sz=: %d\n",(int)sizeof(((struct hostent*)0)->h_aliases));
	printf ("h_addrtype_off=: %d\n",(int)offset(struct hostent,h_addrtype));
	printf ("h_addrtype_sz=: %d\n",(int)sizeof(((struct hostent*)0)->h_addrtype));
	printf ("h_length_off=: %d\n",(int)offset(struct hostent,h_length));
	printf ("h_length_sz=: %d\n",(int)sizeof(((struct hostent*)0)->h_length));
	printf ("h_addr_list_off=: %d\n",(int)offset(struct hostent,h_addr_list));
	printf ("h_addr_list_sz=: %d\n",(int)sizeof(((struct hostent*)0)->h_addr_list));
	puts("");
	puts("");
	printf ("SIOCATMARK=: %d\n",(int)SIOCATMARK);
	puts("");
	puts("");
	printf ("IPPROTO_IP=: %d\n",(int)IPPROTO_IP);
	printf ("IPPROTO_ICMP=: %d\n",(int)IPPROTO_ICMP);
	printf ("IPPROTO_IGMP=: %d\n",(int)IPPROTO_IGMP);
	printf ("IPPROTO_TCP=: %d\n",(int)IPPROTO_TCP);
	printf ("IPPROTO_PUP=: %d\n",(int)IPPROTO_PUP);
	printf ("IPPROTO_UDP=: %d\n",(int)IPPROTO_UDP);
	printf ("IPPROTO_IDP=: %d\n",(int)IPPROTO_IDP);
	printf ("IPPROTO_RAW=: %d\n",(int)IPPROTO_RAW);
	printf ("IPPROTO_MAX=: %d\n",(int)IPPROTO_MAX);
	puts("");
	puts("");
	printf ("INADDR_ANY=: %d\n",(int)INADDR_ANY);
	printf ("INADDR_LOOPBACK=: %d\n",(int)INADDR_LOOPBACK);
	printf ("INADDR_BROADCAST=: %d\n",(int)INADDR_BROADCAST);
#ifdef INADDR_NONE
	printf ("INADDR_NONE=: %d\n",(int)INADDR_NONE);
#else
	puts ("INADDR_NONE=: _1");
#endif
	puts("");
#ifndef _WIN32
	printf ("INADDR_UNSPEC_GROUP=: %d\n",(int)INADDR_UNSPEC_GROUP);
	printf ("INADDR_ALLHOSTS_GROUP=: %d\n",(int)INADDR_ALLHOSTS_GROUP);
	printf ("INADDR_MAX_LOCAL_GROUP=: %d\n",(int)INADDR_MAX_LOCAL_GROUP);
	printf ("IN_LOOPBACKNET=: %d\n",(int)IN_LOOPBACKNET);
#endif
	puts("");
	printf ("SOCK_STREAM=: %d\n",(int)SOCK_STREAM);
	printf ("SOCK_DGRAM=: %d\n",(int)SOCK_DGRAM);
	printf ("SOCK_RAW=: %d\n",(int)SOCK_RAW);
	printf ("SOCK_RDM=: %d\n",(int)SOCK_RDM);
	printf ("SOCK_SEQPACKET=: %d\n",(int)SOCK_SEQPACKET);
	puts("");
	printf ("SOL_SOCKET=: %d\n",(int)SOL_SOCKET);
	printf ("SO_DEBUG=: %d\n",(int)SO_DEBUG);
	printf ("SO_REUSEADDR=: %d\n",(int)SO_REUSEADDR);
	printf ("SO_KEEPALIVE=: %d\n",(int)SO_KEEPALIVE);
	printf ("SO_DONTROUTE=: %d\n",(int)SO_DONTROUTE);
	printf ("SO_BROADCAST=: %d\n",(int)SO_BROADCAST);
	printf ("SO_LINGER=: %d\n",(int)SO_LINGER);
	printf ("SO_OOBINLINE=: %d\n",(int)SO_OOBINLINE);
	puts("");
	printf ("SO_SNDBUF=: %d\n",(int)SO_SNDBUF);
	printf ("SO_RCVBUF=: %d\n",(int)SO_RCVBUF);
	printf ("SO_SNDLOWAT=: %d\n",(int)SO_SNDLOWAT);
	printf ("SO_RCVLOWAT=: %d\n",(int)SO_RCVLOWAT);
	printf ("SO_SNDTIMEO=: %d\n",(int)SO_SNDTIMEO);
	printf ("SO_RCVTIMEO=: %d\n",(int)SO_RCVTIMEO);
	printf ("SO_ERROR=: %d\n",(int)SO_ERROR);
	printf ("SO_TYPE=: %d\n",(int)SO_TYPE);
	puts("");
	printf ("linger_sz=: %d\n",(int)sizeof (struct linger));
	printf ("l_onoff_off=: %d\n",(int)offset(struct linger,l_onoff));
	printf ("l_onoff_sz=: %d\n",(int)sizeof(((struct linger*)0)->l_onoff));
	printf ("l_linger_off=: %d\n",(int)offset(struct linger,l_linger));
	printf ("l_linger_sz=: %d\n",(int)sizeof(((struct linger*)0)->l_linger));
	puts("");
	printf ("AF_UNSPEC=: %d\n",(int)AF_UNSPEC);
	printf ("AF_UNIX=: %d\n",(int)AF_UNIX);
	printf ("AF_INET=: %d\n",(int)AF_INET);
	printf ("AF_SNA=: %d\n",(int)AF_SNA);
	printf ("AF_DECnet=: %d\n",(int)AF_DECnet);
	printf ("AF_APPLETALK=: %d\n",(int)AF_APPLETALK);
	printf ("AF_IPX=: %d\n",(int)AF_IPX);
	printf ("AF_MAX=: %d\n",(int)AF_MAX);
	printf ("PF_UNSPEC=: %d\n",(int)PF_UNSPEC);
	printf ("PF_UNIX=: %d\n",(int)PF_UNIX);
	printf ("PF_INET=: %d\n",(int)PF_INET);
	printf ("PF_SNA=: %d\n",(int)PF_SNA);
	printf ("PF_DECnet=: %d\n",(int)PF_DECnet);
	printf ("PF_APPLETALK=: %d\n",(int)PF_APPLETALK);
	printf ("PF_IPX=: %d\n",(int)PF_IPX);
	printf ("PF_MAX=: %d\n",(int)PF_MAX);
	puts("");
	printf ("SOMAXCONN=: %d\n",(int)SOMAXCONN);
	printf ("MSG_OOB=: %d\n",(int)MSG_OOB);
	printf ("MSG_PEEK=: %d\n",(int)MSG_PEEK);
	printf ("MSG_DONTROUTE=: %d\n",(int)MSG_DONTROUTE);
	puts("");
#ifndef _WIN32
	printf ("msghdr_sz=: %d\n",(int)sizeof (struct msghdr));
	printf ("msg_name_off=: %d\n",(int)offset(struct msghdr,msg_name));
	printf ("msg_name_sz=: %d\n",(int)sizeof(((struct msghdr*)0)->msg_name));
	printf ("msg_namelen_off=: %d\n",(int)offset(struct msghdr,msg_namelen));
	printf ("msg_namelen_sz=: %d\n",(int)sizeof(((struct msghdr*)0)->msg_namelen));
	printf ("msg_iov_off=: %d\n",(int)offset(struct msghdr,msg_iov));
	printf ("msg_iov_sz=: %d\n",(int)sizeof(((struct msghdr*)0)->msg_iov));
	printf ("msg_iovlen_off=: %d\n",(int)offset(struct msghdr,msg_iovlen));
	printf ("msg_iovlen_sz=: %d\n",(int)sizeof(((struct msghdr*)0)->msg_iovlen));
#if defined(linux) || defined(Darwin)
	printf ("msg_control_off=: %d\n",(int)offset(struct msghdr,msg_control));
	printf ("msg_control_sz=: %d\n",(int)sizeof(((struct msghdr*)0)->msg_control));
	printf ("msg_controllen_off=: %d\n",(int)offset(struct msghdr,msg_controllen));
	printf ("msg_controllen_sz=: %d\n",(int)sizeof(((struct msghdr*)0)->msg_controllen));
	printf ("msg_flags_off=: %d\n",(int)offset(struct msghdr,msg_flags));
	printf ("msg_flags_sz=: %d\n",(int)sizeof(((struct msghdr*)0)->msg_flags));
#else
	printf ("msg_accrights_off=: %d\n",(int)offset(struct msghdr,msg_accrights));
	printf ("msg_accrights_sz=: %d\n",(int)sizeof(((struct msghdr*)0)->msg_accrights));
	printf ("msg_accrightslen_off=: %d\n",(int)offset(struct msghdr,msg_accrightslen));
	printf ("msg_accrightslen_sz=: %d\n",(int)sizeof(((struct msghdr*)0)->msg_accrightslen));
#endif
#endif
	puts("");
#ifdef _WIN32
	printf ("SOCKET_ERROR=: %d\n",(int)SOCKET_ERROR);
	printf ("FD_READ=: %d\n",(int)FD_READ);
	printf ("FD_WRITE=: %d\n",(int)FD_WRITE);
	printf ("FD_OOB=: %d\n",(int)FD_OOB);
	printf ("FD_ACCEPT=: %d\n",(int)FD_ACCEPT);
	printf ("FD_CONNECT=: %d\n",(int)FD_CONNECT);
	printf ("FD_CLOSE=: %d\n",(int)FD_CLOSE);
	printf ("WSABASEERR=: %d\n",(int)WSABASEERR);
	printf ("WSAEINTR=: %d\n",(int)WSAEINTR);
	printf ("WSAEBADF=: %d\n",(int)WSAEBADF);
	printf ("WSAEACCES=: %d\n",(int)WSAEACCES);
	printf ("WSAEFAULT=: %d\n",(int)WSAEFAULT);
	printf ("WSAEINVAL=: %d\n",(int)WSAEINVAL);
	printf ("WSAEMFILE=: %d\n",(int)WSAEMFILE);
	printf ("WSAEWOULDBLOCK=: %d\n",(int)WSAEWOULDBLOCK);
	printf ("WSAEINPROGRESS=: %d\n",(int)WSAEINPROGRESS);
	printf ("WSAEALREADY=: %d\n",(int)WSAEALREADY);
	printf ("WSAENOTSOCK=: %d\n",(int)WSAENOTSOCK);
	printf ("WSAEDESTADDRREQ=: %d\n",(int)WSAEDESTADDRREQ);
	printf ("WSAEMSGSIZE=: %d\n",(int)WSAEMSGSIZE);
	printf ("WSAEPROTOTYPE=: %d\n",(int)WSAEPROTOTYPE);
	printf ("WSAENOPROTOOPT=: %d\n",(int)WSAENOPROTOOPT);
	printf ("WSAEPROTONOSUPPORT=: %d\n",(int)WSAEPROTONOSUPPORT);
	printf ("WSAESOCKTNOSUPPORT=: %d\n",(int)WSAESOCKTNOSUPPORT);
	printf ("WSAEOPNOTSUPP=: %d\n",(int)WSAEOPNOTSUPP);
	printf ("WSAEPFNOSUPPORT=: %d\n",(int)WSAEPFNOSUPPORT);
	printf ("WSAEAFNOSUPPORT=: %d\n",(int)WSAEAFNOSUPPORT);
	printf ("WSAEADDRINUSE=: %d\n",(int)WSAEADDRINUSE);
	printf ("WSAEADDRNOTAVAIL=: %d\n",(int)WSAEADDRNOTAVAIL);
	printf ("WSAENETDOWN=: %d\n",(int)WSAENETDOWN);
	printf ("WSAENETUNREACH=: %d\n",(int)WSAENETUNREACH);
	printf ("WSAENETRESET=: %d\n",(int)WSAENETRESET);
	printf ("WSAECONNABORTED=: %d\n",(int)WSAECONNABORTED);
	printf ("WSAECONNRESET=: %d\n",(int)WSAECONNRESET);
	printf ("WSAENOBUFS=: %d\n",(int)WSAENOBUFS);
	printf ("WSAEISCONN=: %d\n",(int)WSAEISCONN);
	printf ("WSAENOTCONN=: %d\n",(int)WSAENOTCONN);
	printf ("WSAESHUTDOWN=: %d\n",(int)WSAESHUTDOWN);
	printf ("WSAETOOMANYREFS=: %d\n",(int)WSAETOOMANYREFS);
	printf ("WSAETIMEDOUT=: %d\n",(int)WSAETIMEDOUT);
	printf ("WSAECONNREFUSED=: %d\n",(int)WSAECONNREFUSED);
	printf ("WSAELOOP=: %d\n",(int)WSAELOOP);
	printf ("WSAENAMETOOLONG=: %d\n",(int)WSAENAMETOOLONG);
	printf ("WSAEHOSTDOWN=: %d\n",(int)WSAEHOSTDOWN);
	printf ("WSAEHOSTUNREACH=: %d\n",(int)WSAEHOSTUNREACH);
	printf ("WSAENOTEMPTY=: %d\n",(int)WSAENOTEMPTY);
	printf ("WSAEPROCLIM=: %d\n",(int)WSAEPROCLIM);
	printf ("WSAEUSERS=: %d\n",(int)WSAEUSERS);
	printf ("WSAEDQUOT=: %d\n",(int)WSAEDQUOT);
	printf ("WSAESTALE=: %d\n",(int)WSAESTALE);
	printf ("WSAEREMOTE=: %d\n",(int)WSAEREMOTE);
	printf ("WSASYSNOTREADY=: %d\n",(int)WSASYSNOTREADY);
	printf ("WSAVERNOTSUPPORTED=: %d\n",(int)WSAVERNOTSUPPORTED);
	printf ("WSANOTINITIALISED=: %d\n",(int)WSANOTINITIALISED);
	printf ("WSAHOST_NOT_FOUND=: %d\n",(int)WSAHOST_NOT_FOUND);
	printf ("HOST_NOT_FOUND=: %d\n",(int)HOST_NOT_FOUND);
	printf ("WSATRY_AGAIN=: %d\n",(int)WSATRY_AGAIN);
	printf ("TRY_AGAIN=: %d\n",(int)TRY_AGAIN);
	printf ("WSANO_RECOVERY=: %d\n",(int)WSANO_RECOVERY);
	printf ("NO_RECOVERY=: %d\n",(int)NO_RECOVERY);
	printf ("WSANO_DATA=: %d\n",(int)WSANO_DATA);
	printf ("NO_DATA=: %d\n",(int)NO_DATA);
	printf ("WSANO_ADDRESS=: %d\n",(int)WSANO_ADDRESS);
	printf ("NO_ADDRESS=: %d\n",(int)NO_ADDRESS);
	printf ("WM_USER=: %d\n",(int)WM_USER);
#endif
	exit (0);
}
