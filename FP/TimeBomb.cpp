#include "TimeBomb.h"


Animation *TimeBomb::bomb_anim;
sf::Texture *TimeBomb::t1;

TimeBomb::TimeBomb()
{
	life_time = std::chrono::high_resolution_clock::now();
	static bool first_call = true;
	if (first_call){
		t1 = new sf::Texture();
		if (!t1->loadFromFile("images/time_bomb.png")) {
			printf("load file failed\n");
		}
		bomb_anim =new Animation(*t1, 0, 0, 48, 49, 3, 0.1);
		first_call = false;
	}
	setType(EnType::TIME_BOMB);
	sf::Vector2i randSpawn = GameUtil::getRandomSpawn(W,H);

	this->settings(*bomb_anim, randSpawn.x, randSpawn.y, rand() % 360, 25);
	this->setAutoRotation(3);
	this->setHp(300);

	sf::Vector2f cartesian_speed = GameUtil::get_movement(5, angle);
	dx = cartesian_speed.x;
	dy = cartesian_speed.y;



}


TimeBomb::~TimeBomb()
{
}
