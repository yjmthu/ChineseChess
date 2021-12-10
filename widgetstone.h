#ifndef WIDGETSTONE_H
#define WIDGETSTONE_H

#include <QPushButton>

#include "chessstone.h"

class WidgetStone: public QPushButton
{
    Q_OBJECT

signals:
    void beEat(unsigned short index);
public:
    explicit WidgetStone(unsigned short i, ChessStone* stone, QWidget* parent);
    ~WidgetStone();
    static WidgetStone* m_btnChecked;
    unsigned short index;
};

#endif // WIDGETSTONE_H
