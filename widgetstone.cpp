#include "widgetstone.h"

#include "chessstone.h"
#include "widgetboard.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>

WidgetStone* WidgetStone::m_btnChecked = nullptr;

void WidgetStone::focusOutEvent(QFocusEvent *event)
{
    setChecked(false);
    WidgetStone::m_btnChecked = nullptr;
    event->accept();
//    QMessageBox::information(this, "提示", "丢失焦点");
}

WidgetStone::WidgetStone(unsigned short i, ChessStone* stone, QWidget* parent):
    QPushButton(parent), index(i)
{
    setFocusPolicy(Qt::ClickFocus);
    setText(ChessStone::name_string[stone->color][stone->type]);
    setCheckable(true);
    connect(this, &QPushButton::clicked, [=](bool checked){
        if (checked)
        {
            setChecked(true);
            WidgetStone::m_btnChecked = this;
        }
        else
        {
            setChecked(false);
            WidgetStone::m_btnChecked = nullptr;
        }
    });
}

WidgetStone::~WidgetStone()
{
}
