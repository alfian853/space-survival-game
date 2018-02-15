#include "CollideEffect.h"

sf::Texture *CollideEffect::t1, *CollideEffect::t2, *CollideEffect::t3;
Animation *CollideEffect::rock_explode_anim, 
		  *CollideEffect::metal_explode_anim,
		  *CollideEffect::bomb_explode_anim,
		  *CollideEffect::resist_anim
;

sf::SoundBuffer *CollideEffect::explotionSoundBuffer, 
				*CollideEffect::bombSoundBuffer,
			    *CollideEffect::asteroidSoundBuffer,
				*CollideEffect::resistSoundBuffer
;

sf::Sound *CollideEffect::explotionSound,
		  *CollideEffect::bombSound,
	      *CollideEffect::asteroidSound,
		  *CollideEffect::resistSound
;



CollideEffect::CollideEffect(CEffType opt,float pos_x,float pos_y)
{
	static bool first_call = true;
	
	if (first_call) {
		first_call = false;
		setHp(0);
		t1 = new sf::Texture();
		if (!t1->loadFromFile("images/explosions/type_C.png")) {
			printf("load file failed\n");
		}
		rock_explode_anim = new Animation(*t1, 0, 0, 256, 256, 48, 0.5);
		resist_anim       = new Animation(*t1, 256 * 35, 0, 256, 256, 13, 0.5);

		t2 = new sf::Texture();
		if (!t2->loadFromFile("images/explosions/type_B.png")) {
			printf("load file failed\n");
		}
		metal_explode_anim = new Animation(*t2, 0, 0, 192, 192, 64, 0.5);

		t3 = new sf::Texture();
		if (!t3->loadFromFile("images/explosions/type_A.png")) {
			printf("load file failed\n");
		}
		bomb_explode_anim = new Animation(*t3, 0, 0, 400, 400, 20, 0.5);

		asteroidSoundBuffer = new sf::SoundBuffer();
		if (!asteroidSoundBuffer->loadFromFile("sound/explosion_asteroid.ogg")) {

		}
		explotionSoundBuffer = new sf::SoundBuffer();
		if (!explotionSoundBuffer->loadFromFile("sound/explosion_metal.ogg")) {
			printf("load file failed\n");
		}
		bombSoundBuffer = new sf::SoundBuffer();
		if (!bombSoundBuffer->loadFromFile("sound/explosion_timeBomb.ogg")) {
			printf("load file failed\n");
		}
		resistSoundBuffer = new sf::SoundBuffer();
		if (!bombSoundBuffer->loadFromFile("sound/explosion_resist.ogg")) {
			printf("load file failed\n");
		}
		asteroidSound = new sf::Sound();
		asteroidSound->setBuffer(*asteroidSoundBuffer);
		explotionSound = new sf::Sound();
		explotionSound->setBuffer(*explotionSoundBuffer);
		bombSound = new sf::Sound();
		bombSound->setBuffer(*bombSoundBuffer);
		resistSound = new sf::Sound();
		resistSound->setBuffer(*resistSoundBuffer);



	}
	setType(EnType::COLLIDE_EFFECT);
	cEffType = opt;

	switch (opt)
	{
	case ROCK_EXLODE:
		settings(*rock_explode_anim, pos_x, pos_y);
		break;
	case METAL_EXPLODE:
		settings(*metal_explode_anim, pos_x, pos_y);
		break;
	case BOMB_EXPLODE:
		settings(*bomb_explode_anim, pos_x, pos_y);
		setHp(150);
		this->R = 150;
		break;
	case RESIST:
		settings(*resist_anim, pos_x, pos_y);
		break;
	default:
		break;
	}
}

void CollideEffect::playSound() {
	switch (cEffType)
	{
	case ROCK_EXLODE:
		asteroidSound->play();
		break;
	case METAL_EXPLODE:
		explotionSound->play();
		break;
	case BOMB_EXPLODE:
		bombSound->play();
		break;
	case RESIST:
		resistSound->play();
		break;
	default:
		break;
	}

}

int CollideEffect::get_CEffType() {
	return cEffType;
}

CollideEffect::~CollideEffect()
{
}
