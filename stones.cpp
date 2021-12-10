#include "stones.h"

struct POS
{
    int t_nRow;
    int t_nCol;
    Stones::type t_emType;
    const char t_name[4];
};

//定义基础的16棋子[预定作为上方使用，黑棋使用]
POS tPos[16]= {
              {0, 0, Stones::type::CHE, "车"},
              {0, 1, Stones::type::MA, "马"},
              {0, 2, Stones::type::XIANG, "象"},
              {0, 3, Stones::type::SHI, "士"},
              {0, 4, Stones::type::JIANG, "将"},
              {0, 5, Stones::type::SHI, "士"},
              {0, 6, Stones::type::XIANG, "相"},
              {0, 7, Stones::type::MA, "马"},
              {0, 8, Stones::type::CHE, "车"},

              {2, 1, Stones::type::PAO, "炮"},
              {2, 7, Stones::type::PAO, "炮"},
              {3, 0, Stones::type::BING, "兵"},
              {3, 2, Stones::type::BING, "兵"},
              {3, 4, Stones::type::BING, "兵"},
              {3, 6, Stones::type::BING, "兵"},
              {3, 8, Stones::type::BING, "兵"}
              };

Stones::Stones(int id)
{
    if(id <16)
    {
        m_nRow = tPos[id].t_nRow;
        m_nCol = tPos[id].t_nCol;
        m_emType = tPos[id].t_emType;
        m_name = tPos[id].t_name;
        m_bRed = false;
    }
    else
    {
        m_nRow = 9-tPos[id-16].t_nRow;
        m_nCol = 8-tPos[id-16].t_nCol;
        m_emType = tPos[id-16].t_emType;
        m_name = tPos[id-16].t_name;
        m_bRed = true;
    }
}
