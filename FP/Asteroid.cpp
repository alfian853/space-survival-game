#include "Asteroid.h"

sf::Texture *Asteroid::t1, *Asteroid::t2, *Asteroid::t3;
Animation *Asteroid::small_rock, *Asteroid::rock, *Asteroid::hard_rock;

Asteroid::Asteroid(AstType opt,int pos_x,int pos_y)
{
	static bool first_call = true;
	rock_type = opt;
	dx = rand() % 12 - 6;
	dy = rand() % 12 - 6;
	
	if (dx == 0 && dy == 0) { dx = rand()%3+1; }
	if (first_call) {
		first_call = false;
		t1 = new sf::Texture();
		if (!t1->loadFromFile("images/rock_small.png")) {
			printf("load file failed\n");
		}
		t2 = new sf::Texture();
		if (!t2->loadFromFile("images/rock.png")) {
			printf("load file failed\n");
		}
	
		t3 = new sf::Texture();
		if (!t3->loadFromFile("images/hard_rock.png")) {
			printf("load file failed\n");
		}
		small_rock = new Animation(*t1, 0, 0, 64, 64, 16, 0.2);
		rock       = new Animation(*t2, 0, 0, 64, 64, 16, 0.2);
		hard_rock  = new Animation(*t3, 0, 0, 150, 150, 15, 0.15);	
	}
	setType(EnType::ASTEROID);
//	randSpawn.x, randSpawn.y
	if (pos_x == -1) {
		sf::Vector2i randSpawn = GameUtil::getRandomSpawn(W, H);
		pos_x = randSpawn.x;
		pos_y = randSpawn.y;
	}

	switch (opt)
	{
	case SMALL_ASTEROID:
		settings(*small_rock, pos_x, pos_y, rand() % 360, 15);
		setHp(50);
		break;
	case NORMAL_ASTEROID:
		settings(*rock, pos_x, pos_y, rand() % 360, 25);
		setHp(100);
		break;
	case HARD_ASTEROID:
		settings(*hard_rock, pos_x, pos_y, rand() % 360, 40);
		setHp(200);
		setAutoRotation(5);
		break;
	default:
		break;
	}

}


AstType Asteroid::get_asteroidType() {
	return rock_type;
}