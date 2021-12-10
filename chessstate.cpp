#include "chessstate.h"
#include "chessstone.h"

#include <QDebug>

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
            {
                if (board[i][4])
                    return false;
            }
        }
        else
        {
            for (short i = st->col + 1; i < move.m_to_row; ++i)
            {
                if (board[i][4])
                    return false;
            }
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
    {
        return false;
    }
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
    qDebug() << _count;
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
        return to_row != cur_row;
    return to_row >= cur_row;
}

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

ChessState::~ChessState()
{
    for (const auto& [i, j]: stones)
        delete j;
}

short ChessState::apply_move(const ChessMove& move)
{
    short id = -1;
    auto st = stones[move.index];
    board[st->row][st->col] = nullptr;
    auto & st1 = board[move.m_to_row][move.m_to_col];
    if (st1) id = st->index;
    st1 = st;
    st->row = move.m_to_row;
    st->col = move.m_to_col;
    next_player.next();
    return id;
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
