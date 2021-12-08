#include "checkerboard.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CheckerBoard w;
    w.show();
    return a.exec();
}
