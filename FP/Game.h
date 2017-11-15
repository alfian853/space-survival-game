#pragma once
#include "Animation.h"
#include "Asteroid.h"
#include "bullet.h"
#include "Entity.h"
#include "player.h"

#include <iostream>
#include <time.h>


class Game
{
private:
	sf::Texture t1, t2, t3, t4, t5, t6, t7,t8,t9;
	sf::Sprite background;
	Animation sExplosion;
	Animation sRock;
	Animation sRock_small;
	Animation sBullet;
	Animation sPlayer;
	Animation sPlayer_go;
	Animation sPlayer_go_left;
	Animation sPlayer_go_right;
	Animation sExplosion_ship;
	Animation hpBoost;
	Animation sModeBoost;
	player *p;
	std::list<Entity*> entities;

	int skor;
	int next_lvl_score;
	const double next_lvl_factor = 1.25;
	int asteroid_factor;
	int hpBoost_factor;
	int sMode_factor;
	clock_t before_t,current_t;


	void reset_game();
public:
//	int W, H;
	Game();
	void run_game();
	bool isCollide(Entity *a, Entity *b);
	~Game();
};
