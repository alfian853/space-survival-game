#include "Asteroid.h"

sf::Texture *asteroid::t1, *asteroid::t2, *asteroid::t3;
Animation *asteroid::small_rock, *asteroid::rock, *asteroid::hard_rock;

asteroid::asteroid(AstType opt,int x,int y)
{
	//asteroid movement
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
//		printf("called once\n");
		t2 = new sf::Texture();
		if (!t2->loadFromFile("images/rock.png")) {
			printf("load file failed\n");
		}
	
//		x = 500, y = 200;
		t3 = new sf::Texture();
		if (!t3->loadFromFile("images/hard_rock.png")) {
			printf("load file failed\n");
		}
		small_rock = new Animation(*t1, 0, 0, 64, 64, 16, 0.2);
		rock       = new Animation(*t2, 0, 0, 64, 64, 16, 0.2);
		hard_rock  = new Animation(*t3, 0, 0, 80, 64, 7, 0.2);
	
	}
	setType(EnType::ASTEROID);

	switch (opt)
	{
	case SMALL_ASTEROID:
		settings(*small_rock, x, y, rand() % 360, 15);
		setHp(25);
		break;
	case NORMAL_ASTEROID:
		settings(*rock, x, y, rand() % 360, 25);
		setHp(40);
		break;
	case HARD_ASTEROID:
		settings(*hard_rock, x, y, rand() % 360, 25);
		setHp(100);
		break;
	default:
		break;
	}

}


int asteroid::get_asteroidType() {
	return rock_type;
}