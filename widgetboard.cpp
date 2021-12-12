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
    for (auto& [i, j] : m_btns) {
        j->setStyleSheet(QString(
            "QPushButton{"
            "border-radius:%1px;"
            "border:1px solid brown;"
            "background-color:#e09a53;"
            "color:%2;font: bold 20pt \"思源宋体 CN SemiBold\";"
            "text-align:center;"
            "}"
        ).arg(D/2).arg(j->index > 15 ? "red" : "black"));
        j->setGeometry(real_rect(m_state->stones[j->index]->row, m_state->stones[j->index]->col));
    }
}

void BoardWidget::mousePressEvent(QMouseEvent *event)
{
    unsigned short r = (event->pos().y() - topPadding + D / 2) / D, c = (event->pos().x() - leftPadding  + D / 2) / D;
    if (r > 10 || c > 9) return;
    // qDebug() << "检查移动" << r << c << (bool)m_state[r][c];
    if (!WidgetStone::m_btnChecked) return;
    ChessMove _move = { WidgetStone::m_btnChecked->index, r, c };
    if (m_state->is_valid_move(_move))
    {
        m_state->apply_move(_move);
        WidgetStone::m_btnChecked->setGeometry(real_rect(r, c));
        QString style = WidgetStone::m_btnChecked->styleSheet();
        WidgetStone::m_btnChecked->setStyleSheet(style.replace(style.indexOf("yellow"), 6,  "#e09a53"));
        WidgetStone::m_btnChecked = nullptr;
        _move = m_state->get_best_move(4);
        const auto st = m_state->board[_move.m_to_row][_move.m_to_col];
        if (st) m_btns[st->index]->hide();
        m_state->apply_move(_move);
        m_btns[_move.index]->setGeometry(real_rect(_move.m_to_row, _move.m_to_col));
        return;
    }
    QString style = WidgetStone::m_btnChecked->styleSheet();
    WidgetStone::m_btnChecked->setStyleSheet(style.replace(style.indexOf("yellow"), 6,  "#e09a53"));
    WidgetStone::m_btnChecked = nullptr;
}


BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent), m_state(new ChessState)
{
    for (auto& [i, j] : m_state->stones) {
        connect(m_btns[i] = new WidgetStone(i, j, this), &WidgetStone::beEat, this, [=](unsigned short index){
            auto st = m_state->stones[index];
            ChessMove _move = { WidgetStone::m_btnChecked->index, st->row, st->col };
            if (m_state->is_valid_move(_move))
            {
                m_state->apply_move(_move);
                m_btns[index]->hide();
                WidgetStone::m_btnChecked->move(m_btns[index]->pos());
                QString style = WidgetStone::m_btnChecked->styleSheet();
                WidgetStone::m_btnChecked->setStyleSheet(style.replace(style.indexOf("yellow"), 6,  "#e09a53"));
                WidgetStone::m_btnChecked = nullptr;
                _move = m_state->get_best_move(4);
                st = m_state->board[_move.m_to_row][_move.m_to_col];
                if (st)
                    m_btns[st->index]->hide();
                m_state->apply_move(_move);
                m_btns[_move.index]->setGeometry(real_rect(_move.m_to_row, _move.m_to_col));
                return;
            }
            QString style = WidgetStone::m_btnChecked->styleSheet();
            WidgetStone::m_btnChecked->setStyleSheet(style.replace(style.indexOf("yellow"), 6,  "#e09a53"));
            WidgetStone::m_btnChecked = nullptr;
        });
    }
}

BoardWidget::~BoardWidget()
{
}
