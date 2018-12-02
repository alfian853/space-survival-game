#pragma once
#include "Entity.h"
#include "gameUtil.h"
#include <vector>
#include <SFML\Audio.hpp>

enum BulletType{BLUE,BIG_BLUE,RED,BIG_RED,LASER,COUNT=5};

class Bullet : public Entity
{
private:
	static std::vector<sf::Texture> txture;
	static std::vector<Animation> vecAnim;

	static sf::SoundBuffer *multiShotSoundBuffer,*oneShotSoundBuffer;
	static sf::Sound *multiShotSound,*oneShotSound;
	BulletType bulletType;
public:
	int speed;
	bool superMode;
	Bullet(BulletType opt,int pos_x,int pos_y,int pos_angle);
	void update()override;
	void playSound();
	void setDamage(int dmg);
	BulletType getBulletType();
	int getDamage();
};