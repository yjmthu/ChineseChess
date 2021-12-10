#include "boardwidget.h"

#include "stones.h"
#include "stonewidget.h"

#include <QPainter>
#include <QDebug>
#include <QResizeEvent>

void BoardWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(QPoint(leftPadding, topPadding), QPoint(leftPadding+8*D, topPadding));
    painter.drawLine(QPoint(leftPadding, topPadding+9*D), QPoint(leftPadding+8*D, topPadding+9*D));
    painter.drawLine(QPoint(topPadding, topPadding), QPoint(leftPadding, topPadding+9*D));
    painter.drawLine(QPoint(topPadding+8*D, topPadding), QPoint(leftPadding+8*D, topPadding+9*D));

    painter.setPen(QPen(Qt::black, 1));
    for(int i = 1; i < 9; i++)
        painter.drawLine(QPoint(leftPadding, topPadding+i*D), QPoint(leftPadding+8*D, topPadding+i*D));
    for(int i = 1; i < 8; i++)
    {
        painter.drawLine(QPoint(leftPadding+i*D, topPadding), QPoint(leftPadding+i*D, topPadding+4*D));
        painter.drawLine(QPoint(leftPadding+i*D, topPadding+5*D), QPoint(leftPadding+i*D, topPadding+9*D));
    }

    painter.drawLine(QPoint(leftPadding+3*D, topPadding), QPoint(leftPadding+5*D, topPadding+2*D));
    painter.drawLine(QPoint(leftPadding+3*D, topPadding+2*D), QPoint(leftPadding+5*D, topPadding));
    painter.drawLine(QPoint(leftPadding+3*D, topPadding+7*D), QPoint(leftPadding+5*D, topPadding+9*D));
    painter.drawLine(QPoint(leftPadding+3*D, topPadding+9*D), QPoint(leftPadding+5*D, topPadding+7*D));

    painter.setPen(QPen(Qt::blue, 2));
    painter.setFont(QFont("汉仪篆书繁", D/2, 800));
    painter.drawText(QRect(leftPadding+D,   topPadding+4*D, D, D), "楚", QTextOption(Qt::AlignCenter));
    painter.drawText(QRect(leftPadding+2*D, topPadding+4*D, D, D), "河", QTextOption(Qt::AlignCenter));
    painter.drawText(QRect(leftPadding+5*D, topPadding+4*D, D, D), "汉", QTextOption(Qt::AlignCenter));
    painter.drawText(QRect(leftPadding+6*D, topPadding+4*D, D, D), "界", QTextOption(Qt::AlignCenter));
}

void BoardWidget::resizeEvent(QResizeEvent *event)
{
    int side = std::min(event->size().width(), event->size().height());
    leftPadding = side / 11, topPadding = side / 11, D = side / 11;
    for (auto & c : m_btns) {
        qDebug() << "显示!";
        c->setStyleSheet(QString(
            "border-radius:%1px;border:1px solid brown;background-color:#e09a53;color:%2;font: 20pt \"华文行楷\";text-align:center;"
        ).arg(D/2).arg(c->m_stone->m_bRed ? "red" : "black"));
        c->setGeometry(leftPadding / 2 + c->m_stone->m_nCol * D, topPadding / 2 +c->m_stone->m_nRow* D, D, D);
    }
}


BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent)
{
    m_btns.resize(32);
    for(int i = 0; i < 32; ++i)
    {
        m_btns[i] = new StoneWidget(i, this);
       // m_btns[i]->setVisible(true);
    }
}

BoardWidget::~BoardWidget()
{
}
