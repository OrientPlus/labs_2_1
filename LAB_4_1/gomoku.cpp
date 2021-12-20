#include "gomoku.h"
#include "ui_gomoku.h"
#include "Board.hpp"

gomoku::gomoku(QWidget *parent) : QMainWindow(parent),
   ui(new Ui::gomoku)
{
    board = new Board();
    ui->setupUi(this);
    current_player = Players::KRESTIK;
};

void gomoku::run()
{
    while (board.get_status_game() == WIN_TYPE::NONE)
            {
                inputMove(board);
                current_player = static_cast<Players>((static_cast<int>(current_player)
                    + 1) % static_cast<int>(Players::_COUNT));
            }
    if (board.get_status_game() == WIN_TYPE::KRESTIK)
    {
        ui->lineEdit->setText("KRESTIK PLAYER WIN!");
    } else if (board.get_status_game() == WIN_TYPE::NOLIK){
        ui->lineEdit->setText("NOLIK PLAYER WIN!");
    }
}

void gomoku::inputMove()
{
    QString pos;
    CELL_TYPE cell_value = CELL_TYPE::NONE;
    if (current_player == Players::KRESTIK)
    {
        pos = "X";
         cell_value = CELL_TYPE::KRESTIK;
    } else if(current_player == Players::NOLIK){
        pos = "O";
        cell_value = CELL_TYPE::NOLIK;
    }

    if (ui->x11->isChecked() && board.set_cell(0, 0, cell_value) == true)
    {
        ui->x11->setText(pos);
        ui->x11->setEnabled(false);
    }
    if (ui->x12->isChecked() && board.set_cell(0, 1, cell_value) == true)
    {
        ui->x12->setText(pos);
        ui->x12->setEnabled(false);
    }
    if (ui->x13->isChecked() && board.set_cell(0, 2, cell_value) == true)
    {
        ui->x13->setText(pos);
        ui->x13->setEnabled(false);
    }
    if (ui->x21->isChecked() && board.set_cell(1, 0, cell_value) == true)
    {
        ui->x21->setText(pos);
        ui->x21->setEnabled(false);
    }
    if (ui->x22->isChecked() && board.set_cell(1, 1, cell_value) == true)
    {
        ui->x22->setText(pos);
        ui->x22->setEnabled(false);
    }
    if (ui->x23->isChecked() && board.set_cell(1, 2, cell_value) == true)
    {
        ui->x23->setText(pos);
        ui->x23->setEnabled(false);
    }
    if (ui->x31->isChecked() && board.set_cell(2, 0, cell_value) == true)
    {
        ui->x31->setText(pos);
        ui->x31->setEnabled(false);
    }
    if (ui->x32->isChecked() && board.set_cell(2, 1, cell_value) == true)
    {
        ui->x32->setText(pos);
        ui->x32->setEnabled(false);
    }
    if (ui->x33->isChecked() && board.set_cell(2, 2, cell_value) == true)
    {
        ui->x33->setText(pos);
        ui->x33->setEnabled(false);
    }

}

