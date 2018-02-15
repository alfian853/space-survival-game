#pragma once
#include "Entity.h"
#include "gameUtil.h"

class ShotBoost :
	public Entity
{
private:
	static sf::Texture *t1;
	static Animation *shotBoost_anim;

public:
	ShotBoost();
	~ShotBoost();
};

