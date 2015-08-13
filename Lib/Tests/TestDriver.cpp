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

#include    "TestDriver.h"

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

//========================================================================
//
//    TODO :
//    プロジェクト固有の必要な機能があれば以下に追加する。
//

DSHOGI_NAMESPACE_BEGIN
namespace  INTERFACE  {

void
checkViewBuffer(
        const  ViewBuffer   vbExp,
        const  ViewBuffer  &vbAct,
        const  int          nLine)
{
    (void)(nLine);

    CPPUNIT_ASSERT_EQUAL(
            vbExp.piBoard[POS_MAT_A1],  vbAct.piBoard[POS_MAT_A1] );
    CPPUNIT_ASSERT_EQUAL(
            vbExp.piBoard[POS_MAT_B1],  vbAct.piBoard[POS_MAT_B1] );
    CPPUNIT_ASSERT_EQUAL(
            vbExp.piBoard[POS_MAT_C1],  vbAct.piBoard[POS_MAT_C1] );

    CPPUNIT_ASSERT_EQUAL(
            vbExp.piBoard[POS_MAT_A2],  vbAct.piBoard[POS_MAT_A2] );
    CPPUNIT_ASSERT_EQUAL(
            vbExp.piBoard[POS_MAT_B2],  vbAct.piBoard[POS_MAT_B2] );
    CPPUNIT_ASSERT_EQUAL(
            vbExp.piBoard[POS_MAT_C2],  vbAct.piBoard[POS_MAT_C2] );

    CPPUNIT_ASSERT_EQUAL(
            vbExp.piBoard[POS_MAT_A3],  vbAct.piBoard[POS_MAT_A3] );
    CPPUNIT_ASSERT_EQUAL(
            vbExp.piBoard[POS_MAT_B3],  vbAct.piBoard[POS_MAT_B3] );
    CPPUNIT_ASSERT_EQUAL(
            vbExp.piBoard[POS_MAT_C3],  vbAct.piBoard[POS_MAT_C3] );

    CPPUNIT_ASSERT_EQUAL(
            vbExp.piBoard[POS_MAT_A4],  vbAct.piBoard[POS_MAT_A4] );
    CPPUNIT_ASSERT_EQUAL(
            vbExp.piBoard[POS_MAT_B4],  vbAct.piBoard[POS_MAT_B4] );
    CPPUNIT_ASSERT_EQUAL(
            vbExp.piBoard[POS_MAT_C4],  vbAct.piBoard[POS_MAT_C4] );

    CPPUNIT_ASSERT_EQUAL(
            vbExp.nHands[PIECE_BLACK_PAWN],
            vbAct.nHands[PIECE_BLACK_PAWN] );
    CPPUNIT_ASSERT_EQUAL(
            vbExp.nHands[PIECE_BLACK_BISHOP],
            vbAct.nHands[PIECE_BLACK_BISHOP]);
    CPPUNIT_ASSERT_EQUAL(
            vbExp.nHands[PIECE_BLACK_ROOK],
            vbAct.nHands[PIECE_BLACK_ROOK]);
    CPPUNIT_ASSERT_EQUAL(
            vbExp.nHands[PIECE_BLACK_KING],
            vbAct.nHands[PIECE_BLACK_KING]);
    CPPUNIT_ASSERT_EQUAL(
            vbExp.nHands[PIECE_BLACK_GOLD],
            vbAct.nHands[PIECE_BLACK_GOLD]);

    CPPUNIT_ASSERT_EQUAL(
            vbExp.nHands[PIECE_WHITE_PAWN],
            vbAct.nHands[PIECE_WHITE_PAWN]);
    CPPUNIT_ASSERT_EQUAL(
            vbExp.nHands[PIECE_WHITE_BISHOP],
            vbAct.nHands[PIECE_WHITE_BISHOP]);
    CPPUNIT_ASSERT_EQUAL(
            vbExp.nHands[PIECE_WHITE_ROOK],
            vbAct.nHands[PIECE_WHITE_ROOK]);
    CPPUNIT_ASSERT_EQUAL(
            vbExp.nHands[PIECE_WHITE_KING],
            vbAct.nHands[PIECE_WHITE_KING]);
    CPPUNIT_ASSERT_EQUAL(
            vbExp.nHands[PIECE_WHITE_GOLD],
            vbAct.nHands[PIECE_WHITE_GOLD]);

    return;
}

void
checkActionView(
        const  ActionView   avExp,
        const  ActionView  &avAct,
        const  int          nLine)
{
    (void)(nLine);

    CPPUNIT_ASSERT_EQUAL( avExp.xOldCol,  avAct.xOldCol );
    CPPUNIT_ASSERT_EQUAL( avExp.yOldRow,  avAct.yOldRow );
    CPPUNIT_ASSERT_EQUAL( avExp.xNewCol,  avAct.xNewCol );
    CPPUNIT_ASSERT_EQUAL( avExp.yNewRow,  avAct.yNewRow );

    CPPUNIT_ASSERT_EQUAL( avExp.piMoved,  avAct.piMoved );
    CPPUNIT_ASSERT_EQUAL( avExp.flgProm,  avAct.flgProm );
    CPPUNIT_ASSERT_EQUAL( avExp.piCatch,  avAct.piCatch );
    CPPUNIT_ASSERT_EQUAL( avExp.putHand,  avAct.putHand );

    return;
}

}   //  End of namespace  INTERFACE
DSHOGI_NAMESPACE_END

