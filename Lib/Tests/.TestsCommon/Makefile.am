
##
##    List of Directories.
##

BLDTOPDIR               =  @top_builddir@
SRCTOPDIR               =  @top_srcdir@
INCTOPDIR               =  $(SRCTOPDIR)/Include
LIBTOPDIR               =  $(BLDTOPDIR)/Lib

DRIVER_LIBDIR           =  $(BLDTOPDIR)/Lib/Tests
DRIVER_SRCDIR           =  $(SRCTOPDIR)/Lib/Tests

TESTEE_LIBDIR           =  ..
TESTEE_SRCDIR           =  @srcdir@/..

##
##    Initialize Test Configurations.
##

TESTDRIVERS             =
LIBNOINSTHEADERS        =
EXTRADRIVERS            =
LDTESTDRIVERS           =

TESTCPPFLAGS            =
TESTLDFLAGS             =
TESTLIBTESTEE           =

##
##    Test Configurations.
##

include  $(srcdir)/TestConf.mak

##
##    List of Source and Header Files.
##

TESTDRIVERS             +=
LIBNOINSTHEADERS        +=
EXTRADRIVERS            +=
LDTESTDRIVERS           +=  $(DRIVER_LIBDIR)/libTestDriver.a

##
##    Compile and Link Options.
##

TESTXUNITCPPFLAGS       =  -DHAVE_CPPUNIT=1
TESTXUNITLDFLAGS        =
TESTXUNITLINKLDADD      =  -lcppunit

AM_CPPFLAGS             =  \
        -I$(TESTEE_SRCDIR)  \
        -I$(INCTOPDIR)      \
        -I$(SRCTOPDIR)/Lib  \
        -I$(DRIVER_SRCDIR)  \
        $(TEST_CPPFLAGS)

AM_CFLAGS               =  $(TESTXUNITCPPFLAGS)
AM_CXXFLAGS             =  $(TESTXUNITCPPFLAGS)
AM_LDFLAGS              =  \
        $(TESTLDFLAGS)       \
        $(TESTXUNITLDFLAGS)  \
        -L$(LIBTOPDIR)
LDADD                   =  \
        $(TESTLIBTESTEE)       \
        $(LDTESTDRIVERS)       \
        $(TESTXUNITLINKLDADD)

##
##    List of Installs.
##

dist_noinst_HEADERS     =  $(EXTRATESTDRIVERS)  $(LIBNOINSTHEADERS)
check_PROGRAMS          =  $(TESTS)

