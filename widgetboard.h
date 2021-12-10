#ifndef WIDGETBOARD_H
#define WIDGETBOARD_H

#include <QWidget>
#include <QButtonGroup>

class ChessState;
class WidgetStone;

class BoardWidget : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
public:
    explicit BoardWidget(QWidget *parent = nullptr);
    ~BoardWidget();
    int leftPadding = 30, topPadding = 30, D = 50;
    std::map<unsigned short, WidgetStone*> m_btns;
    ChessState* m_state;
};

#endif // WIDGETBOARD_H
