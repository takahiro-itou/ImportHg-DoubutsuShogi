
##
##    List of Tests.
##

EXTRATESTS              =
TESTS                   =  \
        BoardStateTest     \
        $(EXTRATESTS)

##
##    Compile and Link Options.
##

TESTCPPFLAGS            +=
TESTLDFLAGS             +=
TESTLIBTESTEE           +=  -ldsgGame

##
##    Test Configurations.
##

##
##    Test Programs.
##

BoardStateTest_SOURCES  =  BoardStateTest.cpp

