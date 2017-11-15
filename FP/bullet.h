#pragma once
#include "Entity.h"
class bullet : public Entity
{
public:
	bool superMode;
	bullet();
	void update();
};