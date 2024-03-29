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

#include    <sstream>
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

constexpr   int     BOARD_TOP_OFFSET    = 1;
constexpr   int     BOARD_LEFT_OFFSET   = 0;
constexpr   int     LEFT_MARGIN         = 64;
constexpr   int     TOP_MARGIN          = 64;
constexpr   int     FIELD_WIDTH         = 64;
constexpr   int     FIELD_HEIGHT        = 64;
constexpr   int     VIEW_NUM_COLS       = (POS_NUM_COLS);
constexpr   int     VIEW_NUM_ROWS       = (POS_NUM_ROWS) + 2;

constexpr   int     WINDOW_WIDTH        = 640;
constexpr   int     WINDOW_HEIGHT       = 640;

constexpr   int     KIFU_VIEW_LEFT      = LEFT_MARGIN
        + ((VIEW_NUM_COLS + 1) * FIELD_WIDTH);
constexpr   int     KIFU_VIEW_WIDTH     = WINDOW_WIDTH - KIFU_VIEW_LEFT;

constexpr   int     KIFU_FONT_HEIGHT    = 24;

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

constexpr   INTERFACE::PieceIndex
s_tblHandEncBlack[]  = {
    PIECE_BLACK_PAWN,  PIECE_BLACK_BISHOP,  PIECE_BLACK_ROOK,
    PIECE_BLACK_KING
};

constexpr   INTERFACE::PieceIndex
s_tblHandEncWhite[]  = {
    PIECE_WHITE_PAWN,  PIECE_WHITE_BISHOP,  PIECE_WHITE_ROOK,
    PIECE_WHITE_KING
};


const   char
s_tblColName[POS_NUM_COLS]  = {
    'A', 'B', 'C'
};

const   char
s_tblRowName[POS_NUM_ROWS]  = {
    '1', '2', '3', '4'
};

/**
**    画面に表示する駒の名称。
**/

const   char  *
s_tblPieceName[NUM_PIECE_TYPES]     = {
    "",
    "PawnA",  "Bis.A",  "RookA",  "KingA",  "GoldA",
    "PawnV",  "Bis.V",  "RookV",  "KingV",  "GoldV"
};

/**
**    画面に表示する持ち駒の表記。
**/

const   char  *
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

LRESULT
onLButtonDown(
        const   HWND    hWnd,
        const   DWORD   fwKeys,
        const   UINT    xPos,
        const   UINT    yPos)
{
    UTL_HELP_UNUSED_ARGUMENT(fwKeys);

    if ( (xPos < LEFT_MARGIN) || (yPos < TOP_MARGIN) ) {
        g_selX  = -1;
        g_selY  = -1;
        g_movX  = -1;
        g_movY  = -1;
        ::InvalidateRect(hWnd, NULL, TRUE);
        return ( 0 );
    }

    const  int  mx  = ((int)(xPos) - LEFT_MARGIN) / FIELD_WIDTH;
    const  int  my  = ((int)(yPos) - TOP_MARGIN) / FIELD_HEIGHT;

    if ( (VIEW_NUM_ROWS <= my) ) {
        g_selX  = -1;
        g_selY  = -1;
        g_movX  = -1;
        g_movY  = -1;
        ::InvalidateRect(hWnd, NULL, TRUE);
        return ( 0 );
    }
    if ( (my == 0) || (my == (POS_NUM_ROWS + BOARD_TOP_OFFSET)) ) {
        if ( (PIECE_WHITE_KING - PIECE_WHITE_PAWN + 1) <= mx ) {
            g_selX  = -1;
            g_selY  = -1;
            g_movX  = -1;
            g_movY  = -1;
            ::InvalidateRect(hWnd, NULL, TRUE);
            return ( 0 );
        }
        g_selX  = mx;
        g_selY  = my;
    } else if ( (VIEW_NUM_COLS <= mx) ) {
        g_selX  = -1;
        g_selY  = -1;
    } else {
        g_selX  = mx;
        g_selY  = my;
    }

    g_movX  = -1;
    g_movY  = -1;
    ::InvalidateRect(hWnd, NULL, TRUE);

    return ( 0 );
}

//----------------------------------------------------------------
/**   マウスボタンを離した時のイベントハンドラ。
**
**/

