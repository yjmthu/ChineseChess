#include "chessstate.h"
#include "chessstone.h"

#include <QDebug>
#include <random>
#include <algorithm>

bool ChessState::can_move_jiang(const ChessStone *st, const ChessMove &move)
{
    const ChessStone *st2 = board[move.m_to_row][move.m_to_col];
    if (st2 && st2->color == st->color) return false;
    unsigned short dis = distance(move.m_to_col, move.m_to_row, st->col, st->row);
    if (dis > 1)
    {
        if (!st2 || st2->type != ChessStone::JIANG || move.m_to_col != st->col)
            return false;
        if (st->color == ChessPlayer::RED)
        {
            for (short i = st->row - 1; i > move.m_to_row; --i)
                if (board[i][st->col])  return false;
        }
        else
        {
            for (short i = st->row + 1; i < move.m_to_row; ++i)
                if (board[i][st->col]) return false;
        }
        return true;
    }
    else if (dis != 1 || move.m_to_col > 5 || move.m_to_col < 3 || (move.m_to_row > 2 && move.m_to_row < 7))
    {
        return false;
    }
    return true;
}

bool ChessState::can_move_shi(const ChessStone *st, const ChessMove &move)
{
    const ChessStone *st2 = board[move.m_to_row][move.m_to_col];
    if (st2 && st2->color == st->color) return false;
    unsigned short dis = distance(move.m_to_col, move.m_to_row, st->col, st->row);
    if (dis != 2)
        return false;
    if (st->col == 4)
        return true;
    else if (move.m_to_col != 4 || (move.m_to_row != 1 && move.m_to_row != 8))
        return false;
    return true;
}

bool ChessState::can_move_xiang(const ChessStone *st, const ChessMove &move)
{
    const ChessStone *st2 = board[move.m_to_row][move.m_to_col];
    if (st2 && st2->color == st->color) return false;
    unsigned short dis = distance(move.m_to_col, move.m_to_row, st->col, st->row);
    if (dis != 8)
        return false;
    if (board[(st->row + move.m_to_row) / 2][(st->col + move.m_to_col) / 2])
        return false;
    if ((st->row < 5 && move.m_to_row > 4) || (st->row > 4 && move.m_to_row < 5))
        return false;
    return true;
}

bool ChessState::can_move_ma(const ChessStone *st, const ChessMove &move)
{
    const ChessStone *st2 = board[move.m_to_row][move.m_to_col];
    if (st2 && st2->color == st->color) return false;
    unsigned short dis = distance(move.m_to_col, move.m_to_row, st->col, st->row);
    if (dis != 5)
        return false;
    if (abs(st->col, move.m_to_col) == 2)
    {
        if (board[st->row][(st->col + move.m_to_col) / 2])
            return false;
    }
    else
    {
        if (board[(st->row + move.m_to_row) / 2][st->col])
            return false;
    }
    return true;
}

bool ChessState::can_move_ju(const ChessStone *st, const ChessMove &move)
{
    const ChessStone *st2 = board[move.m_to_row][move.m_to_col];
    if (st2 && st2->color == st->color) return false;
    short _min, _max;
    if (st->col == move.m_to_col)
    {
        if (st->row > move.m_to_row)
        {
            _max = st->row;
            _min = move.m_to_row;
        }
        else
        {
            _max = move.m_to_row;
            _min = st->row;
        }
        for (short i = _min + 1; i < _max; ++i)
            if (board[i][st->col])
                return false;
    }
    else if (st->row == move.m_to_row)
    {
        if (st->col > move.m_to_col)
        {
            _max = st->col;
            _min = move.m_to_col;
        }
        else
        {
            _max = move.m_to_col;
            _min = st->col;
        }
        for (short i = _min + 1; i < _max; ++i)
            if (board[st->row][i])
                return false;
    }
    else
        return false;
    return true;
}

