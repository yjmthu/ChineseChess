#ifndef BOARDWIDGET_H
#define BOARDWIDGET_H

#include <QWidget>

class StoneWidget;

class BoardWidget : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent* event);
public:
    explicit BoardWidget(QWidget *parent = nullptr);
    ~BoardWidget();
    int leftPadding = 30, topPadding = 30, D = 50;
    std::vector<StoneWidget*> m_btns;

signals:

};

#endif // BOARDWIDGET_H
