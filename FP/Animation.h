#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <time.h>
#include <list>

//using namespace sf;
//using sf::Texture;
extern int W;//width
extern int H;//heigth

class Animation{
public:
	float Frame, speed;
	sf::Sprite sprite;
	std::vector<sf::IntRect> frames;
	Animation();
	Animation(sf::Texture &t, int x, int y, int w, int h, int count, float Speed);
	void update();
	bool isEnd();

};
