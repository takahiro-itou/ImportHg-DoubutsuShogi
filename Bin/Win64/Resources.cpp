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

void
insertMenuItem(
        const  char  *  szTitle,
        const  UINT     wID,
        const  HMENU    hSub,
        const  UINT     uPos,
        const  BOOL     fByPos,
        HMENU           hMenu)
{
    MENUITEMINFO    mi;

    mi.cbSize       = sizeof(MENUITEMINFO);
    mi.fMask        = MIIM_FTYPE | MIIM_ID | MIIM_SUBMENU | MIIM_STRING;
    mi.fType        = MFT_STRING;
    mi.fState       = MFS_ENABLED;
    mi.wID          = wID;
    mi.hSubMenu     = hSub;
    mi.dwTypeData   = (LPTSTR)(szTitle);

    ::InsertMenuItem(hMenu, uPos, fByPos, &mi);
}

//----------------------------------------------------------------
//    メインウィンドウのメニューを作成する。
//

HMENU
createMainMenu()
{
    HMENU   hMenuFile   = ::CreatePopupMenu();
    HMENU   hMenuHelp   = ::CreatePopupMenu();

    HMENU   hMenu       = ::CreateMenu();

    insertMenuItem("&File", MENU_ID_FILE, hMenuFile, 0, FALSE, hMenu);
    insertMenuItem("&Help", MENU_ID_HELP, hMenuHelp, 0, FALSE, hMenu);

    insertMenuItem("E&xit", MENU_ID_FILE_EXIT, NULL, 0, FALSE, hMenuFile);
    insertMenuItem("About", MENU_ID_HELP_SHOW, NULL, 0, FALSE, hMenuHelp);

    return ( hMenu );
}
