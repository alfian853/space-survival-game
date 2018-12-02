#pragma once
#include "Entity.h"
#include <vector>
#include <SFML\Audio.hpp>
#include <SFML\OpenGL.hpp>

enum CEffType {ROCK_EXPLODE,METAL_EXPLODE,BOMB_EXPLODE,RESIST,C_COUNT=4};

class CollideEffect :
	public Entity
{
private:
	static std::vector<sf::Texture>txture;
	static std::vector<Animation>vecAnim;
	static std::vector<sf::SoundBuffer> vecSoundBuffer;
	static std::vector<sf::Sound> vecSound;

	CEffType cEffType;
public:
	CollideEffect(CEffType opt,float pos_x,float pos_y);
	~CollideEffect();
	int get_CEffType();
	void playSound();
};

