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
};

CPPUNIT_TEST_SUITE_REGISTRATION( GameControllerTest );

//========================================================================
//
//    Tests.
//

void  GameControllerTest::testPlayBackward()
{
}

void  GameControllerTest::testPlayMoveAction()
{
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

    CPPUNIT_ASSERT_EQUAL( PIECE_WHITE_ROOK,     vb.piBoard[POS_MAT_A1] );
    CPPUNIT_ASSERT_EQUAL( PIECE_WHITE_KING,     vb.piBoard[POS_MAT_B1] );
    CPPUNIT_ASSERT_EQUAL( PIECE_WHITE_BISHOP,   vb.piBoard[POS_MAT_C1] );

    CPPUNIT_ASSERT_EQUAL( PIECE_EMPTY,          vb.piBoard[POS_MAT_A2] );
    CPPUNIT_ASSERT_EQUAL( PIECE_WHITE_PAWN,     vb.piBoard[POS_MAT_B2] );
    CPPUNIT_ASSERT_EQUAL( PIECE_EMPTY,          vb.piBoard[POS_MAT_C2] );

    CPPUNIT_ASSERT_EQUAL( PIECE_EMPTY,          vb.piBoard[POS_MAT_A3] );
    CPPUNIT_ASSERT_EQUAL( PIECE_BLACK_PAWN,     vb.piBoard[POS_MAT_B3] );
    CPPUNIT_ASSERT_EQUAL( PIECE_EMPTY,          vb.piBoard[POS_MAT_C3] );

    CPPUNIT_ASSERT_EQUAL( PIECE_BLACK_BISHOP,   vb.piBoard[POS_MAT_A4] );
    CPPUNIT_ASSERT_EQUAL( PIECE_BLACK_KING,     vb.piBoard[POS_MAT_B4] );
    CPPUNIT_ASSERT_EQUAL( PIECE_BLACK_ROOK,     vb.piBoard[POS_MAT_C4] );

    CPPUNIT_ASSERT_EQUAL( 0,    vb.nHands[PIECE_BLACK_PAWN]   );
    CPPUNIT_ASSERT_EQUAL( 0,    vb.nHands[PIECE_BLACK_BISHOP] );
    CPPUNIT_ASSERT_EQUAL( 0,    vb.nHands[PIECE_BLACK_ROOK]   );
    CPPUNIT_ASSERT_EQUAL( 0,    vb.nHands[PIECE_BLACK_KING]   );
    CPPUNIT_ASSERT_EQUAL( 0,    vb.nHands[PIECE_BLACK_GOLD]   );

    CPPUNIT_ASSERT_EQUAL( 0,    vb.nHands[PIECE_WHITE_PAWN]   );
    CPPUNIT_ASSERT_EQUAL( 0,    vb.nHands[PIECE_WHITE_BISHOP] );
    CPPUNIT_ASSERT_EQUAL( 0,    vb.nHands[PIECE_WHITE_ROOK]   );
    CPPUNIT_ASSERT_EQUAL( 0,    vb.nHands[PIECE_WHITE_KING]   );
    CPPUNIT_ASSERT_EQUAL( 0,    vb.nHands[PIECE_WHITE_GOLD]   );
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
