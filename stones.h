#ifndef STONES_H
#define STONES_H

class Stones
{
public:
    enum type {JIANG, SHI, XIANG, MA, CHE, PAO, BING} m_emType;
    Stones(int id);
    int m_nRow;
    int m_nCol;
    bool m_bRed;
    const char* m_name;
    //ChessPieces ;
};

#endif // STONES_H
