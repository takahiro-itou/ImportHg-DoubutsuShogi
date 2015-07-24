
SRCTOPDIR       =  @top_srcdir@
INCTOPDIR       =  $(SRCTOPDIR)/Include/DoubutsuShogi
INCLIBDIR       =  $(INCTOPDIR)/Game


LIBCXXSOURCES        =

NOINSTHEADERS        =

INCLIBHEADERS        =  \
        $(INCLIBDIR)/GameController.h

NODISTHEADERS        =


LIB_STATIC           =
LIB_SHARED           =

dshogi_includedir              =  $(includedir)/DoubutsuShogi
dshogi_include_HEADERS         =  $(INCLIBHEADERS)
dist_noinst_HEADERS            =  $(NOINSTHEADERS)

dshogi_libdir                  =  $(libdir)
dshogi_config_libdir           =  $(dshogi_libdir)/Game
dshogi_config_lib_LTLIBRARIES  =  $(LIB_STATIC)
dshogi_config_lib_LIBRARIES    =  $(LIB_SHARED)

nodist_dshogi_include_HEADERS  =  $(NODISTHEADERS)


