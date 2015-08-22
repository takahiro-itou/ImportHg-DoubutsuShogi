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
**      アプリケーション本体。
**
**      @file       Bin/Win64/DoubutsuShogiWin64.cpp
**/

#include    "DoubutsuShogi/Interface/GameController.h"

#include    "Resources.h"

#include    <Wingdi.h>

#if !defined( UTL_HELP_UNUSED_ARGUMENT )
#    define     UTL_HELP_UNUSED_ARGUMENT(var)   (void)(var)
#endif

using   namespace   DSHOGI_NAMESPACE;
using   namespace   DSHOGI_NAMESPACE::INTERFACE;

namespace  {

GameController  gc;

int     g_selX;
int     g_selY;
int     g_movX;
int     g_movY;

const   char
g_szClassName[] = "DoubutsuShogiWindow";

constexpr   int     LEFT_MARGIN = 64;
constexpr   int     TOP_MARGIN  = 64;
constexpr   int     FIELDWIDTH  = 64;
constexpr   int     FIELDHEIGHT = 64;

/**
**    画面表示の処理時に参照する座標の変換表。
**/

constexpr   PosMat
s_tblPosEnc[POS_NUM_ROWS][POS_NUM_COLS] = {
    {   POS_MAT_A1,     POS_MAT_B1,     POS_MAT_C1  },
    {   POS_MAT_A2,     POS_MAT_B2,     POS_MAT_C2  },
    {   POS_MAT_A3,     POS_MAT_B3,     POS_MAT_C3  },
    {   POS_MAT_A4,     POS_MAT_B4,     POS_MAT_C4  }
};

constexpr   PosCol
s_tblColEnc[POS_NUM_COLS]   = {
    POS_COL_A,  POS_COL_B,  POS_COL_C
};

constexpr   PosRow
s_tblRowEnc[POS_NUM_ROWS]   = {
    POS_ROW_1,  POS_ROW_2,  POS_ROW_3,  POS_ROW_4
};

/**
**    画面に表示する駒の名称。
**/

constexpr   const   char  *
s_tblPieceName[NUM_PIECE_TYPES]     = {
    "",
    "PawnA",  "Bis.A",  "RookA",  "KingA",  "GoldA",
    "PawnV",  "Bis.V",  "RookV",  "KingV",  "GoldV"
};

/**
**    画面に表示する持ち駒の表記。
**/

constexpr   const   char  *
s_tblHandName[NUM_PIECE_TYPES][3]   = {
    { nullptr,  nullptr,  nullptr },
    { "",   "P",   "P2"  },
    { "",   "B",   "B2"  },
    { "",   "R",   "R2"  },
    { "",   "K",   "K2"  },
    { "",   "G",   "G2"  },     //  これが出たらバグ。  //
    { "",   "P",   "P2"  },
    { "",   "B",   "B2"  },
    { "",   "R",   "R2"  },
    { "",   "K",   "K2"  },
    { "",   "G",   "G2"  }      //  これが出たらバグ。  //
};

}   //  End of (Unnamed) namespace.

//----------------------------------------------------------------
/**   メニュー項目を選択した時のイベントハンドラ。
**
**/

LRESULT
onCommandMenuClick(
        const   HWND    hWnd,
        const   UINT    wID,
        const   UINT    wNotify)
{
    switch ( wID ) {
    case  MENU_ID_FILE_EXIT:
        if ( ::MessageBox(
                        hWnd,
                        "Exit OK?",
                        NULL,  MB_YESNO | MB_ICONQUESTION) == IDYES )
        {
            ::PostQuitMessage(0);
        }
        break;
    case  MENU_ID_HELP_SHOW:
        break;
    }
    return ( 0 );

}

//----------------------------------------------------------------
/**   マウスボタンを押した時のイベントハンドラ。
**
**/

onLButtonDown(
        const   HWND    hWnd,
        const   DWORD   fwKeys,
        const   UINT    xPos,
        const   UINT    yPos)
{
    UTL_HELP_UNUSED_ARGUMENT(fwKeys);

    const  int  mx  = ((int)(xPos) - LEFT_MARGIN) / FIELDWIDTH;
    const  int  my  = ((int)(yPos) - TOP_MARGIN) / FIELDHEIGHT;

    if ( (mx < 0) || (my < 0)
            || (POS_NUM_COLS <= mx)
            || (POS_NUM_ROWS <= my) )
    {
        return ( 0 );
    }

    g_selX  = mx;
    g_selY  = my;
    ::InvalidateRect(hWnd, NULL, TRUE);

    return ( 0 );
}

//----------------------------------------------------------------
/**   マウスボタンを離した時のイベントハンドラ。
**
**/

