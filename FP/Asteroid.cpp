#include "Asteroid.h"



asteroid::asteroid()
{
	//asteroid movement
	do {
		dx = rand() % 8 - 4;
		dy = rand() % 8 - 4;
	} while (dx == 0 || dy == 0);
	name = "asteroid";
	hp = 20;
}