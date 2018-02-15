#pragma once
#include "Animation.h"

enum EnType {ENTITY,SHIP, BULLET, ASTEROID, TIME_BOMB, HP_BOOST, SHOT_BOOST, COLLIDE_EFFECT};
class Entity {
protected:
	void setType(int x);
private:
	int enType;//karna enum tidak bisa static
public:
	float x, y, dx, dy, R, angle;
	int hp;
	std::string name;
	Animation anim;
	Entity();
	void settings(Animation &a, int X, int Y, float Angle = 0, int radius = 1);
	void setHp(int hp);
	void set_name(std::string name);
	virtual void update();
	sf::Vector2f get_possition();
	void draw(sf::RenderWindow &app);
	int getType();
	void colliding(Entity &enObj);
};
