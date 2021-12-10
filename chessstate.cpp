#include "chessstate.h"

#include "chessstone.h"

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
                                        nullptr,new ChessStone(ChessStone::PAO,2,1,ChessPlayer::BLACK),nullptr,nullptr,
                                        nullptr,nullptr,new ChessStone(ChessStone::PAO,2,7,ChessPlayer::BLACK),nullptr
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
                                        nullptr,new ChessStone(ChessStone::PAO,7,1,ChessPlayer::RED),nullptr,nullptr,
                                        nullptr,nullptr,new ChessStone(ChessStone::PAO,7,7,ChessPlayer::RED),nullptr
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
    for (const auto & i : board.grid)
    {
        for (auto j: i)
            if (!j)
                continue;
            else
                stones[index++] = j;
    }
}

ChessState::~ChessState()
{
    for (const auto& [i, j]: stones)
        delete j;
}

void ChessState::apply_move(ChessMove *move)
{
    auto btn = stones[move->index];
    board.grid[btn->row][btn->col] = nullptr;
    board.grid[move->m_to_row][move->m_to_col] = btn;
    btn->row = move->m_to_row;
    btn->col = move->m_to_col;
}

void ChessState::is_valid_move(ChessMove *move)
{

}
