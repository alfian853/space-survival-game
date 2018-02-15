#pragma once
#include "Entity.h"
#include <SFML\Audio.hpp>
enum CEffType {ROCK_EXLODE,METAL_EXPLODE,BOMB_EXPLODE,RESIST};

class CollideEffect :
	public Entity
{
private:
	static sf::Texture *t1, *t2, *t3;
	static Animation *rock_explode_anim, *metal_explode_anim, *bomb_explode_anim, *resist_anim;
	static sf::SoundBuffer *explotionSoundBuffer,*bombSoundBuffer,*asteroidSoundBuffer,*resistSoundBuffer;
	static sf::Sound *explotionSound,*bombSound,*asteroidSound,*resistSound;
	CEffType cEffType;
public:
	CollideEffect(CEffType opt,float pos_x,float pos_y);
	~CollideEffect();
	int get_CEffType();
	void playSound();
};

