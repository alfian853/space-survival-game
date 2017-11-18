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

void Entity::update()
{
	x += dx;
	y += dy;

	if (x>W) x = 0;
	if (x<0) x = W;
	if (y>H) y = 0;
	if (y<0) y = H;
}

sf::Vector2f Entity::get_possition() {
	return sf::Vector2f(x, y);
}


void Entity::draw(sf::RenderWindow &app)
{
	anim.sprite.setPosition(x, y);
	anim.sprite.setRotation(angle + 90);
	app.draw(anim.sprite);
}

void Entity::set_name(std::string name) {
	this->name = name;
}