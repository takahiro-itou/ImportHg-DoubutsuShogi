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
**      An Implementation of GameController class.
**
**      @file   Game/GameController.cpp
**/

#include    "DoubutsuShogi/Game/GameController.h"

#include    <ostream>

DSHOGI_NAMESPACE_BEGIN
namespace  GAME  {

//========================================================================
//
//    GameController  class.
//

//========================================================================
//
//    Tables.
//

constexpr   std::pair<PosCol, PosRow>
s_tblPosMap[POS_MATRIX_SIZE] = {
    { POS_COL_A, POS_ROW_1 },   { POS_COL_C, POS_ROW_1 },
    { POS_COL_C, POS_ROW_4 },   { POS_COL_A, POS_ROW_4 },
    { POS_COL_A, POS_ROW_2 },   { POS_COL_C, POS_ROW_2 },
    { POS_COL_C, POS_ROW_3 },   { POS_COL_A, POS_ROW_3 },
    { POS_COL_B, POS_ROW_1 },   { POS_COL_B, POS_ROW_2 },
    { POS_COL_B, POS_ROW_4 },   { POS_COL_B, POS_ROW_3 }
};

/**
**    画面表示の処理時に参照する座標の変換表。
**/
constexpr   PosEnc
s_tblPosEnc[POS_NUM_ROWS][POS_NUM_COLS] = {
    {   POS_ENC_A1,     POS_ENC_B1,     POS_ENC_C1  },
    {   POS_ENC_A2,     POS_ENC_B2,     POS_ENC_C2  },
    {   POS_ENC_A3,     POS_ENC_B3,     POS_ENC_C3  },
    {   POS_ENC_A4,     POS_ENC_B4,     POS_ENC_C4  }
};

constexpr   const   char  *
s_tblPieceName[16]  = {
    "ヒ↑",  "ニ↑",    "ゾ↑",  nullptr,
    "キ↑",  nullptr,   "ラ↑",  "    ",
    "↓ヒ",  "↓ニ",    "↓ゾ",  nullptr,
    "↓キ",  nullptr,   "↓ラ",  "    "
};

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （コンストラクタ）。
//

GameController::GameController()
    : m_gsBoard()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

GameController::~GameController()
{
}

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    盤面を初期状態に設定する。
//

void
GameController::resetGameBoard()
{
    this->m_gsBoard = 0x0000068EFFFF24AC;
}

//----------------------------------------------------------------
//    現在の盤面を出力する。
//

std::ostream  &
GameController::writeToStream(
        std::ostream  & strOut)  const
{
    const   BoardState  bs  = (this->m_gsBoard);

    strOut  << "┌──┬──┬──┐\n";
    for ( int y = 0; y < POS_NUM_ROWS; ++ y ) {
        if ( y > 0 ) {
            strOut  << "├──┼──┼──┤\n";
        }
        for ( int x = 0; x < POS_NUM_COLS; ++ x ) {
            const  int  posIdx  = s_tblPosEnc[y][x];
            const  int  nPiece  = (bs >> (posIdx * 4)) & 0xF;
            strOut  << "│" << s_tblPieceName[nPiece];
        }
        strOut  << "│\n";
    }
    strOut  << "└──┴──┴──┘";
    return ( strOut );
}

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  GAME
DSHOGI_NAMESPACE_END
