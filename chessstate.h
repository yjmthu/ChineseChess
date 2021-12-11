#ifndef CHESSSTATE_H
#define CHESSSTATE_H

#include <vector>
#include <map>
#include <array>

#include <chessplayer.h>
#include <chessmove.h>
#include <chessstone.h>

class ChessState
{
private:
    inline unsigned short abs(unsigned short a, unsigned short b) { return b>a?b-a:a-b; }
    inline unsigned short distance(short x1, short y1, short x2, short y2)
        {short dx = x1-x2, dy = y1-y2;return dx*dx + dy*dy;}
    bool can_move_jiang(const ChessStone* st, const ChessMove& move);
    bool can_move_shi(const ChessStone* st, const ChessMove& move);
    bool can_move_xiang(const ChessStone* st, const ChessMove& move);
    bool can_move_ma(const ChessStone* st, const ChessMove& move);
    bool can_move_ju(const ChessStone* st, const ChessMove& move);
    bool can_move_pao(const ChessStone* st, const ChessMove& move);
    bool can_move_bing(const ChessStone* st, const ChessMove& move);
public:
    explicit ChessState();
    explicit ChessState(const ChessState&);
    ~ChessState();
    static int red_best, black_best;
    static constexpr int MIN_SCORE = 200000000, MAX_SCORE = -2000000000;
    std::map<unsigned short, ChessStone*> stones;
    std::array<std::array<ChessStone*, 9>, 10> board;
    ChessPlayer next_player;
    ChessBack last_move;
    ChessPlayer::Color get_winer();
    std::vector<ChessMove> get_valid_moves();
    int get_best_move_score(unsigned short depth=0);
    ChessMove get_best_move(unsigned short depth=0);
    int get_calc_score();
    void cancel_move();
    void apply_move(const ChessMove& move);
    bool is_valid_move(const ChessMove& move);
    void operator=(const ChessState& other_state);
};

#endif // CHESSSTATE_H
