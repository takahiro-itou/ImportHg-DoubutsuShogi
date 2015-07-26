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
    std::cout   << "現在局面：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << bs  << std::endl;
    std::cout   << "指し手  ：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << act << " (B3, B2)" << std::endl;
    bs  = gc.playForward(act);
    std::cout   << "現在局面：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << bs  << std::endl;
    gc.writeToStream(std::cout) << std::endl;

    //  テスト。ヒヨコを成ってみる（動きのルールは無視）。  //
    act = GameController::encodeMoveAction(bs, POS_ENC_B2, POS_ENC_A1);
    std::cout   << "現在局面：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << bs  << std::endl;
    std::cout   << "指し手  ：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << act << " (B2, A1)" << std::endl;
    bs  = gc.playForward(act);
    std::cout   << "現在局面：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << bs  << std::endl;
    gc.writeToStream(std::cout) << std::endl;

    //  テスト。ヒヨコを打ってみる。    //
    act = GameController::encodePutAction(bs, PIECE_F_PAWN, POS_ENC_B3);
    std::cout   << "現在局面：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << bs  << std::endl;
    std::cout   << "指し手  ：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << act << " (.P, B3)" << std::endl;
    bs  = gc.playForward(act);
    std::cout   << "現在局面：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << bs  << std::endl;
    gc.writeToStream(std::cout) << std::endl;

    return ( 0 );
}
