#include "Bullet.h"

std::vector<sf::Texture> Bullet::txture;
std::vector<Animation> Bullet::vecAnim;

sf::SoundBuffer *Bullet::multiShotSoundBuffer, *Bullet::oneShotSoundBuffer;
sf::Sound *Bullet::multiShotSound, *Bullet::oneShotSound;


Bullet::Bullet(BulletType opt,int pos_x,int pos_y,int pos_angle){

	superMode = false;
	this->bulletType= opt;
	static bool first_call = true;
	if (first_call) {
		first_call = false;

		txture.resize(BulletType::COUNT);
		vecAnim.resize(BulletType::COUNT);

		txture[BulletType::BLUE].loadFromFile("images/fire_blue.png");
		txture[BulletType::BIG_BLUE].loadFromFile("images/fire_blueBig.png");
		txture[BulletType::RED].loadFromFile("images/fire_red.png");
		txture[BulletType::BIG_RED].loadFromFile("images/fire_redBig.png");
		txture[BulletType::LASER].loadFromFile("images/laser.png");
		vecAnim[BulletType::BLUE] = Animation(txture[BulletType::BLUE], 0, 0, 32, 64, 16, 0.4);
		vecAnim[BulletType::LASER] = Animation(txture[BulletType::LASER], 0, 0, 82, 200, 1, 0.4);
		vecAnim[BulletType::BIG_BLUE] = Animation(txture[BulletType::BIG_BLUE], 0, 0, 48, 96, 16, 0.4);

		vecAnim[BulletType::RED] = Animation(txture[BulletType::RED], 0, 0, 32, 64, 16, 0.4);
		vecAnim[BulletType::BIG_RED] = Animation(txture[BulletType::BIG_RED], 0, 0, 48, 96, 16, 0.4);


		oneShotSoundBuffer = new sf::SoundBuffer();
		if (!oneShotSoundBuffer->loadFromFile("sound/fire_jf_one.ogg")) {
			printf("load file failed\n");
		}
		multiShotSoundBuffer = new sf::SoundBuffer();
		if (!multiShotSoundBuffer->loadFromFile("sound/fire_jf_multi.ogg")) {
			printf("load file failed\n");
		}
		oneShotSound = new sf::Sound();
		multiShotSound = new sf::Sound();
		oneShotSound->setBuffer(*oneShotSoundBuffer);
		multiShotSound->setBuffer(*multiShotSoundBuffer);

	}
	setType(EnType::BULLET);

	switch (opt)
	{
	case LASER:
		this->setHp(150);
		speed = 25;
		this->settings(vecAnim[BulletType::LASER], pos_x, pos_y, pos_angle, 13);
		break;
	case BLUE:
		this->setHp(50);
		speed = 25;
		this->settings(vecAnim[BulletType::BLUE], pos_x, pos_y, pos_angle, 10);
		break;
	case BIG_BLUE:
		this->setHp(100);
		speed = 25;
		this->settings(vecAnim[BulletType::BIG_BLUE], pos_x, pos_y, pos_angle, 15);
		break;
	case RED:
		this->settings(vecAnim[BulletType::RED], pos_x, pos_y, pos_angle, 10);
		this->setHp(150);
		this->speed = 45;
		break;
	case BIG_RED:
		this->settings(vecAnim[BulletType::BIG_RED], pos_x, pos_y, pos_angle, 15);
		this->setHp(300);
		this->speed = 45;
		break;
	}

	sf::Vector2f cartesian_speed = GameUtil::get_movement(speed, angle);
	dx = cartesian_speed.x;
	dy = cartesian_speed.y;
}

void Bullet::playSound() {
	switch (bulletType) {
	case BulletType::BLUE:
	case BulletType::BIG_BLUE:
		multiShotSound->play();
		break;
	case BulletType::RED:
	case BulletType::BIG_RED:
		oneShotSound->play();
		break;
	}
}
int Bullet::getDamage() {
	return this->getHp();
}
void Bullet::setDamage(int dmg) {
	setHp(dmg);
}


void  Bullet::update()
{
	x += dx;
	y += dy;

	if (superMode) {
		if (x > W) x = 0;
		if (x < 0) x = W;
		if (y > H) y = 0;
		if (y < 0) y = H;
	}
	else if (x>W || x<0 || y>H || y<0) setHp(-1);
}

BulletType Bullet::getBulletType() { return bulletType; }