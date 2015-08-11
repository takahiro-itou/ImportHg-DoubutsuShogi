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
    CPPUNIT_TEST(testPlayForward);
    CPPUNIT_TEST(testPlayMoveAction);
    CPPUNIT_TEST(testPlayPutAction);
    CPPUNIT_TEST(testPromotion);
    CPPUNIT_TEST(testResetGameBoard);
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }


private:
    void  testPlayBackward();
    void  testPlayForward();
    void  testPlayMoveAction();
    void  testPlayPutAction();
    void  testPromotion();
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
}

void  GameControllerTest::testPlayForward()
{
    GameController  gc;
    ViewBuffer      vb;

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.resetGameBoard() );

    //  先手  (B3, B2)  [ ヒヨコ ]  敵ヒヨコ  を取る。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_B, POS_ROW_3, POS_COL_B, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb01 = {
        {   PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_BLACK_PAWN,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  0, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb01, vb, __LINE__ );

    //  後手  (C1, B2)  [  ゾウ  ]  敵ヒヨコ  を取る。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_C, POS_ROW_1, POS_COL_B, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb02 = {
        {   PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  1, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb02, vb, __LINE__ );

    //  先手  (A4, B3)  [  ゾウ  ]  捕獲した駒は無し。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_A, POS_ROW_4, POS_COL_B, POS_ROW_3));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb03 = {
        {   PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  1, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb03, vb, __LINE__ );

    //  後手  (A1, A2)  [ キリン ]  捕獲した駒は無し。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_A, POS_ROW_1, POS_COL_A, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb04 = {
        {   PIECE_EMPTY,         PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_WHITE_ROOK,    PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  1, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb04, vb, __LINE__ );

    //  先手  (B3, A2)  [  ゾウ  ]  敵キリン  を取る。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_B, POS_ROW_3, POS_COL_A, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb05 = {
        {   PIECE_EMPTY,         PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 1, 0, 0,  1, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb05, vb, __LINE__ );

    //  後手  (B1, A2)  [ライオン]  敵ゾウ    を取る。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_B, POS_ROW_1, POS_COL_A, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb06 = {
        {   PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 1, 0, 0,  1, 1, 0, 0, 0 }
    };
    checkViewBuffer( vb06, vb, __LINE__ );

    //  先手  (.R, B3)  [ キリン ]  持ち駒を打つ。      //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playPutAction(POS_COL_B, POS_ROW_3, PIECE_BLACK_ROOK));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb07 = {
        {   PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_ROOK,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  1, 1, 0, 0, 0 }
    };
    checkViewBuffer( vb07, vb, __LINE__ );

    //  後手  (.B, C2)  [  ゾウ  ]  持ち駒を打つ。      //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playPutAction(POS_COL_C, POS_ROW_2, PIECE_WHITE_BISHOP));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb08 = {
        {   PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,  PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_BLACK_ROOK,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  1, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb08, vb, __LINE__ );

    //  先手  (B3, B2)  [ キリン ]  敵ゾウ    を取る。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_B, POS_ROW_3, POS_COL_B, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb09 = {
        {   PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_WHITE_KING,    PIECE_BLACK_ROOK,    PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 1, 0, 0, 0,  1, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb09, vb, __LINE__ );

    //  後手  (A2, B2)  [ライオン]  敵キリン  を取る。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_A, POS_ROW_2, POS_COL_B, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb10 = {
        {   PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 1, 0, 0, 0,  1, 0, 1, 0, 0 }
    };
    checkViewBuffer( vb10, vb, __LINE__ );

    //  先手  (.B, A3)  [  ゾウ  ]  持ち駒を打つ。      //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playPutAction(POS_COL_A, POS_ROW_3, PIECE_BLACK_BISHOP));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb11 = {
        {   PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,
            PIECE_BLACK_BISHOP,  PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  1, 0, 1, 0, 0 }
    };
    checkViewBuffer( vb11, vb, __LINE__ );

    //  後手  (B2, A2)  [ライオン]  捕獲した駒は無し。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_B, POS_ROW_2, POS_COL_A, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb12 = {
        {   PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_WHITE_KING,    PIECE_EMPTY,         PIECE_WHITE_BISHOP,
            PIECE_BLACK_BISHOP,  PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  1, 0, 1, 0, 0 }
    };
    checkViewBuffer( vb12, vb, __LINE__ );

    //  先手  (C4, C3)  [ キリン ]  捕獲した駒は無し。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_C, POS_ROW_4, POS_COL_C, POS_ROW_3));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb13 = {
        {   PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_WHITE_KING,    PIECE_EMPTY,         PIECE_WHITE_BISHOP,
            PIECE_BLACK_BISHOP,  PIECE_EMPTY,         PIECE_BLACK_ROOK,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_EMPTY
        }, { 0,     1, 0, 0, 0, 0,  1, 0, 1, 0, 0 }
    };
    checkViewBuffer( vb13, vb, __LINE__ );

    //  後手  (.P, B2)  [ ヒヨコ ]  持ち駒を打つ。      //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playPutAction(POS_COL_B, POS_ROW_2, PIECE_WHITE_PAWN));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb14 = {
        {   PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_WHITE_KING,    PIECE_WHITE_PAWN,    PIECE_WHITE_BISHOP,
            PIECE_BLACK_BISHOP,  PIECE_EMPTY,         PIECE_BLACK_ROOK,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_EMPTY
        }, { 0,     1, 0, 0, 0, 0,  0, 0, 1, 0, 0 }
    };
    checkViewBuffer( vb14, vb, __LINE__ );

    //  先手  (A3, B2)  [  ゾウ  ]  敵ヒヨコ  を取る。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_A, POS_ROW_3, POS_COL_B, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb15 = {
        {   PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_WHITE_KING,    PIECE_BLACK_BISHOP,  PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_BLACK_ROOK,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_EMPTY
        }, { 0,     2, 0, 0, 0, 0,  0, 0, 1, 0, 0 }
    };
    checkViewBuffer( vb15, vb, __LINE__ );

    //  後手  (A2, B2)  [ライオン]  敵ゾウ    を取る。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_A, POS_ROW_2, POS_COL_B, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb16 = {
        {   PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_BLACK_ROOK,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_EMPTY
        }, { 0,     2, 0, 0, 0, 0,  0, 1, 1, 0, 0 }
    };
    checkViewBuffer( vb16, vb, __LINE__ );

    //  先手  (.P, B3)  [ ヒヨコ ]  持ち駒を打つ。      //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playPutAction(POS_COL_B, POS_ROW_3, PIECE_BLACK_PAWN));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb17 = {
        {   PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_BLACK_PAWN,    PIECE_BLACK_ROOK,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_EMPTY
        }, { 0,     1, 0, 0, 0, 0,  0, 1, 1, 0, 0 }
    };
    checkViewBuffer( vb17, vb, __LINE__ );

    //  後手  (B2, B1)  [ライオン]  捕獲した駒は無し。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_B, POS_ROW_2, POS_COL_B, POS_ROW_1));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb18 = {
        {   PIECE_EMPTY,         PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_BLACK_PAWN,    PIECE_BLACK_ROOK,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_EMPTY
        }, { 0,     1, 0, 0, 0, 0,  0, 1, 1, 0, 0 }
    };
    checkViewBuffer( vb18, vb, __LINE__ );

    //  先手  (B4, A3)  [ライオン]  捕獲した駒は無し。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_B, POS_ROW_4, POS_COL_A, POS_ROW_3));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb19 = {
        {   PIECE_EMPTY,         PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_WHITE_BISHOP,
            PIECE_BLACK_KING,    PIECE_BLACK_PAWN,    PIECE_BLACK_ROOK,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY
        }, { 0,     1, 0, 0, 0, 0,  0, 1, 1, 0, 0 }
    };
    checkViewBuffer( vb19, vb, __LINE__ );

    //  後手  (.R, A2)  [ キリン ]  持ち駒を打つ。      //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playPutAction(POS_COL_A, POS_ROW_2, PIECE_WHITE_ROOK));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb20 = {
        {   PIECE_EMPTY,         PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_WHITE_ROOK,    PIECE_EMPTY,         PIECE_WHITE_BISHOP,
            PIECE_BLACK_KING,    PIECE_BLACK_PAWN,    PIECE_BLACK_ROOK,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY
        }, { 0,     1, 0, 0, 0, 0,  0, 1, 0, 0, 0 }
    };
    checkViewBuffer( vb20, vb, __LINE__ );

    return;
}

