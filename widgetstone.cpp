#include "widgetstone.h"

#include "chessstone.h"
#include "widgetboard.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>

WidgetStone* WidgetStone::m_btnChecked = nullptr;

void WidgetStone::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && !isChecked())
    {
        setChecked(true);
        WidgetStone::m_btnChecked = this;
        event->accept();
    }
}

WidgetStone::WidgetStone(unsigned short i, ChessStone* stone, QWidget* parent):
    QPushButton(parent), index(i)
{
    setText(ChessStone::name_string[stone->color][stone->type]);
    setCheckable(true);
}

WidgetStone::~WidgetStone()
{
}
