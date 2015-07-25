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

constexpr   const   char  *
s_tblHandName[8]    = {
    "ヒ",   "ヒ",   "ゾ",   "ゾ",   "キ",   "キ",   "ラ",   "ラ"
};

//----------------------------------------------------------------
/**   配列の要素数を返す関数。
**
**/

template  <typename  T,  size_t  N>
const   size_t
getArraySize(
        const  T  (&) [N])
{
    return ( N );
}

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
//    入力した指し手を内部形式に変換する。
//

const   GameController::ActionData
GameController::encodeMoveAction(
        const   BoardState  bsCur,
        const   PosEnc      posOld,
        const   PosEnc      posNew)
{
    const   ActionData  piMove  = (bsCur >> (posOld * 4)) & PIECE_TYPE_MASK;
    const   ActionData  piCapt  = (bsCur >> (posNew * 4)) & PIECE_TYPE_MASK;

    ActionData  retAct  = 0;
    retAct  |= ((PIECE_EMPTY ^ piMove) << (posOld * 4));
    retAct  |= ((piCapt ^ piMove) << (posNew * 4));

    /**
    **  @todo   ヒヨコ不成は、とりあえず考えてない。
    **/
    if ( (piMove == PIECE_F_PAWN)
            && (s_tblPosMap[posNew].second == POS_ROW_1) )
    {
        retAct  ^= ((PIECE_F_PAWN ^ PIECE_F_GOLD) << (posNew * 4));
    } else if ( (piMove == PIECE_S_PAWN)
            && (s_tblPosMap[posNew].second == POS_ROW_4) )
    {
        retAct  ^= ((PIECE_S_PAWN ^ PIECE_S_GOLD) << (posNew * 4));
    }

    if ( piCapt == PIECE_EMPTY ) {
        return ( retAct );
    }

    //  駒を取った時は、持ち駒の増加もエンコードする。  //
    const   ActionData
        piHand  = (piCapt & PIECE_REVERT_PIECE) ^ PIECE_CHANGE_PLAYER;
    const   ActionData  tmp = (bsCur >> (piHand + 47));
    return ( retAct | ((tmp | 0x01) << (piHand + 48)) );
}

//----------------------------------------------------------------
//    入力した指し手を内部形式に変換する。
//

const   GameController::ActionData
GameController::encodePutAction(
        const   BoardState  bsCur,
        const   PieceIndex  hPiece,
        const   PosEnc      posPut)
{
}

//----------------------------------------------------------------
//    指定した指し手を取り消して盤面を戻す。
//

const   GameController::BoardState
GameController::playBackward(
        const   ActionData  actBwd)
{
    return ( this->m_gsBoard ^= actBwd );
}

//----------------------------------------------------------------
//    指定した指し手で盤面を進める。
//

const   GameController::BoardState
GameController::playForward(
        const   ActionData  actFwd)
{
    return ( this->m_gsBoard ^= actFwd );
}

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

    strOut  << "後持：";
    for ( int c = 0; c < 8; ++ c ) {
        if ( (bs >> (56 + c)) & 0x1 ) {
            strOut  << s_tblHandName[c];
        }
    }
    strOut  << "\n┌──┬──┬──┐\n";
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
    strOut  << "└──┴──┴──┘\n";
    strOut  << "先持：";
    for ( int c = 0; c < 8; ++ c ) {
        if ( (bs >> (48 + c)) & 0x1 ) {
            strOut  << s_tblHandName[c];
        }
    }

    return ( strOut );
}

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  GAME
DSHOGI_NAMESPACE_END
