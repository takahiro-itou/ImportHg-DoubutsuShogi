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

#include    <stdexcept>

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
s_tblPosColConv[]   =
{
    GPOS_COL_A,  GPOS_COL_B,  GPOS_COL_C
};

constexpr   GuardPosRow
s_tblPosRowConv[]   =
{
    GPOS_ROW_1,  GPOS_ROW_2,  GPOS_ROW_3,  GPOS_ROW_4
};

constexpr   FieldConst
s_tblHandConv[INTERFACE::NUM_PIECE_TYPES]   =
{
    FIELD_EMPTY_SQUARE,
    FIELD_BLACK_PAWN,   FIELD_BLACK_BISHOP,
    FIELD_BLACK_ROOK,   FIELD_BLACK_KING,
    FIELD_BLACK_GOLD,

    FIELD_WHITE_PAWN,   FIELD_WHITE_BISHOP,
    FIELD_WHITE_ROOK,   FIELD_WHITE_KING,
    FIELD_WHITE_GOLD
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
        const  PosCol       xOldCol,
        const  PosRow       yOldRow,
        const  PosCol       xNewCol,
        const  PosRow       yNewRow,
        const  PromoteFlag  flgProm)  const
{
    return ( encodeMoveAction(
                     this->m_ibState,
                     xOldCol, yOldRow, xNewCol, yNewRow,
                     flgProm) );
}

//----------------------------------------------------------------
//    駒を移動する指し手を内部形式に変換する。
//

