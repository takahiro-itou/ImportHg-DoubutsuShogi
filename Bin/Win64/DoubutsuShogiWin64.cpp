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

namespace  {

const   char
g_szClassName[] = "DoubutsuShogiWindow";

}   //  End of (Unnamed) namespace.

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
        break;
    case  WM_DESTROY:
        //  ウィンドウを閉じる。    //
        ::PostQuitMessage(0);
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
