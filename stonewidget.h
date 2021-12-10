#ifndef STONEWIDGET_H
#define STONEWIDGET_H

#include <QPushButton>

class Stones;

class StoneWidget: public QPushButton
{
public:
    explicit StoneWidget(int i, QWidget* parent);
    ~StoneWidget();
    Stones* const m_stone;
};

#endif // STONEWIDGET_H
