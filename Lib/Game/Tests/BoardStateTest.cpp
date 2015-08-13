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
    CPPUNIT_TEST(testCopyToViewBuffer);
    CPPUNIT_TEST(testCurrentState);
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
    void  testCopyToViewBuffer();
    void  testCurrentState();
};

CPPUNIT_TEST_SUITE_REGISTRATION( BoardStateTest );

//========================================================================
//
//    Tests.
//

void  BoardStateTest::testDecodeActionData()
{
}

void  BoardStateTest::testIsLegalAction()
{
}

void  BoardStateTest::testPlayBackward()
{
}

void  BoardStateTest::testPlayForward()
{
}

void  BoardStateTest::testResetGameBoard()
{
}

void  BoardStateTest::testCopyToViewBuffer()
{
}

void  BoardStateTest::testCurrentState()
{
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
