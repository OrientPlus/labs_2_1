#include "gomoku.h"
#include "ui_gomoku.h"

#include <QMessageBox>


gomoku::gomoku(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::gomoku)
{
    current_player = Players::KRESTIK;
    ui->setupUi(this);
    connect(ui->tableWidget, &QTableWidget::cellChanged , this, &gomoku::run);
    connect(ui->pushButton, SIGNAL(clicked()), SLOT(restart()));
}

gomoku::~gomoku()
{
    delete ui;
}

void gomoku::createBoard(Board &_board)
{
    ui->tableWidget->setRowCount(_board.get_size());
    ui->tableWidget->setColumnCount(_board.get_size());

    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(50);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(50);
}

void gomoku::run()
{
    CELL_TYPE cell_value;

    if (current_player == Players::KRESTIK)
    {
        cell_value = CELL_TYPE::KRESTIK;
    }
    else if (current_player == Players::NOLIK)
    {
        cell_value = CELL_TYPE::NOLIK;
    }
    _board.set_cell(ui->tableWidget->currentColumn(), ui->tableWidget->currentRow(), cell_value);

    if (_board.get_status_game() != WIN_TYPE::NONE)
    {
       QMessageBox box;

       if (_board.get_status_game() == WIN_TYPE::KRESTIK)
       {
           box.setTextFormat(Qt::RichText);
           box.setText("KRESTIK PLAYER WIN!");
       }
       if (_board.get_status_game() == WIN_TYPE::NOLIK)
       {
           box.setTextFormat(Qt::RichText);
           box.setText("NOLIK PLAYER WIN!");
       }
       if (_board.get_status_game() == WIN_TYPE::DRAW)
       {
           box.setTextFormat(Qt::RichText);
           box.setText("DRAW!");
       }
       box.exec();
    }

        current_player = static_cast<Players>((static_cast<int>(current_player)
                    + 1) % static_cast<int>(Players::_COUNT));

}

void gomoku::restart()
{
    _board.restart();
    current_player = Players::KRESTIK;
    ui->tableWidget->clear();
}

