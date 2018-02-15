#include "player.h"
#include <stdio.h>

Animation *player::ship_idle,
*player::ship_go_left,*player::ship_go_right,*player::ship_go;
sf::Texture *player::t1;


player::player()
{
	move_direction = 0;
	hp = 100;
	superMode = false;

	static bool first_call = true;
	if (first_call) {
		first_call = false;
		t1 = new sf::Texture();
		if (!t1->loadFromFile("images/spaceship.png")) {
			printf("load file failed\n");
		}
		ship_idle = new Animation(*t1, 40, 0, 40, 40, 1, 0);
		
		t1 = new sf::Texture();
		if (!t1->loadFromFile("images/spaceship.png")) {
			printf("load file failed\n");
		}
		ship_idle	  = new Animation(*t1, 40, 0, 40, 40, 1, 0);
		ship_go_left = new Animation(*t1, 80, 40, 40, 40, 1, 0);
		ship_go_right  = new Animation(*t1, 0, 40, 40, 40, 1, 0);
		ship_go       = new Animation(*t1, 40, 40, 40, 40, 1, 0);
	}
	this->settings(*ship_idle, W / 2, H / 2, 0, 16);
	setType(EnType::SHIP);

}


void player::set_angle(double angle) {
	this->angle = angle;
}
void player::update()
{
	cartesian_speed = gameUtil::get_movement(0.12f, angle);
	if (move_direction == 1) {
		dx += cartesian_speed.x;
		dy += cartesian_speed.y;
		anim = *ship_go;
	}
	else if (move_direction == 2) {
		dx -= cartesian_speed.x;
		dy -= cartesian_speed.y;
		anim = *ship_go;
	}
	else if (move_direction == 3) {
		dx -= cartesian_speed.y;
		dy += cartesian_speed.x;;
		anim = *ship_go_left;
	}
	else if (move_direction == 4) {
		dx += cartesian_speed.y;
		dy -= cartesian_speed.x;
		anim = *ship_go_right;
	}
	else{
		anim = *ship_idle;
		dx *= 0.81;
		dy *= 0.81;
	}
	float maxSpeed = 7.5;
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
