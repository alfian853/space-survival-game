#include "Game.h"

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
	sResisted		 = Animation(t3, 256*35,0 , 256, 256,13,0.5);
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
	hpBoost_factor = 1000;
	asteroid_factor = 150;
	sMode_factor = 5000;
	p->settings(sPlayer, W/2, H/2, 0, 16);
	entities.clear();
	entities.push_back(p);
	before_t = current_t = std::chrono::high_resolution_clock::now();
}

double Game::compute_angle(double x1, double y1, double x2, double y2) {
	if(x1<x2)return atan(  (y1-y2)/(x1-x2)  )*180/phi;
	
	return -180+atan((y1 - y2) / (x1 - x2)) * 180 / phi;
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

	spaceKeyPressed = false;

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

					b = new bullet();
					b->settings(sBullet, p->x, p->y, p->angle+20, 10);
					entities.push_back(b);

					b = new bullet();
					b->settings(sBullet, p->x, p->y, p->angle-20, 10);
					entities.push_back(b);

					spaceKeyPressed = true;
				}
				if (event.key.code == sf::Keyboard::Right|| event.key.code == sf::Keyboard::D) {
//					if (abs(p->dx) > 1.5 || abs(p->dy) > 1.5) p->anim = sPlayer_go_right;
					p->anim = sPlayer_go_right;
					p->move_direction = 3;
	//				p->angle +=10;
					
				}
				if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
	//				if (abs(p->dx) > 1.5 || abs(p->dy) > 1.5) p->anim = sPlayer_go_left;
					p->anim = sPlayer_go_left;
					p->move_direction = 4;
