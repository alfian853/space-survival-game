#pragma once
#include "Entity.h"
#include "gameUtil.h"
#include "Buff.h"
#include "Debuff.h"
#include <chrono>
#include <vector>


class Ship : public Entity
{
private:
	enum resources{SHIP_IDLE,SHIP_GO,SHIP_LEFT,SHIP_RIGHT,SHIELD};
	static std::vector<Animation> vecAnim;
	static std::vector<sf::Texture> txture;
	std::vector<std::chrono::high_resolution_clock::time_point> boost_t;
	std::vector<std::chrono::high_resolution_clock::time_point> debuff_t;
	std::vector<bool> boost_stat;
	std::vector<bool> debuff_stat;
	std::chrono::high_resolution_clock::time_point current_t;
	double comp;
public:
//	bool thrust;
	/*
	0 not move
	1 move forward
	2 move backward
	3 move left
	4 move right
	*/
	bool move_left, move_right, move_forward, move_backward;
	int shieldHp;
	int getShieldHp();
	void setShieldHp(int sHp);
	std::chrono::high_resolution_clock::time_point getEffectDuration(BuffType opt);
	std::chrono::high_resolution_clock::time_point getEffectDuration(DebuffType opt);
	bool isBoosted(BuffType opt);
	bool isDebuffed(DebuffType opt);

	void setEffect(DebuffType opt);
	void setEffect(BuffType opt);

	void setOffEffect(DebuffType opt);
	void setOffEffect(BuffType opt);

	void updateEffectDuration();
	int move_direction;
	sf::Vector2f cartesian_speed;
	Ship();
	void update()override;
	void draw(sf::RenderWindow &app)override;

	void set_angle(double angle);
};