void  GameControllerTest::testPlayMoveAction()
{
    GameController  gc;
    ViewBuffer      vb;

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.resetGameBoard() );

    //  先手  (B3, B2)  [ ヒヨコ ]  敵ヒヨコ  を取る。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_B, POS_ROW_3, POS_COL_B, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb01 = {
        {   PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_BLACK_PAWN,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  0, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb01, vb, __LINE__ );

    //  後手  (B1, B2)  [ライオン]  敵ヒヨコ  を取る。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_B, POS_ROW_1, POS_COL_B, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb02 = {
        {   PIECE_WHITE_ROOK,    PIECE_EMPTY,         PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  1, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb02, vb, __LINE__ );
}

void  GameControllerTest::testPlayPutAction()
{
    GameController  gc;
    ViewBuffer      vb;

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.resetGameBoard() );

    //  先手  (B3, B2)  [ ヒヨコ ]  敵ヒヨコ  を取る。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_B, POS_ROW_3, POS_COL_B, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb01 = {
        {   PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_BLACK_PAWN,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  0, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb01, vb, __LINE__ );

    //  後手  (C1, B2)  [  ゾウ  ]  敵ヒヨコ  を取る。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_C, POS_ROW_1, POS_COL_B, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb02 = {
        {   PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  1, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb02, vb, __LINE__ );

    //  先手  (.P, A2)  [ ヒヨコ ]  持ち駒を打つ。      //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playPutAction(POS_COL_A, POS_ROW_2, PIECE_BLACK_PAWN));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb03 = {
        {   PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_BLACK_PAWN,    PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     0, 0, 0, 0, 0,  1, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb03, vb, __LINE__ );

    //  後手  (A1, A2)  [ キリン ]  敵ヒヨコ  を取る。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_A, POS_ROW_1, POS_COL_A, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb04 = {
        {   PIECE_EMPTY,         PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_WHITE_ROOK,    PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     0, 0, 0, 0, 0,  2, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb04, vb, __LINE__ );

    //  先手  (A4, B3)  [  ゾウ  ]  捕獲した駒は無し。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_A, POS_ROW_4, POS_COL_B, POS_ROW_3));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb05 = {
        {   PIECE_EMPTY,         PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_WHITE_ROOK,    PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     0, 0, 0, 0, 0,  2, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb05, vb, __LINE__ );

    //  先手  (.P, C3)  [ ヒヨコ ]  持ち駒を打つ。      //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playPutAction(POS_COL_C, POS_ROW_3, PIECE_WHITE_PAWN));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb06 = {
        {   PIECE_EMPTY,         PIECE_WHITE_KING,    PIECE_EMPTY,
            PIECE_WHITE_ROOK,    PIECE_WHITE_BISHOP,  PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_BLACK_BISHOP,  PIECE_WHITE_PAWN,
            PIECE_EMPTY,         PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     0, 0, 0, 0, 0,  1, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb06, vb, __LINE__ );

    return;
}

