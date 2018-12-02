#pragma once
#include "Entity.h"
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <vector>
#include "GameUtil.h"
class UFO :
	public Entity
{
private:
	static sf::Texture *txture;
	static Animation *ufoAnim;
	static sf::SoundBuffer *sbuffer;
	static sf::Sound *spawnSound;
	bool canShot;
public:

	UFO();
	~UFO();
	void draw(sf::RenderWindow &app)override;
	bool isCanShot();
	void update()override;
	void playSound();
};	

