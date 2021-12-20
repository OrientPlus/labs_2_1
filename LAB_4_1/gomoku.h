#ifndef GOMOKU_H
#define GOMOKU_H

#include <QMainWindow>
#include "Board.hpp"
#include "ui_gomoku.h"

enum class Players { KRESTIK, NOLIK, _COUNT };

QT_BEGIN_NAMESPACE
namespace Ui { class gomoku; }
QT_END_NAMESPACE

class gomoku : public QMainWindow
{
    Q_OBJECT

    Players current_player;
public:
     gomoku(QWidget *parent = nullptr);
     ~gomoku();

private:
    Ui::gomoku *ui;
    Board *Board;
    void inputMove();
    void run();
};



#endif // GOMOKU_H
