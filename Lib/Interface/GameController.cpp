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
**    手番を交代する処理に使うテーブル。
**/

constexpr   TurnPlayer
s_tblNextPlayerTable[]  = {
    TURN_2ND_PLAYER,
    TURN_1ST_PLAYER
};

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
    : m_gcBoard(),
      m_curMove(),
      m_actList()
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
//    棋譜データを表示用に変換する。
//

ErrCode
GameController::makeActionViewList(
        ActionViewList  &actList)  const
{
    typedef     ActionList::const_iterator  ActIter;

    const  ActionList  &obj = (this->m_actList);

    actList.clear();
    actList.resize(obj.size());

    size_t          idx     = 0;
    const  ActIter  itrEnd  = obj.end();
    for ( ActIter itr = obj.begin(); itr != itrEnd; ++ itr, ++ idx )
    {
        this->m_gcBoard.decodeActionData( *itr, actList[idx] );
    }

    return ( ERR_SUCCESS );
}

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
//    最後の指し手を取り消して盤面を戻す。
//

ErrCode
GameController::playBackward()
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    駒を移動する指し手を入力して盤面を進める。
//

ErrCode
GameController::playMoveAction(
        const  PosCol       xOldCol,
        const  PosRow       yOldRow,
        const  PosCol       xNewCol,
        const  PosRow       yNewRow,
        const  PromoteFlag  flgProm)
{
    const  GAME::BoardState::ActionData
        act = this->m_gcBoard.encodeMoveAction(
                    xOldCol, yOldRow, xNewCol, yNewRow, flgProm);

    const  ErrCode  retErr  = this->m_gcBoard.isLegalAction(act);
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    this->m_gcBoard.playForward(act);
    this->m_actList.push_back  (act);
    this->m_curMove = s_tblNextPlayerTable[this->m_curMove];

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    持ち駒を打つ指し手を入力して盤面を進める。
//

ErrCode
GameController::playPutAction(
        const  PosCol       xPutCol,
        const  PosRow       yPutRow,
        const  PieceIndex   pHand)
{
    const   GAME::BoardState::ActionData
        act = this->m_gcBoard.encodePutAction(
                    xPutCol, yPutRow, pHand);

    const  ErrCode  retErr  = this->m_gcBoard.isLegalAction(act);
    if ( retErr != ERR_SUCCESS ) {
        return ( retErr );
    }

    this->m_gcBoard.playForward(act);
    this->m_actList.push_back  (act);
    this->m_curMove = s_tblNextPlayerTable[this->m_curMove];

    return ( ERR_SUCCESS );
}

//----------------------------------------------------------------
//    盤面を初期状態に設定する。
//

ErrCode
GameController::resetGameBoard()
{
    this->m_curMove = TURN_1ST_PLAYER;
    this->m_actList.clear();
    return ( this->m_gcBoard.resetGameBoard() );
}

//----------------------------------------------------------------
//    現在の盤面を出力する。
//

std::ostream  &
GameController::writeToStream(
        std::ostream  & strOut)  const
{
    ViewBuffer      bufView;

    writeToViewBuffer( bufView );

    strOut  << "後持：";
    for ( int c = PIECE_WHITE_PAWN; c < PIECE_WHITE_GOLD; ++ c ) {
        const  int  numHand = bufView.nHands[c];
        if ( numHand > 0 ) {
            strOut  << s_tblHandName[c][numHand];
        }
    }

    strOut  << "\n   A     B     C";
    strOut  << "\n┌──┬──┬──┐\n";
    for ( int y = 0; y < POS_NUM_ROWS; ++ y ) {
        if ( y > 0 ) {
            strOut  << "├──┼──┼──┤\n";
        }
        for ( int x = 0; x < POS_NUM_COLS; ++ x ) {
            const  int  posIdx  = s_tblPosEnc[y][x];
            const  int  nPiece  = (bufView.piBoard[posIdx]);
            strOut  << "│" << s_tblPieceName[nPiece];
        }
        strOut  << "│" << (y + 1) << "\n";
    }
    strOut  << "└──┴──┴──┘\n";

    strOut  << "先持：";
    for ( int c = PIECE_BLACK_PAWN; c < PIECE_BLACK_GOLD; ++ c ) {
        const  int  numHand = bufView.nHands[c];
        if ( numHand > 0 ) {
            strOut  << s_tblHandName[c][numHand];
        }
    }

    return ( strOut );
}

//----------------------------------------------------------------
//    現在の盤面を表示用バッファにコピーする。
//

ErrCode
GameController::writeToViewBuffer(
        ViewBuffer  &bufView)  const
{
    return ( this->m_gcBoard.copyToViewBuffer(bufView) );
}

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//

//----------------------------------------------------------------
//    手番を持っているプレーヤーを設定する。
//

ErrCode
GameController::setTurnPlayer(
        const  TurnPlayer   curMove)
{
    this->m_curMove = curMove;
    return ( ERR_SUCCESS );
}

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  INTERFACE
DSHOGI_NAMESPACE_END
