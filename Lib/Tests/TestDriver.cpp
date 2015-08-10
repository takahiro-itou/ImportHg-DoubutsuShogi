//  -*-  coding: utf-8; mode: c++  -*-  //
/*************************************************************************
**                                                                      **
**                      ---   Doubutsu  Shogi  ---                      **
**                                                                      **
**          Copyright (C), 2015-2015, Takahiro Itou                     **
**          All Rights Reserved.                                        **
**                                                                      **
*************************************************************************/

/**
**      An Implementation of Test Driver.
**
**      @file       Tests/TestDriver.cpp
**/

#if ( HAVE_CPPUNIT )
#    include    <cppunit/BriefTestProgressListener.h>
#    include    <cppunit/CompilerOutputter.h>
#    include    <cppunit/extensions/TestFactoryRegistry.h>
#    include    <cppunit/TestResult.h>
#    include    <cppunit/TestResultCollector.h>
#    include    <cppunit/TestRunner.h>
#endif

int
executeCppUnitTests(
        int     argc,
        char *  argv[])
{
    //  未使用の引数。  //
    (void)(argc);
    (void)(argv);

    CPPUNIT_NS::TestResult                  controller;
    CPPUNIT_NS::TestResultCollector         result;

    CPPUNIT_NS::BriefTestProgressListener   progress;
    CPPUNIT_NS::TestRunner                  runner;

    //  単体テストの準備。  //
    controller.addListener( &result );
    controller.addListener( &progress );

    //  テストを実行する。  //
    runner.addTest(
            CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest() );
    runner.run( controller );

    //  テスト結果を表示。  //
    CPPUNIT_NS::CompilerOutputter
            outputter( &result, CPPUNIT_NS::stdCOut() );
    outputter.write();

    return ( result.wasSuccessful() ? 0 : 1 );
}
