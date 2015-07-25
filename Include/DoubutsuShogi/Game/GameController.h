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
**      @file   Game/GameController.h
**/

#if !defined( DSHOGI_GAME_INCLUDED_GAME_CONTROLELR_H )
#    define   DSHOGI_GAME_INCLUDED_GAME_CONTROLELR_H

#include    "DoubutsuShogi/Game/DoubutsuShogiTypes.h"

#include    <iosfwd>

DSHOGI_NAMESPACE_BEGIN
namespace  GAME  {

//========================================================================
//
//    GameController  class.
//
/**
**    ゲームを管理するクラス。
**/

class  GameController
{

//========================================================================
//
//    Type Definitions.
//
public:

    /**
    **    盤面の状態を管理する型。
    **/
    typedef     uint64_t        BoardState;

    /**
    **    指し手（棋譜）の壱手分を管理する型。
    **/
    typedef     uint64_t        ActionData;

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
    ~GameController();

//========================================================================
//
//    Public Member Functions.
//
public:

    //----------------------------------------------------------------
    /**   入力した指し手を内部形式に変換する。
    **
    **  @param [in] bsCur     現在の盤面。
    **  @param [in] posOld    移動する駒の位置。
    **  @param [in] posNew    移動先の位置。
    **  @return     指し手データの内部形式。
    **/
    static  const   ActionData
    encodeMoveAction(
            const   BoardState  bsCur,
            const   PosEnc      posOld,
            const   PosEnc      posNew);

    //----------------------------------------------------------------
    /**   入力した指し手を内部形式に変換する。
    **
    **  @param [in] bsCur     現在の盤面。
    **  @param [in] hPiece    持ち駒の種類。
    **  @param [in] posPut    駒を打つ位置。
    **  @return     指し手データの内部形式。
    **/
    static  const   ActionData
    encodePutAction(
            const   BoardState  bsCur,
            const   PieceIndex  hPiece,
            const   PosEnc      posPut);

    //----------------------------------------------------------------
    /**   指定した指し手を取り消して盤面を戻す。
    **
    **  @param [in] actBwd    指し手データの内部形式。
    **  @return     戻した盤面を返す。
    **/
    const   BoardState
    playBackward(
            const   ActionData  actBwd);

    //----------------------------------------------------------------
    /**   指定した指し手で盤面を進める。
    **
    **  @param [in] actFwd    指し手データの内部形式。
    **  @return     進めた盤面を返す。
    **/
    const   BoardState
    playForward(
            const   ActionData  actFwd);

    //----------------------------------------------------------------
    /**   盤面を初期状態に設定する。
    **
    **  @return     void.
    **/
    void
    resetGameBoard();

    //----------------------------------------------------------------
    /**   現在の盤面を出力する。
    **
    **  @param[out] strOut    出力ストリーム。
    **  @return     出力後のストリームの参照。
    **/
    std::ostream  &
    writeToStream(
            std::ostream  & strOut)  const;

//========================================================================
//
//    Accessors.
//
public:

    //----------------------------------------------------------------
    /**   現在の盤面を取得する。
    **
    **  @return     現在の盤面の状態。
    **/
    const   BoardState
    getCurrentBoard()  const
    {
        return ( this->m_gsBoard );
    }

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
    BoardState      m_gsBoard;

//========================================================================
//
//    Other Features.
//
private:

public:
    //  テストクラス。  //
    friend  class   GameControllerTest;
};

}   //  End of namespace  GAME
DSHOGI_NAMESPACE_END

#endif
