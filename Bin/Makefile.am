
SRCTOPDIR       =  @top_srcdir@
INCTOPDIR       =  $(SRCTOPDIR)/Include
INCPKGDIR       =  $(INCTOPDIR)/DoubutsuShogi
INCLIBDIR       =  $(INCPKGDIR)/Game

BLDTOPDIR       =  @top_builddir@
LIBTOPDIR       =  $(BLDTOPDIR)/Lib

bin_PROGRAMS    =  \
        DoubutsuShogi

AM_CPPFLAGS          =  -I$(INCTOPDIR)
AM_CFLAGS            =
AM_CXXFLAGS          =
AM_LDFLAGS           =  -L$(LIBTOPDIR)

DoubutsuShogi_SOURCES  =  DoubutsuShogi.cpp
DoubutsuShogi_LDADD    =  -ldsgGame

