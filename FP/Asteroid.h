#pragma once
#include "Entity.h"
#include <SFML\Graphics.hpp>

class asteroid : public Entity
{
public:
	sf::Texture asdj;
	asteroid();
	void  update();
	
};