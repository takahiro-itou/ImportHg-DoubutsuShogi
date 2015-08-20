
##
##    List of Directories.
##

SUBDIRS                 =  .

SRCTOPDIR               =  @top_srcdir@
INCTOPDIR               =  $(SRCTOPDIR)/Include
INCPKGDIR               =  $(INCTOPDIR)/DoubutsuShogi
INCLIBDIR               =  $(INCPKGDIR)/.Config

CNF_SRCTOPDIR           =  @top_builddir@
CNF_INCTOPDIR           =  $(CNF_SRCTOPDIR)/Include
CNF_INCPKGDIR           =  $(CNF_INCTOPDIR)/DoubutsuShogi
CNF_INCLIBDIR           =  $(CNF_INCLIBDIR)/.Config


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
        $(INCLIBDIR)/DoubutsuShogiSettings.h  \
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

##
##    Include Common Settings.
##

##
##    List of Installs.
##

dshogi_includedir              =  $(includedir)/DoubutsuShogi
dshogi_config_includedir       =  $(dshogi_includedir)/.Config
dshogi_config_include_HEADERS  =  $(INCLIBHEADERS)
dist_noinst_HEADERS            =  $(LIBNOINSTHEADERS)

dshogi_libdir                  =  $(libdir)
dshogi_config_libdir           =  $(dshogi_libdir)/.Config
dshogi_config_lib_LTLIBRARIES  =  $(LIB_SHARED)
dshogi_config_lib_LIBRARIES    =  $(LIB_STATIC)

nodist_dshogi_config_include_HEADERS  =  $(NODISTHEADERS)

##
##    Build Libraries.
##

