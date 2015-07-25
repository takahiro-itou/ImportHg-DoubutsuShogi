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
**      Type Definitions.
**
**      @file   Game/DoubutsuShogiTypes.h
**/

#if !defined( DSHOGI_GAME_INCLUDED_DOUBUTSU_SHOGI_TYPES_H )
#    define   DSHOGI_GAME_INCLUDED_DOUBUTSU_SHOGI_TYPES_H

#include    "DoubutsuShogi/.Config/DoubutsuShogiSettings.h"

#include    <stdint.h>

DSHOGI_NAMESPACE_BEGIN

//========================================================================
//
//    Type Definitions.
//

/**
**    横方向の座標を表す列挙型。
**/

enum  PosCol
{
    POS_COL_A,
    POS_COL_B,
    POS_COL_C,
    POS_NUM_COLS
};

/**
**    縦方向の座標を表す列挙型。
**/

enum  PosRow
{
    POS_ROW_1,
    POS_ROW_2,
    POS_ROW_3,
    POS_ROW_4,
    POS_NUM_ROWS
};


enum  PosMat
{
    POS_MAT_A1,
    POS_MAT_B1,
    POS_MAT_C1,
    POS_MAT_A2,
    POS_MAT_B2,
    POS_MAT_C2,
    POS_MAT_A3,
    POS_MAT_B3,
    POS_MAT_C3,
    POS_MAT_A4,
    POS_MAT_B4,
    POS_MAT_C4,
    POS_MATRIX_SIZE
};

enum  PosEnc
{
    POS_ENC_A1,
    POS_ENC_C1,
    POS_ENC_C4,
    POS_ENC_A4,
    POS_ENC_A2,
    POS_ENC_C2,
    POS_ENC_C3,
    POS_ENC_A3,
    POS_ENC_B1,
    POS_ENC_B2,
    POS_ENC_B4,
    POS_ENC_B3,
    POS_ENCTABLE_SIZE
};

DSHOGI_NAMESPACE_END

#endif