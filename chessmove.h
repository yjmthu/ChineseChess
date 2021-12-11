#ifndef CHESSMOVE_H
#define CHESSMOVE_H

#include "chessstone.h"

struct ChessMove
{
    unsigned short index;
    unsigned short m_to_row, m_to_col;
};

struct ChessBack
{
    unsigned short moved;
    ChessStone* eated;
    unsigned short old_row, old_col;
    ChessStone::Type eated_type;
};

#endif // CHESSMOVE_H
