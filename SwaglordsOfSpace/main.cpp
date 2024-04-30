#include "Game.h"
#include <time.h>

int main()
{
	srand(time(static_cast<time_t*>(0)));

	Game game;

	game.run();

	return 0;
}