bool ChessState::can_move_pao(const ChessStone *st, const ChessMove &move)
{
    const ChessStone *st2 = board[move.m_to_row][move.m_to_col];
    if (st2 && st2->color == st->color) return false;
    short _min, _max, _count = 0;
    if (st->col == move.m_to_col)
    {
        if (st->row > move.m_to_row)
        {
            _max = st->row;
            _min = move.m_to_row;
        }
        else
        {
            _max = move.m_to_row;
            _min = st->row;
        }
        for (short i = _min + 1; i < _max; ++i)
            if (board[i][st->col])
                ++_count;
    }
    else if (st->row == move.m_to_row)
    {
        if (st->col > move.m_to_col)
        {
            _max = st->col;
            _min = move.m_to_col;
        }
        else
        {
            _max = move.m_to_col;
            _min = st->col;
        }
        for (short i = _min + 1; i < _max; ++i)
            if (board[st->row][i])
                ++_count;
    }
    else
        return false;
    if (st2)
        return _count == 1;
    else
        return !_count;
}

bool ChessState::can_move_bing(const ChessStone *st, const ChessMove &move)
{
    const ChessStone *st2 = board[move.m_to_row][move.m_to_col];
    if (st2 && st2->color == st->color) return false;
    unsigned short dis = distance(move.m_to_col, move.m_to_row, st->col, st->row);
    if (dis != 1) return false;
    unsigned short cur_row, to_row;
    if (st->color == ChessPlayer::RED)
    {
        cur_row = 9 - st->row;
        to_row = 9 - move.m_to_row;
    }
    else
    {
        cur_row = st->row;
        to_row = move.m_to_row;
    }
    if (cur_row < 5)
        return to_row > cur_row;
    return to_row >= cur_row;
}

///
/// \brief ChessState::ChessState
/// 默认构造函数, 暂时就先这么写吧
///

ChessState::ChessState():
    board({
          std::array<ChessStone*, 9>(
              {
                  new ChessStone(ChessStone::CHE,0,0,ChessPlayer::BLACK),
                  new ChessStone(ChessStone::MA,0,1,ChessPlayer::BLACK),
                  new ChessStone(ChessStone::XIANG,0,2,ChessPlayer::BLACK),
                  new ChessStone(ChessStone::SHI,0,3,ChessPlayer::BLACK),
                  new ChessStone(ChessStone::JIANG,0,4,ChessPlayer::BLACK),
                  new ChessStone(ChessStone::SHI,0,5,ChessPlayer::BLACK),
                  new ChessStone(ChessStone::XIANG,0,6,ChessPlayer::BLACK),
                  new ChessStone(ChessStone::MA,0,7,ChessPlayer::BLACK),
                  new ChessStone(ChessStone::CHE,0,8,ChessPlayer::BLACK)
              }),
          std::array<ChessStone*,9>({nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr}),
          std::array<ChessStone*,9>({
                                        nullptr,
                                        new ChessStone(ChessStone::PAO,2,1,ChessPlayer::BLACK),
                                        nullptr,nullptr,nullptr,nullptr, nullptr,
                                        new ChessStone(ChessStone::PAO,2,7,ChessPlayer::BLACK),
                                        nullptr
                                    }),
          std::array<ChessStone*,9>(
              {
                  new ChessStone(ChessStone::BING,3,0,ChessPlayer::BLACK),nullptr,
                  new ChessStone(ChessStone::BING,3,2,ChessPlayer::BLACK),nullptr,
                  new ChessStone(ChessStone::BING,3,4,ChessPlayer::BLACK),nullptr,
                  new ChessStone(ChessStone::BING,3,6,ChessPlayer::BLACK),nullptr,
                  new ChessStone(ChessStone::BING,3,8,ChessPlayer::BLACK)
              }),
          std::array<ChessStone*,9>({nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr}),
          std::array<ChessStone*,9>({nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr}),
          std::array<ChessStone*,9>(
              {
                  new ChessStone(ChessStone::BING,6,0,ChessPlayer::RED),nullptr,
                  new ChessStone(ChessStone::BING,6,2,ChessPlayer::RED),nullptr,
                  new ChessStone(ChessStone::BING,6,4,ChessPlayer::RED),nullptr,
                  new ChessStone(ChessStone::BING,6,6,ChessPlayer::RED),nullptr,
                  new ChessStone(ChessStone::BING,6,8,ChessPlayer::RED)
              }),
          std::array<ChessStone*,9>({
                                        nullptr,
                                        new ChessStone(ChessStone::PAO,7,1,ChessPlayer::RED),
                                        nullptr,nullptr,nullptr,nullptr,nullptr,
                                        new ChessStone(ChessStone::PAO,7,7,ChessPlayer::RED),
                                        nullptr
                                    }),
          std::array<ChessStone*,9>({nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr,nullptr}),
          std::array<ChessStone*,9>(
              {
                  new ChessStone(ChessStone::CHE,9,0,ChessPlayer::RED),
                  new ChessStone(ChessStone::MA,9,1,ChessPlayer::RED),
                  new ChessStone(ChessStone::XIANG,9,2,ChessPlayer::RED),
                  new ChessStone(ChessStone::SHI,9,3,ChessPlayer::RED),
                  new ChessStone(ChessStone::JIANG,9,4,ChessPlayer::RED),
                  new ChessStone(ChessStone::SHI,9,5,ChessPlayer::RED),
                  new ChessStone(ChessStone::XIANG,9,6,ChessPlayer::RED),
                  new ChessStone(ChessStone::MA,9,7,ChessPlayer::RED),
                  new ChessStone(ChessStone::CHE,9,8,ChessPlayer::RED)
              })
    }),
    next_player(ChessPlayer::Color::RED)
{
    unsigned short index = 0;
    for (const auto & i : board)
    {
        for (auto j: i)
            if (!j)
                continue;
            else
                stones[j->index=index++] = j;
    }
}

