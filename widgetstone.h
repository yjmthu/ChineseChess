#ifndef WIDGETSTONE_H
#define WIDGETSTONE_H

#include <QPushButton>

#include "chessstone.h"

class WidgetStone: public QPushButton
{
protected:
    void focusOutEvent(QFocusEvent *event);
public:
    explicit WidgetStone(unsigned short i, ChessStone* stone, QWidget* parent);
    ~WidgetStone();
    static WidgetStone* m_btnChecked;
    unsigned short index;
};

#endif // WIDGETSTONE_H
