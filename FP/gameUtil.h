#pragma once
#include <SFML\Graphics.hpp>
class GameUtil
{
public:
	static const double phi;
	static const float DEGTORAD;
	static sf::Vector2f get_movement(float speed,float angle);
	static bool isCollide(double x1, double y1, double R1, double x2, double y2, double R2);
	static double compute_angle(double x1, double y1, double x2, double y2);
	static sf::Vector2i getRandomSpawn(int w,int h);
	static sf::Vector2i getRandomSpawn(int w1,int h1,int w2,int h2);
	GameUtil();
	~GameUtil();
};

