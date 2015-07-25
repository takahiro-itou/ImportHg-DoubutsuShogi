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

    POS_NUM_COLS        /**<  列の数。  **/
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

    POS_NUM_ROWS        /**<  行の数。  **/
};


/**
**    盤面の座標を表す列挙型。
**/

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

    POS_MATRIX_SIZE     /**<  盤上のマスの数。  **/
};

/**
**    盤面の座標を内部形式に変換した定数。
**/

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

/**
**    駒の種類を表す定数。
**/

enum  PieceIndex
{
    PIECE_F_PAWN    = 0,    /**<  先手のヒヨコ。    **/
    PIECE_F_GOLD    = 1,    /**<  先手のニワトリ。  **/
    PIECE_F_BISHOP  = 2,    /**<  先手のゾウ。      **/
    PIECE_F_ROOK    = 4,    /**<  先手のキリン。    **/
    PIECE_F_KING    = 6,    /**<  先手のライオン。  **/

    PIECE_S_PAWN    = 8,    /**<  後手のヒヨコ。    **/
    PIECE_S_GOLD    = 9,    /**<  後手のニワトリ。  **/
    PIECE_S_BISHOP  = 10,   /**<  後手のゾウ。      **/
    PIECE_S_ROOK    = 12,   /**<  後手のキリン。    **/
    PIECE_S_KING    = 14,   /**<  後手のライオン。  **/

    PIECE_EMPTY     = 15,   /**<  空いているマス。  **/

    /**   駒の種類を取得するためのマスク。  **/
    PIECE_TYPE_MASK     = 0xF,

    /**
    **    先手か後手かを判定するためのマスク。
    **/
    PIECE_PLAYER_MASK   = 0x8,

    /**
    **    相手の駒を取った場合に、成り駒を元にもどすためのマスク。
    **/
    PIECE_REVERT_PIECE  = 0xE,

    /**
    **    相手の駒を取った場合に、先手後手を入れ替えて、
    **  自分の駒に変更するための定数。
    **  取った駒の番号に排他的論理輪を取る。
    **/
    PIECE_CHANGE_PLAYER = 0x8
};

DSHOGI_NAMESPACE_END

#endif
