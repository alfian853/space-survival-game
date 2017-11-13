#pragma once
#include "Animation.h"
#include "Asteroid.h"
#include "bullet.h"
#include "Entity.h"
#include "player.h"

class Game
{
public:
	static const int W = 1200;//width
	static const int H = 800;//heigth
	Game();
	void run_game();
	bool isCollide(Entity *a, Entity *b);
	~Game();
};
