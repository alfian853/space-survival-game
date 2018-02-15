#include "HpBoost.h"

sf::Texture *HpBoost::t1;
Animation *HpBoost::hpBoost_anim;


HpBoost::HpBoost()
{
	static bool first_call = true;
	if (first_call) {
		first_call = false;
		t1 = new sf::Texture();
		if (!t1->loadFromFile("images/hpBoost.png")) {
			printf("load file failed\n");
		}
		hpBoost_anim = new Animation(*t1, 0, 0, 49, 42, 1, 0);
		setType(EnType::HP_BOOST);
	}
	setType(EnType::HP_BOOST);
	this->settings(*hpBoost_anim, 0, rand() % H, rand() % 360, 25);
	sf::Vector2f cartesian_speed = gameUtil::get_movement(4, angle);
	this->setHp(75);
	dx = cartesian_speed.x;
	dy = cartesian_speed.y;
}


HpBoost::~HpBoost()
{
}

