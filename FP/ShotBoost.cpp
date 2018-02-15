#include "ShotBoost.h"

sf::Texture *ShotBoost::t1;
Animation *ShotBoost::shotBoost_anim;



ShotBoost::ShotBoost()
{
	static bool first_call = true;
	if (first_call) {
		first_call = false;
		t1 = new sf::Texture();
		if (!t1->loadFromFile("images/diamond.png")) {
			printf("load file failed\n");
		}
		shotBoost_anim = new Animation(*t1, 0, 0, 32, 32, 8, 0.2);

	}
	setType(EnType::SHOT_BOOST);
	this->settings(*shotBoost_anim, 0, rand() % H, rand() % 360, 25);
	sf::Vector2f cartesian_speed = gameUtil::get_movement(4, angle);
	this->setHp(100);
	dx = cartesian_speed.x;
	dy = cartesian_speed.y;

}


ShotBoost::~ShotBoost()
{
}
