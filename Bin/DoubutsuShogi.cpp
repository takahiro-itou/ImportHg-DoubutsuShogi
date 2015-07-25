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
**      アプリケーション本体。
**
**      @file   DoubutsuShogi.cpp
**/

#include    "DoubutsuShogi/Game/GameController.h"

#include    <iomanip>
#include    <iostream>

using   namespace   DSHOGI_NAMESPACE;
using   namespace   DSHOGI_NAMESPACE::GAME;

int  main(int argc, char * argv[])
{
    GameController  gc;

    gc.resetGameBoard();
    gc.writeToStream(std::cout) << std::endl;

    //  テスト。ヒヨコを取ってみる。    //
    GameController::BoardState  bs  = gc.getCurrentBoard();
    GameController::ActionData  act;

    act = GameController::encodeMoveAction(bs, POS_ENC_B3, POS_ENC_B2);
    std::cout   << "指し手：B3,B2 = 0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << act << std::endl;

    bs  = gc.playForward(act);
    gc.writeToStream(std::cout) << std::endl;

    //  テスト。ヒヨコを成ってみる（動きのルールは無視）。  //
    act = GameController::encodeMoveAction(bs, POS_ENC_B2, POS_ENC_A1);
    std::cout   << "指し手：B3,B2 = 0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << act << std::endl;

    bs  = gc.playForward(act);
    gc.writeToStream(std::cout) << std::endl;

    return ( 0 );
}
