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

constexpr   GuardPosCol
s_tblPosColConv[] = {
    GPOS_COL_A,  GPOS_COL_B,  GPOS_COL_C
};

constexpr   GuardPosRow
s_tblPosRowConv[] = {
    GPOS_ROW_1,  GPOS_ROW_2,  GPOS_ROW_3,  GPOS_ROW_4
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
    : m_ibState()
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
//    駒を移動する指し手を内部形式に変換する。
//

const   BoardState::ActionData
BoardState::encodeMoveAction(
        const   PosCol  xOldCol,
        const   PosRow  yOldRow,
        const   PosCol  xNewCol,
        const   PosRow  yNewRow,
        const   int     bfProm)  const
{
    const   ActionData  act = {
        s_tblPosColConv[xOldCol],
        s_tblPosRowConv[yOldRow],
        s_tblPosColConv[xNewCol],
        s_tblPosRowConv[yNewRow],
        (bfProm ? 0x04 : 0x00),
        FIELD_EMPTY_SQUARE
    };

    return ( act );
}

//----------------------------------------------------------------
//    持ち駒を打つ指し手を内部形式に変換する。
//

const   BoardState::ActionData
BoardState::encodePutAction(
        const   PosCol      xPutCol,
        const   PosRow      yPutRow,
        const   PieceIndex  pHand)  const
{
    const   ActionData  act = {
    };

    return ( act );
}

//----------------------------------------------------------------
//    指定した指し手を取り消して盤面を戻す。
//

const   BoardState::InternBoard
BoardState::playBackward(
        const   ActionData  actBwd)
{
    return ( this->m_ibState );
}

//----------------------------------------------------------------
//    指定した指し手で盤面を進める。
//

const   BoardState::InternBoard
BoardState::playForward(
        const   ActionData  actFwd)
{
    InternBoard  & ibSt = (this->m_ibState);

    //  移動先にある駒を持ち駒にする。  //
    FieldConst  &
            fAfter  = ibSt.m_bsField[actFwd.yNewRow][actFwd.xNewCol];
    ++ ibSt.m_nHands[ (fAfter ^ FIELD_WALL_SQUARE) ];

    //  移動元の駒を移動先へ書き込む。  //
    if ( actFwd.putHand == FIELD_EMPTY_SQUARE ) {
        //  盤上の駒を移動させる場合。  //
        FieldConst  &
                fBefore = ibSt.m_bsField[actFwd.yOldRow][actFwd.xOldCol];
        fAfter  = fBefore;
        fBefore = FIELD_EMPTY_SQUARE;
    } else {
        //  持ち駒を打った場合の処理。  //
    }

    return ( this->m_ibState );
}

//----------------------------------------------------------------
//    盤面を初期状態に設定する。
//

ErrCode
BoardState::resetGameBoard()
{
    InternBoard  & ibSt = (this->m_ibState);

    for ( int yr = 0; yr < GPOS_NUM_ROWS; ++ yr ) {
        for ( int xc = 0; xc < GPOS_NUM_COLS; ++ xc ) {
            ibSt.m_bsField[yr][xc]  = FIELD_EMPTY_SQUARE;
        }
    }

    ibSt.m_bsField[GPOS_ROW_1][GPOS_COL_A]  = FIELD_WHITE_ROOK;
    ibSt.m_bsField[GPOS_ROW_1][GPOS_COL_B]  = FIELD_WHITE_KING;
    ibSt.m_bsField[GPOS_ROW_1][GPOS_COL_C]  = FIELD_WHITE_BISHOP;
    ibSt.m_bsField[GPOS_ROW_2][GPOS_COL_B]  = FIELD_WHITE_PAWN;

    ibSt.m_bsField[GPOS_ROW_3][GPOS_COL_B]  = FIELD_BLACK_PAWN;
    ibSt.m_bsField[GPOS_ROW_4][GPOS_COL_A]  = FIELD_BLACK_BISHOP;
    ibSt.m_bsField[GPOS_ROW_4][GPOS_COL_B]  = FIELD_BLACK_KING;
    ibSt.m_bsField[GPOS_ROW_4][GPOS_COL_C]  = FIELD_BLACK_ROOK;

    for ( int hp = 0; hp < FIELD_WALL_SQUARE; ++ hp ) {
        ibSt.m_nHands[hp]   = 0;
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

    const  InternBoard  & ibSt  = (this->m_ibState);

    for ( int y = 0; y < POS_NUM_ROWS; ++ y ) {
        for ( int x = 0; x < POS_NUM_COLS; ++ x ) {
            const   FieldConst  fc  = ibSt.m_bsField[y + 1][x + 1];
            bufView.piBoard[y * POS_NUM_COLS + x]   = s_tblPieceConv[fc];
        }
    }

    for ( int hp = INTERFACE::PIECE_BLACK_PAWN;
            hp <= INTERFACE::PIECE_BLACK_GOLD; ++ hp )
    {
        const  int  hs  = hp + FIELD_BLACK_PAWN - INTERFACE::PIECE_BLACK_PAWN;
        bufView.nHands[hp]  = ibSt.m_nHands[hs];
    }

    for ( int hp = INTERFACE::PIECE_WHITE_PAWN;
            hp <= INTERFACE::PIECE_WHITE_GOLD; ++ hp )
    {
        const  int  hs  = hp + FIELD_WHITE_PAWN - INTERFACE::PIECE_WHITE_PAWN;
        bufView.nHands[hp]  = ibSt.m_nHands[hs];
    }

    return ( ERR_SUCCESS );
}

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  INTERFACE
DSHOGI_NAMESPACE_END
