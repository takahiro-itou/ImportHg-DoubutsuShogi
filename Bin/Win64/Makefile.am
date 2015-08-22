
##
##    List of Directories.
##

SRCTOPDIR               =  @top_srcdir@
INCTOPDIR               =  $(SRCTOPDIR)/Include
INCPKGDIR               =  $(INCTOPDIR)/DoubutsuShogi

BLDTOPDIR               =  @top_builddir@
LIBTOPDIR               =  $(BLDTOPDIR)/Lib

##
##    List of Source and Header Files.
##

EXTRALIBSOURCES         =
EXTRANOINSTHEADERS      =
EXTRALIBHEADERS         =

LIBCXXSOURCEFILES       =  \
        $(EXTRALIBSOURCES)

LIBINSTANTIATIONS       =
LIBCXXINLINEFILES       =

LIBNOINSTHEADERS        =  \
        Resources.h            \
        $(EXTRANOINSTHEADERS)

INCLIBHEADERS           =  \
        $(EXTRALIBHEADERS)

LIBNODISTHEADERS        =

LIBINSTALLSOURCES       =
LIBCOMPILESOURCES       =  $(LIBCXXSOURCEFILES)  $(LIBINSTANTIATIONS)

##
##    List of Libraries.
##

##
##    Compile and Link Options.
##

AM_CPPFLAGS             =  -I$(INCTOPDIR)
AM_CFLAGS               =
AM_CXXFLAGS             =
AM_LDFLAGS              =  -L$(LIBTOPDIR)

AM_CPPFLAGS             += -DDSHOGI_WIN64=1

##
##    Include Common Settings.
##

##
##    List of Installs.
##

bin_PROGRAMS            =  \
        DoubutsuShogiWin64

dist_noinst_HEADERS     =  $(LIBNOINSTHEADERS)

##
##    Build Programs.
##

DoubutsuShogiWin64_SOURCES   =  \
        DoubutsuShogiWin64.cpp  \
        Resources.cpp
DoubutsuShogiWin64_LDADD     =  -ldsgInterface  -lGdi32

