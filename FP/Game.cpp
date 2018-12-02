#include "Game.h"

Game::Game()
{	
	inDb.open("scoredb.txt");
	int score;
	std::string player;
	while (inDb >> score &&inDb >> player) {
		pqScoreBoard.push_back(make_pair(score,player));
	}

	W = sf::VideoMode::getDesktopMode().width;
	H = sf::VideoMode::getDesktopMode().height;
	//pre load static resources
	temp_explode = new CollideEffect(CEffType::BOMB_EXPLODE, 1, 2);
	delete(temp_explode);
	temp_bullet = new Bullet(BLUE, 0, 0, 0);
	delete(temp_bullet);
	temp_buff = new Buff(BuffType::DAMAGE_BOOST);
	delete(temp_buff);
	temp_ast = new Asteroid(AstType::HARD_ASTEROID);
	delete(temp_ast);
	temp_ufo = new UFO();
	delete(temp_ufo);
	gameOverBuffer.loadFromFile("sound/gameOver.ogg");
	gameOverSound.setBuffer(gameOverBuffer);
	//

	skor = 0;
	fontnya.loadFromFile("arial.ttf");
	t1.loadFromFile("images/background2.jpg");
	t2.loadFromFile("images/start_button.png");
	t3.loadFromFile("images/text_input.png");
	t4.loadFromFile("images/game_over.png");
	t5.loadFromFile("images/score_board.png");
	t6.loadFromFile("images/game_name.png");
	t7.loadFromFile("images/small_start_button.png");
	t8.loadFromFile("images/helpTable.jpg");

	backSoundBuffer.loadFromFile("sound/Dark-Techno-City_Looping.ogg");
	backSound.setBuffer(backSoundBuffer);
	backSound.setLoop(true);

	gameName.setTexture(t6);
	gameName.setPosition(sf::Vector2f(W/2-400,5));

	t1.setSmooth(true);
	t2.setSmooth(true);
	background = sf::Sprite(t1);
	gameOverTxtSprite = sf::Sprite(t4);
	gameOverTxtSprite.setPosition(sf::Vector2f(W / 2, H / 2));
	gameOverTxtSprite.setOrigin(sf::Vector2f(640, 360));
	scoreBoard = sf::Sprite(t5);

	startButton.setTexture(t2);
	startButton.setPosition(sf::Vector2f(W/2, H/2+140));
	startButton.setOrigin(64,64);

	startButton_pressed.setTexture(t7);
	startButton_pressed.setPosition(sf::Vector2f(W / 2, H / 2 + 140));
	startButton_pressed.setOrigin(50,50);

	helpTable.setTexture(t8);
	helpTable.setPosition(sf::Vector2f(W/2+220,H/2-20));


	textInput.setTexture(t3);
	textInput.setPosition(sf::Vector2f(W/2, H/2));
	textInput.setOrigin(200, 50);
	temp_text.setCharacterSize(17);
	temp_text.setFont(fontnya);
	temp_text.setFillColor(sf::Color::Cyan);
	
}


Game::~Game()
{
}


bool Game::isCollide(Entity *a, Entity *b){
	return isCollide(a->x, a->y, a->R, b->x, b->y, b->R);
}
int tescount = 1;
bool Game::isCollide(double x1, double y1, double R1, double x2, double y2, double R2){
	return (x2 - x1)*(x2 - x1) +
		(y2 - y1)*(y2 - y1)<
		(R1 + R2)*(R1 + R2);
}

