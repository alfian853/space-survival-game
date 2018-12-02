#pragma once
#include "Entity.h"
#include "gameUtil.h"
#include <SFML\Audio.hpp>
#include <vector>

enum BuffType{RANGE_BOOST,DAMAGE_BOOST,FREEZER_BOOST,SHIELD_BOOST,REGEN_BOOST,BOOST_COUNT=5};
class Buff :
	public Entity
{
private:
	static std::vector<sf::Texture> txture;
	static std::vector<Animation> vecAnim;
	static sf::SoundBuffer *soundBuffer;
	static sf::Sound *buffSound;
	BuffType boostType;
public:
	Buff(BuffType opt);
	BuffType getBoostType();
	static void bufferSoundPlay();
	static int getBuffTimeLimit(BuffType opt);
	~Buff();
};

