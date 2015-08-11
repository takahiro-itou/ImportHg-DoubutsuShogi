
##
##    List of Tests.
##

EXTRATESTS              =
TESTS                   =  \
        GameControllerTest  \
        $(EXTRATESTS)

##
##    Compile and Link Options.
##

TESTCPPFLAGS            +=
TESTLDFLAGS             +=
TESTLIBTESTEE           +=  -ldsgInterface

##
##    Test Configurations.
##

##
##    Test Programs.
##

GameControllerTest_SOURCES  =  GameControllerTest.cpp