onLButtonUp(
        const   HWND    hWnd,
        const   DWORD   fwKeys,
        const   UINT    xPos,
        const   UINT    yPos)
{
    UTL_HELP_UNUSED_ARGUMENT(hWnd);
    UTL_HELP_UNUSED_ARGUMENT(fwKeys);

    if ( (g_selX < 0) || (g_selY < 0) ) {
        return ( 0 );
    }

    const  int  mx  = ((int)(xPos) - LEFT_MARGIN) / FIELDWIDTH;
    const  int  my  = ((int)(yPos) - TOP_MARGIN) / FIELDHEIGHT;

    if ( (mx < 0) || (my < 0)
            || (POS_NUM_COLS <= mx)
            || (POS_NUM_ROWS <= my) )
    {
        g_selX  = -1;
        g_selY  = -1;
        return ( 0 );
    }
    if ( (mx == g_selX) && (my == g_selY) ) {
        g_selX  = -1;
        g_selY  = -1;
        return ( 0 );
    }

    gc.playMoveAction(
            s_tblColEnc[g_selX],  s_tblRowEnc[g_selY],
            s_tblColEnc[mx],  s_tblRowEnc[my]);
    ::InvalidateRect(hWnd, NULL, TRUE);

    return ( 0 );
}

//----------------------------------------------------------------
/**   マウスを移動させた時のイベントハンドラ。
**
**/

onMouseMove(
        const   HWND    hWnd,
        const   DWORD   fwKeys,
        const   UINT    xPos,
        const   UINT    yPos)
{
    UTL_HELP_UNUSED_ARGUMENT(fwKeys);

    if ( (g_selX < 0) || (g_selY < 0) ) {
        return ( 0 );
    }

    const  int  mx  = ((int)(xPos) - LEFT_MARGIN) / FIELDWIDTH;
    const  int  my  = ((int)(yPos) - TOP_MARGIN) / FIELDHEIGHT;

    if ( (mx < 0) || (my < 0)
            || (POS_NUM_COLS <= mx)
            || (POS_NUM_ROWS <= my) )
    {
        return ( 0 );
    }

    g_movX  = mx;
    g_movY  = my;
    ::InvalidateRect(hWnd, NULL, TRUE);

    return ( 0 );
}

//----------------------------------------------------------------

LRESULT
onPaint(
        const   HWND    hWnd,
        const   HDC     hDC)
{
    for ( int y = 0; y <= 4; ++ y ) {
        const  int  dy  = (y * FIELDHEIGHT) + TOP_MARGIN;
        const  int  dx  = (3 * FIELDWIDTH) + LEFT_MARGIN;
        ::MoveToEx(hDC, LEFT_MARGIN, dy, NULL);
        ::LineTo  (hDC, dx, dy);
    }

    for ( int x = 0; x <= 3; ++ x ) {
        const  int  dx  = (x * FIELDWIDTH) + LEFT_MARGIN;
        const  int  dy  = (4 * FIELDHEIGHT) + TOP_MARGIN;
        ::MoveToEx(hDC, dx, TOP_MARGIN, NULL);
        ::LineTo  (hDC, dx, dy);
    }

    if ( (g_selX >= 0) && (g_selY >= 0) ) {
        HBRUSH  hbrBack = ::CreateSolidBrush( RGB(255, 255, 0) );

        const  int  dx  = (g_selX * FIELDWIDTH) + LEFT_MARGIN;
        const  int  dy  = (g_selY * FIELDHEIGHT) + TOP_MARGIN;

        HBRUSH  hbrOld  = (HBRUSH)::SelectObject(hDC, hbrBack);
        ::Rectangle(hDC, dx, dy, dx + FIELDWIDTH, dy + FIELDHEIGHT);
        ::SelectObject(hDC, hbrOld);
        ::DeleteObject(hbrBack);
    }
    if ( (g_movX >= 0) && (g_movY >= 0) ) {
        HBRUSH  hbrBack = ::CreateSolidBrush( RGB(0, 0, 255) );

        const  int  dx  = (g_movX * FIELDWIDTH) + LEFT_MARGIN;
        const  int  dy  = (g_movY * FIELDHEIGHT) + TOP_MARGIN;

        HBRUSH  hbrOld  = (HBRUSH)::SelectObject(hDC, hbrBack);
        ::Rectangle(hDC, dx, dy, dx + FIELDWIDTH, dy + FIELDHEIGHT);
        ::SelectObject(hDC, hbrOld);
        ::DeleteObject(hbrBack);
    }

    ViewBuffer  vb;
    gc.writeToViewBuffer(vb);
    for ( int y = 0; y < 4; ++ y ) {
        for ( int x = 0; x < 3; ++ x ) {
            const  int  dx  = (x * FIELDWIDTH) + LEFT_MARGIN
                + (FIELDWIDTH / 4);
            const  int  dy  = (y * FIELDHEIGHT) + TOP_MARGIN
                + (FIELDHEIGHT / 2);
            const  int  pi  = s_tblPosEnc[y][x];
            const  int  dp  = vb.piBoard[pi];
            const  char  *  pn  = s_tblPieceName[dp];
            ::TextOut(hDC, dx, dy, pn, strlen(pn));
        }
    }

    return ( 0 );
}

