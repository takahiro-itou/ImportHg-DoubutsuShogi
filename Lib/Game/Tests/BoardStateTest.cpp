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
**      An Implementation of Test Case 'BoardState'
**
**      @file       Game/Tests/BoardStateTest.cpp
**/

#include    "Tests/TestDriver.h"

#include    "DoubutsuShogi/Game/BoardState.h"

DSHOGI_NAMESPACE_BEGIN
namespace  GAME  {

//========================================================================
//
//    BoardStateTest  class.
//
/**
**    単体テストクラス。
**/

class  BoardStateTest : public  CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE(BoardStateTest);
    CPPUNIT_TEST(testDecodeActionData);
    CPPUNIT_TEST(testIsLegalAction);
    CPPUNIT_TEST(testPlayBackward);
    CPPUNIT_TEST(testPlayForward);
    CPPUNIT_TEST(testResetGameBoard);
    CPPUNIT_TEST(testCurrentState);
    CPPUNIT_TEST(testPlayingGame);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }

private:
    void  testDecodeActionData();
    void  testIsLegalAction();
    void  testPlayBackward();
    void  testPlayForward();
    void  testResetGameBoard();
    void  testCurrentState();
    void  testPlayingGame();
};

CPPUNIT_TEST_SUITE_REGISTRATION( BoardStateTest );

//========================================================================
//
//    Tests.
//

using   namespace   INTERFACE;

//----------------------------------------------------------------

void  BoardStateTest::testDecodeActionData()
{
    BoardState  bs;
    ActionView  av;

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS,  bs.resetGameBoard() );

    BoardState::ActionData  act;

    //  先手  (B3, B2)  [ ヒヨコ ]  敵ヒヨコ  を取る。  //
    constexpr  ActionView  av01 = {
        POS_COL_B,  POS_ROW_3,  POS_COL_B,  POS_ROW_2,
        PIECE_BLACK_PAWN,       ACT_NO_PROMOTION,
        PIECE_WHITE_PAWN,       PIECE_EMPTY
    };

    act = bs.encodeMoveAction(
                POS_COL_B,  POS_ROW_3,  POS_COL_B,  POS_ROW_2,
                ACT_AUTO_PROMOTION);
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, bs.decodeActionData(act, av) );
    checkActionView( av01, av, __LINE__ );
}

//----------------------------------------------------------------

void  BoardStateTest::testIsLegalAction()
{
}

//----------------------------------------------------------------

void  BoardStateTest::testPlayBackward()
{
}

//----------------------------------------------------------------

void  BoardStateTest::testPlayForward()
{
}

//----------------------------------------------------------------

void  BoardStateTest::testResetGameBoard()
{
    BoardState  bs;
    ViewBuffer  vb;

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS,  bs.resetGameBoard() );
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS,  bs.copyToViewBuffer(vb) );

    constexpr  ViewBuffer  vb1 = {
        {   PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_WHITE_PAWN,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_PAWN,    PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     0, 0, 0, 0, 0,  0, 0, 0, 0, 0 }
    };

    checkViewBuffer( vb1, vb, __LINE__ );
}

//----------------------------------------------------------------

void  BoardStateTest::testCurrentState()
{
}

//----------------------------------------------------------------