ChessState::ChessState(const ChessState & other):
    stones(other.stones), board(other.board), next_player(other.next_player)
{
    for (auto& i: board)
    {
        for (auto& j: i)
        {
            if (!j)
                continue;
            else
            {
                j = new ChessStone(*j);
                stones[j->index] = j;
            }
        }
    }
    for (auto& j: stones)
    {
        if (j->type == ChessStone::DEAD)
        {
            j = new ChessStone(*j);
        }
    }
}

ChessState::~ChessState()
{
    for (const auto j: stones)
        delete j;
}

ChessPlayer::Color ChessState::get_winer()
{
    if (next_player == ChessPlayer::RED && stones[27]->type == ChessStone::DEAD)
        return ChessPlayer::BLACK;
    if (next_player == ChessPlayer::BLACK && stones[4]->type == ChessStone::DEAD)
        return ChessPlayer::RED;
    return ChessPlayer::NONE;
}

std::vector<ChessMove> ChessState::get_valid_moves()
{
    std::vector<ChessMove> lst;
    ChessMove temp_move;
    for (unsigned char i = 0; i < 32; ++i)
    {
        temp_move.index = i;
        temp_move.m_to_row = 0;
        for (const auto& k: board)
        {
            temp_move.m_to_col = 0;
            for (const auto l: k)
            {
                (void)l;
                if (is_valid_move(temp_move))
                {
                    //qDebug() << i << temp_move.m_to_row << temp_move.m_to_col;
                    if (can_directly_win(&temp_move))
                    {
                        lst.clear();
                        lst.push_back(temp_move);
                        return lst;
                    }
                    lst.push_back(temp_move);
                }
                ++temp_move.m_to_col;
            }
            ++temp_move.m_to_row;
        }
    }
    return lst;
}

bool ChessState::can_directly_win(const ChessMove *move)
{
    auto & c = board[move->m_to_row][move->m_to_col];
    return c && c->type == ChessStone::JIANG;
}

short ChessState::get_max_score(short cur_min_score, unsigned short depth)
{
//    if (get_winer() == next_player.other())
//        return MIN_SCORE;
    if (!depth)
        return get_score();
    short max_score = MIN_SCORE, score;
    for (auto& candidate_move: get_valid_moves())
    {
        apply_move(candidate_move);
        score = get_min_score(max_score, depth-1);
        cancel_move();
        if (score >= cur_min_score)
        {
            return score;
        }
        if (score > max_score)
        {
            max_score = score;
        }
    }
    return max_score;
}

///
/// \brief ChessState::get_best_move_score
/// 获取当前next_player的最佳分数
/// \param depth
/// \return
///

