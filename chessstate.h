#ifndef CHESSSTATE_H
#define CHESSSTATE_H

#include <vector>
#include <map>
#include <array>
#include <stack>

#include <chessplayer.h>
#include <chessmove.h>
#include <chessstone.h>

class ChessState
{
private:
    inline unsigned short abs(unsigned short a, unsigned short b) { return b>a?b-a:a-b; }
    inline unsigned short distance(short x1, short y1, short x2, short y2) {short dx = x1-x2, dy = y1-y2;return dx*dx + dy*dy;}
    const bool is_computer_black = true;
    bool can_move_jiang(const ChessStone* st, const ChessMove& move);
    bool can_move_shi(const ChessStone* st, const ChessMove& move);
    bool can_move_xiang(const ChessStone* st, const ChessMove& move);
    bool can_move_ma(const ChessStone* st, const ChessMove& move);
    bool can_move_ju(const ChessStone* st, const ChessMove& move);
    bool can_move_pao(const ChessStone* st, const ChessMove& move);
    bool can_move_bing(const ChessStone* st, const ChessMove& move);
public:
    explicit ChessState(ChessPlayer computer);
    explicit ChessState(const ChessState&);
    ~ChessState();
    static constexpr short MIN_SCORE = std::numeric_limits<short>::min();
    static constexpr short MAX_SCORE = std::numeric_limits<short>::max();
    std::array<ChessStone*, 32> stones;
    std::array<std::array<ChessStone*, 9>, 10> board;
    ChessPlayer next_player;
    std::stack<ChessBack> last_steps;
    ChessPlayer::Color get_winer();
    std::vector<ChessMove> get_valid_moves();
    bool can_directly_win(const ChessMove* move);
    short get_min_score(short cur_max_score, unsigned short depth=1);
    short get_max_score(short cur_min_score, unsigned short depth=1);
    ChessMove get_best_move(unsigned short depth=1);
    short get_score();
    void cancel_move();
    void apply_move(const ChessMove& move);
    bool is_valid_move(const ChessMove& move);
    void operator=(const ChessState& other_state);
};

#endif // CHESSSTATE_H
