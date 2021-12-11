#include "chessstate.h"
#include "chessstone.h"

#include <QDebug>
#include <random>
#include <algorithm>

int ChessState::red_best= 0;
int ChessState::black_best = 0;

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
            for (short i = st->col - 1; i > move.m_to_row; --i)
                if (board[i][4])  return false;
        }
        else
        {
            for (short i = st->col + 1; i < move.m_to_row; ++i)
                if (board[i][4]) return false;
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
    red_best = black_best = 0;
}

ChessState::ChessState(const ChessState & other):
    board(other.board), next_player(other.next_player)
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
}

ChessState::~ChessState()
{
    for (const auto& [i, j]: stones)
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
    for (const auto & [i, j]: stones)
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
                    lst.push_back(temp_move);
                }
                ++temp_move.m_to_col;
            }
            ++temp_move.m_to_row;
        }
    }
    qDebug() << "君子有所为, 有所不为" << lst.size();
    return lst;
}

///
/// \brief ChessState::get_best_move_score
/// 获取当前next_player的最佳分数
/// \param depth
/// \return
///

int ChessState::get_best_move_score(unsigned short depth)  // next = red player
{
    ChessState temp_state(*this);
    ChessPlayer winer = get_winer();
    qDebug() << "进入此地却无人" << temp_state.next_player;
    if (winer == next_player)
        return MAX_SCORE;
    else if (winer == next_player.other())
        return MIN_SCORE;
    qDebug() << "出入此地快哉";
    if (!depth)
        return get_calc_score();
    qDebug() << "人生一场, 得失难量";
    int our_result, best_so_far = MIN_SCORE;
    for (auto& candidate_move: get_valid_moves())
    {
        qDebug() << "循环王府, 五十五中" << candidate_move.index << candidate_move.m_to_col << candidate_move.m_to_row;
        temp_state.apply_move(candidate_move);                   // next = black
        our_result = -temp_state.get_best_move_score(depth-1);   //
        qDebug() << "分数无常, 无需忧劳" << our_result << best_so_far;
        if (our_result > best_so_far)
        {
            best_so_far = our_result;
            if (next_player == ChessPlayer::BLACK)               // yes
            {
                qDebug() << "黑方入场" << best_so_far;
                if (best_so_far > red_best)
                    red_best = best_so_far;
                if (-best_so_far < black_best)
                    return best_so_far;
            }
            else
            {
                qDebug() << "红方入场" << best_so_far;
                if (best_so_far > black_best)
                    black_best = best_so_far;
                if (-best_so_far < red_best)
                    return best_so_far;
            }
        }
        temp_state.cancel_move();
    }
    qDebug() << "狭路相逢勇者胜";
    return best_so_far;
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
    ChessState temp_state(*this);
    int our_result, best_so_far = MIN_SCORE;
    for (auto& candidate_move: possible_moves)
    {
        temp_state.apply_move(candidate_move);            // next = red
        qDebug() << "101010=========1";
        our_result = temp_state.get_best_move_score(depth - 1);   // next black's max
        qDebug() << "101010=========2" << our_result;
        if (our_result > best_so_far)
        {
            best_so_far = our_result;
            qDebug() << "101010=========4";
            if (next_player == ChessPlayer::BLACK)               // false
            {
                qDebug() << "101010========5";
                if (best_so_far > red_best)
                    red_best = best_so_far;
                qDebug() << "101010========51" << candidate_move.index << candidate_move.m_to_col << candidate_move.m_to_row;
                if (-best_so_far < black_best)
                    return candidate_move;
                qDebug() << "101010=========52";
            }
            else
            {
                qDebug() << "101010========6";
                if (best_so_far > black_best)
                    black_best = best_so_far;
                if (-best_so_far < red_best)
                    return candidate_move;
            }
        }
        qDebug() << "101010========7";
        temp_state.cancel_move();                                // next = black
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, possible_moves.size()-1);
    return possible_moves[dis(gen)];
}

///
/// \brief ChessState::get_calc_score
/// 获取next_player的分数
/// \return
///

int ChessState::get_calc_score()
{
    int playerScore = 0;
    static constexpr short chessScore[8] = { 200, 20, 40, 60, 100, 80, 10, 0 };
    for (const auto & [i, j]: stones)
        if (i < 16)
            playerScore += chessScore[j->type];
        else
            playerScore -= chessScore[j->type];
    return next_player == ChessPlayer::BLACK ? playerScore: -playerScore;
}

void ChessState::cancel_move()
{
    if (last_move.moved == (unsigned short)-1)
        return;
    auto st = stones[last_move.moved];
    board[st->row][st->col] = last_move.eated;
    st->col = last_move.old_col;
    st->row = last_move.old_row;
    board[last_move.old_row][last_move.old_col] = st;
    if (last_move.eated)
    {
        last_move.eated->type = last_move.eated_type;
    }
    last_move.moved = (unsigned short)-1;
    next_player.next();
}

void ChessState::apply_move(const ChessMove& move)
{
    auto st = stones[move.index];
    board[st->row][st->col] = nullptr;
    auto& st1 = board[move.m_to_row][move.m_to_col];
    last_move.eated = st1;
    last_move.moved = move.index;
    last_move.old_col = st->col;
    last_move.old_row = st->row;
    if (st1)
    {
        last_move.eated_type = st1->type;
        st1->type = ChessStone::DEAD;
    }
    st1 = st;
    st->row = move.m_to_row;
    st->col = move.m_to_col;
    next_player.next();
}

bool ChessState::is_valid_move(const ChessMove& move)
{
    auto st = stones[move.index];
    if (next_player != st->color) return false;
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
    default:
        break;
    }
    return false;
}

void ChessState::operator=(const ChessState &other_state)
{
    stones.clear();
    next_player = other_state.next_player;
    for (unsigned short i = 0; i < 10; ++ i)
    {
        for (unsigned short j = 0; j < 9; ++j)
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
