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
**      リソース定義。
**
**      @file       Bin/Win64/Resources.h
**/

#if !defined( DSHOGI_BIN_WIN64_INCLUDED_RESOURCES_H )
#    define   DSHOGI_BIN_WIN64_INCLUDED_RESOURCES_H

#if !defined( DSHOGI_WIN64_INCLUDED_SYS_WINDOWS_H )
#    define     STRICT
#    define     WIN32_LEAN_AND_MEAN
#    include    <windows.h>
#    define     DSHOGI_WIN64_INCLUDED_SYS_WINDOWS_H
#endif

//========================================================================
//
//    メニューリソース。
//

//----------------------------------------------------------------
/**
**    リソース ID の定義。
**/

enum  MenuResource
{
    MENU_ID_FILE        = 10000,
    MENU_ID_FILE_EXIT   = 10001,
    MENU_ID_HELP        = 10100,
    MENU_ID_HELP_SHOW   = 10101,
};

//----------------------------------------------------------------
/**   メインウィンドウのメニューを作成する。
**
**  @return     作成したメニューのハンドル。
**/

HMENU
createMainMenu();

#endif

