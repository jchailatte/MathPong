#include "Game.h"
#include <ctime>
#include <cstdlib> 

int main(int argc, char** argv)
{
	Game game;
	if (game.Initialize() == true)
	{
		game.RunLoop();
		game.Shutdown();
	}

	return 0;
}