short ChessState::get_min_score(short cur_max_score, unsigned short depth)
{
//    if (get_winer() == next_player.other())
//        return MIN_SCORE;
    if (!depth)
        return get_score();
    short min_score = MAX_SCORE, score;
    for (auto& candidate_move: get_valid_moves())
    {
        apply_move(candidate_move);
        score = get_max_score(min_score, depth - 1);
        cancel_move();
        if (score <= cur_max_score)
        {
            return score;
        }
        if (score < min_score)
        {
            min_score = score;
        }
    }
    return min_score;
}

///
/// \brief ChessState::get_best_move
/// \param depth
/// 获取next_player的比较好的选择
/// \return
///

ChessMove ChessState::get_best_move(unsigned short depth) // next = black
{
    std::vector<ChessMove> && possible_moves = get_valid_moves();
    short cur_max_score = MIN_SCORE, score;
    ChessMove* step = nullptr;
    for (auto& candidate_move: possible_moves)
    {
        apply_move(candidate_move);
        score = get_min_score(cur_max_score, depth - 1);
        cancel_move();
        if (score > cur_max_score)
        {
            cur_max_score = score;
            step = &candidate_move;
        }
    }
    if (!step)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dis(0, possible_moves.size()-1);
        step = &possible_moves .at(dis(gen));
    }
    return *step;
}

short ChessState::get_score()
{
    short playerScore = 0;
    //  { JIANG, SHI, XIANG, MA, CHE, PAO, BING, DEAD }
    static constexpr short chessScore[8] = { 150, 1, 1, 5, 10, 5, 2, 0 };
    unsigned char i = 0;
    for (const auto j: stones)
        if (i++ < 16)
            playerScore += chessScore[j->type];
        else
            playerScore -= chessScore[j->type];
    return playerScore;
}

void ChessState::cancel_move()
{
    if (!last_steps.size())
        return;
    ChessBack& top = last_steps.top();
    auto st = stones[top.moved];
    board[st->row][st->col] = top.eated;
    st->col = top.old_col;
    st->row = top.old_row;
    board[top.old_row][top.old_col] = st;
    if (top.eated)
        top.eated->type = top.eated_type;
    last_steps.pop();
    next_player.next();
}

void ChessState::apply_move(const ChessMove& move)
{
    auto st = stones[move.index];
    board[st->row][st->col] = nullptr;
    auto& st1 = board[move.m_to_row][move.m_to_col];
    if (st1)
    {
        last_steps.push(ChessBack {move.index, st1, st->row, st->col, st1->type});
        st1->type = ChessStone::DEAD;
    }
    else
    {
        last_steps.push(ChessBack {move.index, st1, st->row, st->col, ChessStone::DEAD});
    }
    st1 = st;
    st->row = move.m_to_row;
    st->col = move.m_to_col;
    board[st->row][st->col] = st;
    next_player.next();
}

bool ChessState::is_valid_move(const ChessMove& move)
{
    auto st = stones[move.index];
    if (next_player != st->color)
        return false;
    if (get_winer() != ChessPlayer::NONE)
        return false;
    switch (st->type) {
    case ChessStone::JIANG:
        return can_move_jiang(st, move);
    case ChessStone::BING:
        return can_move_bing(st, move);
    case ChessStone::PAO:
        return can_move_pao(st, move);
    case ChessStone::CHE:
        return can_move_ju(st, move);
    case ChessStone::XIANG:
        return can_move_xiang(st, move);
    case ChessStone::SHI:
        return can_move_shi(st, move);
    case ChessStone::MA:
        return can_move_ma(st, move);
    default:  // SUCH AS DEAD
        break;
    }
    return false;
}

void ChessState::operator=(const ChessState &other_state)
{
    next_player = other_state.next_player;
    for (unsigned char i = 0; i < 10; ++ i)
    {
        for (unsigned char j = 0; j < 9; ++j)
        {
            auto & st = board[i][j];
            delete st;
            if (!other_state.board[i][j])
                st = nullptr;
            else
            {
                st = new ChessStone(*other_state.board[i][j]);
                stones[st->index] = st;
            }
        }
    }
}
