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
**      An Implementation of Test Case 'GameController'
**
**      @file       Interface/Tests/GameControllerTest.cpp
**/

#include    "Tests/TestDriver.h"

#include    "DoubutsuShogi/Interface/GameController.h"

#include    <iostream>

DSHOGI_NAMESPACE_BEGIN
namespace  INTERFACE  {

//========================================================================
//
//    GameControllerTest  class.
//
/**
**    単体テストクラス。
**/

class  GameControllerTest : public  CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(GameControllerTest);
    CPPUNIT_TEST(testPlayBackward);
    CPPUNIT_TEST(testPlayMoveAction);
    CPPUNIT_TEST(testPlayPutAction);
    CPPUNIT_TEST(testResetGameBoard);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }


private:
    void  testPlayBackward();
    void  testPlayMoveAction();
    void  testPlayPutAction();
    void  testResetGameBoard();

    static  void
    checkViewBuffer(
            const  ViewBuffer   vbExp,
            const  ViewBuffer  &vbAct,
            const  int          nLine);
};

CPPUNIT_TEST_SUITE_REGISTRATION( GameControllerTest );

//========================================================================
//
//    Tests.
//

void  GameControllerTest::testPlayBackward()
{
    GameController  gc;
    ViewBuffer      vb;

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.resetGameBoard() );

    //  先手  (B3, B2)  [ヒヨコ],   敵ヒヨコ  を取る。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_B, POS_ROW_3, POS_COL_B, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr   ViewBuffer  vb01 = {
        {
            PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_BLACK_PAWN,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  0, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb01, vb, __LINE__ );

    //  先手  (.P, A2) [ヒヨコ],    持ち駒を打つ。      //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playPutAction(POS_COL_A, POS_ROW_2, PIECE_BLACK_PAWN));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr   ViewBuffer  vb02 = {
        {
            PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,
            PIECE_BLACK_PAWN,    PIECE_BLACK_PAWN,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     0, 0, 0, 0, 0,  0, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb02, vb, __LINE__ );
}

void  GameControllerTest::testPlayMoveAction()
{
    GameController  gc;
    ViewBuffer      vb;

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.resetGameBoard() );

    //  先手  (B3, B2)  [ヒヨコ],   敵ヒヨコ  を取る。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_B, POS_ROW_3, POS_COL_B, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr   ViewBuffer  vb01 = {
        {
            PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_BLACK_PAWN,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  0, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb01, vb, __LINE__ );

    //  後手 (C1, B2) [ゾウ],       敵ヒヨコ  を取る。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_C, POS_ROW_1, POS_COL_B, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr   ViewBuffer  vb02 = {
        {
            PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  1, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb02, vb, __LINE__ );
}

void  GameControllerTest::testPlayPutAction()
{
}

void  GameControllerTest::testResetGameBoard()
{
    GameController  gc;
    ViewBuffer      vb;

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.resetGameBoard() );
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr   ViewBuffer  vb1 = {
        {
            PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_WHITE_PAWN,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_PAWN,    PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     0, 0, 0, 0, 0,  0, 0, 0, 0, 0 }
    };

    checkViewBuffer( vb1, vb, __LINE__ );
}

void
GameControllerTest::checkViewBuffer(
        const  ViewBuffer   vbExp,
        const  ViewBuffer  &vbAct,
        const  int          nLine)
{
    (void)(nLine);
    ////std::cerr   << "CheckViewBuffer : Caller = " << nLine << std::endl;

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

    ////std::cerr   << "CheckViewBuffer : OK" << std::endl;

    return;
}

}   //  End of namespace  INTERFACE
DSHOGI_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
