#include "GameUtil.h"


const float GameUtil::DEGTORAD = 0.017453;
const double GameUtil::phi = 3.141592654f;
GameUtil::GameUtil()
{
}


GameUtil::~GameUtil()
{
}

sf::Vector2i GameUtil::getRandomSpawn(int w,int h) {

	int s_x, s_y;
	float s_angle;

	switch (rand() % 4)
	{
	case 0:
		s_x = 0;
		s_y = rand()%h;
		break;
	case 1:
		s_x = w;
		s_y = rand()%h;
		break;
	case 2:
		s_x = rand()%w;
		s_y = 0;
		break;
	case 3:
		s_x = rand()%w;
		s_y = h;
		break;
	}
	return sf::Vector2i(s_x, s_y);

}
sf::Vector2i GameUtil::getRandomSpawn(int w1, int h1, int w2, int h2) {
	int s_x, s_y;
	float s_angle;

	switch (rand() % 4)
	{
	case 0:
		s_x = w1;
		s_y = h1+rand() % (h2 - h1);
		break;
	case 1:
		s_x = w2;
		s_y = h1+rand() % (h2 - h1);;
		break;
	case 2:
		s_x = w1+rand() % (w2 - w1);
		s_y = h1;
		break;
	case 3:
		s_x = w1+rand() % (w2 - w1);
		s_y = h2;
		break;
	}
	return sf::Vector2i(s_x, s_y);




}



double GameUtil::compute_angle(double x1, double y1, double x2, double y2) {
	if (x1<x2)return atan((y1 - y2) / (x1 - x2)) * 180 / phi;
	return -180 + atan((y1 - y2) / (x1 - x2)) * 180 / phi;
}

bool GameUtil::isCollide(double x1, double y1, double R1, double x2, double y2, double R2) {
	return (x2 - x1)*(x2 - x1) +
		(y2 - y1)*(y2 - y1)<
		(R1 + R2)*(R1 + R2);
}

sf::Vector2f GameUtil::get_movement(float speed,float angle) {
	return sf::Vector2f(cos(angle*DEGTORAD) * speed , sin(angle*DEGTORAD) * speed);
}

