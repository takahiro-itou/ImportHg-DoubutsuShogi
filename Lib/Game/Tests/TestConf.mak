
##
##    List of Tests.
##

EXTRATESTS          =
TESTS               =  \
        BoardStateTest  \
        $(EXTRATESTS)

##
##    Compile and Link Options.
##

TESTCPPFLAGS        =
TESTLDFLAGS         =
LDADD               =  ../libdsgGame.staticd.a

##
##    Test Configurations.
##

##
##    Test Programs.
##

BoardStateTest_SOURCES  =  BoardStateTest.cpp

