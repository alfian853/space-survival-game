#pragma once
#include "Animation.h"

enum EnType {ENTITY,SHIP, BULLET, ASTEROID, TIME_BOMB, DEBUFF, BUFF, COLLIDE_EFFECT,EN_UFO,EN_COUNT=10};
class Entity {
protected:
private:
	int enType;//karna enum tidak bisa static
public:
	int hp;
	void setType(int x);
	float x, y, dx, dy, R, angle,rotateAngle,rotateSpeed;
	bool autoRotation;
	std::string name;
	Animation anim;
	Entity();
	void settings(Animation &a, int X, int Y, float Angle = 0, int radius = 1);
	void setHp(int hp);
	int getHp();
	void setAutoRotation(float rotateSpeed);
	void set_name(std::string name);
	virtual void update();
	sf::Vector2f get_possition();
	virtual void draw(sf::RenderWindow &app);
	int getType();
	void colliding(Entity &enObj);
};
