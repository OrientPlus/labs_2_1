#ifndef GOMOKU_H
#define GOMOKU_H

#include <QMainWindow>

#include "Board.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class gomoku; }
QT_END_NAMESPACE

enum class Players { KRESTIK, NOLIK, _COUNT };

class gomoku : public QMainWindow
{
    Q_OBJECT

public:
    Board _board;
    gomoku(QWidget *parent = nullptr);
    ~gomoku();
    Players current_player;
public slots:
    void createBoard(Board &_board);
    void run();
    void restart();

private:
    Ui::gomoku *ui;
};
#endif // GOMOKU_H
