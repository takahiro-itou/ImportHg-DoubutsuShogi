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

#include    "Resources.h"

#if !defined( UTL_HELP_UNUSED_ARGUMENT )
#    define     UTL_HELP_UNUSED_ARGUMENT(var)   (void)(var)
#endif

namespace  {

const   char
g_szClassName[] = "DoubutsuShogiWindow";

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
    UTL_HELP_UNUSED_ARGUMENT(hWnd);
    UTL_HELP_UNUSED_ARGUMENT(fwKeys);
    UTL_HELP_UNUSED_ARGUMENT(xPos);
    UTL_HELP_UNUSED_ARGUMENT(yPos);
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
    UTL_HELP_UNUSED_ARGUMENT(xPos);
    UTL_HELP_UNUSED_ARGUMENT(yPos);
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
    UTL_HELP_UNUSED_ARGUMENT(hWnd);
    UTL_HELP_UNUSED_ARGUMENT(fwKeys);
    UTL_HELP_UNUSED_ARGUMENT(xPos);
    UTL_HELP_UNUSED_ARGUMENT(yPos);
    return ( 0 );
}

//----------------------------------------------------------------

LRESULT
onPaint(
        const   HWND    hWnd,
        const   HDC     hDC)
{
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
