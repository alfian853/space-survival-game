#include "Buff.h"

std::vector<sf::Texture> Buff::txture;
std::vector<Animation> Buff::vecAnim;
sf::SoundBuffer *Buff::soundBuffer;
sf::Sound *Buff::buffSound;


Buff::Buff(BuffType opt)
{
	static bool first_call = true;
	this->boostType = opt;
	if (first_call) {

		txture.resize(BuffType::BOOST_COUNT);
		vecAnim.resize(BuffType::BOOST_COUNT);

		txture[BuffType::RANGE_BOOST].loadFromFile("images/purpleCrystal.png");
		txture[BuffType::DAMAGE_BOOST].loadFromFile("images/redCrystal.png");
		txture[BuffType::FREEZER_BOOST].loadFromFile("images/blueCrystal.png");
		txture[BuffType::SHIELD_BOOST].loadFromFile("images/greyCrystal.png");
		txture[BuffType::REGEN_BOOST].loadFromFile("images/greenCrystal.png");

		vecAnim[BuffType::RANGE_BOOST] = Animation(txture[BuffType::RANGE_BOOST], 0, 0, 32, 32, 8, 0.2);
		vecAnim[BuffType::DAMAGE_BOOST] = Animation(txture[BuffType::DAMAGE_BOOST], 0, 0, 32, 32, 8, 0.2);
		vecAnim[BuffType::FREEZER_BOOST] = Animation(txture[BuffType::FREEZER_BOOST], 0, 0, 32, 32, 8, 0.2);
		vecAnim[BuffType::SHIELD_BOOST] = Animation(txture[BuffType::SHIELD_BOOST], 0, 0, 32, 32, 8, 0.2);
		vecAnim[BuffType::REGEN_BOOST] = Animation(txture[BuffType::REGEN_BOOST], 0, 0, 32, 32, 8, 0.2);

		soundBuffer = new sf::SoundBuffer();
		soundBuffer->loadFromFile("sound/getbuff.ogg");
		buffSound = new sf::Sound();
		buffSound->setBuffer(*soundBuffer);



		setType(EnType::BUFF);

	}
	sf::Vector2i randSpawn = GameUtil::getRandomSpawn(W,H);

	switch (opt)
	{
	case RANGE_BOOST:
		this->settings(vecAnim[BuffType::RANGE_BOOST],randSpawn.x,randSpawn.y, rand() % 360, 25);
		break;
	case DAMAGE_BOOST:
		this->settings(vecAnim[BuffType::DAMAGE_BOOST], randSpawn.x, randSpawn.y, rand() % 360, 25);
		break;
	case FREEZER_BOOST:
		this->settings(vecAnim[BuffType::FREEZER_BOOST], randSpawn.x, randSpawn.y, rand() % 360, 25);
		break;
	case SHIELD_BOOST:
		this->settings(vecAnim[BuffType::SHIELD_BOOST], randSpawn.x, randSpawn.y, rand() % 360, 25);
		break;
	case REGEN_BOOST:
		this->settings(vecAnim[BuffType::REGEN_BOOST], randSpawn.x, randSpawn.y, rand() % 360, 25);
	default:
		break;
	}

	sf::Vector2f cartesian_speed = GameUtil::get_movement(4, angle);
	this->setHp(70);
	dx = cartesian_speed.x; 
	dy = cartesian_speed.y;

}
BuffType Buff::getBoostType() {
	return boostType;
}

void Buff::bufferSoundPlay() {
	buffSound->play();
}

Buff::~Buff()
{
}

int Buff::getBuffTimeLimit(BuffType opt) {
	
	static std::vector<int> buffDuration;
	static bool firstcall = true;
	if (firstcall) {
		firstcall = false;
		buffDuration.resize(BuffType::BOOST_COUNT);
		buffDuration[BuffType::RANGE_BOOST] = 3000;
		buffDuration[BuffType::DAMAGE_BOOST] = 12500;
		buffDuration[BuffType::FREEZER_BOOST] = 15000;
		buffDuration[BuffType::SHIELD_BOOST] = 10000;
		buffDuration[BuffType::REGEN_BOOST] = INT_MAX;
	}
	return buffDuration[opt];

}

