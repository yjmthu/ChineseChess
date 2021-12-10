#ifndef CHESSSTATE_H
#define CHESSSTATE_H

#include <vector>
#include <map>

#include <chessboard.h>
#include <chessplayer.h>
#include <chessmove.h>

class ChessState
{
public:
    explicit ChessState();
    ~ChessState();
    std::map<unsigned short, ChessStone*> stones;
    ChessBoard board;
    ChessPlayer next_player;
    ChessMove last_move;
    //static ChessState new_game();
    void apply_move(const ChessMove& move);
    void is_valid_move(ChessMove* move);
};

#endif // CHESSSTATE_H
