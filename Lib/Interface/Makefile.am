
##
##    List of Directories.
##

SUBDIRS                 =  .  Tests

SRCTOPDIR               =  @top_srcdir@
INCTOPDIR               =  $(SRCTOPDIR)/Include
INCPKGDIR               =  $(INCTOPDIR)/DoubutsuShogi
INCLIBDIR               =  $(INCPKGDIR)/Interface

##
##    List of Source and Header Files.
##

EXTRALIBSOURCES         =
EXTRANOINSTHEADERS      =
EXTRALIBHEADERS         =

LIBCXXSOURCEFILES       =  \
        GameController.cpp  \
        $(EXTRALIBSOURCES)

LIBINSTANTIATIONS       =
LIBCXXINLINEFILES       =

LIBNOINSTHEADERS        =  \
        $(EXTRANOINSTHEADERS)

INCLIBHEADERS           =  \
        $(INCLIBDIR)/GameController.h  \
        $(INCLIBDIR)/ViewBuffer.h      \
        $(EXTRALIBHEADERS)

LIBNODISTHEADERS        =

LIBINSTALLSOURCES       =
LIBCOMPILESOURCES       =  $(LIBCXXSOURCEFILES)  $(LIBINSTANTIATIONS)

##
##    List of Libraries.
##

LIB_STATIC              =  libdsgInterface.staticd.a
LIB_SHARED              =

##
##    Internal Libraries.
##

##
##    Compile and Link Options.
##

AM_CPPFLAGS             =  -I$(INCTOPDIR)
AM_CFLAGS               =
AM_CXXFLAGS             =

##
##    Include Common Settings.
##

##
##    List of Installs.
##

dshogi_includedir                 =  $(includedir)/DoubutsuShogi
dshogi_interface_includedir       =  $(dshogi_includedir)/Interface
dshogi_interface_include_HEADERS  =  $(INCLIBHEADERS)
dist_noinst_HEADERS               =  $(LIBNOINSTHEADERS)

dshogi_libdir                     =  $(libdir)
dshogi_interface_libdir           =  $(dshogi_libdir)/Interface
dshogi_interface_lib_LTLIBRARIES  =  $(LIB_SHARED)
dshogi_interface_lib_LIBRARIES    =  $(LIB_STATIC)

##
##    Build Libraries.
##

libdsgInterface_staticd_a_SOURCES   =  $(LIBCOMPILESOURCES)

