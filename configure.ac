
AC_PREREQ([2.69])

AC_INIT([DoubutsuShogi], [1.0])

AC_CONFIG_AUX_DIR([.config])

AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([Lib])
AC_CONFIG_HEADER([Include/.DoubutsuShogi.config.h:Include/DoubutsuShogi/.Config/Config.h.in])

AC_PROG_CC
AM_PROG_AS

dnl
dnl   Basic Features.
dnl
AC_CONFIG_FILES([
    Makefile
    Bin/Makefile
    Lib/Makefile
    Lib/.Config/Makefile
    Lib/Game/Makefile
])

dnl
dnl   Test Festures.
dnl
AC_CONFIG_FILES([
    Lib/Tests/Makefile
])

AC_OUTPUT


