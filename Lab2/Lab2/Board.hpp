#pragma once
#include <vector>

enum class CELL_TYPE { NONE, KRESTIK, NOLIK };

enum class WIN_TYPE { NONE, KRESTIK, NOLIK, DRAW };

class Board
{
	const int size;
	std::vector<std::vector<CELL_TYPE>> field;
	WIN_TYPE game_status;

public:

	Board(int _size = 3) : size(_size)
	{
		field.resize(size);
		for (int i = 0; i < size; ++i)
		{
			field[i].resize(size, CELL_TYPE::NONE);
		}
		game_status = WIN_TYPE::NONE;
	}

	int get_size() const { return size; }

	CELL_TYPE get_cell(int i, int j) const
	{
		return field[i][j];
	}

	bool set_cell(unsigned int i, unsigned int j, CELL_TYPE cell_value)
	{
		if (i < size && j < size && field[i][j] == CELL_TYPE::NONE)
		{
			field[i][j] = cell_value;
			return true;
		}
		else
			return false;
	}

	WIN_TYPE get_status_game()
	{
		// ???
		int str_flag = 0, column_flag = 0, diag_flag = 0;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (field[i][j] == CELL_TYPE::KRESTIK)
					str_flag++;
				else if (field[i][j] == CELL_TYPE::NOLIK){
					str_flag--;
				}

				if (field[j][i] == CELL_TYPE::KRESTIK)
					column_flag++;
				else if (field[j][i] == CELL_TYPE::NOLIK) {
					column_flag--;
				}

				if (field[j][j] == CELL_TYPE::KRESTIK)
					diag_flag++;
				else if (field[j][j] == CELL_TYPE::NOLIK) {
					diag_flag--;
				}
			}
			if (str_flag == 3 || column_flag == 3 || diag_flag == 3)
			{
				game_status = WIN_TYPE::KRESTIK;
				return game_status;
			}
			else if (str_flag == -3 || column_flag == -3 || diag_flag == -3) {
				game_status = WIN_TYPE::NOLIK;
				return game_status;
			}
			else {
				game_status = WIN_TYPE::NONE;
				return game_status;
			}
			str_flag = 0;
			column_flag = 0;
			diag_flag = 0;
		}
	}
};