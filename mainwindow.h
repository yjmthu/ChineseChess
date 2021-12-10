#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CheckerBoard; }
QT_END_NAMESPACE

class CheckerBoard : public QMainWindow
{
    Q_OBJECT
private:
    void setupUi();
public:
    CheckerBoard(QWidget *parent = nullptr);
    ~CheckerBoard();
};
#endif // MAINWINDOW_H
