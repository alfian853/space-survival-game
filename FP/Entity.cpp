#include "Entity.h"


Entity::Entity()
{
	hp = 20;
}
void Entity::setHp(int hp) { this->hp = hp; }
void Entity::settings(Animation &a, int X, int Y, float Angle, int radius)
{
	anim = a;
	x = X; y = Y;
	angle = Angle;
	R = radius;
}

void Entity::update() {};

sf::Vector2f Entity::get_possition() {
	return sf::Vector2f(x, y);
}


void Entity::draw(sf::RenderWindow &app)
{

	anim.sprite.setPosition(x, y);
	anim.sprite.setRotation(angle + 90);
	app.draw(anim.sprite);
}
