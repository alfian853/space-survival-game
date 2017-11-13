#pragma once
#include "Animation.h"
#include "Asteroid.h"
#include "bullet.h"
#include "Entity.h"
#include "player.h"

class Game
{
private:
	sf::Texture t1, t2, t3, t4, t5, t6, t7;

	sf::Sprite background;
	Animation sExplosion;
	Animation sRock;
	Animation sRock_small;
	Animation sBullet;
	Animation sPlayer;
	Animation sPlayer_go;
	Animation sExplosion_ship;

	player *p;


	std::list<Entity*> entities;
public:
	static const int W = 1200;//width
	static const int H = 800;//heigth

	Game();
	void run_game();
	bool isCollide(Entity *a, Entity *b);
	~Game();
};
