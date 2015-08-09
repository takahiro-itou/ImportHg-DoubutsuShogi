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
**      An Interface of Internal Types.
**
**      @file       Game/InternalTypes.h
**/

#if !defined( DSHOGI_GAME_INCLUDED_INTERNAL_TYPES_H )
#    define   DSHOGI_GAME_INCLUDED_INTERNAL_TYPES_H

#include    "DoubutsuShogi/Common/DoubutsuShogiTypes.h"

DSHOGI_NAMESPACE_BEGIN
namespace  GAME  {

//========================================================================
//
//    Internal Type Definitions.
//

/**
**    盤上の状態を表す定数。
**/

enum  FieldConst
{
    FIELD_EMPTY_SQUARE  = 0x00,     /**<  空いているマス。  **/
    FIELD_BLACK_PIECE   = 0x08,     /**<  先手の駒。        **/
    FIELD_WHITE_PIECE   = 0x10,     /**<  後手の駒。        **/
    FIELD_WALL_SQUARE   = 0x18,     /**<  壁マス（番兵）。  **/

    FIELD_BLACK_PAWN    = 0x08,     /**<  先手のヒヨコ。    **/
    FIELD_BLACK_BISHOP  = 0x09,     /**<  先手のゾウ。      **/
    FIELD_BLACK_ROOK    = 0x0A,     /**<  先手のキリン。    **/
    FIELD_BLACK_KING    = 0x0B,     /**<  先手のライオン。  **/
    FIELD_BLACK_GOLD    = 0x0C,     /**<  先手のニワトリ。  **/

    FIELD_WHITE_PAWN    = 0x10,     /**<  後手のヒヨコ。    **/
    FIELD_WHITE_BISHOP  = 0x11,     /**<  後手のゾウ。      **/
    FIELD_WHITE_ROOK    = 0x12,     /**<  後手のキリン。    **/
    FIELD_WHITE_KING    = 0x13,     /**<  後手のライオン。  **/
    FIELD_WHITE_GOLD    = 0x14,     /**<  後手のニワトリ。  **/

    /**   盤上にどちらの駒があるかを取得するためのマスク。  **/
    FIELD_MASK_PIECE_OWNER  = 0x18
};

//----------------------------------------------------------------
/**
**    番兵を含めた横方向の座標を表す列挙型。
**/

enum  GuardPosCol
{
    GPOS_COL_L,         /**<  左端の番兵。  **/
    GPOS_COL_A,
    GPOS_COL_B,
    GPOS_COL_C,
    GPOS_COL_R,         /**<  右端の番兵。  **/

    GPOS_NUM_COLS       /**<  列の数。      **/
};

//----------------------------------------------------------------
/**
**    番兵を含めた縦方向の座標を表す列挙型。
**/

enum  GuardPosRow
{
    GPOS_ROW_U,         /**<  上端の番兵。  **/
    GPOS_ROW_1,
    GPOS_ROW_2,
    GPOS_ROW_3,
    GPOS_ROW_4,
    GPOS_ROW_D,         /**<  下端の番兵。  **/

    GPOS_NUM_ROWS       /**<  行の数。      **/
};

}   //  End of namespace  GAME
DSHOGI_NAMESPACE_END

#endif
