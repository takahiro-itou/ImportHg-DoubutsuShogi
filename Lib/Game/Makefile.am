
##
##    List of Directories.
##

SUBDIRS                 =  .  Tests

SRCTOPDIR               =  @top_srcdir@
INCTOPDIR               =  $(SRCTOPDIR)/Include
INCPKGDIR               =  $(INCTOPDIR)/DoubutsuShogi
INCLIBDIR               =  $(INCPKGDIR)/Game

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
        $(EXTRALIBHEADERS)

LIBNODISTHEADERS        =

LIBINSTALLSOURCES       =
LIBCOMPILESOURCES       =  $(LIBCXXSOURCEFILES)  $(LIBINSTANTIATIONS)

##
##    List of Libraries.
##

LIB_STATIC              =  libdsgGame.staticd.a
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
dshogi_game_includedir       =  $(dshogi_includedir)/Game
dshogi_game_include_HEADERS  =  $(INCLIBHEADERS)
dist_noinst_HEADERS               =  $(NOINSTHEADERS)

dshogi_libdir                     =  $(libdir)
dshogi_game_libdir           =  $(dshogi_libdir)/Game
dshogi_game_lib_LTLIBRARIES  =  $(LIB_SHARED)
dshogi_game_lib_LIBRARIES    =  $(LIB_STATIC)

##
##    Build Libraries.
##

libdsgGame_staticd_a_SOURCES   =  $(LIBCOMPILESOURCES)

