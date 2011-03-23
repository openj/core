#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([J], [7.0.1], [programming@jsoftware.com])
AC_CANONICAL_TARGET
AC_CONFIG_SRCDIR([jconsole.c])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([foreign])
AC_PROG_LIBTOOL

# Check for CPU-specific features
case $target_cpu in
	# TODO list more 64-bit aches here
	x86_64|ppc64)
		unix64="yes"
		;;
	*)
		unix64="no"
		;;
esac

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AC_CHECK_LIB([dl], [dlopen],,[AC_MSG_ERROR([Cannot find -ldl])])
AC_CHECK_LIB([m], [log],,[AC_MSG_ERROR([Cannot find -lm])])
#AC_CHECK_LIB([ncurses], [setterm])
AC_CHECK_LIB([readline], [readline], [
	      LIBS+="-lreadline"
	      readline="yes"
	      ],[
	       readline="no"
	       AC_MSG_WARN([No -lreadline found])
	       ])

# Checks for header files.
AC_CHECK_HEADERS([arpa/inet.h fcntl.h fenv.h float.h limits.h malloc.h memory.h netdb.h netinet/in.h stdlib.h string.h sys/ioctl.h sys/param.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE
AC_TYPE_MODE_T
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_MMAP
AC_FUNC_REALLOC
AC_FUNC_STRTOD
AC_CHECK_FUNCS([floor getcwd gettimeofday localeconv memchr memmove memset mkdir munmap pow rmdir sqrt strchr strrchr strspn strtol])

AM_CONDITIONAL(HAVE_UNIX64, test "$unix64" = "yes")
AM_CONDITIONAL(HAVE_LIBREADLINE, test "$readline" = "yes")

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
