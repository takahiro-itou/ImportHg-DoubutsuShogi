
##
##    List of Directories.
##

SUBMODULES              =  .

if  DSHOGI_AMCNF_ENABLE_WINDOWS_H
SUBMODULES              += Win64
endif

SUBDIRS                 =  .  $(SUBMODULES)

SRCTOPDIR               =  @top_srcdir@
INCTOPDIR               =  $(SRCTOPDIR)/Include
INCPKGDIR               =  $(INCTOPDIR)/DoubutsuShogi

BLDTOPDIR               =  @top_builddir@
LIBTOPDIR               =  $(BLDTOPDIR)/Lib

##
##    List of Source and Header Files.
##

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

##
##    Include Common Settings.
##

##
##    List of Installs.
##

bin_PROGRAMS            =  \
        DoubutsuShogi

##
##    Build Programs.
##

DoubutsuShogi_SOURCES   =  DoubutsuShogi.cpp
DoubutsuShogi_LDADD     =  -ldsgInterface

