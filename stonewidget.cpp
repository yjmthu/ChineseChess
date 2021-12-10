#include "stonewidget.h"

#include "stones.h"
#include "boardwidget.h"

#include <QPainter>
#include <QDebug>

StoneWidget::StoneWidget(int i, QWidget* parent):
    QPushButton(parent),
    m_stone(new Stones(i))
{
    setText(m_stone->m_name);
}

StoneWidget::~StoneWidget()
{
    delete m_stone;
}
