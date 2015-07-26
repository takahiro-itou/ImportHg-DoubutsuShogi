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

#include    <iostream>

using   namespace   DSHOGI_NAMESPACE;
using   namespace   DSHOGI_NAMESPACE::GAME;

int  main(int argc, char * argv[])
{
    GameController  gc;

    gc.resetGameBoard();
    gc.writeToStream(std::cout) << std::endl;

    return ( 0 );
}
