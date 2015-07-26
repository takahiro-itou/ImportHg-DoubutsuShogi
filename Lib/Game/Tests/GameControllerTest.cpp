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
**      An Implementation of Test Case 'GameController'.
**
**      @file   Game/Tests/GameControllerTest.cpp
**/

#include    "DoubutsuShogi/Game/GameController.h"

#include    <iomanip>
#include    <iostream>

DSHOGI_NAMESPACE_BEGIN
namespace  GAME  {

int  testGameController()
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
    gc.writeToStream(std::cout) << "\n" << std::endl;

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
    gc.writeToStream(std::cout) << "\n" << std::endl;

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
    gc.writeToStream(std::cout) << "\n" << std::endl;

    //  テスト。    //
    act = GameController::encodeMoveAction(bs, POS_ENC_C1, POS_ENC_C4);
    std::cout   << "現在局面：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << bs  << std::endl;
    std::cout   << "指し手  ：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << act << " (C1, C4)" << std::endl;
    bs  = gc.playForward(act);
    std::cout   << "現在局面：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << bs  << std::endl;
    gc.writeToStream(std::cout) << "\n" << std::endl;

    //  テスト。    //
    act = GameController::encodePutAction(bs, PIECE_S_ROOK, POS_ENC_C3);
    std::cout   << "現在局面：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << bs  << std::endl;
    std::cout   << "指し手  ：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << act << " (.R, C3)" << std::endl;
    bs  = gc.playForward(act);
    std::cout   << "現在局面：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << bs  << std::endl;
    gc.writeToStream(std::cout) << "\n" << std::endl;

    //  テスト。    //
    act = GameController::encodeMoveAction(bs, POS_ENC_B4, POS_ENC_C3);
    std::cout   << "現在局面：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << bs  << std::endl;
    std::cout   << "指し手  ：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << act << " (B4, C3)" << std::endl;
    bs  = gc.playForward(act);
    std::cout   << "現在局面：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << bs  << std::endl;
    gc.writeToStream(std::cout) << "\n" << std::endl;

    //  テスト。    //
    act = GameController::encodePutAction(bs, PIECE_F_ROOK, POS_ENC_A2);
    std::cout   << "現在局面：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << bs  << std::endl;
    std::cout   << "指し手  ：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << act << " (.R, A2)" << std::endl;
    bs  = gc.playForward(act);
    std::cout   << "現在局面：0x"
                << std::hex << std::setw(16) << std::setfill('0')
                << bs  << std::endl;
    gc.writeToStream(std::cout) << "\n" << std::endl;

    return ( 0 );
}

}   //  End of namespace  GAME
DSHOGI_NAMESPACE_END

int  main(int argc, char * argv[])
{
    using   namespace   DSHOGI_NAMESPACE;

    return ( GAME::testGameController() );
}
