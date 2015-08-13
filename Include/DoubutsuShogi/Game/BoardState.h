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
//    Internal Types.
//
public:

    /**   盤面データの内部形式の型。    **/
    struct  InternBoard
    {
        /**   盤上の状態。  **/
        FieldConst      m_bsField[GPOS_NUM_ROWS][GPOS_NUM_COLS];

        /**   持ち駒の数。  **/
        int             m_nHands [FIELD_WALL_SQUARE];
    };

    /**   指し手データの内部形式の型。  **/
    struct  ActionData
    {
        GuardPosCol     xOldCol;
        GuardPosRow     yOldRow;
        GuardPosCol     xNewCol;
        GuardPosRow     yNewRow;
        FieldConst      fpCatch;    /**<  捕まえた駒。  **/
        FieldConst      fpMoved;    /**<  移動した駒。  **/
        FieldConst      fpAfter;    /**<  移動後成り。  **/
        FieldConst      putHand;
    };

private:
    /**   駒の種類を表す定数。  **/
    typedef     INTERFACE::PieceIndex   PieceIndex;

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
    /**   指し手の内部形式を表示用データに変換する。
    **
    **  @param [in] actData   指し手データの内部形式。
    **  @param[out] actView   表示用データを書き込む領域。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    decodeActionData(
            const  ActionData      &actData,
            INTERFACE::ActionView  &actView);

    //----------------------------------------------------------------
    /**   駒を移動する指し手を内部形式に変換する。
    **
    **  @param [in] xOldCol   移動元の座標（横方向）。
    **  @param [in] yOldRow   移動元の座標（縦方向）。
    **  @param [in] xNewCol   移動先の座標（横方向）。
    **  @param [in] yNewRow   移動先の座標（縦方向）。
    **  @param [in] flgProm   駒の成り、又は、不成り。
    **  @return     指し手の内部形式。
    **/
    const   ActionData
    encodeMoveAction(
            const  PosCol       xOldCol,
            const  PosRow       yOldRow,
            const  PosCol       xNewCol,
            const  PosRow       yNewRow,
            const  PromoteFlag  flgProm)  const;

    //----------------------------------------------------------------
    /**   駒を移動する指し手を内部形式に変換する。
    **
    **  @param [in] curStat   現在の盤面データ。
    **  @param [in] xOldCol   移動元の座標（横方向）。
    **  @param [in] yOldRow   移動元の座標（縦方向）。
    **  @param [in] xNewCol   移動先の座標（横方向）。
    **  @param [in] yNewRow   移動先の座標（縦方向）。
    **  @param [in] flgProm   駒の成り、又は、不成り。
    **  @return     指し手の内部形式。
    **/
    static  const   ActionData
    encodeMoveAction(
            const  InternBoard  &curStat,
            const  PosCol       xOldCol,
            const  PosRow       yOldRow,
            const  PosCol       xNewCol,
            const  PosRow       yNewRow,
            const  PromoteFlag  flgProm);

    //----------------------------------------------------------------
    /**   持ち駒を打つ指し手を内部形式に変換する。
    **
    **  @param [in] xPutCol   駒を打つ座標（横方向）。
    **  @param [in] yPutRow   駒を打つ座標（縦方向）。
    **  @param [in] pHand     打つ駒の種類。
    **  @return     指し手の内部形式。
    **/
    const   ActionData
    encodePutAction(
            const  PosCol       xPutCol,
            const  PosRow       yPutRow,
            const  PieceIndex   pHand)  const;

    //----------------------------------------------------------------
    /**   持ち駒を打つ指し手を内部形式に変換する。
    **
    **  @param [in] curStat   現在の盤面データ。
    **  @param [in] xPutCol   駒を打つ座標（横方向）。
    **  @param [in] yPutRow   駒を打つ座標（縦方向）。
    **  @param [in] pHand     打つ駒の種類。
    **  @return     指し手の内部形式。
    **/
    static  const   ActionData
    encodePutAction(
            const  InternBoard  &curStat,
            const  PosCol       xPutCol,
            const  PosRow       yPutRow,
            const  PieceIndex   pHand);

    //----------------------------------------------------------------
    /**   指定した指し手が合法手か判定する。
    **
    **  @param [in] actData   指し手データの内部形式。
    **  @retval     ERR_SUCCESS           合法手。
    **  @retval     ERR_ILLEGAL_ACTION    非合法手。
    **/
    ErrCode
    isLegalAction(
            const  ActionData   &actData)  const;

    //----------------------------------------------------------------
    /**   指定した指し手が合法手か判定する。
    **
    **  @param [in] curStat   現在の盤面データ。
    **  @param [in] actData   指し手データの内部形式。
    **  @retval     ERR_SUCCESS           合法手。
    **  @retval     ERR_ILLEGAL_ACTION    非合法手。
    **/
    static  ErrCode
    isLegalAction(
            const  InternBoard  &curStat,
            const  ActionData   &actData);

    //----------------------------------------------------------------
    /**   指定した指し手を取り消して盤面を戻す。
    **
    **  @param [in] actBwd    指し手データの内部形式。
    **  @return     戻した盤面を返す。
    **/
    const   InternBoard
    playBackward(
            const  ActionData   &actBwd);

    //----------------------------------------------------------------
    /**   指定した指し手で盤面を進める。
    **
    **  @param [in] actFwd    指し手データの内部形式。
    **  @return     進めた盤面を返す。
    **/
    const   InternBoard
    playForward(
            const  ActionData   &actFwd);

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

    //----------------------------------------------------------------
    /**   盤面を初期状態に設定する。
    **
    **  @param[out] pCurStat    盤面データを書き込む領域。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    resetGameBoard(
            InternBoard  *  pCurStat);

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

    //----------------------------------------------------------------
    /**   現在の盤面を取得して、表示用バッファにコピーする。
    **
    **  @param [in] curStat   現在の盤面データ。
    **  @param[out] bufView   表示用バッファ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    static  ErrCode
    copyToViewBuffer(
            const  InternBoard     &curStat,
            INTERFACE::ViewBuffer  &bufView);

    //----------------------------------------------------------------
    /**   現在の盤面を内部形式で取得する。
    **
    **  @return     現在の盤面の状態。
    **/
    const   InternBoard
    getCurrentState()  const;

    //----------------------------------------------------------------
    /**   現在の局面を設定する。
    **
    **  @param [in] curStat   設定する内容。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setCurrentState(
            const  InternBoard  &curStat);

    //----------------------------------------------------------------
    /**   現在の局面を設定する。
    **
    **  @param [in] curStat   設定する内容。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setCurrentState(
            const  INTERFACE::ViewBuffer  & bufView);

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//
private:

    /**   現在の盤面。  **/
    InternBoard     m_ibState;

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