void Game::play() {

	backSound.play();
	bool playing = true;
	int aa = W / 2;
	int bb = H / 2;
	Entity *clickPoint = new Entity();
	app =new sf::RenderWindow(sf::VideoMode(W, H), "Space survival!", sf::Style::Fullscreen);
	
	app->setFramerateLimit(60);
	player_name = "player";
	sf::Text playerNameTxt;
	playerNameTxt.setFillColor(sf::Color::Cyan);
	playerNameTxt.setPosition(W / 2 - player_name.length() * 5, H / 2 );
	playerNameTxt.setFont(fontnya);
	playerNameTxt.setCharacterSize(20);
	bool backspaced = false;
	scoreBoard.setPosition(sf::Vector2f(30,30));
	for (int i = 0; i < 6; ++i) {
		Asteroid *a = new Asteroid(HARD_ASTEROID);
		entities.push_back(a);
		Asteroid *b = new Asteroid(NORMAL_ASTEROID);
		entities.push_back(b);
		TimeBomb *c = new TimeBomb();
		entities.push_back(c);
	}

	bool isButtonPressed = false;
	bool run_theGame = false;
	while (app->isOpen() ) {
		sf::Event event;
		
		while (app->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app->close();
			double x = sf::Mouse::getPosition().x;
			double y = sf::Mouse::getPosition().y;
			
			if (event.type == sf::Event::MouseButtonReleased &&
				event.mouseButton.button == sf::Mouse::Left) {
				if (isButtonPressed &&isCollide(x, y, 2, startButton.getPosition().x, startButton.getPosition().y, 30)) {
					run_theGame = true;
				}
				isButtonPressed = false;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isButtonPressed) {
				if (isCollide(x, y, 2, startButton.getPosition().x, startButton.getPosition().y, 40)) {
					isButtonPressed = true;
				}
			}
			
			if (event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::BackSpace && player_name.size()!=0) {

				player_name.pop_back();
				playerNameTxt.setPosition(W / 2 - player_name.length() * 5, H / 2);
			}
			else if (event.type == sf::Event::TextEntered && 
				event.text.unicode < 128&&event.text.unicode!='\n' && event.text.unicode!=8 && player_name.length()<14) {
				
				player_name.push_back(static_cast<char>(event.text.unicode));
				playerNameTxt.setPosition(W / 2 - player_name.length()*5, H / 2);
			}			
		}
		if (run_theGame) {
			run_theGame = false;
			entities.clear();
			run_game();
			for (auto i = entities.begin(); i != entities.end();) {
				Entity *e = *i;
				if (e->getType() == EnType::COLLIDE_EFFECT) {
					i = entities.erase(i); delete e;
					continue;
				}
				i++;
			}
			pqScoreBoard.push_back(make_pair(skor, player_name));
			sort(pqScoreBoard.begin(), pqScoreBoard.end(), [](const pis a, const pis b) {return a.first > b.first; });
			skordb = fopen("scoredb.txt", "w");
			for (int i = 0; i < std::min(10, (int)pqScoreBoard.size()); ++i) {
				fprintf(skordb, "%d %s\n", pqScoreBoard[i].first, pqScoreBoard[i].second.c_str());
				temp_text.setString(std::to_string(i + 1) + ". " + pqScoreBoard[i].second + " : " + std::to_string(pqScoreBoard[i].first));
				temp_text.setPosition(10, 10 * i);
				app->draw(temp_text);
			}
			fclose(skordb);
		}
		playerNameTxt.setString(player_name);
		app->draw(background);
		for (Entity *e : entities) {
			e->update();
			e->anim.update();
			e->draw(*app);
		}

		if(isButtonPressed)app->draw(startButton_pressed);
		else app->draw(startButton);
		app->draw(helpTable);

		app->draw(scoreBoard);
		for (int i = 0;i < std::min(10,(int)pqScoreBoard.size());++i) {
			temp_text.setString(std::to_string(i + 1) + ". " + pqScoreBoard[i].second + " : " + std::to_string(pqScoreBoard[i].first));
			temp_text.setPosition(60,120+30 * i);
			app->draw(temp_text);
		}
		app->draw(textInput);
		app->draw(playerNameTxt);
		app->draw(gameName); 
		app->display();

	}
	
	
}

void Game::fight(int &a, int &b) {
	if (a < 1 || b < 1)return;
	int temp = a;
	a-= b;
	b-=temp;
}


void Game::increase_level() {
	asteroid_factor = std::max(50, asteroid_factor-10);
	timeBomb_factor = std::max(75, timeBomb_factor - 30);
	debuffer_factor = std::max(75, debuffer_factor-20);
	buff_factor = std::max(350, buff_factor - 30);
}



