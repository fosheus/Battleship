#include "Game.h"
#include "DEFINITIONS.h"
#include <cstdlib>
#include <ctime>
int main()
{
	srand(time(NULL));
	Game(SCREEN_WIDTH, SCREEN_HEIGHT, "SFML WORKS");

	return EXIT_SUCCESS;
}