LRESULT
onLButtonUp(
        const   HWND    hWnd,
        const   DWORD   fwKeys,
        const   UINT    xPos,
        const   UINT    yPos)
{
    UTL_HELP_UNUSED_ARGUMENT(fwKeys);

    if ( (g_selX < 0) || (g_selY < 0) ) {
        return ( 0 );
    }

    const  int  mx  = ((int)(xPos) - LEFT_MARGIN) / FIELD_WIDTH;
    const  int  my  = ((int)(yPos) - TOP_MARGIN) / FIELD_HEIGHT;

    if ( (mx < BOARD_LEFT_OFFSET) || (my < BOARD_TOP_OFFSET)
            || (POS_NUM_COLS + BOARD_LEFT_OFFSET <= mx)
            || (POS_NUM_ROWS + BOARD_TOP_OFFSET  <= my) )
    {
        g_selX  = -1;
        g_selY  = -1;
        g_movX  = -1;
        g_movY  = -1;
        ::InvalidateRect(hWnd, NULL, TRUE);
        return ( 0 );
    }
    if ( (mx == g_selX) && (my == g_selY) ) {
        g_selX  = -1;
        g_selY  = -1;
        g_movX  = -1;
        g_movY  = -1;
        ::InvalidateRect(hWnd, NULL, TRUE);
        return ( 0 );
    }

    if ( (g_selY == 0) ) {
        //  後手の持ち駒を打つ。    //
        gc.playPutAction(
                s_tblColEnc[mx - BOARD_LEFT_OFFSET],
                s_tblRowEnc[my - BOARD_TOP_OFFSET],
                s_tblHandEncWhite[g_selX - BOARD_LEFT_OFFSET]);
    } else if ( g_selY == POS_NUM_ROWS + BOARD_TOP_OFFSET ) {
        //  先手の持ち駒を打つ。    //
        gc.playPutAction(
                s_tblColEnc[mx - BOARD_LEFT_OFFSET],
                s_tblRowEnc[my - BOARD_TOP_OFFSET],
                s_tblHandEncBlack[g_selX - BOARD_LEFT_OFFSET]);
    } else {
        //  盤上の駒を移動させる。  //
        gc.playMoveAction(
                s_tblColEnc[g_selX - BOARD_LEFT_OFFSET],
                s_tblRowEnc[g_selY - BOARD_TOP_OFFSET],
                s_tblColEnc[mx - BOARD_LEFT_OFFSET],
                s_tblRowEnc[my - BOARD_TOP_OFFSET]);
    }

    g_selX  = -1;
    g_selY  = -1;
    g_movX  = -1;
    g_movY  = -1;
    ::InvalidateRect(hWnd, NULL, TRUE);

    return ( 0 );
}

//----------------------------------------------------------------
/**   マウスを移動させた時のイベントハンドラ。
**
**/

LRESULT
onMouseMove(
        const   HWND    hWnd,
        const   DWORD   fwKeys,
        const   UINT    xPos,
        const   UINT    yPos)
{
    UTL_HELP_UNUSED_ARGUMENT(fwKeys);

    int     mvX, mvY;

    if ( (g_selX < 0) || (g_selY < 0) ) {
        return ( 0 );
    }

    const  int  mx  = ((int)(xPos) - LEFT_MARGIN) / FIELD_WIDTH;
    const  int  my  = ((int)(yPos) - TOP_MARGIN) / FIELD_HEIGHT;

    if ( (xPos < LEFT_MARGIN) || (yPos < TOP_MARGIN) ) {
        mvX = -1;
        mvY = -1;
        goto    label_redraw_board;
    }

    if ( (mx < BOARD_LEFT_OFFSET) || (my < BOARD_TOP_OFFSET)
            || (POS_NUM_COLS + BOARD_LEFT_OFFSET <= mx)
            || (POS_NUM_ROWS + BOARD_TOP_OFFSET  <= my) )
    {
        mvX = -1;
        mvY = -1;
    } else {
        mvX = mx;
        mvY = my;
    }

label_redraw_board:
    if ( (g_movX != mvX) || (g_movY != mvY) ) {
        g_movX  = mvX;
        g_movY  = mvY;
        ::InvalidateRect(hWnd, NULL, TRUE);
    }

    return ( 0 );
}

//----------------------------------------------------------------

