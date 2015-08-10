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
**      An Implementation of BoardState class.
**
**      @file       Game/BoardState.cpp
**/

#include    "DoubutsuShogi/Game/BoardState.h"

DSHOGI_NAMESPACE_BEGIN
namespace  GAME  {

namespace  {

//----------------------------------------------------------------
/**
**    画面表示の処理時に参照する座標の変換表。
**/

//----------------------------------------------------------------
/**
**    画面表示の処理時に参照する駒番号の変換表。
**/

constexpr   INTERFACE::PieceIndex
s_tblPieceConv[FIELD_WALL_SQUARE + 1]   =
{
    INTERFACE::PIECE_EMPTY,         INTERFACE::NUM_PIECE_TYPES,
    INTERFACE::NUM_PIECE_TYPES,     INTERFACE::NUM_PIECE_TYPES,
    INTERFACE::NUM_PIECE_TYPES,     INTERFACE::NUM_PIECE_TYPES,
    INTERFACE::NUM_PIECE_TYPES,     INTERFACE::NUM_PIECE_TYPES,

    INTERFACE::PIECE_BLACK_PAWN,    INTERFACE::PIECE_BLACK_BISHOP,
    INTERFACE::PIECE_BLACK_ROOK,    INTERFACE::PIECE_BLACK_KING,
    INTERFACE::PIECE_BLACK_GOLD,    INTERFACE::NUM_PIECE_TYPES,
    INTERFACE::NUM_PIECE_TYPES,     INTERFACE::NUM_PIECE_TYPES,

    INTERFACE::PIECE_WHITE_PAWN,    INTERFACE::PIECE_WHITE_BISHOP,
    INTERFACE::PIECE_WHITE_ROOK,    INTERFACE::PIECE_WHITE_KING,
    INTERFACE::PIECE_WHITE_GOLD,    INTERFACE::NUM_PIECE_TYPES,
    INTERFACE::NUM_PIECE_TYPES,     INTERFACE::NUM_PIECE_TYPES,

    INTERFACE::NUM_PIECE_TYPES
};

}   //  End of (Unnamed) namespace.

//========================================================================
//
//    BoardState  class.
//

//========================================================================
//
//    Constructor(s) and Destructor.
//

//----------------------------------------------------------------
//    インスタンスを初期化する
//  （コンストラクタ）。
//

BoardState::BoardState()
{
}

//----------------------------------------------------------------
//    インスタンスを破棄する
//  （デストラクタ）。
//

BoardState::~BoardState()
{
}

//========================================================================
//
//    Public Member Functions.
//

//----------------------------------------------------------------
//    盤面を初期状態に設定する。
//

ErrCode
BoardState::resetGameBoard()
{
    for ( int y = 0; y < GPOS_NUM_ROWS; ++ y ) {
        for ( int x = 0; x < GPOS_NUM_COLS; ++ x ) {
            this->m_bsField[y][x]   = FIELD_EMPTY_SQUARE;
        }
    }

    this->m_bsField[GPOS_ROW_1][GPOS_COL_A] = FIELD_WHITE_ROOK;
    this->m_bsField[GPOS_ROW_1][GPOS_COL_B] = FIELD_WHITE_KING;
    this->m_bsField[GPOS_ROW_1][GPOS_COL_C] = FIELD_WHITE_BISHOP;
    this->m_bsField[GPOS_ROW_2][GPOS_COL_B] = FIELD_WHITE_PAWN;

    this->m_bsField[GPOS_ROW_3][GPOS_COL_B] = FIELD_BLACK_PAWN;
    this->m_bsField[GPOS_ROW_4][GPOS_COL_A] = FIELD_BLACK_BISHOP;
    this->m_bsField[GPOS_ROW_4][GPOS_COL_B] = FIELD_BLACK_KING;
    this->m_bsField[GPOS_ROW_4][GPOS_COL_C] = FIELD_BLACK_ROOK;

    for ( int hp = 0; hp < FIELD_WALL_SQUARE; ++ hp ) {
        this->m_nHands[hp]  = 0;
    }

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    現在の盤面を取得して、表示用バッファにコピーする。
//

ErrCode
BoardState::copyToViewBuffer(
        INTERFACE::ViewBuffer  &bufView)  const
{
    using   namespace   INTERFACE;

    for ( int y = 0; y < POS_NUM_ROWS; ++ y ) {
        for ( int x = 0; x < POS_NUM_COLS; ++ x ) {
            const   FieldConst  fc  = this->m_bsField[y + 1][x + 1];
            bufView.piBoard[y * POS_NUM_COLS + x]   = s_tblPieceConv[fc];
        }
    }

    for ( int hp = INTERFACE::PIECE_BLACK_PAWN;
            hp <= INTERFACE::PIECE_BLACK_GOLD; ++ hp )
    {
        const  int  hs  = hp + FIELD_BLACK_PAWN - INTERFACE::PIECE_BLACK_PAWN;
        bufView.nHands[hp]  = this->m_nHands[hs];
    }

    for ( int hp = INTERFACE::PIECE_WHITE_PAWN;
            hp <= INTERFACE::PIECE_WHITE_GOLD; ++ hp )
    {
        const  int  hs  = hp + FIELD_WHITE_PAWN - INTERFACE::PIECE_WHITE_PAWN;
        bufView.nHands[hp]  = this->m_nHands[hs];
    }


    return ( ERR_SUCCESS );
}

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  INTERFACE
DSHOGI_NAMESPACE_END
