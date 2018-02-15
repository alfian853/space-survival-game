#pragma once
#include "Entity.h"
#include <SFML\Graphics.hpp>

enum AstType {SMALL_ASTEROID,NORMAL_ASTEROID,HARD_ASTEROID};

class asteroid : public Entity
{
private:
	static Animation *small_rock,*rock,*hard_rock;
	static sf::Texture *t1, *t2, *t3;
	int rock_type;
public:
	asteroid(AstType opt,int x=rand()/W,int y=rand()/H);
	int get_asteroidType();
};