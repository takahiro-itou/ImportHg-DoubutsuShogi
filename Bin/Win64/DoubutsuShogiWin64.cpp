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

#include    <windows.h>

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
    WNDCLASSEX  wcEx;
    HWND        hWnd;

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

    hWnd    = ::CreateWindowEx(
                    0, wcEx.lpszClassName, "Doubutsu Shogi (WIN64)",
                    WS_OVERLAPPEDWINDOW,
                    CW_USEDEFAULT, CW_USEDEFAULT,
                    CW_USEDEFAULT, CW_USEDEFAULT,
                    NULL, NULL, hInst, NULL);

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
