#include "Game.h"
#include <math.h>
#include <stdio.h>
#include <thread>

Game::Game()
{
	W = sf::VideoMode::getDesktopMode().width;
	H = sf::VideoMode::getDesktopMode().height;
	skor = 0;
	t1.loadFromFile("images/spaceship.png");
	t2.loadFromFile("images/background.jpg");
	t3.loadFromFile("images/explosions/type_C.png");
	t4.loadFromFile("images/rock.png");
	t5.loadFromFile("images/fire_blue.png");
	t6.loadFromFile("images/rock_small.png");
	t7.loadFromFile("images/explosions/type_B.png");
	t8.loadFromFile("images/hpBoost.png");
	t9.loadFromFile("images/car.png");


	t1.setSmooth(true);
	t2.setSmooth(true);
	background = sf::Sprite(t2);

	sExplosion       = Animation(t3, 0, 0, 256, 256, 48, 0.5);
	sRock            = Animation(t4, 0, 0, 64, 64, 16, 0.2);
	sRock_small      = Animation(t6, 0, 0, 64, 64, 16, 0.2);
	sBullet          = Animation(t5, 0, 0, 32, 64, 16, 0.8);
	sPlayer          = Animation(t1, 40, 0, 40, 40, 1, 0);
	sPlayer_go_right = Animation(t1, 80, 40, 40, 40,1, 0);
	sPlayer_go_left  = Animation(t1,0,40,40,40,1,0);
	sPlayer_go       = Animation(t1, 40, 40, 40, 40, 1, 0);
	sExplosion_ship  = Animation(t7, 0, 0, 192, 192, 64, 0.5);
	hpBoost          = Animation(t8, 0, 0,49,42,1,0 );
	sModeBoost		 = Animation(t9, 0, 0, 43, 45, 1, 0);
	/*for (int i = 0;i<15;i++)
	{
		asteroid *a = new asteroid();
		a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
		entities.push_back(a);
	}*/

	
}


Game::~Game()
{
}

bool Game::isCollide(Entity *a, Entity *b)
{
	return (b->x - a->x)*(b->x - a->x) +
		(b->y - a->y)*(b->y - a->y)<
		(a->R + b->R)*(a->R + b->R);
}

void Game::reset_game() {
	delete p;
	skor = 0;
	next_lvl_score = 400;
	p = new player();
	hpBoost_factor = 50000;
	asteroid_factor = 150000;
	sMode_factor = 200;
	p->settings(sPlayer, W/2, H/2, 0, 20);
	entities.clear();
	entities.push_back(p);
	before_t = current_t = 0.0;
}

