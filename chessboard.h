#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <array>

class ChessStone;
class ChessMove;

class ChessBoard
{
public:
    ChessBoard(const std::array< std::array<ChessStone*, 9>, 10>& lst);
    std::array<std::array<ChessStone*, 9>, 10> grid;
    void move_stone(ChessMove* move);
    void is_on_grid(ChessMove* move);
};

#endif // CHESSBOARD_H
