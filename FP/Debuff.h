#pragma once
#include "Entity.h"
#include "gameUtil.h"
#include <vector>

enum DebuffType{LOW_DAMAGE,DEBUFF_COUNT=1};
class Debuff :
	public Entity
{
private:
	static sf::Texture *t1;
	static std::vector<sf::Texture> txture;
	static std::vector<Animation> vecAnim;
public:
	Debuff(DebuffType opt);
	static int getDebuffTimeLimit(DebuffType opt);
	~Debuff();
};

