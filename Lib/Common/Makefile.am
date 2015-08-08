
##
##    List of Directories.
##

SRCTOPDIR               =  @top_srcdir@
INCTOPDIR               =  $(SRCTOPDIR)/Include
INCPKGDIR               =  $(INCTOPDIR)/DoubutsuShogi
INCLIBDIR               =  $(INCPKGDIR)/Common

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
        $(EXTRANOINSTHEADERS)

INCLIBHEADERS           =  \
        $(INCLIBDIR)/DoubutsuShogiTypes.h  \
        $(EXTRALIBHEADERS)

LIBNODISTHEADERS        =

LIBINSTALLSOURCES       =
LIBCOMPILESOURCES       =  $(LIBCXXSOURCEFILES)  $(LIBINSTANTIATIONS)

##
##    List of Libraries.
##

LIB_STATIC              =
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

dshogi_includedir              =  $(includedir)/DoubutsuShogi
dshogi_common_includedir       =  $(dshogi_includedir)/Common
dshogi_common_include_HEADERS  =  $(INCLIBHEADERS)
dist_noinst_HEADERS            =  $(NOINSTHEADERS)

dshogi_libdir                  =  $(libdir)
dshogi_common_libdir           =  $(dshogi_libdir)/Common
dshogi_common_lib_LTLIBRARIES  =  $(LIB_SHARED)
dshogi_common_lib_LIBRARIES    =  $(LIB_STATIC)

##
##    Build Libraries.
##

