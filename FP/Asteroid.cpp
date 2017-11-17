#include "Asteroid.h"



asteroid::asteroid()
{
	//asteroid movement
	do {
		dx = rand() % 8 - 4;
		dy = rand() % 8 - 4;
	} while (dx == 0 || dy == 0);
	name = "asteroid";
	hp = 40;
}
void asteroid::setName(std::string new_name) {
	name = new_name;
}
void asteroid::update()
{
	x += dx;
	y += dy;

	if (x>W) x = 0;
	if (x<0) x = W;
	if (y>H) y = 0;
	if (y<0) y = H;
}
