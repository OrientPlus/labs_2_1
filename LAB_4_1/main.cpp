#include "gomoku.h"
#include "Board.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Board board;
    gomoku w(QApplication a, Board board);
    w().show();
    return a.exec();
}
