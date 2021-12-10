#include "mainwindow.h"
#include "widgetboard.h"

#include <QScreen>
#include <QGuiApplication>

void CheckerBoard::setupUi()
{
    BoardWidget * board = new BoardWidget(this);
    QRect geo = QGuiApplication::primaryScreen()->geometry();         // 获取屏幕分辨率
    setCentralWidget(board);
    setGeometry(geo.width()/4, geo.height()/7, geo.width()/2, geo.height()*5/7);
}

CheckerBoard::CheckerBoard(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("中国象棋");
    setupUi();
}

CheckerBoard::~CheckerBoard()
{
}
