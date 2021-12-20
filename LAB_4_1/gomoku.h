#ifndef GOMOKU_H
#define GOMOKU_H

#include <QMainWindow>
#include "Board.hpp"
#include "ui_gomoku.h"

enum class Players { KRESTIK, NOLIK, _COUNT };

QT_BEGIN_NAMESPACE
namespace Ui { class gomoku; }
QT_END_NAMESPACE

class gomoku : public QMainWindow, public Board
{
    Q_OBJECT

    Board &board;
    Players current_player;
public:
     gomoku(QWidget *parent, Board &_board) : QMainWindow(parent), board (_board)
       , ui(new Ui::gomoku)
     {
         ui->setupUi(this);
         current_player = Players::KRESTIK;
     };
    ~gomoku()
     {
         delete ui;
     };

private:
    Ui::gomoku *ui;

    void inputMove();
    void run();
};



#endif // GOMOKU_H
