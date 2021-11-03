#include <exception>

#include "Board.hpp"
#include "BoardView.hpp"
#include "ConsoleGraphic.hpp"

int main()
{
	hidecursor();
	setcolor(1);
	setconsoletextsize(30);
	setconsolesize(500, 500);
	char choise = 'y';

	try
	{
		while (choise == 'y')
		{
			Board board;
			BoardView board_view(board);
			board_view.run();
			std::cout << std::endl << "Press 'y' if you want to play again or any other key to exit: ";
			std::cin >> choise;
		}
		
	}
	catch (const std::exception& ex)
	{
		std::cerr << "Standart exception: " << ex.what() << std::endl;
	}
	catch ()
	{
		
	}
	system("pause");
	return 0;
}