//----------------------------------------------------------------
/**   ウィンドウプロシージャ。
**
**/

LRESULT  CALLBACK
WindowProc(
        HWND    hWnd,
        UINT    uMsg,
        WPARAM  wParam,
        LPARAM  lParam)
{
    switch ( uMsg ) {
    case  WM_COMMAND:
        //  メニュー選択時の処理。  //
        if ( lParam == 0 ) {
            return ( onCommandMenuClick(
                             hWnd,
                             LOWORD(wParam),
                             HIWORD(wParam) )
            );
        }
        break;
    case  WM_DESTROY:
        //  ウィンドウを閉じる。    //
        ::PostQuitMessage(0);
        break;
    case  WM_LBUTTONDOWN:
        return ( onLButtonDown(
                         hWnd,
                         wParam,
                         LOWORD(lParam),
                         HIWORD(lParam) )
        );
        break;
    case  WM_LBUTTONUP:
        return ( onLButtonUp(
                         hWnd,
                         wParam,
                         LOWORD(lParam),
                         HIWORD(lParam) )
        );
        break;
    case  WM_MOUSEMOVE:
        return ( onMouseMove(
                         hWnd,
                         wParam,
                         LOWORD(lParam),
                         HIWORD(lParam) )
        );
        break;

    case  WM_PAINT:
        ; {
            PAINTSTRUCT     ps;
            HDC             hDC = ::BeginPaint(hWnd, &ps);
            onPaint(hWnd, hDC);
            ::EndPaint(hWnd, &ps);
        }
        break;
    default:
        return ( ::DefWindowProc(hWnd, uMsg, wParam, lParam) );
    }
    return ( 0 );
}

//----------------------------------------------------------------
/**   アプリケーションのエントリポイント。
**
**/

int  APIENTRY
WinMain(
        HINSTANCE   hInst,
        HINSTANCE,
        LPSTR       lpCmdLine,
        int         nCmdShow)
{
    HWND        hWnd;
    WNDCLASSEX  wcEx;

    wcEx.cbSize         = sizeof(WNDCLASSEX);
    wcEx.style          = CS_HREDRAW | CS_VREDRAW;
    wcEx.lpfnWndProc    = (WNDPROC)WindowProc;
    wcEx.cbClsExtra     = 0;
    wcEx.cbWndExtra     = 0;
    wcEx.hInstance      = hInst;
    wcEx.hIcon          = NULL;
    wcEx.hCursor        = ::LoadCursor(NULL, IDC_ARROW);
    wcEx.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wcEx.lpszMenuName   = NULL;
    wcEx.lpszClassName  = g_szClassName;
    wcEx.hIconSm        = 0;

    if ( ::RegisterClassEx(&wcEx) == 0 ) {
        return ( 0 );
    }

    HMENU   hMenu   = createMainMenu();

    CREATESTRUCT    cs;
    cs.dwExStyle    =  WS_EX_CLIENTEDGE;
    cs.style        =  WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    cs.style        |= WS_OVERLAPPED;

    RECT    rect    = { 0, 0, 640, 480 };
    ::AdjustWindowRectEx(&rect, cs.style, FALSE, cs.dwExStyle);

    const  int  w   = (rect.right - rect.left);
    const  int  h   = (rect.bottom - rect.top);
    cs.x            =  CW_USEDEFAULT;
    cs.y            =  CW_USEDEFAULT;
    cs.cx           =  w;
    cs.cy           =  h;

    hWnd    = ::CreateWindowEx(
                    cs.dwExStyle,
                    wcEx.lpszClassName, "Doubutsu Shogi (WIN64)",
                    cs.style,
                    cs.x, cs.y, cs.cx, cs.cy,
                    NULL, hMenu, hInst, NULL);

    if ( hWnd == 0 ) {
        return ( 0 );
    }

    gc.resetGameBoard();
    g_selX  = -1;
    g_selY  = -1;
    g_movX  = -1;
    g_movY  = -1;

    ::ShowWindow(hWnd, nCmdShow);
    ::UpdateWindow(hWnd);

    int     ret;
    MSG     msg;
    for ( ;; ) {
        ret = ::GetMessage(&msg, NULL, 0, 0);
        if ( ret == 0 || ret == -1 ) {
            break;
        }
        ::DispatchMessage(&msg);
    }

    return ( msg.wParam );
}
