#include "widgetboard.h"

#include "chessstone.h"
#include "widgetstone.h"
#include "chessstate.h"

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
    for (auto & i : m_btns.buttons()) {
        auto c = static_cast<WidgetStone*>(i);
        c->setStyleSheet(QString(
            "QPushButton{"
            "border-radius:%1px;"
            "border:1px solid brown;"
            "background-color:#e09a53;"
            "color:%2;font: 20pt \"超研澤粗行楷\";"
            "text-align:center;"
            "}"
            "QPushButton:hover{"
            "background-color:rgb(14, 220, 0);"
            "}"
            "QPushButton:checked{"
            "background-color:yellow;"
            "}"
        ).arg(D/2).arg(m_state->stones[c->index]->color == ChessPlayer::RED ? "red" : "black"));
        c->setGeometry(leftPadding / 2 + m_state->stones[c->index]->col * D, topPadding / 2 + m_state->stones[c->index]->row * D, D, D);
    }
}

void BoardWidget::mousePressEvent(QMouseEvent *event)
{
    int r = (event->pos().y() - topPadding + D / 2) / D, c = (event->pos().x() - leftPadding  + D / 2) / D;
    // qDebug() << "检查移动" << r << c << (bool)m_state[r][c];
    if (!m_state->board.grid[r][c] && WidgetStone::m_btnChecked)
    {
        qDebug() << "可以移动!";
        auto btn = m_state->stones[WidgetStone::m_btnChecked->index];
        m_state->board.grid[btn->row][btn->col] = nullptr;
        m_state->board.grid[r][c] = btn;
        btn->row = r; btn->col = c;
        WidgetStone::m_btnChecked->setGeometry(leftPadding / 2 + c * D, topPadding / 2 + r * D, D, D);
        WidgetStone::m_btnChecked->setChecked(false);
        WidgetStone::m_btnChecked = nullptr;
    }
    else if (WidgetStone::m_btnChecked)
    {
        WidgetStone::m_btnChecked->setChecked(false);
        WidgetStone::m_btnChecked = nullptr;
    }
}


BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent), m_state(new ChessState)
{
    for (auto& [i, j] : m_state->stones) {
        m_btns.addButton(new WidgetStone(i, j, this));
    }
    m_btns.setExclusive(true);
}

BoardWidget::~BoardWidget()
{
}
