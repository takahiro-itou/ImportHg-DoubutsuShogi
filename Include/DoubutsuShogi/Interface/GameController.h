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
**      An Interface of GameController class.
**
**      @file       Interface/GameController.h
**/

#if !defined( DSHOGI_INTERFACE_INCLUDED_GAME_CONTROLLER_H )
#    define   DSHOGI_INTERFACE_INCLUDED_GAME_CONTROLLER_H

#include    "DoubutsuShogi/Common/DoubutsuShogiTypes.h"

#include    "ViewBuffer.h"

#include    "DoubutsuShogi/Game/BoardState.h"

#include    <iosfwd>
#include    <string>
#include    <vector>

DSHOGI_NAMESPACE_BEGIN
namespace  INTERFACE  {

//----------------------------------------------------------------
/**
**    現在の手番を管理する列挙型。
**/

enum  TurnPlayer
{
    TURN_1ST_PLAYER     = 0,
    TURN_2ND_PLAYER     = 1
};

//========================================================================
//
//    GameController  class.
//
/**
**    ゲームの進行管理するクラス。
**/

class  GameController
{
public:

    typedef     std::vector<ActionView>     ActionViewList;

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
    GameController();

    //----------------------------------------------------------------
    /**   インスタンスを破棄する
    **  （デストラクタ）。
    **
    **/
    virtual  ~GameController();

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
public:

    //----------------------------------------------------------------
    /**   棋譜データを表示用に変換する。
    **
    **  @param[out] actList   棋譜表示用構造体の配列。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    makeActionViewList(
            ActionViewList  &actList)  const;

    //----------------------------------------------------------------
    /**   盤面表示の設定ファイルを開く。
    **
    **  @param [in] sFileName   ファイル名。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    openSettingFile(
            const  std::string  &sFileName);

    //----------------------------------------------------------------
    /**   最後の指し手を取り消して盤面を戻す。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    playBackward();

    //----------------------------------------------------------------
    /**   駒を移動する指し手を入力して盤面を進める。
    **
    **  @param [in] xOldCol   移動元の座標（横方向）。
    **  @param [in] yOldRow   移動元の座標（縦方向）。
    **  @param [in] xNewCol   移動先の座標（横方向）。
    **  @param [in] yNewRow   移動先の座標（縦方向）。
    **  @param [in] flgProm   駒の成り、又は、不成り。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    playMoveAction(
            const  PosCol       xOldCol,
            const  PosRow       yOldRow,
            const  PosCol       xNewCol,
            const  PosRow       yNewRow,
            const  PromoteFlag  flgProm = ACT_AUTO_PROMOTION);

    //----------------------------------------------------------------
    /**   持ち駒を打つ指し手を入力して盤面を進める。
    **
    **  @param [in] xPutCol   駒を打つ座標（横方向）。
    **  @param [in] yPutRow   駒を打つ座標（縦方向）。
    **  @param [in] pHand     打つ駒の種類。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    playPutAction(
            const  PosCol       xPutCol,
            const  PosRow       yPutRow,
            const  PieceIndex   pHand);

    //----------------------------------------------------------------
    /**   盤面を初期状態に設定する。
    **
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    resetGameBoard();

    //----------------------------------------------------------------
    /**   現在の盤面を出力する。
    **
    **  @param[out] strOut    出力ストリーム。
    **  @return     出力後のストリームの参照。
    **/
    virtual  std::ostream  &
    writeToStream(
            std::ostream  & strOut)  const;

    //----------------------------------------------------------------
    /**   現在の盤面を表示用バッファにコピーする。
    **
    **  @param[out] bufView   表示用バッファ。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    virtual  ErrCode
    writeToViewBuffer(
            ViewBuffer  &bufView)  const;

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   手番を持っているプレーヤーを取得する。
    **
    **  @return     現在の手番を返す。
    **/
    TurnPlayer
    getTurnPlayer()  const
    {
        return ( this->m_curMove );
    }

    //----------------------------------------------------------------
    /**   手番を持っているプレーヤーを設定する。
    **
    **  @param [in] curMove   設定する値。
    **  @return     エラーコードを返す。
    **      -   異常終了の場合は、
    **          エラーの種類を示す非ゼロ値を返す。
    **      -   正常終了の場合は、ゼロを返す。
    **/
    ErrCode
    setTurnPlayer(
            const  TurnPlayer   curMove);

//========================================================================
//
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//
private:
    typedef     GAME::BoardState::ActionData    ActionData;
    typedef     std::vector<ActionData>         ActionList;

private:

    /**   盤面の状態。  **/
    GAME::BoardState    m_gcBoard;

    /**   現在の手番。  **/
    TurnPlayer          m_curMove;

    /**   棋譜データ。  **/
    ActionList          m_actList;

//========================================================================
//
//    Other Features.
//
private:

public:
    //  テストクラス。  //
    friend  class   GameControllerTest;
};

}   //  End of namespace  INTERFACE
DSHOGI_NAMESPACE_END

#endif
