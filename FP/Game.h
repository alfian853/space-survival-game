#pragma once

#include "Animation.h"
#include "Asteroid.h"
#include "bullet.h"
#include "Entity.h"
#include "player.h"
#include "TimeBomb.h"
#include "HpBoost.h"
#include "ShotBoost.h"
#include "CollideEffect.h"
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
	const double phi = 3.141592654f;
	sf::Texture t1, t2, t3, t4, t5,t6;
	sf::Sprite background;
	sf::Sprite gameOverTxtSprite;
	sf::Sprite gameName;
	sf::Sprite scoreBoard;
	

	//global temp variable
	asteroid *temp_ast;
	CollideEffect *temp_explode;
	bullet *temp_bullet;

	//


	sf::Sprite startButton;
	sf::Sprite textInput;
	player *p;
	sf::Text gameOverTxt;
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
	const double next_lvl_factor = 1.25;
	/////////////////
	int asteroid_factor;
	int hpBoost_factor;
	int sMode_factor;
	int timeBomb_factor;
	std::string player_name;
	bool spaceKeyPressed;
	std::chrono::high_resolution_clock::time_point before_t,current_t;
	double compute_angle(double x1,double y1,double x2,double y2);
	void reset_game();
	void increase_level();
	bool isAlive();
public:
	Game();
	void run_game();
	FILE *skordb;
	void play();
	bool isCollide(Entity *a, Entity *b);
	bool isCollide(double x1,double y1,double R1,double x2,double y2,double R2);
	~Game();
};
