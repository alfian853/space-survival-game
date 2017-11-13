#pragma once
#include "Animation.h"

class Entity
{
public:
	static const int W = 1200;//width
	static const int H = 800;//heigth
	float DEGTORAD = 0.017453f;
	float x, y, dx, dy, R, angle;
	bool life;
	std::string name;
	Animation anim;
	//virtual void setImage();
	Entity();
	void settings(Animation &a, int X, int Y, float Angle = 0, int radius = 1);

	virtual void update();

	void draw(sf::RenderWindow &app);

};
