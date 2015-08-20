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
**      @file       Bin/DoubutsuShogi.cpp
**/

#include    "DoubutsuShogi/Interface/GameController.h"

#include    <fstream>
#include    <iostream>

using   namespace   DSHOGI_NAMESPACE;
using   namespace   DSHOGI_NAMESPACE::INTERFACE;

namespace  {

const   char
s_tblColName[POS_NUM_COLS]  = {
    'A', 'B', 'C'
};

const   char
s_tblRowName[POS_NUM_ROWS]  = {
    '1', '2', '3', '4'
};

const   char
s_tblPieceName[]    = {
    '?',
    'P', 'B', 'R', 'K', 'G',    //  先手。  //
    'P', 'B', 'R', 'K', 'G'     //  後手。  //
};

}   //  End of (Unnamed) namespace.

const   ErrCode
dumpActionViewList(
        const  GameController  &gCtrl,
        std::ostream           &outStr)
{
    typedef     GameController::ActionViewList  ActionViewList;
    typedef     ActionViewList::const_iterator  ActIter;

    ActionViewList  avl;

    gCtrl.makeActionViewList(avl);
    outStr  << "<BEGIN>"  << std::endl;
    int             idx     = 0;
    const  ActIter  itrEnd  = avl.end();
    for ( ActIter itr = avl.begin(); itr != itrEnd; ++ itr, ++ idx ) {
        const  ActionView  act  = (* itr);
        outStr  << (idx) << ":\t";
        if ( act.putHand != PIECE_EMPTY ) {
            outStr  << '.' << s_tblPieceName[(act.putHand)];
        } else {
            outStr  << s_tblColName[(act.xOldCol)]
                    << s_tblRowName[(act.yOldRow)];
        }
        outStr  << s_tblColName[(act.xNewCol)]
                << s_tblRowName[(act.yNewRow)];
        outStr  << std::endl;
    }
    outStr  << "<END>"  << std::endl;

    return ( ERR_SUCCESS );
}


const   PosCol
encodeColName(
        const  char  chCol)
{
    switch ( chCol ) {
    case  'A':  case  'a':
        return ( POS_COL_A );
    case  'B':  case  'b':
        return ( POS_COL_B );
    case  'C':  case  'c':
        return ( POS_COL_C );
    }
    return ( POS_NUM_COLS );
}

const   PosRow
encodeRowName(
        const  char  chRow)
{
    switch ( chRow ) {
    case  '1':
        return ( POS_ROW_1 );
    case  '2':
        return ( POS_ROW_2 );
    case  '3':
        return ( POS_ROW_3 );
    case  '4':
        return ( POS_ROW_4 );
    }
    return ( POS_NUM_ROWS );
}

const   INTERFACE::PieceIndex
encodePieceName(
        const  TurnPlayer   nPlayer,
        const  char         chName)
{
    switch ( chName ) {
    case  'B':  case  'b':
        return ( nPlayer ? PIECE_WHITE_BISHOP : PIECE_BLACK_BISHOP );
    case  'G':  case  'g':
        return ( nPlayer ? PIECE_WHITE_GOLD   : PIECE_BLACK_GOLD   );
    case  'K':  case  'k':
        return ( nPlayer ? PIECE_WHITE_KING   : PIECE_BLACK_KING   );
    case  'P':  case  'p':
        return ( nPlayer ? PIECE_WHITE_PAWN   : PIECE_BLACK_PAWN   );
    case  'R':  case  'r':
        return ( nPlayer ? PIECE_WHITE_ROOK   : PIECE_BLACK_ROOK   );
    }

    return ( PIECE_EMPTY );
}

void
showHelpMessage(
        std::ostream  & strOut)
{
    strOut  << "\n------------------------------------------------\n"
            << "指し手の入力方法：\n"
            << "\n(1) 盤上の駒を動かす場合\n"
            << "移動元＋移動先。\n"
            <<" 例： B2B3  -- B2 の駒を B3 に移動する。\n"
            << "\n(2) 持ち駒を打つ場合\n"
            << "ピリオド＋駒を表す壱文字＋場所。\n"
            << "例： .PB2  -- ヒヨコを B2 に打つ。\n"
            << "  P - ヒヨコ (Pawn)\n"
            << "  B - ゾウ   (Bishop)\n"
            << "  R - キリン (Rook)\n"
            << "\n(3) その他：\n"
            << "q   - プログラムを終了する\n"
            << "?   - このヘルプを表示する\n"
            << ":v  - 棋譜を表示する\n"
            << ":w  - 棋譜を保存する。名前省略時は Kifu.txt\n"
            << "------------------------------------------------"
            << std::endl;
    return;
}

int  main(int argc, char * argv[])
{
    GameController  gc;

    std::istream  & isCnsl  = (std::cin);
    std::string     strLine;

    gc.resetGameBoard();

    while ( 1 ) {
        gc.writeToStream(std::cout) << std::endl;
        std::cout   << "\n"
                    << (gc.getTurnPlayer() ? "後手" : "先手")
                    << "の手番です。\n"
                    << "指し手を入力してください（? でヘルプ）：";

        std::getline(isCnsl, strLine);

        if ( strLine[0] == 'q' ) {
            //  プログラムを終了する。  //
            break;
        }
        if ( strLine[0] == '?' ) {
            //  ヘルプを表示する。      //
            showHelpMessage(std::cout);
            continue;
        }

        if ( strLine[0] == ':' ) {
            //  特殊コマンド実行。  //
            if ( strLine.length() == 1 ) {
                continue;
            }
            if ( strLine[1] == 'w' ) {
                //  棋譜データを保存する。  //
                std::ofstream   ofsOut;
                const  char  *  psFile  = "Kifu.txt";
                if ( strLine.length() > 3 ) {
                    psFile  = &strLine[3];
                }
                ofsOut.open(psFile);
                dumpActionViewList(gc, ofsOut);
                std::cerr  << "Wrote " << psFile << std::endl;
            } else if ( strLine[1] == 'v' ) {
                //  棋譜データを表示する。  //
                dumpActionViewList(gc, std::cout);
                std::cout  << std::endl;
            }
            continue;
        }

        if ( strLine[0] == '.' ) {
            //  持ち駒を打つ。      //
            const  PieceIndex
                piHand  = encodePieceName(gc.getTurnPlayer(), strLine[1]);
            const  PosCol   xPutCol = encodeColName(strLine[2]);
            const  PosRow   yPutRow = encodeRowName(strLine[3]);
            if ( (piHand == PIECE_EMPTY)
                    || (xPutCol == POS_NUM_COLS)
                    || (yPutRow == POS_NUM_ROWS) )
            {
                continue;
            }
            gc.playPutAction(xPutCol, yPutRow, piHand);
        } else {
            //  盤上の駒を動かす。  //
            const  PosCol   xOldCol = encodeColName(strLine[0]);
            const  PosRow   yOldRow = encodeRowName(strLine[1]);
            const  PosCol   xNewCol = encodeColName(strLine[2]);
            const  PosRow   yNewRow = encodeRowName(strLine[3]);
            if ( (xOldCol == POS_NUM_COLS)
                    || (yOldRow == POS_NUM_ROWS)
                    || (xNewCol == POS_NUM_COLS)
                    || (yNewRow == POS_NUM_ROWS) )
            {
                continue;
            }
            gc.playMoveAction(xOldCol, yOldRow, xNewCol, yNewRow);
        }
    }

    return ( 0 );
}
