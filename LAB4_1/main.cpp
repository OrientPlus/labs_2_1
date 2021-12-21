#include "gomoku.h"
#include "Board.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gomoku w;
    Board board;
    w.createBoard(board);
    w.show();
    return a.exec();
}
