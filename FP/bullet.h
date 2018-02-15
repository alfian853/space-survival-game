#pragma once
#include "Entity.h"
#include "gameUtil.h"
#include <SFML\Audio.hpp>

enum BulletType{BLUE_BULLET,RED_BULLET};

class bullet : public Entity
{
private:
	static sf::Texture *t1,*t2;
	static Animation *blue_bullet_anim , *red_bullet_anim;
	static sf::SoundBuffer *multiShotSoundBuffer,*oneShotSoundBuffer;
	static sf::Sound *multiShotSound,*oneShotSound;
	BulletType bulletType;
public:
	int speed;
	bool superMode;
	bullet(BulletType opt,int pos_x,int pos_y,int pos_angle);
	void update()override;
	void playSound();
};