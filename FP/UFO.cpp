#include "UFO.h"

sf::Texture *UFO::txture;
Animation *UFO::ufoAnim;
sf::SoundBuffer *UFO::sbuffer;
sf::Sound *UFO::spawnSound;



UFO::UFO()
{
	canShot = false;
	static bool first_call = true;
	if (first_call) {
		first_call = false;
		txture = new sf::Texture();
		txture->loadFromFile("images/ufo.png");
		ufoAnim = new Animation(*txture, 0, 0, 200, 200, 3, 0.03);
		sbuffer = new sf::SoundBuffer();
		sbuffer->loadFromFile("sound/boss_arival.ogg");
		spawnSound = new sf::Sound();
		spawnSound->setBuffer(*sbuffer);
	}
	setType(EnType::EN_UFO);
	sf::Vector2i randSpawn = GameUtil::getRandomSpawn(50,50,W-50,H-50);
	this->settings(*ufoAnim, randSpawn.x, randSpawn.y, rand() % 360, 80);
	this->setAutoRotation(3);
	this->setHp(10000);

	sf::Vector2f cartesian_speed = GameUtil::get_movement(5, angle);
	dx = cartesian_speed.x;
	dy = cartesian_speed.y;

}


UFO::~UFO()
{
}

void UFO::draw(sf::RenderWindow &app)
{
	canShot = false;
	anim.sprite.setPosition(x, y);
	anim.sprite.setRotation(angle);
	angle += 1;
	if (angle > 360) {
		angle -= 360;
	}
	if (angle == 72 || angle ==144 ||angle == 216 || angle ==288 || angle==360)canShot = true;
	app.draw(anim.sprite);
};

bool UFO::isCanShot() { return canShot; }

void UFO::playSound() {
	spawnSound->play();
}

void UFO::update() {

		x += dx;
		y += dy;
		sf::Vector2f cartesian_speed;
		if (x > W-50) {
			cartesian_speed = GameUtil::get_movement(5, rand() % 180+90);
			dx = cartesian_speed.x;
			dy = cartesian_speed.y;
		}
		else if (x < 50) {
			cartesian_speed = GameUtil::get_movement(5, rand() % 180 - 90);
			dx = cartesian_speed.x;
			dy = cartesian_speed.y;
		}
		else if (y > H - 30) {
			cartesian_speed = GameUtil::get_movement(5, rand() % 180+180);
			dx = cartesian_speed.x;
			dy = cartesian_speed.y;
		}
		else if (y < 30) {
			cartesian_speed = GameUtil::get_movement(5, rand() % 180);
			dx = cartesian_speed.x;
			dy = cartesian_speed.y;
		}

}