#include "widgetstone.h"

#include "chessstone.h"
#include "widgetboard.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>

WidgetStone* WidgetStone::m_btnChecked = nullptr;

WidgetStone::WidgetStone(unsigned short i, ChessStone* stone, QWidget* parent):
    QPushButton(parent), index(i)
{
    setFocusPolicy(Qt::ClickFocus);
    setText(ChessStone::name_string[stone->color][stone->type]);
    connect(this, &QPushButton::clicked, [=](){
        if (m_btnChecked)
        {
            if  (((m_btnChecked->index < 16 && index > 15) || (m_btnChecked->index > 15 && index < 16)))
            {
                emit beEat(index);
            }
            else
            {

                QString&& style = m_btnChecked->styleSheet();
                m_btnChecked->setStyleSheet(styleSheet());
                setStyleSheet(style);
                m_btnChecked = this;
            }
        }
        else
        {
            m_btnChecked = this;
            QString style = styleSheet();
            setStyleSheet(style.replace(style.indexOf("#e09a53"), 7,  "yellow"));
        }
    });
}

WidgetStone::~WidgetStone()
{
}
