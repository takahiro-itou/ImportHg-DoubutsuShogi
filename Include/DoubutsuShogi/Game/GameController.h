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
//    For Internal Use Only.
//

//========================================================================
//
//    Member Variables.
//
private:

    /**   現在の局面。  **/
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
