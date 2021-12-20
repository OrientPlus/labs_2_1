#include "gomoku.h"
#include "Board.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gomoku w;
    w.show();
    return a.exec();
}
