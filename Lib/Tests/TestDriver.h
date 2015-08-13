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
**      An Interface of Test Driver.
**
**      @file       Tests/TestDriver.h
**/

#if !defined( DSHOGI_TESTS_INCLUDED_TEST_DRIVER_H )
#    define   DSHOGI_TESTS_INCLUDED_TEST_DRIVER_H

//----------------------------------------------------------------
/**   単体テストを起動するエントリポイント。
**
**  @param [in] argc
**  @param [in] argv
**  @return
**/

int
executeCppUnitTests(
        int     argc,
        char *  argv[]);

#if ( HAVE_CPPUNIT )
#    include    <cppunit/extensions/HelperMacros.h>
#endif

//========================================================================
//
//    TODO :
//    プロジェクト固有の必要な機能があれば以下に追加する。
//

#include    "DoubutsuShogi/Interface/ViewBuffer.h"

DSHOGI_NAMESPACE_BEGIN
namespace  INTERFACE  {

void
checkViewBuffer(
        const  ViewBuffer   vbExp,
        const  ViewBuffer  &vbAct,
        const  int          nLine);

void
checkActionView(
        const  ActionView   avExp,
        const  ActionView  &avAct,
        const  int          nLine);

}   //  End of namespace  INTERFACE
DSHOGI_NAMESPACE_END

#endif
