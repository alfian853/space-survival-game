#pragma once
#include "Entity.h"
class player : public Entity
{
private:
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
	int hp;
	bool superMode;
	player();
	void update();
	void set_angle(double angle);
	void set_move_direction(int mv_mode);
	void set_hp(int x);
};
