#include "checkerboard.h"
#include "ui_checkerboard.h"

CheckerBoard::CheckerBoard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CheckerBoard)
{
    ui->setupUi(this);
}

CheckerBoard::~CheckerBoard()
{
    delete ui;
}