LRESULT
onPaint(
        const   HWND    hWnd,
        const   HDC     hDC)
{
    int     sx, sy, dx, dy;

    for ( int y = 0; y <= POS_NUM_ROWS; ++ y ) {
        sx  = ((BOARD_LEFT_OFFSET) * FIELD_WIDTH) + LEFT_MARGIN;
        sy  = ((y + BOARD_TOP_OFFSET) * FIELD_HEIGHT) + TOP_MARGIN;
        dx  = sx + (POS_NUM_COLS * FIELD_WIDTH);
        dy  = sy;
        ::MoveToEx(hDC, sx, sy, NULL);
        ::LineTo  (hDC, dx, dy);
    }

    for ( int x = 0; x <= POS_NUM_COLS; ++ x ) {
        sx  = ((x + BOARD_LEFT_OFFSET) * FIELD_WIDTH) + LEFT_MARGIN;
        sy  = ((BOARD_TOP_OFFSET) * FIELD_HEIGHT) + TOP_MARGIN;
        dx  = sx;
        dy  = sy + (POS_NUM_ROWS * FIELD_HEIGHT);
        ::MoveToEx(hDC, sx, sy, NULL);
        ::LineTo  (hDC, dx, dy);
    }

    if ( (g_selX >= 0) && (g_selY >= 0) ) {
        HBRUSH  hbrBack = ::CreateSolidBrush( RGB(255, 255, 0) );

        dx  = ((g_selX) * FIELD_WIDTH) + LEFT_MARGIN;
        dy  = ((g_selY) * FIELD_HEIGHT) + TOP_MARGIN;

        HBRUSH  hbrOld  = (HBRUSH)::SelectObject(hDC, hbrBack);
        ::Rectangle(hDC, dx, dy, dx + FIELD_WIDTH, dy + FIELD_HEIGHT);
        ::SelectObject(hDC, hbrOld);
        ::DeleteObject(hbrBack);
    }
    if ( (g_movX >= 0) && (g_movY >= 0) ) {
        HBRUSH  hbrBack = ::CreateSolidBrush( RGB(0, 0, 255) );

        dx  = ((g_movX) * FIELD_WIDTH) + LEFT_MARGIN;
        dy  = ((g_movY) * FIELD_HEIGHT) + TOP_MARGIN;

        HBRUSH  hbrOld  = (HBRUSH)::SelectObject(hDC, hbrBack);
        ::Rectangle(hDC, dx, dy, dx + FIELD_WIDTH, dy + FIELD_HEIGHT);
        ::SelectObject(hDC, hbrOld);
        ::DeleteObject(hbrBack);
    }

    ViewBuffer  vb;
    gc.writeToViewBuffer(vb);

    //  後手の持ち駒を表示する。    //
    int     tx  = 0;
    for ( int c = PIECE_WHITE_PAWN; c < PIECE_WHITE_GOLD; ++ c, ++ tx )
    {
        const  int  numHand = vb.nHands[c];
        if ( numHand <= 0 ) { continue; }
        dx = (tx * FIELD_WIDTH) + LEFT_MARGIN;
        dy = TOP_MARGIN;

        if ( (g_selY != 0)
                || (g_selX != tx + BOARD_LEFT_OFFSET) )
        {
            ::Rectangle(hDC, dx, dy, dx + FIELD_WIDTH, dy + FIELD_HEIGHT);
        }

        dx  += (FIELD_WIDTH / 4);
        dy  += (FIELD_HEIGHT / 2);

        const  char  *  pn  = s_tblHandName[c][numHand];
        ::TextOut(hDC, dx, dy, pn, strlen(pn));
    }

    //  盤上にある駒を表示する。    //
    for ( int y = 0; y < POS_NUM_ROWS; ++ y ) {
        for ( int x = 0; x < POS_NUM_COLS; ++ x ) {
            dx  = (x * FIELD_WIDTH) + LEFT_MARGIN + (FIELD_WIDTH / 4);
            dy  = ((y + BOARD_TOP_OFFSET) * FIELD_HEIGHT)
                        + TOP_MARGIN + (FIELD_HEIGHT / 2);
            const  int      pi  = s_tblPosEnc[y][x];
            const  int      dp  = vb.piBoard[pi];
            const  char  *  pn  = s_tblPieceName[dp];
            ::TextOut(hDC, dx, dy, pn, strlen(pn));
        }
    }

    //  先手の持ち駒を表示する。    //
    tx  = 0;
    for ( int c = PIECE_BLACK_PAWN; c < PIECE_BLACK_GOLD; ++ c, ++ tx )
    {
        const  int  numHand = vb.nHands[c];
        if ( numHand <= 0 ) { continue; }
        dx = (tx * FIELD_WIDTH) + LEFT_MARGIN;
        dy = (POS_NUM_ROWS + BOARD_TOP_OFFSET) * FIELD_HEIGHT + TOP_MARGIN;

        if ( (g_selY != POS_NUM_ROWS + BOARD_TOP_OFFSET)
                || (g_selX != tx + BOARD_LEFT_OFFSET) )
        {
            ::Rectangle(hDC, dx, dy, dx + FIELD_WIDTH, dy + FIELD_HEIGHT);
        }

        dx  += (FIELD_WIDTH / 4);
        dy  += (FIELD_HEIGHT / 2);

        const  char  *  pn  = s_tblHandName[c][numHand];
        ::TextOut(hDC, dx, dy, pn, strlen(pn));
    }

    //  現在の棋譜を表示する。  //
    typedef     GameController::ActionViewList  ActionViewList;
    typedef     ActionViewList::const_iterator  ActIter;

    ActionViewList  avl;
    gc.makeActionViewList(avl);
    int             idx     = 0;
    const  ActIter  itrEnd  = avl.end();
    for ( ActIter itr = avl.begin(); itr != itrEnd; ++ itr, ++ idx ) {
        std::stringstream   ss;

        const  ActionView  act  = (* itr);
        if ( !(idx & 1) ) {
            ss  << ((idx / 2) + 1) << ":  ";
        }
        if ( act.putHand != PIECE_EMPTY ) {
            ss  << '.' << s_tblHandName[(act.putHand)][1];
        } else {
            ss  << s_tblColName[(act.xOldCol)]
                << s_tblRowName[(act.yOldRow)];
        }
        ss  << s_tblColName[(act.xNewCol)]
            << s_tblRowName[(act.yNewRow)];

        dx  = KIFU_VIEW_LEFT;
        if ( idx & 1 ) {
            dx  += (KIFU_VIEW_WIDTH / 2);
        }
        const  int  dy  = ((idx / 2) * KIFU_FONT_HEIGHT) + TOP_MARGIN;
        ::TextOut(hDC, dx, dy, ss.str().c_str(), ss.str().length());
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

    RECT    rect    = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
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
