
SRCTOPDIR       =  @top_srcdir@
INCTOPDIR       =  $(SRCTOPDIR)/Include
INCPKGDIR       =  $(INCTOPDIR)/DoubutsuShogi
INCLIBDIR       =  $(INCPKGDIR)/Game

EXTRALIBSOURCES      =
EXTRALIBHEADERS      =

LIBCXXSOURCES        =  \
        GameController.cpp  \
        $(EXTRALIBSOURCES)

NOINSTHEADERS        =

INCLIBHEADERS        =  \
        $(INCLIBDIR)/DoubutsuShogiTypes.h  \
        $(INCLIBDIR)/GameController.h      \
        $(EXTRALIBHEADERS)

NODISTHEADERS        =

AM_CPPFLAGS          =  -I$(INCTOPDIR)
AM_CFLAGS            =
AM_CXXFLAGS          =

LIB_STATIC           =  libdsgGame.a
LIB_SHARED           =

dshogi_includedir              =  $(includedir)/DoubutsuShogi
dshogi_include_HEADERS         =  $(INCLIBHEADERS)
dist_noinst_HEADERS            =  $(NOINSTHEADERS)

dshogi_libdir                  =  $(libdir)
dshogi_config_libdir           =  $(dshogi_libdir)/Game
dshogi_config_lib_LTLIBRARIES  =  $(LIB_SHARED)
dshogi_config_lib_LIBRARIES    =  $(LIB_STATIC)

nodist_dshogi_include_HEADERS  =  $(NODISTHEADERS)

libdsgGame_a_SOURCES  =  $(LIBCXXSOURCES)

