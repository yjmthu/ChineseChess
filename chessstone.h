#ifndef CHESSSTONES_H
#define CHESSSTONES_H

#include "chessplayer.h"

class ChessStone
{
    typedef ChessPlayer::Color Color ;
public:
    static constexpr char name_string[2][7][4]
    {
        {"將", "士", "象", "馬", "車", "砲", "卒"},
        {"帥", "仕", "相", "傌", "俥", "炮", "兵"}
    };
    enum Type { JIANG, SHI, XIANG, MA, CHE, PAO, BING, DEAD } type;
    unsigned short index, row, col;
    Color color;
    inline ChessStone(Type type, unsigned short r, unsigned short c, Color color):
        type(type), row(r), col(c), color(color) {}
};

#endif // CHESSSTONES_H
