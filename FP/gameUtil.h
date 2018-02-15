#pragma once
#include <SFML\Graphics.hpp>
class gameUtil
{
public:
	static const float DEGTORAD;
	static sf::Vector2f get_movement(float speed,float angle);
	static bool isCollide(double x1, double y1, double R1, double x2, double y2, double R2);
	gameUtil();
	~gameUtil();
};

