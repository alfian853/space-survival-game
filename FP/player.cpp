#include "player.h"
#include <stdio.h>

player::player()
{
	name = "player";
	move_direction = 0;
	hp = 100;
	superMode = false;
}
void player::set_angle(double angle) {
	this->angle = angle;
}
void player::update()
{

	if (move_direction == 1) {
		dx += cos(angle*DEGTORAD)*0.12;
		dy += sin(angle*DEGTORAD)*0.12;
	}
	else if (move_direction == 2) {
		dx -= cos(angle*DEGTORAD)*0.12;
		dy -= sin(angle*DEGTORAD)*0.12;
	}
	else if (move_direction == 3) {

	}
	else if (move_direction == 4) {

	}
	else
	{
		dx *= 0.83;
		dy *= 0.83;
	}
	int maxSpeed = 10;
	float speed = sqrt(dx*dx + dy*dy);
	if (speed > maxSpeed){
			dx *= maxSpeed / speed;
			dy *= maxSpeed / speed;
	}

	x += dx;
	y += dy;
	if (x>W) x = 0; if (x<0) x = W;
	if (y>H) y = 0; if (y<0) y = H;
}