const   BoardState::ActionData
BoardState::encodeMoveAction(
        const  InternBoard  curStat,
        const  PosCol       xOldCol,
        const  PosRow       yOldRow,
        const  PosCol       xNewCol,
        const  PosRow       yNewRow,
        const  PromoteFlag  flgProm)
{
    const  GuardPosCol  gOX = s_tblPosColConv[xOldCol];
    const  GuardPosRow  gOY = s_tblPosRowConv[yOldRow];
    const  GuardPosCol  gNX = s_tblPosColConv[xNewCol];
    const  GuardPosRow  gNY = s_tblPosRowConv[yNewRow];
    const  FieldConst   tmp = curStat.m_bsField[gOY][gOX];

    FieldConst  prm = tmp;

    //  成れるかどうかを判定する。  //
    if ( (tmp == FIELD_BLACK_PAWN) && (yNewRow == POS_ROW_1) ) {
        prm = FIELD_BLACK_GOLD;
    } else if ( (tmp == FIELD_WHITE_PAWN) && (yNewRow == POS_ROW_4) ) {
        prm = FIELD_WHITE_GOLD;
    }

    //  成りフラグをチェックする。  //
    if ( flgProm == ACT_NO_PROMOTION ) {
        //  成れる場合でも成らない。    //
        prm = tmp;
    } else if ( flgProm == ACT_PROMOTION ) {
        //  成れない場合にこのフラグが指定された場合はエラー。  //
        if ( prm == tmp ) {
            throw  std::runtime_error("Invalid Promotion");
        }
    } else {
        //  成れる場合には自動で成る。  //
    }

    const  ActionData   act = {
        gOX,    gOY,
        gNX,    gNY,
        curStat.m_bsField[gNY][gNX],
        tmp,
        prm,
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
    return ( encodePutAction(this->m_ibState, xPutCol, yPutRow, pHand) );
}

//----------------------------------------------------------------
//    持ち駒を打つ指し手を内部形式に変換する。
//

const   BoardState::ActionData
BoardState::encodePutAction(
        const  InternBoard  curStat,
        const  PosCol       xPutCol,
        const  PosRow       yPutRow,
        const  PieceIndex   pHand)
{
    const  FieldConst   fcHand  = s_tblHandConv[pHand];

    const  ActionData   act = {
        GPOS_COL_L,
        GPOS_ROW_U,
        s_tblPosColConv[xPutCol],
        s_tblPosRowConv[yPutRow],
        FIELD_EMPTY_SQUARE,
        FIELD_EMPTY_SQUARE,
        fcHand,
        fcHand
    };

    return ( act );
}

//----------------------------------------------------------------
//    指定した指し手が合法手か判定する。
//

ErrCode
BoardState::isLegalAction(
        const  ActionData   actData)  const
{
    return ( isLegalAction(this->m_ibState, actData) );
}

//----------------------------------------------------------------
//    指定した指し手が合法手か判定する。
//

ErrCode
BoardState::isLegalAction(
        const  InternBoard  curStat,
        const  ActionData   actData)
{
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    指定した指し手を取り消して盤面を戻す。
//

const   BoardState::InternBoard
BoardState::playBackward(
        const  ActionData   actBwd)
{
    return ( this->m_ibState );
}

//----------------------------------------------------------------
//    指定した指し手で盤面を進める。
//

const   BoardState::InternBoard
BoardState::playForward(
        const  ActionData   actFwd)
{
    InternBoard  & ibSt = (this->m_ibState);

    //  移動元のマスを空きマスにする。  //
    ibSt.m_bsField[actFwd.yOldRow][actFwd.xOldCol]  = FIELD_EMPTY_SQUARE;

    //  移動先に指定した駒を書き込む。  //
    ibSt.m_bsField[actFwd.yNewRow][actFwd.xNewCol]  = actFwd.fpAfter;

    //  取った相手の駒を持ち駒にする。  //
    if ( actFwd.fpCatch != FIELD_EMPTY_SQUARE ) {
        ++ ibSt.m_nHands[(actFwd.fpCatch ^ FIELD_WALL_SQUARE)];
    }

    //  駒を打つ場合は持ち駒を減らす。  //
    if ( actFwd.putHand != FIELD_EMPTY_SQUARE ) {
        -- ibSt.m_nHands[actFwd.putHand];
    }

    return ( this->m_ibState );
}

//----------------------------------------------------------------
//    盤面を初期状態に設定する。
//

ErrCode
BoardState::resetGameBoard()
{
    return ( resetGameBoard(&(this->m_ibState)) );
}

//----------------------------------------------------------------
//    盤面を初期状態に設定する。
//

ErrCode
BoardState::resetGameBoard(
        InternBoard  *  pCurStat)
{
    for ( int yr = 0; yr < GPOS_NUM_ROWS; ++ yr ) {
        for ( int xc = 0; xc < GPOS_NUM_COLS; ++ xc ) {
            pCurStat->m_bsField[yr][xc] = FIELD_EMPTY_SQUARE;
        }
    }

    pCurStat->m_bsField[GPOS_ROW_1][GPOS_COL_A] = FIELD_WHITE_ROOK;
    pCurStat->m_bsField[GPOS_ROW_1][GPOS_COL_B] = FIELD_WHITE_KING;
    pCurStat->m_bsField[GPOS_ROW_1][GPOS_COL_C] = FIELD_WHITE_BISHOP;
    pCurStat->m_bsField[GPOS_ROW_2][GPOS_COL_B] = FIELD_WHITE_PAWN;

    pCurStat->m_bsField[GPOS_ROW_3][GPOS_COL_B] = FIELD_BLACK_PAWN;
    pCurStat->m_bsField[GPOS_ROW_4][GPOS_COL_A] = FIELD_BLACK_BISHOP;
    pCurStat->m_bsField[GPOS_ROW_4][GPOS_COL_B] = FIELD_BLACK_KING;
    pCurStat->m_bsField[GPOS_ROW_4][GPOS_COL_C] = FIELD_BLACK_ROOK;

    for ( int hp = 0; hp < FIELD_WALL_SQUARE; ++ hp ) {
        pCurStat->m_nHands[hp]  = 0;
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
    return ( copyToViewBuffer(this->m_ibState, bufView) );
}

//----------------------------------------------------------------
//    現在の盤面を取得して、表示用バッファにコピーする。
//

ErrCode
BoardState::copyToViewBuffer(
        const  InternBoard      curStat,
        INTERFACE::ViewBuffer  &bufView)
{
    using   namespace   INTERFACE;

    for ( int y = 0; y < POS_NUM_ROWS; ++ y ) {
        for ( int x = 0; x < POS_NUM_COLS; ++ x ) {
            const   FieldConst  fc  = curStat.m_bsField[y + 1][x + 1];
            bufView.piBoard[y * POS_NUM_COLS + x]   = s_tblPieceConv[fc];
        }
    }

    for ( int hp = INTERFACE::PIECE_BLACK_PAWN;
            hp <= INTERFACE::PIECE_BLACK_GOLD; ++ hp )
    {
        const  int  hs  = hp + FIELD_BLACK_PAWN - INTERFACE::PIECE_BLACK_PAWN;
        bufView.nHands[hp]  = curStat.m_nHands[hs];
    }

    for ( int hp = INTERFACE::PIECE_WHITE_PAWN;
            hp <= INTERFACE::PIECE_WHITE_GOLD; ++ hp )
    {
        const  int  hs  = hp + FIELD_WHITE_PAWN - INTERFACE::PIECE_WHITE_PAWN;
        bufView.nHands[hp]  = curStat.m_nHands[hs];
    }

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    現在の局面を設定する。
//

ErrCode
BoardState::setCurrentState(
        const  InternBoard  curStat)
{
    this->m_ibState = curStat;
    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    現在の局面を設定する。
//

ErrCode
BoardState::setCurrentState(
        const  INTERFACE::ViewBuffer  & bufView)
{
    InternBoard     curStat;

    resetGameBoard(&curStat);

    return ( setCurrentState(curStat) );
}

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  INTERFACE
DSHOGI_NAMESPACE_END
