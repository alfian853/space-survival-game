#include "gameUtil.h"


const float gameUtil::DEGTORAD = 0.017453;
gameUtil::gameUtil()
{
}


gameUtil::~gameUtil()
{
}
bool gameUtil::isCollide(double x1, double y1, double R1, double x2, double y2, double R2) {
	return (x2 - x1)*(x2 - x1) +
		(y2 - y1)*(y2 - y1)<
		(R1 + R2)*(R1 + R2);
}

sf::Vector2f gameUtil::get_movement(float speed,float angle) {
	return sf::Vector2f(cos(angle*DEGTORAD) * speed , sin(angle*DEGTORAD) * speed);
}

