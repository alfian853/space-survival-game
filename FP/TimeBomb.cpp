#include "TimeBomb.h"


Animation *TimeBomb::bomb_anim;
sf::Texture *TimeBomb::t1;

TimeBomb::TimeBomb()
{
	//asteroid movement
	do {
		dx = rand() % 8 - 4;
		dy = rand() % 8 - 4;
	} while (dx == 0 || dy == 0);


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
	this->settings(*bomb_anim, 0, rand() % H, rand() % 360, 25);
	hp = 100;

	


}


TimeBomb::~TimeBomb()
{
}
