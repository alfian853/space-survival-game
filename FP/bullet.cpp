#include "bullet.h"

bullet::bullet()
{
	name = "bullet";
	superMode = false;
	hp = 20;
}

void  bullet::update()
{
	dx = cos(angle*DEGTORAD) * 20;
	dy = sin(angle*DEGTORAD) * 20;
	x += dx;
	y += dy;

	if (superMode) {
		if (x > W) x = 0;
		if (x < 0) x = W;
		if (y > H) y = 0;
		if (y < 0) y = H;
	}
	else if (x>W || x<0 || y>H || y<0) hp = -1;
}