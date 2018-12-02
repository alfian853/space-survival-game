#pragma once
#include "Entity.h"
#include "GameUtil.h"
#include <chrono>
class TimeBomb :
	public Entity
{
private:
	static Animation *bomb_anim;
	static sf::Texture *t1;
public:
	std::chrono::high_resolution_clock::time_point life_time;
	TimeBomb();
	~TimeBomb();
};

