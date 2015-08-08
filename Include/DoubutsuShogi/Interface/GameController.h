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

#include    <iosfwd>
#include    <string>

DSHOGI_NAMESPACE_BEGIN
namespace  INTERFACE  {

//========================================================================
//
//    GameController  class.
//
/**
**    ゲームの進行管理するクラス。
**/

class  GameController
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
    std::ostream  &
    writeToStream(
            std::ostream  & strOut)  const;

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

//========================================================================
//
//    Member Variables.
//

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
