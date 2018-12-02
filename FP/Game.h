#pragma once

#include "Animation.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Entity.h"
#include "Ship.h"
#include "TimeBomb.h"
#include "Debuff.h"
#include "Buff.h"
#include "CollideEffect.h"
#include "UFO.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <queue>
#include <ratio>
#include <string.h>
#include <stdexcept>
#include <SFML\Audio.hpp>
#include <SFML\OpenGL.hpp>
#include <utility>

typedef std::pair<int, std::string> pis;

class Game
{
private:
	sf::Texture t1, t2, t3, t4, t5,t6,t7,t8;
	sf::Sprite background;
	sf::Sprite gameOverTxtSprite;
	sf::Sprite gameName;
	sf::Sprite helpTable;
	sf::Sprite scoreBoard;
	sf::SoundBuffer gameOverBuffer;
	sf::Sound gameOverSound;

	//global temp variable
	Asteroid *temp_ast;
	Entity *temp_en;
	CollideEffect *temp_explode;
	Bullet *temp_bullet;
	Buff *temp_buff;
	Debuff *temp_debuff;
	TimeBomb *temp_bomb;
	UFO *temp_ufo;
	//


	sf::Sprite startButton;
	sf::Sprite startButton_pressed;
	sf::Sprite textInput;
	Ship *p;
	sf::Text tempOutTxt;
	std::string tempOutString;
	sf::SoundBuffer backSoundBuffer;
	sf::Font fontnya;
	sf::Text score_text;
	sf::Text player_hp;
	sf::Text temp_text;
	std::ifstream inDb;
	std::ofstream outDb;
	std::vector<std::pair<int, std::string> >pqScoreBoard;
	

	sf::Sound backSound;
	


	sf::RenderWindow *app;

	std::list<Entity*> entities;
	char rest_time[256];
	/////////////
	int skor;
	int next_lvl_score;
	const double next_lvl_factor = 1.2;
	/////////////////
	int asteroid_factor;
	int debuffer_factor;
	int buff_factor;
	int timeBomb_factor;
	int ufo_factor;

	std::string player_name;
	bool spaceKeyPressed;
	std::chrono::high_resolution_clock::time_point current_t;
	void reset_game();
	void increase_level();
public:
	Game();
	void run_game();
	FILE *skordb;
	void play();
	void fight(int &a,int &b);
	bool isCollide(Entity *a, Entity *b);
	bool isCollide(double x1,double y1,double R1,double x2,double y2,double R2);
	~Game();
};
