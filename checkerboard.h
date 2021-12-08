#ifndef CHECKERBOARD_H
#define CHECKERBOARD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CheckerBoard; }
QT_END_NAMESPACE

class CheckerBoard : public QMainWindow
{
    Q_OBJECT

public:
    CheckerBoard(QWidget *parent = nullptr);
    ~CheckerBoard();

private:
    Ui::CheckerBoard *ui;
};
#endif // CHECKERBOARD_H
