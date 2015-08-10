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

#endif
