#include "TimeBomb.h"



TimeBomb::TimeBomb()
{
	//asteroid movement
	do {
		dx = rand() % 8 - 4;
		dy = rand() % 8 - 4;
	} while (dx == 0 || dy == 0);
	name = "asteroid";
	hp = 80;

	life_time = std::chrono::high_resolution_clock::now();
}


TimeBomb::~TimeBomb()
{
}