void  GameControllerTest::testPromotion()
{
    GameController  gc;
    ViewBuffer      vb;

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.resetGameBoard() );

    //  先手  (B3, B2)  [ ヒヨコ ]  敵ヒヨコ  を取る。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_B, POS_ROW_3, POS_COL_B, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb01 = {
        {   PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,
            PIECE_EMPTY,         PIECE_BLACK_PAWN,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  0, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb01, vb, __LINE__ );

    //  後手  (B1, A2)  [ライオン]  捕獲した駒は無し。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_B, POS_ROW_1, POS_COL_A, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb02 = {
        {   PIECE_WHITE_ROOK,    PIECE_EMPTY,         PIECE_WHITE_BISHOP,
            PIECE_WHITE_KING,    PIECE_BLACK_PAWN,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  0, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb02, vb, __LINE__ );

    //  先手  (B2, B1)  [ヒヨコ成]  捕獲した駒は無し。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_B, POS_ROW_2, POS_COL_B, POS_ROW_1));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb03 = {
        {   PIECE_WHITE_ROOK,    PIECE_BLACK_GOLD,    PIECE_WHITE_BISHOP,
            PIECE_WHITE_KING,    PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  0, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb03, vb, __LINE__ );

    //  テストなので、先手番だけ処理する。              //
    //  先手  (B1, B2)  [ニワトリ]  捕獲した駒は無し。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playMoveAction(POS_COL_B, POS_ROW_1, POS_COL_B, POS_ROW_2));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb04 = {
        {   PIECE_WHITE_ROOK,    PIECE_EMPTY,         PIECE_WHITE_BISHOP,
            PIECE_WHITE_KING,    PIECE_BLACK_GOLD,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     1, 0, 0, 0, 0,  0, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb04, vb, __LINE__ );

    //  先手  (.P, B1)  [ ヒヨコ ]  持ち駒を打つ。      //
    //  持ち駒を打つ場合は、成り駒で打ってはいけない。  //
    CPPUNIT_ASSERT_EQUAL(
            ERR_SUCCESS,
            gc.playPutAction(POS_COL_B, POS_ROW_1, PIECE_BLACK_PAWN));
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb05 = {
        {   PIECE_WHITE_ROOK,    PIECE_BLACK_PAWN,    PIECE_WHITE_BISHOP,
            PIECE_WHITE_KING,    PIECE_BLACK_GOLD,    PIECE_EMPTY,
            PIECE_EMPTY,         PIECE_EMPTY,         PIECE_EMPTY,
            PIECE_BLACK_BISHOP,  PIECE_BLACK_KING,    PIECE_BLACK_ROOK
        }, { 0,     0, 0, 0, 0, 0,  0, 0, 0, 0, 0 }
    };
    checkViewBuffer( vb05, vb, __LINE__ );

    return;
}

void  GameControllerTest::testResetGameBoard()
{
    GameController  gc;
    ViewBuffer      vb;

    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.resetGameBoard() );
    CPPUNIT_ASSERT_EQUAL( ERR_SUCCESS, gc.writeToViewBuffer(vb) );

    constexpr  ViewBuffer  vb1 = {
        {   PIECE_WHITE_ROOK,    PIECE_WHITE_KING,    PIECE_WHITE_BISHOP,
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
