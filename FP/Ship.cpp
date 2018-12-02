#include "Ship.h"

std::vector<Animation> Ship::vecAnim;
std::vector<sf::Texture> Ship::txture;

Ship::Ship()
{
	move_left = move_right = move_forward = move_backward = false;
	
	this->setHp(500);
	
	boost_t.resize(BuffType::BOOST_COUNT);
	debuff_t.resize(DebuffType::DEBUFF_COUNT);

	//boost_stat.assign(BuffType::BOOST_COUNT, 0);
	//debuff_stat.assign(DebuffType::DEBUFF_COUNT, 0);
	
	for (int i = 0; i < 10; i++) {
		boost_stat.push_back(false);
		debuff_stat.push_back(false);
	}

	static bool first_call = true;
	if (first_call) {
		first_call = false;
		/*
		txture 0 can be used by vecAnim 0..4
		*/
		txture.resize(2);
		vecAnim.resize(5);
		
		txture[0].loadFromFile("images/spaceship.png");
		txture[1].loadFromFile("images/shield.png");
		vecAnim[resources::SHIP_IDLE] = Animation(txture[0], 40, 0, 40, 40, 1, 0);
		vecAnim[resources::SHIP_GO] = Animation(txture[0], 40, 40, 40, 40, 1, 0);
		vecAnim[resources::SHIP_LEFT] = Animation(txture[0], 80, 40, 40, 40, 1, 0);
		vecAnim[resources::SHIP_RIGHT] = Animation(txture[0], 0, 40, 40, 40, 1, 0);
		vecAnim[resources::SHIELD] = Animation(txture[1],0, 0, 144, 148, 1, 0);
	}
	this->settings(vecAnim[resources::SHIP_IDLE], W / 2, H / 2, 0, 16);
	setType(EnType::SHIP);

}


std::chrono::high_resolution_clock::time_point Ship::getEffectDuration(BuffType opt) {
	return boost_t[opt];
}
std::chrono::high_resolution_clock::time_point Ship::getEffectDuration(DebuffType opt) {
	return debuff_t[opt];
}

bool Ship::isBoosted(BuffType opt) {
	return boost_stat[opt];
}


int Ship::getShieldHp() { return shieldHp; }
void Ship::setShieldHp(int sHp) { this->shieldHp = sHp; }

void Ship::setEffect(BuffType opt) {
	boost_t[opt] = std::chrono::high_resolution_clock::now();
	boost_stat[opt] = true;
	if (opt == BuffType::SHIELD_BOOST) {
		this->R = 73;
		shieldHp = 2000;
	}
}
void Ship::setEffect(DebuffType opt) {
	debuff_t[opt] = std::chrono::high_resolution_clock::now();
	debuff_stat[opt] = true;
}

bool Ship::isDebuffed(DebuffType opt) {
	return debuff_stat[opt];
}

void Ship::setOffEffect(DebuffType opt) {
	debuff_stat[opt] = false;
}

void Ship::setOffEffect(BuffType opt) {
	boost_stat[opt] = false;
	if (opt == BuffType::SHIELD_BOOST) {
		this->R = 16;
	}
}

void Ship::updateEffectDuration() {
	for (int i = 0;i<BuffType::BOOST_COUNT; i++) {
		if (boost_stat[i]) {
			current_t = std::chrono::high_resolution_clock::now();
			comp = std::chrono::duration<double, std::milli>(current_t - boost_t[i]).count();
			if (comp > Buff::getBuffTimeLimit((BuffType)i)) {//super mode dapat dari diamond,effect : peluru tembus
				setOffEffect((BuffType)i);
			}
		}
	}
	if (shieldHp < 0) {
		setOffEffect(BuffType::SHIELD_BOOST);
		shieldHp = 0;
		printf("masuk\n");
	}
	for(int i=0;i<DebuffType::DEBUFF_COUNT;i++){
		if (debuff_stat[i]) {
			current_t = std::chrono::high_resolution_clock::now();
			comp = std::chrono::duration<double, std::milli>(current_t - debuff_t[i]).count();
			if (comp > Debuff::getDebuffTimeLimit((DebuffType)i)) {//super mode dapat dari diamond,effect : peluru tembus
				setOffEffect((DebuffType)i);
			}
		}
	}

}

void Ship::set_angle(double angle) {
	this->angle = angle;
}

void Ship::update()
{
	cartesian_speed = GameUtil::get_movement(0.3f, angle);
	if (move_direction == 1) {
		dx += cartesian_speed.x;
		dy += cartesian_speed.y;
		anim = vecAnim[resources::SHIP_GO];
	}
	else if (move_direction == 2) {
		dx -= cartesian_speed.x;
		dy -= cartesian_speed.y;
		anim = vecAnim[resources::SHIP_GO];
	}
	else if (move_direction == 3) {
		dx -= cartesian_speed.y;
		dy += cartesian_speed.x;;
		anim = vecAnim[resources::SHIP_LEFT];
	}
	else if (move_direction == 4) {
		dx += cartesian_speed.y;
		dy -= cartesian_speed.x;
		anim = vecAnim[resources::SHIP_RIGHT];
	}
	else{
		anim = vecAnim[resources::SHIP_IDLE];
		dx *= 0.81;
		dy *= 0.81;
	}
	float maxSpeed = 7.5;
	float speed = sqrt(dx*dx + dy*dy);
	if (speed > maxSpeed){
			dx *= maxSpeed / speed;
			dy *= maxSpeed / speed;
	}

	x += dx;
	y += dy;
	if (x>W) x = 0; if (x<0) x = W;
	if (y>H) y = 0; if (y<0) y = H;
}


void Ship::draw(sf::RenderWindow &app)
{
	anim.sprite.setPosition(x, y);
	anim.sprite.setRotation(angle + 90);
	app.draw(anim.sprite);
	if (isBoosted(BuffType::SHIELD_BOOST)) {
		vecAnim[resources::SHIELD].sprite.setPosition(x, y);
		app.draw(vecAnim[resources::SHIELD].sprite);
		vecAnim[resources::SHIELD].sprite.setRotation(rotateAngle);
		rotateAngle += 5;
		if (rotateAngle > 360)rotateAngle -= 360;
	}

};


