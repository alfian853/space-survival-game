#pragma once
#include "Entity.h"
#include <chrono>
class TimeBomb :
	public Entity
{
public:
	std::chrono::high_resolution_clock::time_point life_time;

	TimeBomb();
	~TimeBomb();
};

