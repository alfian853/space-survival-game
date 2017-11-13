#include "Game.h"



Game::Game()
{
	t1.loadFromFile("images/spaceship.png");
	t2.loadFromFile("images/background.jpg");
	t3.loadFromFile("images/explosions/type_C.png");
	t4.loadFromFile("images/rock.png");
	t5.loadFromFile("images/fire_blue.png");
	t6.loadFromFile("images/rock_small.png");
	t7.loadFromFile("images/explosions/type_B.png");

	t1.setSmooth(true);
	t2.setSmooth(true);
	background = sf::Sprite(t2);

	sExplosion = Animation(t3, 0, 0, 256, 256, 48, 0.5);
	sRock = Animation(t4, 0, 0, 64, 64, 16, 0.2);
	sRock_small = Animation(t6, 0, 0, 64, 64, 16, 0.2);
	sBullet = Animation(t5, 0, 0, 32, 64, 16, 0.8);
	sPlayer = Animation(t1, 40, 0, 40, 40, 1, 0);
	sPlayer_go = Animation(t1, 40, 40, 40, 40, 1, 0);
	sExplosion_ship = Animation(t7, 0, 0, 192, 192, 64, 0.5);

	for (int i = 0;i<15;i++)
	{
		asteroid *a = new asteroid();
		a->settings(sRock, rand() % W, rand() % H, rand() % 360, 25);
		entities.push_back(a);
	}

	p = new player();
	p->settings(sPlayer, 200, 200, 0, 20);
	entities.push_back(p);

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


void Game::run_game() {
	

	srand(time(0));

	sf::RenderWindow app(sf::VideoMode(W, H), "Asteroids!");
	app.setFramerateLimit(60);


	
	/////main loop/////
	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app.close();

			if (event.type == sf::Event::KeyPressed)
				if (event.key.code == sf::Keyboard::Space)
				{
					bullet *b = new bullet();
					b->settings(sBullet, p->x, p->y, p->angle, 10);
					entities.push_back(b);
				}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) p->angle += 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  p->angle -= 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) p->thrust = true;
		else p->thrust = false;



		for (auto a : entities)
			for (auto b : entities)
			{
				if (a->name == "asteroid" && b->name == "bullet")
					if (isCollide(a, b))
					{
						a->life = false;
						b->life = false;

						Entity *e = new Entity();
						e->settings(sExplosion, a->x, a->y);
						e->name = "explosion";
						entities.push_back(e);


						for (int i = 0;i<2;i++)
						{
							if (a->R == 15) continue;
							Entity *e = new asteroid();
							e->settings(sRock_small, a->x, a->y, rand() % 360, 15);
							entities.push_back(e);
						}

					}

				if (a->name == "player" && b->name == "asteroid")
					if (isCollide(a, b))
					{
						b->life = false;

						Entity *e = new Entity();
						e->settings(sExplosion_ship, a->x, a->y);
						e->name = "explosion";
						entities.push_back(e);

						p->settings(sPlayer, W / 2, H / 2, 0, 20);
						p->dx = 0; p->dy = 0;
					}
			}


		if (p->thrust)  p->anim = sPlayer_go;
		else   p->anim = sPlayer;


		for (auto e : entities)
			if (e->name == "explosion")
				if (e->anim.isEnd()) e->life = 0;

		if (rand() % 150 == 0)
		{
			asteroid *a = new asteroid();
			a->settings(sRock, 0, rand() % H, rand() % 360, 25);
			entities.push_back(a);
		}

		for (auto i = entities.begin();i != entities.end();)
		{
			Entity *e = *i;

			e->update();
			e->anim.update();

			if (e->life == false) { i = entities.erase(i); delete e; }
			else i++;
		}



		//////draw//////
		app.draw(background);

		for (auto i : entities)
			i->draw(app);

		app.display();
	}




}
