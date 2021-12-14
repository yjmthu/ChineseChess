#include "widgetboard.h"

#include "chessstone.h"
#include "widgetstone.h"
#include "chessstate.h"

#include <QPainter>
#include <QDebug>
#include <QResizeEvent>
#include <QTimer>
#include <QMessageBox>

void BoardWidget::paintEvent(QPaintEvent *)
{
    QPalette pal(palette());
    pal.setColor(QPalette::Window, QColor(0xEACCA6));
    setAutoFillBackground(true);
    setPalette(pal);

    QPainter painter(this);

    painter.setPen(QPen(Qt::black, 2));
    painter.drawLine(QPoint(leftPadding, topPadding), QPoint(leftPadding+8*D, topPadding));
    painter.drawLine(QPoint(leftPadding, topPadding+9*D), QPoint(leftPadding+8*D, topPadding+9*D));
    painter.drawLine(QPoint(topPadding, topPadding), QPoint(leftPadding, topPadding+9*D));
    painter.drawLine(QPoint(topPadding+8*D, topPadding), QPoint(leftPadding+8*D, topPadding+9*D));

    painter.setPen(QPen(Qt::red, 1));

    const int len = D / 6, dis = 2;
    std::array<QPoint, 10> lst {real_pos(2, 1), real_pos(2, 7), real_pos(7, 1), real_pos(7, 7), real_pos(3, 2), real_pos(3, 4), real_pos(3, 6), real_pos(6, 2), real_pos(6, 4), real_pos(6, 6)};
    std::array<QPoint, 2> lst_l = {real_pos(3, 0), real_pos(6, 0) }, lst_r {real_pos(6, 8), real_pos(3, 8)};
    for (const auto& i : lst) {
        painter.drawLine(i + QPoint(dis, dis), i + QPoint(dis, dis + len));
        painter.drawLine(i + QPoint(dis, dis), i + QPoint(dis + len, dis));
        painter.drawLine(i + QPoint(dis, -dis), i + QPoint(dis, -dis - len));
        painter.drawLine(i + QPoint(dis, -dis), i + QPoint(dis + len, -dis));
        painter.drawLine(i + QPoint(-dis, dis), i + QPoint(-dis, dis + len));
        painter.drawLine(i + QPoint(-dis, dis), i + QPoint(-dis - len, dis));
        painter.drawLine(i + QPoint(-dis, -dis), i + QPoint(-dis - len, -dis));
        painter.drawLine(i + QPoint(-dis, -dis), i + QPoint(-dis, -dis - len));
    }
    for (const auto& i: lst_l)
    {
        painter.drawLine(i + QPoint(dis, dis), i + QPoint(dis, dis + len));
        painter.drawLine(i + QPoint(dis, dis), i + QPoint(dis + len, dis));
        painter.drawLine(i + QPoint(dis, -dis), i + QPoint(dis, -dis - len));
        painter.drawLine(i + QPoint(dis, -dis), i + QPoint(dis + len, -dis));
    }

    for (const auto& i: lst_r)
    {
        painter.drawLine(i + QPoint(-dis, dis), i + QPoint(-dis, dis + len));
        painter.drawLine(i + QPoint(-dis, dis), i + QPoint(-dis - len, dis));
        painter.drawLine(i + QPoint(-dis, -dis), i + QPoint(-dis - len, -dis));
        painter.drawLine(i + QPoint(-dis, -dis), i + QPoint(-dis, -dis - len));
    }

    painter.setPen(QPen(Qt::black, 1));

    for(int i = 1; i < 9; i++)
        painter.drawLine(QPoint(leftPadding, topPadding+i*D), QPoint(leftPadding+8*D, topPadding+i*D));
    for(int i = 1; i < 8; i++)
    {
        painter.drawLine(real_pos(0, i), real_pos(4, i));
        painter.drawLine(real_pos(5, i), real_pos(9, i));
    }

    painter.drawLine(real_pos(0, 3), real_pos(2, 5));
    painter.drawLine(real_pos(2, 3), real_pos(0, 5));
    painter.drawLine(real_pos(7, 3), real_pos(9, 5));
    painter.drawLine(real_pos(9, 3), real_pos(7, 5));

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

        QTimer::singleShot(100, this, [this](){
            ChessMove _move = m_state->get_best_move(5);
            const auto st = m_state->board[_move.m_to_row][_move.m_to_col];
            if (st) m_btns[st->index]->hide();
            m_state->apply_move(_move);
            m_btns[_move.index]->setGeometry(real_rect(_move.m_to_row, _move.m_to_col));
            if (m_state->get_winer() == ChessPlayer::BLACK)
            {
                QMessageBox::information(this, "提示", "恭喜, 您输得很惨了!");
                return ;
            }
        });

        return;
    }
    QString style = WidgetStone::m_btnChecked->styleSheet();
    WidgetStone::m_btnChecked->setStyleSheet(style.replace(style.indexOf("yellow"), 6,  "#e09a53"));
    WidgetStone::m_btnChecked = nullptr;
}


BoardWidget::BoardWidget(QWidget *parent) : QWidget(parent), m_state(new ChessState(ChessPlayer::BLACK))
{
    unsigned char i = 0;
    for (auto j : m_state->stones) {
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
                if (m_state->get_winer() == ChessPlayer::RED)
                {
                    QMessageBox::information(this, "提示", "可惜了, 您终于获胜了!");
                    return ;
                }
                QTimer::singleShot(100, this, [this](){
                    ChessMove _move = m_state->get_best_move(5);
                    auto st = m_state->board[_move.m_to_row][_move.m_to_col];
                    if (st)
                        m_btns[st->index]->hide();
                    m_state->apply_move(_move);
                    m_btns[_move.index]->setGeometry(real_rect(_move.m_to_row, _move.m_to_col));
                    if (m_state->get_winer() == ChessPlayer::BLACK)
                    {
                        QMessageBox::information(this, "提示", "恭喜恭喜, 您输得很惨了!");
                        return ;
                    }
                });
                return;
            }
            QString style = WidgetStone::m_btnChecked->styleSheet();
            WidgetStone::m_btnChecked->setStyleSheet(style.replace(style.indexOf("yellow"), 6,  "#e09a53"));
            WidgetStone::m_btnChecked = nullptr;
        });
        ++i;
    }
}

BoardWidget::~BoardWidget()
{
}
