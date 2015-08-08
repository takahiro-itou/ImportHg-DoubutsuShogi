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
**      @file       Interface/GameController.cpp
**/

#include    "DoubutsuShogi/Interface/GameController.h"

#include    <ostream>

DSHOGI_NAMESPACE_BEGIN
namespace  INTERFACE  {

namespace  {

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

/**
**    画面に表示する駒の名称。
**/

constexpr   const   char  *
s_tblPieceName[NUM_PIECE_TYPES]     = {
    "    ",
    "ヒ↑",  "ゾ↑",  "キ↑",  "ラ↑",  "ニ↑",
    "↓ヒ",  "↓ゾ",  "↓キ",  "↓ラ",  "↓ニ"
};

/**
**    画面に表示する持ち駒の表記。
**/

constexpr   const   char  *
s_tblHandName[NUM_PIECE_TYPES][3]   = {
    { nullptr,  nullptr,  nullptr },
    { "",   "ヒ",   "ヒ２"  },
    { "",   "ゾ",   "ゾ２"  },
    { "",   "キ",   "キ２"  },
    { "",   "ラ",   "ラ２"  },
    { "",   "ニ",   "ニ２"  },      //  これが出たらバグ。  //
    { "",   "ヒ",   "ヒ２"  },
    { "",   "ゾ",   "ゾ２"  },
    { "",   "キ",   "キ２"  },
    { "",   "ラ",   "ラ２"  },
    { "",   "ニ",   "ニ２"  }       //  これが出たらバグ。  //
};

}   //  End of (Unnamed) namespace.


//========================================================================
//
//    GameController  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （コンストラクタ）。
//

GameController::GameController()
    : m_gsCur()
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
//    Public Member Functions (Implement Pure Virtual).
//

//========================================================================
//
//    Public Member Functions (Overrides).
//

//========================================================================
//
//    Public Member Functions (Pure Virtual Functions).
//

//========================================================================
//
//    Public Member Functions (Virtual Functions).
//

//----------------------------------------------------------------
//    盤面表示の設定ファイルを開く。
//

ErrCode
GameController::openSettingFile(
        const  std::string  &sFileName)
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    盤面を初期状態に設定する。
//

ErrCode
GameController::resetGameBoard()
{
    for ( int pos = 0; pos < POS_MATRIX_SIZE; ++ pos ) {
        this->m_gsCur.piBoard[pos]  = PIECE_EMPTY;
    }
    this->m_gsCur.piBoard[ POS_MAT_A1 ] = PIECE_WHITE_ROOK;
    this->m_gsCur.piBoard[ POS_MAT_B1 ] = PIECE_WHITE_KING;
    this->m_gsCur.piBoard[ POS_MAT_C1 ] = PIECE_WHITE_BISHOP;
    this->m_gsCur.piBoard[ POS_MAT_B2 ] = PIECE_WHITE_PAWN;
    this->m_gsCur.piBoard[ POS_MAT_B3 ] = PIECE_BLACK_PAWN;
    this->m_gsCur.piBoard[ POS_MAT_A4 ] = PIECE_BLACK_BISHOP;
    this->m_gsCur.piBoard[ POS_MAT_B4 ] = PIECE_BLACK_KING;
    this->m_gsCur.piBoard[ POS_MAT_C4 ] = PIECE_BLACK_ROOK;

    for ( int i = 0; i < NUM_PIECE_TYPES; ++ i ) {
        this->m_gsCur.nHands[i] = 0;
    }

    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    現在の盤面を出力する。
//

std::ostream  &
GameController::writeToStream(
        std::ostream  & strOut)  const
{
    strOut  << "後持：";
    for ( int c = PIECE_WHITE_PAWN; c < PIECE_WHITE_GOLD; ++ c ) {
        const  int  numHand = this->m_gsCur.nHands[c];
        if ( numHand > 0 ) {
            strOut  << s_tblHandName[c][numHand];
        }
    }

    strOut  << "\n┌──┬──┬──┐\n";
    for ( int y = 0; y < POS_NUM_ROWS; ++ y ) {
        if ( y > 0 ) {
            strOut  << "├──┼──┼──┤\n";
        }
        for ( int x = 0; x < POS_NUM_COLS; ++ x ) {
            const  int  posIdx  = s_tblPosEnc[y][x];
            const  int  nPiece  = (this->m_gsCur.piBoard[posIdx]);
            strOut  << "│" << s_tblPieceName[nPiece];
        }
        strOut  << "│\n";
    }
    strOut  << "└──┴──┴──┘\n";

    strOut  << "先持：";
    for ( int c = PIECE_BLACK_PAWN; c < PIECE_BLACK_GOLD; ++ c ) {
        const  int  numHand = this->m_gsCur.nHands[c];
        if ( numHand > 0 ) {
            strOut  << s_tblHandName[c][numHand];
        }
    }

    return ( strOut );
}

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  INTERFACE
DSHOGI_NAMESPACE_END