void Game::reset_game() {
	delete p;
	skor = 0;
	next_lvl_score = 1000;
	p = new Ship();
	debuffer_factor = 250;
	asteroid_factor = 150;
	buff_factor = 700;
	timeBomb_factor = 400;
	ufo_factor = 34000;
	entities.clear();
	
	entities.push_back(p);
	current_t = std::chrono::high_resolution_clock::now();
}


void Game::run_game() {
	double comp = 0;
	std::list<Entity*> temp_vEntity;
	reset_game();
	srand(time(0));
	score_text.setCharacterSize(20);
	score_text.setPosition({ 10,10 });
	score_text.setFont(fontnya);
	score_text.setCharacterSize(20);
	score_text.setPosition({ 20,10 });
	score_text.setFont(fontnya);
	temp_text.setCharacterSize(17);
	temp_text.setFont(fontnya);
	app->setFramerateLimit(60);

	spaceKeyPressed = false;
	std::chrono::high_resolution_clock::time_point game_over_start,game_over_finish;
	bool game_over = false;
	/////main loop/////
	int healPS = 0;

	while (app->isOpen()){
		if (p->isBoosted(BuffType::REGEN_BOOST)) {
			if(healPS % 7 == 0) { p->setHp(p->getHp() + 1); healPS = 0; } 
		}
		else {
			if(healPS%20==0){ p->setHp(p->getHp() + 1); healPS = 0; }
		}
		healPS++;
		sf::Event event;
		
			if (!game_over) {
				while (app->pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						app->close();

					if (event.type == sf::Event::KeyPressed) {

						if (event.key.code == sf::Keyboard::Space && !spaceKeyPressed) {//shoting
							if (p->isBoosted(BuffType::DAMAGE_BOOST)) {
								for (int id = -20; id < 21; id += 20) {
									temp_bullet = new Bullet(BulletType::BIG_BLUE, p->x, p->y, p->angle + id);
									if (p->isDebuffed(DebuffType::LOW_DAMAGE)) { temp_bullet->setDamage(temp_bullet->getDamage()/4); }
									entities.push_back(temp_bullet);
								}
							}
							else {
								for (int id = -20; id < 21; id += 20) {
									temp_bullet = new Bullet(BulletType::BLUE, p->x, p->y, p->angle + id);
									if (p->isDebuffed(DebuffType::LOW_DAMAGE)) { temp_bullet->setDamage(temp_bullet->getDamage() / 4); }
									entities.push_back(temp_bullet);
								}
							}
							temp_bullet->playSound();
							spaceKeyPressed = true;
						}
						if (event.key.code == sf::Keyboard::E && p->isBoosted(BuffType::FREEZER_BOOST)) {
							Buff::bufferSoundPlay();
							//p->setEffect(BuffType::SHIELD_BOOST);
							for (Entity *e : entities) {
								if (e->getType() != EnType::BULLET && e->getType()!=EnType::EN_UFO) {
									e->dx = 0;
									e->dy = 0;
								}
							}
							p->setOffEffect(BuffType::FREEZER_BOOST);
							//temp_en = new UFO();//Asteroid(AstType::HARD_ASTEROID);
							//temp_en->x = 500;
							//temp_en->y = 400;
							////temp_en->dx = 0;
							////temp_en->dy = 0;
							//entities.push_back(temp_en);
							//						temp_ufo = new UFO();
//							entities.push_back(temp_ufo);
							/*
							Entity *asd = new UFO();
							asd->x = 500;
							asd->y = 300;
							asd->dx = 0;
							asd->dy = 0;
							entities.push_back(asd);

							asd = new Buff(BuffType::SHIELD_BOOST);
							asd->x = 700;
							asd->y = 300;
							asd->dx = 0;
							asd->dy = 0;
							entities.push_back(asd);*/


						}
						if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
							p->move_direction = 1;
						}
						if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
							p->move_direction = 3;
						}
						if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
							p->move_direction = 4;
						}
						if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
							p->move_direction = 2;
						}
					}
					if (event.type == sf::Event::KeyReleased) {
						if (event.key.code == sf::Keyboard::Space)spaceKeyPressed = false;
						else if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up
							|| event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down
							|| event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left
							|| event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right

							) {
							p->move_direction = 0;
						}
						else if (event.key.code == sf::Mouse::Left) {
							spaceKeyPressed = false;
						}
					}
					if (event.type == sf::Event::MouseMoved) {
						double xx = sf::Mouse::getPosition().x;
						double yy = sf::Mouse::getPosition().y;
						double temp = GameUtil::compute_angle(p->get_possition().x , p->get_possition().y, xx, yy);
						p->set_angle(temp);
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !spaceKeyPressed) {//nembak 3
					//if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !spaceKeyPressed) {//nembak 3
						if (p->isBoosted(BuffType::DAMAGE_BOOST)) {
							for (int id = -20; id < 21; id += 20) {
								temp_bullet = new Bullet(BulletType::BIG_BLUE, p->x, p->y, p->angle + id);
								if (p->isDebuffed(DebuffType::LOW_DAMAGE)) { temp_bullet->setDamage(temp_bullet->getDamage() / 4); }
								entities.push_back(temp_bullet);
							}
						}
						else {
							for (int id = -20; id < 21; id += 20) {
								temp_bullet = new Bullet(BulletType::BLUE, p->x, p->y, p->angle + id);
								if (p->isDebuffed(DebuffType::LOW_DAMAGE)) { temp_bullet->setDamage(temp_bullet->getDamage() / 4); }
								entities.push_back(temp_bullet);
							}
						}
						temp_bullet->playSound();
						spaceKeyPressed = true;
					}
					//if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !spaceKeyPressed) {//nembak satu
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !spaceKeyPressed) {//nembak satu
						spaceKeyPressed = true;
						if(p->isBoosted(BuffType::DAMAGE_BOOST))temp_bullet = new Bullet(BulletType::BIG_RED, p->x, p->y, p->angle);
						else { temp_bullet = new Bullet(BulletType::RED, p->x, p->y, p->angle); }
						if (p->isDebuffed(DebuffType::LOW_DAMAGE)) { temp_bullet->setDamage(temp_bullet->getDamage() / 4); }
						temp_bullet->playSound();
						entities.push_back(temp_bullet);
					}

					if (event.type == sf::Event::MouseButtonReleased && (event.mouseButton.button == sf::Mouse::Left
						|| event.mouseButton.button == sf::Mouse::Right )) {
						spaceKeyPressed = false;
					}
				}//close input block
			}


			for (auto a : entities) {
				for (auto b : entities)
				{
					if (!isCollide(a, b))continue;
					if (a->getHp() < 1 || b->getHp() < 1)continue;
					if( ((a->getType()==EnType::BULLET && ((Bullet*)a)->getBulletType() == BulletType::LASER)
						&& b->getType()!=EnType::SHIP) ||(
						(b->getType() == EnType::BULLET && ((Bullet*)b)->getBulletType() == BulletType::LASER)
						&& a->getType() != EnType::SHIP)){continue; }


					if (((a->getType() == EnType::BULLET )|| a->getType()==EnType::SHIP)&&
						b->getType()==EnType::ASTEROID) {
					
						if(a->getType()==EnType::SHIP && p->isBoosted(BuffType::SHIELD_BOOST))fight(b->hp, p->shieldHp);
						fight(a->hp, b->hp);
					
						if (a->getType()==EnType::SHIP && p->isBoosted(BuffType::REGEN_BOOST) && 
							!p->isBoosted(BuffType::SHIELD_BOOST)) { p->setOffEffect(BuffType::REGEN_BOOST); }

						if (b->getHp() < 1) {
							temp_explode = new CollideEffect(CEffType::ROCK_EXPLODE,b->x,b->y);
							temp_explode->playSound();
						}
						else {
							temp_explode = new CollideEffect(CEffType::RESIST, b->x, b->y);
							temp_explode->playSound();
						}
						entities.push_back(temp_explode);
						
						if (b->getHp() > 0)continue;
						if (b->R == 15)skor += 10;//jika tembak asteroid kecil
						else skor += 20;

						temp_ast = (Asteroid*)b;
						if (b->R > 15 && temp_ast->get_asteroidType()==AstType::NORMAL_ASTEROID) {
							for (int i = 0;i < 2;i++) {
								temp_ast = new Asteroid(AstType::SMALL_ASTEROID,b->x,b->y);
								entities.push_back(temp_ast);
							}
						}

					}
					else if ( (a->getType()==EnType::BULLET || a->getType()==EnType::SHIP)&& 
					b->getType() == EnType::DEBUFF) {
						
						if (a->getType() == EnType::SHIP && p->isBoosted(BuffType::REGEN_BOOST) &&
							!p->isBoosted(BuffType::SHIELD_BOOST)) {
							p->setOffEffect(BuffType::REGEN_BOOST);
						}
						if (a->getType() == EnType::SHIP && p->isBoosted(BuffType::SHIELD_BOOST))fight(b->hp, p->shieldHp);
						fight(a->hp, b->hp);
						if (b->getHp() < 1) {//penambahan darah kalau dapat
							if (a->getType() == EnType::SHIP &&
								!p->isBoosted(BuffType::SHIELD_BOOST)) {
								p->setEffect(DebuffType::LOW_DAMAGE); 
							}
							temp_explode= new CollideEffect(CEffType::METAL_EXPLODE, b->x, b->y);
							temp_explode->playSound();
						}
						else {
							temp_explode = new CollideEffect(CEffType::RESIST, b->x, b->y);
							temp_explode->playSound();
						}
						entities.push_back(temp_explode);
					}
					else if ( (a->getType() == EnType::BULLET || a->getType()==EnType::SHIP)&&
						b->getType() == EnType::BUFF) {
						
						if (a->getType() == EnType::SHIP && p->isBoosted(BuffType::REGEN_BOOST) &&
							!p->isBoosted(BuffType::SHIELD_BOOST)) {
							p->setOffEffect(BuffType::REGEN_BOOST);
						}
						if (a->getType() == EnType::SHIP && p->isBoosted(BuffType::SHIELD_BOOST))fight(b->hp, p->shieldHp);
						fight(a->hp, b->hp);
						if (b->getHp() < 1) {
							temp_buff = (Buff*)b;
							p->setEffect(temp_buff->getBoostType());
							temp_buff->bufferSoundPlay();
							skor += 35;
							temp_explode = new CollideEffect(CEffType::ROCK_EXPLODE, b->x, b->y);

							temp_explode->playSound();
						}
						else {
							temp_explode = new CollideEffect(CEffType::RESIST, b->x, b->y);
							temp_explode->playSound();
						}
						entities.push_back(temp_explode);
					}
					else if ((a->getType() == EnType::BULLET || a->getType() == EnType::SHIP) && 
					(b->getType() == EnType::TIME_BOMB || b->getType()==EnType::EN_UFO)) {
				
						if (a->getType() == EnType::SHIP && p->isBoosted(BuffType::REGEN_BOOST) &&
						!p->isBoosted(BuffType::SHIELD_BOOST)) {
							p->setOffEffect(BuffType::REGEN_BOOST);
						}
						if (a->getType() == EnType::SHIP && p->isBoosted(BuffType::SHIELD_BOOST))fight(b->hp, p->shieldHp);
						fight(a->hp, b->hp);
						if (b->getHp() < 1) {
							if (b->getType() == EnType::TIME_BOMB) {
								if (a->getType() == EnType::BULLET) {
									if(b->getType()==EnType::TIME_BOMB)skor += 45;
									else skor += 1000;
									temp_explode = new CollideEffect(CEffType::METAL_EXPLODE, b->x, b->y);
									temp_explode->playSound();
								}
								else {
									temp_explode = new CollideEffect(CEffType::BOMB_EXPLODE, b->x, b->y);
									temp_explode->playSound();
								}
							}
							else {
								temp_explode = new CollideEffect(CEffType::BOMB_EXPLODE, b->x, b->y);
								entities.push_back(temp_explode);
								temp_explode->playSound();
								temp_explode = new CollideEffect(CEffType::METAL_EXPLODE, b->x, b->y);
								temp_explode->playSound();

							}
							entities.push_back(temp_explode);
						}
						else {
							temp_explode = new CollideEffect(CEffType::RESIST, a->x, a->y);
							temp_explode->playSound();
							entities.push_back(temp_explode);
						}	
					}
					else if (a->getType()==EnType::SHIP && b->getType()==EnType::COLLIDE_EFFECT &&(
					( (CollideEffect*)b)->get_CEffType()==CEffType::BOMB_EXPLODE) ) {
				
						if (p->isBoosted(BuffType::REGEN_BOOST)) { p->setOffEffect(BuffType::REGEN_BOOST); }
						if (p->shieldHp > 0) { p->shieldHp -= 12; }
						else a->hp-= 12;
					
					}
					else if (a->getType() == EnType::SHIP && b->getType() == EnType::BULLET && 
						((Bullet*)b)->getBulletType() == BulletType::LASER) {
						
						if (a->getType() == EnType::SHIP && p->isBoosted(BuffType::SHIELD_BOOST))fight(b->hp, p->shieldHp);
						fight(a->hp, b->hp);
						temp_explode = new CollideEffect(CEffType::RESIST, a->x, a->y);
							temp_explode->playSound();
							entities.push_back(temp_explode);
					}

				}
			}

			if (p->getHp() < 1&&!game_over) {
				temp_explode = new CollideEffect(CEffType::METAL_EXPLODE,p->x,p->y);
				temp_explode->playSound();
				entities.push_back(temp_explode);
				game_over = true;
				gameOverSound.play();
				game_over_start = std::chrono::high_resolution_clock::now();
			}

			if (rand() % asteroid_factor == 0)
			{
				if (rand() % 2 == 0) {
					Asteroid *a = new Asteroid(AstType::NORMAL_ASTEROID);
					entities.push_back(a);
				}
				else{
					Asteroid *a = new Asteroid(AstType::HARD_ASTEROID);
					entities.push_back(a);
				}
			}
			if (rand() % debuffer_factor == 0)
			{
				Debuff *a = new Debuff(DebuffType::LOW_DAMAGE);
				entities.push_back(a);
			}
			if (rand() % buff_factor == 0)
			{
				temp_buff = new Buff((BuffType)(rand() % 5));
				entities.push_back(temp_buff);
			}
			if (rand() % timeBomb_factor == 0)
			{
				TimeBomb *a = new TimeBomb();
				entities.push_back(a);
			}
			if (rand()%ufo_factor == 0) {
				temp_ufo = new UFO();
				temp_ufo->playSound();
				entities.push_back(temp_ufo);
			}

			//update all boost time
			p->updateEffectDuration();

			tempOutString = "Score : " + std::to_string(skor) + "\nHp : " + std::to_string(p->getHp())+"\n";
			current_t = std::chrono::high_resolution_clock::now();
			if (p->isBoosted(BuffType::RANGE_BOOST)) {
				comp = std::chrono::duration<double, std::milli>(current_t - p->getEffectDuration(BuffType::RANGE_BOOST)).count();
				sprintf(rest_time, "%.2f", (Buff::getBuffTimeLimit(BuffType::RANGE_BOOST) - comp) / 1000);
				tempOutString = tempOutString + "BrutalShot : "+ std::string(rest_time)+"\n";
			}
			if (p->isBoosted(BuffType::DAMAGE_BOOST)){
				comp = std::chrono::duration<double, std::milli>(current_t - p->getEffectDuration(BuffType::DAMAGE_BOOST)).count();
				sprintf(rest_time, "%.2f", (Buff::getBuffTimeLimit(BuffType::DAMAGE_BOOST) - comp) / 1000);
				tempOutString = tempOutString + "DoubleDamage : " + std::string(rest_time) + "\n";
			}
			if (p->isBoosted(BuffType::SHIELD_BOOST)) {
				comp = std::chrono::duration<double, std::milli>(current_t - p->getEffectDuration(BuffType::SHIELD_BOOST)).count();
				sprintf(rest_time, "%.2f", (Buff::getBuffTimeLimit(BuffType::SHIELD_BOOST) - comp) / 1000);
				tempOutString = tempOutString + "Shield : " +std::to_string(p->getShieldHp())+"+, "+ std::string(rest_time) + "\n";
			}
			if (p->isBoosted(BuffType::REGEN_BOOST)) {
				tempOutString = tempOutString + "FastRegen : Until Damaged\n";
			}
			if (p->isBoosted(BuffType::FREEZER_BOOST)) {
				comp = std::chrono::duration<double, std::milli>(current_t - p->getEffectDuration(BuffType::FREEZER_BOOST)).count();
				sprintf(rest_time, "Freezer : %.2f ,Press 'E'\n", (Buff::getBuffTimeLimit(BuffType::FREEZER_BOOST) - comp) / 1000);
				tempOutString = tempOutString + std::string(rest_time);
			}
			if (p->isDebuffed(DebuffType::LOW_DAMAGE)) {
				comp = std::chrono::duration<double, std::milli>(current_t - p->getEffectDuration(DebuffType::LOW_DAMAGE)).count();
				sprintf(rest_time, "%.2f",(Debuff::getDebuffTimeLimit(DebuffType::LOW_DAMAGE)- comp) / 1000);
				tempOutString = tempOutString + "LowDamage : " + std::string(rest_time) + "\n";

			}
			score_text.setString(tempOutString);
			app->draw(background);




			//control dead object
			for (auto i = entities.begin();i != entities.end();){

				Entity *e = *i;
				if (e->getType() == EnType::SHIP ) {
					if (e->getHp() < 1) { i++; continue; }
				}
				if (e->getType()==EnType::COLLIDE_EFFECT && e->anim.isEnd()) {
					i = entities.erase(i);
					delete e;
					continue;
				}
				else if (e->getType() == EnType::EN_UFO && ((UFO*)e)->isCanShot()) {
					for (int i = -120; i < 121; i += 120) {
						temp_bullet = new Bullet(BulletType::LASER, e->x, e->y,e->angle+i-15);
						entities.push_back(temp_bullet);
					}
				}
				else if (e->getType()==EnType::BULLET && ((Bullet*)e)->getBulletType()!=BulletType::LASER) {
					Bullet *temp = (Bullet*)e;
					if (p->isBoosted(BuffType::RANGE_BOOST)) {
						temp->superMode = true;
					}
					else {
						temp->superMode = false;
					}
				}
				else if (e->getType() == EnType::TIME_BOMB) {
					TimeBomb *temp = (TimeBomb*)e;
					current_t = std::chrono::high_resolution_clock::now();
					comp = std::chrono::duration<double, std::milli>(current_t - temp->life_time).count();
					sprintf(rest_time, "%d", (int)(1+(4000 - comp) / 1000));//atur waktu time bomb
					temp_text.setPosition({ e->x-4, e->y+3.5f });
					temp_text.setString(std::string(rest_time));
					e->update();
					e->anim.update();
					e->draw(*app);
					app->draw(temp_text);

					if (comp > 4000) {//atur waktu time bomb
						temp_explode = new CollideEffect(CEffType::BOMB_EXPLODE, e->x, e->y);
						temp_explode->playSound();
						temp_vEntity.push_back(temp_explode);
						i = entities.erase(i);
						delete e;
						continue;
					}
					if (e->getHp() < 1) { i = entities.erase(i); delete e; }
					i++;
					continue;
				}

				e->update();
				e->anim.update();
				e->draw(*app);

				if (e->getHp() < 1&&e->getType()!=EnType::SHIP) { i = entities.erase(i); delete e; }
				else i++;
			}
			//freezer boost just effect one time
			//p->setOffBoost(BuffType::FREEZER_BOOST);

			//draw score,hp and boost			
			app->draw(score_text);

			for (auto x = temp_vEntity.begin();x != temp_vEntity.end();x++) {
					Entity *tm = *x;
					entities.push_back(tm);
				}
			temp_vEntity.clear();
			if(p->getHp()>0)p->draw(*app);

			if (game_over == true) {
				app->draw(gameOverTxtSprite);
				game_over_finish = std::chrono::high_resolution_clock::now();
				comp = std::chrono::duration<double, std::milli>(game_over_finish - game_over_start).count();
				if (comp > 3000) {
					return;
				}
			}
			app->display();
			if (skor >= next_lvl_score)increase_level(), next_lvl_score *= next_lvl_factor;
		
}//while window open
}//function close





