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
**      @file       Bin/Win64/Resources.cpp
**/

#include    "Resources.h"

//----------------------------------------------------------------
//    メインウィンドウのメニューを作成する。
//

HMENU
createMainMenu()
{
    HMENU   hMenu   = ::CreateMenu();

    ::InsertMenu(hMenu, 0, MF_BYPOSITION, 0, "File");

    return ( hMenu );
}
