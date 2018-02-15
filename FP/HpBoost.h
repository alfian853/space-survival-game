#pragma once
#include "Entity.h"
#include "gameUtil.h"
class HpBoost :
	public Entity
{
private:
	static sf::Texture *t1;
	static Animation *hpBoost_anim;
public:
	HpBoost();
	~HpBoost();
};

