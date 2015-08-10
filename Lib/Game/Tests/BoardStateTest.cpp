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

#include    <iomanip>
#include    <iostream>

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
    CPPUNIT_TEST_SUITE_END();

public:
    virtual  void   setUp()     override    { }
    virtual  void   tearDown()  override    { }
};

}   //  End of namespace  GAME
DSHOGI_NAMESPACE_END

int  main(int argc, char * argv[])
{
    return ( executeCppUnitTests(argc, argv) );
}
