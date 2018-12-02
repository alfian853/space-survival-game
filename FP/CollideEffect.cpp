#include "CollideEffect.h"

std::vector<sf::Texture> CollideEffect::txture;
std::vector<Animation> CollideEffect::vecAnim;
std::vector<sf::SoundBuffer> CollideEffect::vecSoundBuffer;
std::vector<sf::Sound> CollideEffect::vecSound;


CollideEffect::CollideEffect(CEffType opt,float pos_x,float pos_y)
{
	static bool first_call = true;
	
	if (first_call) {
		first_call = false;
		setHp(12);
		txture.resize(CEffType::C_COUNT);
		vecAnim.resize(CEffType::C_COUNT);

		txture[CEffType::ROCK_EXPLODE].loadFromFile("images/explosions/type_C.png");
		txture[CEffType::METAL_EXPLODE].loadFromFile("images/explosions/type_B.png");
		txture[CEffType::BOMB_EXPLODE].loadFromFile("images/explosions/type_A.png");

		vecAnim[CEffType::ROCK_EXPLODE] = Animation(txture[CEffType::ROCK_EXPLODE], 0, 0, 256, 256, 48, 0.5);
		vecAnim[CEffType::RESIST] = Animation(txture[CEffType::ROCK_EXPLODE], 256 * 35, 0, 256, 256, 13, 0.5);
		vecAnim[CEffType::METAL_EXPLODE] = Animation(txture[CEffType::METAL_EXPLODE], 0, 0, 192, 192, 64, 0.5);
		vecAnim[CEffType::BOMB_EXPLODE]= Animation(txture[CEffType::BOMB_EXPLODE], 0, 0, 400, 400, 20, 0.5);

		vecSoundBuffer.resize(CEffType::C_COUNT);
		vecSound.resize(CEffType::C_COUNT);

		vecSoundBuffer[CEffType::ROCK_EXPLODE].loadFromFile("sound/explosion_asteroid.ogg");
		vecSoundBuffer[CEffType::RESIST].loadFromFile("sound/explosion_resist.ogg");
		vecSoundBuffer[CEffType::METAL_EXPLODE].loadFromFile("sound/explosion_metal.ogg");
		vecSoundBuffer[CEffType::BOMB_EXPLODE].loadFromFile("sound/explosion_timeBomb.ogg");

		vecSound[CEffType::ROCK_EXPLODE].setBuffer(vecSoundBuffer[CEffType::ROCK_EXPLODE]);
		vecSound[CEffType::RESIST].setBuffer(vecSoundBuffer[CEffType::RESIST]);
		vecSound[CEffType::METAL_EXPLODE].setBuffer(vecSoundBuffer[CEffType::METAL_EXPLODE]);
		vecSound[CEffType::BOMB_EXPLODE].setBuffer(vecSoundBuffer[CEffType::BOMB_EXPLODE]);

	}
	setType(EnType::COLLIDE_EFFECT);
	cEffType = opt;

	this->settings(vecAnim[opt], pos_x, pos_y,0,150);
}

void CollideEffect::playSound() {
	vecSound[cEffType].play();
}

int CollideEffect::get_CEffType() {
	return cEffType;
}

CollideEffect::~CollideEffect()
{
}
