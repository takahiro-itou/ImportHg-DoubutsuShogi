
AC_PREREQ([2.69])

AC_INIT(
    [DoubutsuShogi],
    [1.0.145],
    [BUG-REPORT-ADDRESS],
    [DoubutsuShogi])

AC_CONFIG_AUX_DIR([.config])

AM_INIT_AUTOMAKE(
    [serial-tests]
)

AC_CONFIG_SRCDIR([Bin/DoubutsuShogi.cpp])
AC_CONFIG_HEADERS([Include/.DoubutsuShogi.config.h:Include/DoubutsuShogi/.Config/Config.h.in])

: ${CFLAGS:='-O2  -g'}
: ${CXXFLAGS:='-O2  -g'}

CFLAGS="${CFLAGS}  -std=c++11  -Wall"
CXXFLAGS="${CXXFLAGS}  -std=c++11  -Wall  -Weffc++"

dnl
dnl   Check Programs.
dnl

AC_LANG_CPLUSPLUS
AC_PROG_CC
AC_PROG_CXX
AM_PROG_AS
AC_PROG_RANLIB

dnl
dnl   Check Header Files.
dnl

AC_CHECK_HEADER([stdint.h])
AC_CHECK_HEADER(
    [windows.h],
    [dsgcnf_have_windows_h=TRUE],
    [dsgcnf_have_windows_h=FALSE]
)

AM_CONDITIONAL(
    DSHOGI_AMCNF_ENABLE_WINDOWS_H,
    test  "x${dsgcnf_have_windows_h}" = 'xTRUE')
if  test  "x${dsgcnf_have_windows_h}" = 'xTRUE' ; then
  AC_DEFINE(
      [HAVE_WINDOWS_H], [1],
      [Define to 1 if you have the <windows.h> header file.])
fi

dnl
dnl   Check Libraries.
dnl

dnl
dnl   Check Types.
dnl

AC_TYPE_UINT64_T

dnl
dnl   Project Name Space.
dnl

DSHOGI_CNF_NAMESPACE=DOUBUTSUSHOGI
AC_SUBST(DSHOGI_CNF_NAMESPACE)

dnl
dnl   Basic Features.
dnl

AC_CONFIG_FILES([
    Makefile
    Bin/Makefile
    Bin/Win64/Makefile
    Lib/Makefile
    Lib/.Config/Makefile
    Lib/Common/Makefile
    Lib/Game/Makefile
    Lib/Interface/Makefile
])

AC_CONFIG_FILES([
    Include/DoubutsuShogi/.Config/ConfiguredDoubutsuShogi.h
])

AC_CONFIG_FILES([Lib/libdsgGame.a:Lib/.LinkerScript/dsgGame.in])
AC_CONFIG_FILES([Lib/libdsgInterface.a:Lib/.LinkerScript/dsgInterface.in])

dnl
dnl   Test Festures.
dnl

AC_CONFIG_FILES([
    Lib/Game/Tests/Makefile
    Lib/Interface/Tests/Makefile
    Lib/Tests/Makefile
])

AC_OUTPUT

