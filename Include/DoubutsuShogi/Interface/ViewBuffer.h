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
**      An Interface of ViewBuffer class.
**
**      @file       Interface/ViewBuffer.h
**/

#if !defined( DSHOGI_INTERFACE_INCLUDED_VIEW_BUFFER_H )
#    define   DSHOGI_INTERFACE_INCLUDED_VIEW_BUFFER_H

#include    "DoubutsuShogi/Common/DoubutsuShogiTypes.h"

DSHOGI_NAMESPACE_BEGIN
namespace  INTERFACE  {

//----------------------------------------------------------------
/**
**    駒の種類を表す定数。
**/

enum  PieceIndex
{
    PIECE_EMPTY         = 0,        /**<  空いているマス。  **/

    PIECE_BLACK_PAWN    = 1,        /**<  先手のヒヨコ。    **/
    PIECE_BLACK_BISHOP  = 2,        /**<  先手のゾウ。      **/
    PIECE_BLACK_ROOK    = 3,        /**<  先手のキリン。    **/
    PIECE_BLACK_KING    = 4,        /**<  先手のライオン。  **/
    PIECE_BLACK_GOLD    = 5,        /**<  先手のニワトリ。  **/

    PIECE_WHITE_PAWN    = 6,        /**<  後手のヒヨコ。    **/
    PIECE_WHITE_BISHOP  = 7,        /**<  後手のゾウ。      **/
    PIECE_WHITE_ROOK    = 8,        /**<  後手のキリン。    **/
    PIECE_WHITE_KING    = 9,        /**<  後手のライオン。  **/
    PIECE_WHITE_GOLD    = 10,       /**<  後手のニワトリ。  **/

    NUM_PIECE_TYPES                 /**<  駒の種類数。      **/
};

//----------------------------------------------------------------
/**
**    ゲームの局面を表示するためのバッファ構造体。
**/

struct  ViewBuffer
{
    PieceIndex  piBoard[POS_MATRIX_SIZE];       /**<  盤上の状態。  **/
    int         nHands [NUM_PIECE_TYPES];       /**<  持ち駒の数。  **/
};

//----------------------------------------------------------------
/**
**    指し手の内部形式を表示用データに変換した構造体。
**/

struct  ActionView
{
    PosCol          xOldCol;        /**<  移動元の座標（横方向）。  **/
    PosRow          yOldRow;        /**<  移動元の座標（縦方向）。  **/
    PosCol          xNewCol;        /**<  移動先の座標（横方向）。  **/
    PosRow          yNewRow;        /**<  移動先の座標（縦方向）。  **/

    PieceIndex      fpMoved;        /**<  移動した自分の駒の種類。  **/
    PromoteFlag     flgProm;        /**<  駒が成るか成らないか？    **/
    PieceIndex      piCatch;        /**<  捕獲した敵駒の種類。      **/

    PieceIndex      putHand;        /**<  打った持ち駒の種類。      **/
};

}   //  End of namespace  INTERFACE
DSHOGI_NAMESPACE_END

#endif
