#include "Debuff.h"

std::vector<sf::Texture> Debuff::txture;
std::vector<Animation> Debuff::vecAnim;


Debuff::Debuff(DebuffType opt)
{
	static bool first_call = true;
	if (first_call) {
		first_call = false;
		txture.resize(DebuffType::DEBUFF_COUNT);
		vecAnim.resize(DebuffType::DEBUFF_COUNT);
		txture[DebuffType::LOW_DAMAGE].loadFromFile("images/lowDamageItem.png");
		vecAnim[DebuffType::LOW_DAMAGE]=Animation(txture[DebuffType::LOW_DAMAGE], 0, 0, 49, 42, 1, 0);
		setType(EnType::DEBUFF);
	}
	setType(EnType::DEBUFF);
	sf::Vector2f cartesian_speed;
	sf::Vector2i randSpawn = GameUtil::getRandomSpawn(W,H);
	switch (opt)
	{
	case LOW_DAMAGE:
		this->settings(vecAnim[DebuffType::LOW_DAMAGE], randSpawn.x, randSpawn.y, rand() % 360, 25);
		cartesian_speed = GameUtil::get_movement(7, angle);
		dx = cartesian_speed.x;
		dy = cartesian_speed.y;
		break;
	default:
		break;
	}
	this->setAutoRotation(3);
	this->setHp(70);
}

int Debuff::getDebuffTimeLimit(DebuffType opt) {

	static std::vector<int> buffDuration;
	static bool firstcall = true;
	if (firstcall) {
		firstcall = false;
		buffDuration.resize(DebuffType::DEBUFF_COUNT);
		buffDuration[DebuffType::LOW_DAMAGE] = 7000;
	}
	return buffDuration[opt];

}



Debuff::~Debuff()
{
}

