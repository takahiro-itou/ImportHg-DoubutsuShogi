
AC_PREREQ([2.69])

AC_INIT([DoubutsuShogi], [1.0])

AC_CONFIG_AUX_DIR([.config])

AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([Lib])
AC_CONFIG_HEADER([Include/.DoubutsuShogi.config.h:Include/DoubutsuShogi/.Config/Config.h.in])

: ${CFLAGS:='-std=c++11'}
: ${CXXFLAGS:='-std=c++11'}

AC_LANG_CPLUSPLUS
AC_PROG_CC
AC_PROG_CXX
AM_PROG_AS
AC_PROG_RANLIB

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

AC_CONFIG_FILES([
    Include/DoubutsuShogi/.Config/ConfiguredDoubutsuShogi.h
])

AC_CONFIG_FILES([Lib/libdsgGame.a:Lib/.LinkerScript/dsgGame.in])

dnl
dnl   Test Festures.
dnl

AC_CONFIG_FILES([
    Lib/Tests/Makefile
])

AC_OUTPUT