void  BoardStateTest::testPlayingGame()
{
    BoardState  bs;
    ActionView  av;
    ViewBuffer  vb;

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS,  bs.resetGameBoard() );

    BoardState::ActionData  act;

    //  先手  (B3, B2)  [ ヒヨコ ]  敵ヒヨコ  を取る。  //
    constexpr  ActionView  av01 = {
        POS_COL_B,  POS_ROW_3,  POS_COL_B,  POS_ROW_2,
        PIECE_BLACK_PAWN,       ACT_NO_PROMOTION,
        PIECE_WHITE_PAWN,       PIECE_EMPTY
    };
    constexpr  ViewBuffer  vb01 = {
        {   PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_BLACK_PAWN,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  0, 0, 0, 0, 0 }
    };
    act = bs.encodeMoveAction(
                POS_COL_B,  POS_ROW_3,  POS_COL_B,  POS_ROW_2,
                ACT_AUTO_PROMOTION);

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, bs.decodeActionData(act, av) );
    checkActionView( av01, av, __LINE__ );
    bs.playForward(act);
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, bs.copyToViewBuffer(vb) );
    checkViewBuffer( vb01, vb, __LINE__ );

    //  後手  (C1, B2)  [  ゾウ  ]  敵ヒヨコ  を取る。  //
    constexpr  ActionView  av02 = {
        POS_COL_C,  POS_ROW_1,  POS_COL_B,  POS_ROW_2,
        PIECE_WHITE_BISHOP,     ACT_NO_PROMOTION,
        PIECE_BLACK_PAWN,       PIECE_EMPTY
    };
    constexpr  ViewBuffer  vb02 = {
        {   PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  1, 0, 0, 0, 0 }
    };
    act = bs.encodeMoveAction(
                POS_COL_C,  POS_ROW_1,  POS_COL_B,  POS_ROW_2,
                ACT_AUTO_PROMOTION);

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, bs.decodeActionData(act, av) );
    checkActionView( av02, av, __LINE__ );
    bs.playForward(act);
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, bs.copyToViewBuffer(vb) );
    checkViewBuffer( vb02, vb, __LINE__ );

    //  先手  (A4, B3)  [  ゾウ  ]  捕獲した駒は無し。  //
    constexpr  ActionView  av03 = {
        POS_COL_A,  POS_ROW_4,  POS_COL_B,  POS_ROW_3,
        PIECE_BLACK_BISHOP,     ACT_NO_PROMOTION,
        PIECE_EMPTY,            PIECE_EMPTY
    };
    constexpr  ViewBuffer  vb03 = {
        {   PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  1, 0, 0, 0, 0 }
    };

    act = bs.encodeMoveAction(
                POS_COL_A,  POS_ROW_4,  POS_COL_B,  POS_ROW_3,
                ACT_AUTO_PROMOTION);

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, bs.decodeActionData(act, av) );
    checkActionView( av03, av, __LINE__ );
    bs.playForward(act);
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, bs.copyToViewBuffer(vb) );
    checkViewBuffer( vb03, vb, __LINE__ );

    //  後手  (A1, A2)  [ キリン ]  捕獲した駒は無し。  //
    constexpr  ActionView  av04 = {
        POS_COL_A,  POS_ROW_1,  POS_COL_A,  POS_ROW_2,
        PIECE_WHITE_ROOK,       ACT_NO_PROMOTION,
        PIECE_EMPTY,            PIECE_EMPTY
    };
    constexpr  ViewBuffer  vb04 = {
        {   PIECE_EMPTY,         PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_WHITE_ROOK,    PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  1, 0, 0, 0, 0 }
    };

    act = bs.encodeMoveAction(
                POS_COL_A,  POS_ROW_1,  POS_COL_A,  POS_ROW_2,
                ACT_AUTO_PROMOTION);

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, bs.decodeActionData(act, av) );
    checkActionView( av04, av, __LINE__ );
    bs.playForward(act);
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, bs.copyToViewBuffer(vb) );
    checkViewBuffer( vb04, vb, __LINE__ );

    //  先手  (B3, A2)  [  ゾウ  ]  敵キリン  を取る。  //
    constexpr  ActionView  av05 = {
        POS_COL_B,  POS_ROW_3,  POS_COL_A,  POS_ROW_2,
        PIECE_BLACK_BISHOP,     ACT_NO_PROMOTION,
        PIECE_WHITE_ROOK,       PIECE_EMPTY
    };
    constexpr  ViewBuffer  vb05 = {
        {   PIECE_EMPTY,         PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 1, 0, 0,  1, 0, 0, 0, 0 }
    };

    act = bs.encodeMoveAction(
                POS_COL_B,  POS_ROW_3,  POS_COL_A,  POS_ROW_2,
                ACT_AUTO_PROMOTION);

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, bs.decodeActionData(act, av) );
    checkActionView( av05, av, __LINE__ );
    bs.playForward(act);
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, bs.copyToViewBuffer(vb) );
    checkViewBuffer( vb05, vb, __LINE__ );

    //  後手  (B1, A2)  [ライオン]  敵ゾウ    を取る。  //
    constexpr  ActionView  av06 = {
        POS_COL_B,  POS_ROW_1,  POS_COL_A,  POS_ROW_2,
        PIECE_WHITE_KING,       ACT_NO_PROMOTION,
        PIECE_BLACK_BISHOP,     PIECE_EMPTY
    };
    constexpr  ViewBuffer  vb06 = {
        {   PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 1, 0, 0,  1, 1, 0, 0, 0 }
    };

    act = bs.encodeMoveAction(
                POS_COL_B,  POS_ROW_1,  POS_COL_A,  POS_ROW_2,
                ACT_AUTO_PROMOTION);

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, bs.decodeActionData(act, av) );
    checkActionView( av06, av, __LINE__ );
    bs.playForward(act);
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, bs.copyToViewBuffer(vb) );
    checkViewBuffer( vb06, vb, __LINE__ );

    //  先手  (.R, B3)  [ キリン ]  持ち駒を打つ。      //
    constexpr  ActionView  av07 = {
        POS_NUM_COLS,   POS_NUM_ROWS,   POS_COL_B,  POS_ROW_3,
        PIECE_BLACK_ROOK,       ACT_NO_PROMOTION,
        PIECE_EMPTY,            PIECE_BLACK_ROOK
    };
    constexpr  ViewBuffer  vb07 = {
        {   PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_ROOK,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  1, 1, 0, 0, 0 }
    };

    act = bs.encodePutAction(
                POS_COL_B,  POS_ROW_3,  PIECE_BLACK_ROOK);

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, bs.decodeActionData(act, av) );
    checkActionView( av07, av, __LINE__ );
    bs.playForward(act);
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, bs.copyToViewBuffer(vb) );
    checkViewBuffer( vb07, vb, __LINE__ );

    //  後手  (.B, C2)  [  ゾウ  ]  持ち駒を打つ。      //
    constexpr  ActionView  av08 = {
        POS_NUM_COLS,   POS_NUM_ROWS,   POS_COL_C,  POS_ROW_2,
        PIECE_WHITE_BISHOP,     ACT_NO_PROMOTION,
        PIECE_EMPTY,            PIECE_WHITE_BISHOP
    };
    constexpr  ViewBuffer  vb08 = {
        {   PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,  PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_BLACK_ROOK,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  1, 0, 0, 0, 0 }
    };

    act = bs.encodePutAction(
                POS_COL_C,  POS_ROW_2,  PIECE_WHITE_BISHOP);

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, bs.decodeActionData(act, av) );
    checkActionView( av08, av, __LINE__ );
    bs.playForward(act);
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, bs.copyToViewBuffer(vb) );
    checkViewBuffer( vb08, vb, __LINE__ );

    return;
}

}   //  End of namespace  GAME
DSHOGI_NAMESPACE_END

//========================================================================
//
//    エントリポイント。
//

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
