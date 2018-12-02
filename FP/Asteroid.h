#pragma once
#include "Entity.h"
#include "GameUtil.h"
#include <SFML\Graphics.hpp>

enum AstType {SMALL_ASTEROID,NORMAL_ASTEROID,HARD_ASTEROID};

class Asteroid : public Entity
{
private:
	static Animation *small_rock,*rock,*hard_rock;
	static sf::Texture *t1, *t2, *t3;
	AstType rock_type;
public:
	Asteroid(AstType opt, int x = -1, int y = -1);
	AstType get_asteroidType();
};