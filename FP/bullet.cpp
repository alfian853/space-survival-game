#include "bullet.h"

bullet::bullet()
{
	name = "bullet";
}

void  bullet::update()
{
	dx = cos(angle*DEGTORAD) * 20;
	dy = sin(angle*DEGTORAD) * 20;
	// angle+=rand()%6-3;
	x += dx;
	y += dy;

	if (x>W || x<0 || y>H || y<0) life = 0;
}