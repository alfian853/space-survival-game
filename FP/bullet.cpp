#include "bullet.h"

sf::Texture *bullet::t1, *bullet::t2;
Animation *bullet::blue_bullet_anim, *bullet::red_bullet_anim;
sf::SoundBuffer *bullet::multiShotSoundBuffer, *bullet::oneShotSoundBuffer;
sf::Sound *bullet::multiShotSound, *bullet::oneShotSound;


bullet::bullet(BulletType opt,int pos_x,int pos_y,int pos_angle)
{
	name = "bullet";
	superMode = false;
	this->bulletType= opt;
	static bool first_call = true;
	if (first_call) {
		first_call = false;
		t1 = new sf::Texture();
		if (!t1->loadFromFile("images/fire_blue.png")) {
			printf("load file failed\n");
		}
		blue_bullet_anim = new Animation(*t1, 0, 0, 32, 64, 16, 0.4);
		this->settings(*blue_bullet_anim, W / 2, H / 2, 0, 16);

		t2 = new sf::Texture();
		if (!t2->loadFromFile("images/fire_red.png")) {
			printf("load file failed\n");
		}
		red_bullet_anim = new Animation(*t2, 0, 0, 32, 64, 16, 0.4);
		this->settings(*red_bullet_anim, W / 2, H / 2, 0, 16);

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

	if (opt == BLUE_BULLET) {
		hp = 25;
		speed = 25;
		this->settings(*blue_bullet_anim,pos_x, pos_y, pos_angle, 10);
	}
	else if (opt == RED_BULLET) {
		this->settings(*red_bullet_anim, pos_x, pos_y, pos_angle, 10);
		this->hp = 70;
		this->speed = 45;
	}

	sf::Vector2f cartesian_speed = gameUtil::get_movement(speed, angle);
	dx = cartesian_speed.x;
	dy = cartesian_speed.y;
}

void bullet::playSound() {
	switch (bulletType) {
	case BulletType::BLUE_BULLET:
		multiShotSound->play();
		break;
	case BulletType::RED_BULLET:
		oneShotSound->play();
		break;
	}
}


void  bullet::update()
{
	x += dx;
	y += dy;

	if (superMode) {
		if (x > W) x = 0;
		if (x < 0) x = W;
		if (y > H) y = 0;
		if (y < 0) y = H;
	}
	else if (x>W || x<0 || y>H || y<0) hp = -1;
}