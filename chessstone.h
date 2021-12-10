#ifndef CHESSSTONES_H
#define CHESSSTONES_H

#include "chessplayer.h"

class ChessStone
{
    typedef ChessPlayer::Color Color ;
public:
    static constexpr char name_string[2][7][4]
    {
        {"將", "士", "象", "馬", "車", "炮", "卒"},
        {"帥", "士", "相", "馬", "車", "炮", "兵"}
    };
    const enum Type { JIANG, SHI, XIANG, MA, CHE, PAO, BING } type;
    unsigned short row, col;
    Color color;
    inline ChessStone(Type type, unsigned short r, unsigned short c, Color color):
        type(type), row(r), col(c), color(color) {}
};

#endif // CHESSSTONES_H
