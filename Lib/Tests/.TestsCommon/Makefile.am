
SRCTOPDIR       =  @top_srcdir@
INCTOPDIR       =  $(SRCTOPDIR)/Include
INCPKGDIR       =  $(INCTOPDIR)/DoubutsuShogi
INCLIBDIR       =  $(INCPKGDIR)/Game

BLDTOPDIR       =  @top_builddir@
LIBTOPDIR       =  $(BLDTOPDIR)/Lib

##
##    Test Configurations.
##

include  TestConf.mak

##
##    Compile and Link Options.
##

AM_CPPFLAGS          =  -I$(INCTOPDIR)
AM_CFLAGS            =
AM_CXXFLAGS          =
AM_LDFLAGS           =  -L$(LIBTOPDIR)

##
##    List of Programs.
##

check_PROGRAMS  =  $(TESTS)

