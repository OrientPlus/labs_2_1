#pragma once
#include "Board.hpp"
#include "ConsoleGraphic.hpp"

#include <iostream>
#include <locale>
#include <exception>

enum class Players { KRESTIK, NOLIK, _COUNT };

class BoardView
{
	Board& board;
	Players current_player;

public:
	BoardView(Board& _board) : board(_board)
	{
		current_player = Players::KRESTIK;
	}

	void run()
	{
		while (board.get_status_game() == WIN_TYPE::NONE)
		{
			system("cls");
			draw();
			input_move();
			current_player = static_cast<Players>((static_cast<int>(current_player)
				+ 1) % static_cast<int>(Players::_COUNT));
		}
		system("cls");
		draw();
		if (board.get_status_game() == WIN_TYPE::KRESTIK)
			std::cout << "KRESTIK PLAYER WIN!" << std::endl;
		else if (board.get_status_game() == WIN_TYPE::NOLIK)
			std::cout << "NOLIK PLAYER WIN!" << std::endl;
		else {
			std::cout << "NO ONE WON!" << std::endl;
		}
	}

	void input_move()
	{
		int x, y;
		std::string pos;
		CELL_TYPE cell_value = CELL_TYPE::NONE;
		do
		{
			std::cout << "Enter coords(y,x):" << std::endl;
			std::cin >> pos;

			if (pos[0] == 'q')
			{
				x = 0; y = 0;
			}
			else if (pos[0] == 'w')
			{
				x = 1; y = 0;
			}
			else if (pos[0] == 'e')
			{
				x = 2; y = 0;
			}
			else if (pos[0] == 'a')
			{
				x = 0; y = 1;
			}
			else if (pos[0] == 's') 
			{
				x = 1; y = 1;
			}
			else if (pos[0] == 'd')
			{
				x = 2; y = 1;
			}
			else if (pos[0] == 'z')
			{
				x = 0; y = 2;
			}
			else if (pos[0] == 'x')
			{
				x = 1; y = 2;
			}
			else if (pos[0] == 'c')
			{
				x = 2; y = 2;
			}

			if (current_player == Players::KRESTIK)
				cell_value = CELL_TYPE::KRESTIK;
			else if (current_player == Players::NOLIK)
				cell_value = CELL_TYPE::NOLIK;
		} while (board.set_cell(y, x, cell_value) == false);
	}

	void draw()
	{
		int size = board.get_size();
		char cell;
		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j)
			{
				switch (board.get_cell(i, j))
				{
				case CELL_TYPE::NONE:
					cell = '?';
					break;
				case CELL_TYPE::KRESTIK:
					cell = 'X';
					break;
				case CELL_TYPE::NOLIK:
					cell = 'O';
					break;
				default:
					break;
				}
				std::cout << cell;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
};