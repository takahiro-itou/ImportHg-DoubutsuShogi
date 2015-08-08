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
//    盤面表示の設定ファイルを開く。
//

ErrCode
GameController::openSettingFile(
        const  std::string  &sFileName)
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    盤面を初期状態に設定する。
//

ErrCode
GameController::resetGameBoard()
{
    return ( ERR_FAILURE );
}

//----------------------------------------------------------------
//    現在の盤面を出力する。
//

std::ostream  &
GameController::writeToStream(
        std::ostream  & strOut)  const
{
    return ( strOut );
}

//========================================================================
//
//    Public Member Functions.
//

//========================================================================
//
//    Accessors.
//

//========================================================================
//
//    For Internal Use Only.
//

}   //  End of namespace  INTERFACE
DSHOGI_NAMESPACE_END
