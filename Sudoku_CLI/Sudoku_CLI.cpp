#include "Game.h"

int main()
{
	Game game;
	game.main_menu();
	game.run();

	std::cout << "Press any key to exit..." << std::flush;
	_getch();
}