//					p->angle -= 10;
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
				printf("masuk\n");
				if (event.key.code == sf::Keyboard::Space)spaceKeyPressed = false;
				if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up
					|| event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down
					|| event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left
					|| event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right

					) {
					p->move_direction = 0;p->anim = sPlayer; //printf("masuk\n");
				}
				if (event.key.code == sf::Mouse::Left) {
					spaceKeyPressed = false;
				}

			}
			if (p->move_direction == 0)p->anim = sPlayer;
			if (event.type == sf::Event::MouseMoved) {
				double xx = sf::Mouse::getPosition().x;
				double yy = sf::Mouse::getPosition().y;
				double temp = compute_angle(p->get_possition().x+18, p->get_possition().y+18, xx, yy);
				/*printf("%.2f %.2f %.2f %.2f set angle %f\n",
					xx,yy,p->get_possition().x,p->get_possition().y,
					temp);*/
				p->set_angle( temp);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left ) && !spaceKeyPressed) {
				bullet *b = new bullet();
				b->settings(sBullet, p->x, p->y, p->angle, 10);
				entities.push_back(b);

				b = new bullet();
				b->settings(sBullet, p->x, p->y, p->angle + 20, 10);
				entities.push_back(b);

				b = new bullet();
				b->settings(sBullet, p->x, p->y, p->angle - 20, 10);
				entities.push_back(b);
				spaceKeyPressed = true;
			}
			else if(!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				spaceKeyPressed = false;
			}
		}//close input block

		

		for (auto a : entities) {
			bool breakga = false;
			for (auto b : entities)
			{
				if (a->name == "asteroid" && b->name == "bullet") {
					if (a->hp < 1 || b->hp < 1)continue;
					if (isCollide(a, b))
					{
						int temp = a->hp;
						a->hp -= b->hp;
						b->hp -= temp;
						Entity *e;
						e = new Entity();
						if (a->hp < 1) {
							e->settings(sExplosion, a->x, a->y);
							e->name = "explosion";

						}
						else {
							e->settings(sResisted, a->x, a->y);
							e->name = "explosion";
						}
						entities.push_back(e);
						if (a->R == 15)skor += 10;
						else skor += 20;

						if (a->R > 15 && a->hp < 1) {
							for (int i = 0;i < 2;i++)
							{
								e = new asteroid();
								e->setHp(20);
								e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
								entities.push_back(e);
							}
						}

					}
				}
				else if (a->name == "player" && b->name == "asteroid") {
					if (a->hp < 1 || b->hp < 1)continue;
					if (isCollide(a, b))
					{
						player *pl = (player*)a;

						int temp = a->hp;
						a->hp -= b->hp;
						b->hp -= temp;
						
						printf("%d %d %d\n", a->hp, b->hp,temp);
						if (b->hp < 1 || a->hp < 1) {
							if (b->R == 15)skor += 10;
							else {
								skor += 20;
								for (int i = 0;i < 2;i++)
								{
									asteroid *e = new asteroid();
									e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
									entities.push_back(e);
								}
							}
							Entity *e;
							e = new Entity();
							e->settings(sExplosion_ship, a->x, a->y);
							e->name = "explosion";
							entities.push_back(e);
						}
						if (pl->hp < 1) { p->settings(sPlayer, W / 2, H / 2, 0, 20);reset_game();breakga = true;break; }
						p->dx = 0; p->dy = 0;
					}
				}
				else if ((a->name == "bullet" || a->name == "player") && b->name == "hpBoost") {
					if (a->hp < 1 || b->hp < 1)continue;
					if (isCollide(a, b)) {
						int temp = b->hp;
						b->hp -= a->hp;
						a->hp -= temp;
						Entity *e;
						e = new Entity();
						e->name = "explosion";
						if (b->hp < 1) {
							p->hp += 100;
							e->settings(sExplosion, b->x, b->y);
						}
						else {
							e->settings(sResisted, b->x, b->y);
						}
						entities.push_back(e);
					}
				}
				else if ((a->name == "bullet" || a->name == "player") && b->name == "sMode") {
					if (a->hp < 1 || b->hp < 1)continue;
					if (isCollide(a, b)) {
						int temp = b->hp;
						b->hp -= a->hp;
						a->hp -= temp;
						Entity *e;
						e = new Entity();
						e->name = "explosion";
						if (b->hp < 1) {
							p->superMode = true;
							e->settings(sExplosion, b->x, b->y);
						}
						else {
							e->settings(sResisted, b->x, b->y);
						}
						before_t = std::chrono::high_resolution_clock::now();
						entities.push_back(e);
					}

				}//collide activity
			}
			if (breakga)break;
		}

		if (asteroid_factor <= 0)asteroid_factor = 50;
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
			a->setHp(100);
			entities.push_back(a);
		}
		if (rand() % sMode_factor == 0)
		{
			asteroid *a = new asteroid();
			a->settings(sModeBoost, 0, rand() % H, rand() % 360, 25);
			a->name = "sMode";
			a->setHp(100);
			entities.push_back(a);
		}


		if (p->superMode) {
			current_t = std::chrono::high_resolution_clock::now();
			comp = std::chrono::duration<double, std::milli>(current_t - before_t).count();
			if ( comp > 4999) {
				p->superMode = false;
				//printf("supermode off");
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

			if ( e->hp<1 ) { i = entities.erase(i); delete e; }
			else i++;
		}


		sprintf(rest_time, "%.2f", (5000 - comp) / 1000);
		//////draw//////
		if (p->superMode) {
			score_text.setString(
				"Score : " + std::to_string(skor) + "\nHp : " + std::to_string(p->hp)
				+ "\nsuperMode : "+std::string(rest_time)
			);
		}
		else {
			score_text.setString(
				"Score : " + std::to_string(skor) + "\nHp : " + std::to_string(p->hp)
			);
		}
	
		app.draw(background);

		for (auto i : entities)i->draw(app);

		app.draw(score_text);
		p->draw(app);
		app.display();

		if (skor >= next_lvl_score)asteroid_factor -= 10,next_lvl_score *= next_lvl_factor;
		
		}
	}