void Game::run_game() {

	double comp = 0;
	reset_game();
	srand(time(0));
	sf::Font fontnya;
	fontnya.loadFromFile("arial.ttf");
	sf::Text score_text;
	score_text.setCharacterSize(20);
	score_text.setPosition({ 10,10 });
	score_text.setFont(fontnya);
	sf::Text player_hp;
	score_text.setCharacterSize(20);
	score_text.setPosition({ 20,10 });
	score_text.setFont(fontnya);


	sf::RenderWindow app(sf::VideoMode(W, H), "Asteroids!");
	app.setFramerateLimit(60);

	bool spaceKeyPressed = false;

	/////main loop/////
	while (app.isOpen())
	{	
		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app.close();

			if (event.type == sf::Event::KeyPressed) {

				if (event.key.code == sf::Keyboard::Space && !spaceKeyPressed) {
					bullet *b = new bullet();
					b->settings(sBullet, p->x, p->y, p->angle, 10);
					entities.push_back(b);
					spaceKeyPressed = true;
				}
				if (event.key.code == sf::Keyboard::Right) {
					if (abs(p->dx) > 1.5 || abs(p->dy) > 1.5) p->anim = sPlayer_go_right;
					p->angle +=10;
				}
				if (event.key.code == sf::Keyboard::Left) {
					if (abs(p->dx) > 1.5 || abs(p->dy) > 1.5) p->anim = sPlayer_go_left;
					p->angle -= 10;
				}
				if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
					p->anim = sPlayer_go;
					p->move_direction = 1;
				}
				if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
					p->anim = sPlayer;
					p->move_direction = 2;
				}
			}
			if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Space)spaceKeyPressed = false;
				if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up
					|| event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down					
					) {
					p->move_direction = 0;p->anim = sPlayer; //printf("masuk\n");
				}

			}
			if (p->move_direction == 0)p->anim = sPlayer;
		}//close input block

		

		for (auto a : entities)
			for (auto b : entities)
			{
				if (a->name == "asteroid" && b->name == "bullet") {
					if (isCollide(a, b))
					{
						a->life = false;
						b->life = false;

						Entity *e = new Entity();
						e->settings(sExplosion, a->x, a->y);
						e->name = "explosion";
						entities.push_back(e);
						if (a->R == 15)skor += 10;
						else skor += 20;

						for (int i = 0;i < 2;i++)
						{
							if (a->R == 15) continue;
							Entity *e = new asteroid();
							e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
							entities.push_back(e);
						}

					}
				}

				if (a->name == "player" && b->name == "asteroid") {
					if (isCollide(a, b))
					{
						player *pl = (player*)a;
						if (b->R == 15)pl->hp -= (rand() % 8 + 15), skor += 10;
						else pl->hp -= (rand() % 8 + 32), skor += 20;


						b->life = false;
						Entity *e = new Entity();
						e->settings(sExplosion_ship, a->x, a->y);
						e->name = "explosion";
						entities.push_back(e);

						if (pl->hp < 1) { p->settings(sPlayer, W / 2, H / 2, 0, 20); pl->hp = 100; skor = 0; }
						p->dx = 0; p->dy = 0;

					}
				}
				if ((a->name == "bullet" || a->name == "player") && b->name == "hpBoost") {
					if (isCollide(a, b)) {
						p->hp += 100;
						b->life = false;
						Entity *e = new Entity();
						e->settings(sExplosion, b->x, b->y);
						e->name = "explosion";
						entities.push_back(e);
					}
				}
	
				if ((a->name == "bullet" || a->name == "player") && b->name == "sMode"){
					if (isCollide(a, b)) {
						printf("collide\n");
						p->superMode = true;
						b->life = false;
						before_t = clock();
						Entity *e = new Entity();
						e->settings(sExplosion, b->x, b->y);
						e->name = "explosion";
						entities.push_back(e);
					}

				}//collide activity
			}


		if (rand() % asteroid_factor == 0)
		{
			asteroid *a = new asteroid();
			a->settings(sRock,0, rand() % H, rand() % 360, 25);
			entities.push_back(a);
		}
		if (rand() % hpBoost_factor == 0)
		{
			asteroid *a = new asteroid();
			a->settings(hpBoost, 0, rand() % H, rand() % 360, 25);
			a->name = "hpBoost";
			entities.push_back(a);
		}
		if (rand() % sMode_factor == 0)
		{
			asteroid *a = new asteroid();
			a->settings(sModeBoost, 0, rand() % H, rand() % 360, 25);
			a->name = "sMode";
			entities.push_back(a);
		}


		if (p->superMode) {
			current_t = clock();
			comp = (double)current_t - (double)before_t;
			if ( comp > 4.999) {
				p->superMode = false;
			}
		}

		for (auto i = entities.begin();i != entities.end();)
		{
			Entity *e = *i;
			if (e->name == "explosion" && e->anim.isEnd()){
				i = entities.erase(i);
				delete e;
				continue;
			}
			if (e->name == "bullet") {
				bullet *temp = (bullet*)e;
				if (p->superMode) {
					temp->superMode = true;
				}
				else {
					temp->superMode = false;
				}
			}
			e->update();
			e->anim.update();

			if (e->life == false) { i = entities.erase(i); delete e; }
			else i++;
		}



		//////draw//////
		score_text.setString(
			"Score : " + std::to_string(skor) + "\nHp : " + std::to_string(p->hp)
			+ "\n superMode : " + std::to_string(comp)
			+ "\n t1: " + std::to_string(before_t)
			+ "\n t2: " + std::to_string(current_t)
		
		);
	//	player_hp.setString(std::to_string(p->hp));
		app.draw(background);

		for (auto i : entities)i->draw(app);

		app.draw(score_text);

		app.display();

		if (skor >= next_lvl_score)asteroid_factor -= 10,next_lvl_score *= next_lvl_factor;
		
		}
	}





