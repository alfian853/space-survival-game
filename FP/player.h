#pragma once
#include "Entity.h"
#include "gameUtil.h"
class player : public Entity
{
private:
	static Animation *ship_idle,*ship_go,*ship_go_left,*ship_go_right;
	static sf::Texture *t1,*t2,*t3,*t4;
public:
//	bool thrust;
	/*
	0 not move
	1 move forward
	2 move backward
	3 move left
	4 move right
	*/
	int move_direction;
	bool superMode;
	sf::Vector2f cartesian_speed;
	player();
	void update()override;
	void set_angle(double angle);
};
