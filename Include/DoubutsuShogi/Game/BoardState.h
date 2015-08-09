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
**      An Interface of BoardState class.
**
**      @file       Game/BoardState.h
**/

#if !defined( DSHOGI_GAME_INCLUDED_BOARD_STATE_H )
#    define   DSHOGI_GAME_INCLUDED_BOARD_STATE_H

#include    "DoubutsuShogi/Common/DoubutsuShogiTypes.h"

#include    "InternalTypes.h"

#include    "DoubutsuShogi/Interface/ViewBuffer.h"

DSHOGI_NAMESPACE_BEGIN
namespace  GAME  {

//========================================================================
//
//    BoardState  class.
//
/**
**    盤面の状態を管理するクラス。
**/

class  BoardState
{

//========================================================================
//
//    Constructor(s) and Destructor.
//
public:

    //----------------------------------------------------------------
    /**   インスタンスを初期化する
    **  （コンストラクタ）。
    **
    **/
    BoardState();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    ~BoardState();

//========================================================================
//
//    Public Member Functions.
//
public:

    //----------------------------------------------------------------
    /**   盤面を初期状態に設定する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    resetGameBoard();

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   現在の盤面を取得して、表示用バッファにコピーする。
    **
    **  @param[out] bufView   表示用バッファ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    copyToViewBuffer(
            INTERFACE::ViewBuffer  &bufView)  const;

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//
private:

    /**   盤上の状態。  **/
    FieldConst      m_bsField[GPOS_NUM_ROWS][GPOS_NUM_COLS];

    /**   持ち駒の数。  **/
    int             m_nHands [FIELD_WALL_SQUARE];

//========================================================================
//
//    Other Features.
//
private:

public:
    //  テストクラス。  //
    friend  class   BoardStateTest;
};

}   //  End of namespace  GAME
DSHOGI_NAMESPACE_END

#endif
