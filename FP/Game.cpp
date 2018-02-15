#include "Game.h"

Game::Game()
{	
	inDb.open("scoredb.txt");
	int score;
	std::string player;
	while (inDb >> score &&inDb >> player) {
		pqScoreBoard.push_back(make_pair(score,player));
	}
	//pre load resources
	temp_explode = new CollideEffect(CEffType::BOMB_EXPLODE,1,2);
	temp_bullet = new bullet(BLUE_BULLET,0,0,0);
	Entity *enti = new Entity();
	//

	W = sf::VideoMode::getDesktopMode().width;
	H = sf::VideoMode::getDesktopMode().height;

	skor = 0;
	fontnya.loadFromFile("arial.ttf");
	t1.loadFromFile("images/background.jpg");
	t2.loadFromFile("images/start_button.png");
	t3.loadFromFile("images/text_input.png");
	t4.loadFromFile("images/game_over.png");
	t5.loadFromFile("images/score_board.png");
	t6.loadFromFile("images/game_name.png");

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
		asteroid *a = new asteroid(HARD_ASTEROID);
		entities.push_back(a);
		asteroid *b = new asteroid(NORMAL_ASTEROID);
		entities.push_back(b);
		TimeBomb *c = new TimeBomb();
		entities.push_back(c);
	}
	
	while (app->isOpen() ) {
		sf::Event event;
		
		while (app->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				app->close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				//printf("clicked\n");
				//			double x, y;
				double x = sf::Mouse::getPosition().x;
				double y = sf::Mouse::getPosition().y;
				if (isCollide(x, y, 1, startButton.getPosition().x, startButton.getPosition().y, 25)) {
					entities.clear();
					run_game();
					pqScoreBoard.push_back(make_pair(skor, player_name));
					sort(pqScoreBoard.begin(), pqScoreBoard.end(), [](const pis a, const pis b) {return a.first > b.first; });
					skordb = fopen("scoredb.txt", "w");
					for (int i = 0;i < std::min(10,(int)pqScoreBoard.size());++i) {
						fprintf(skordb, "%d %s\n", pqScoreBoard[i].first,pqScoreBoard[i].second.c_str());
						temp_text.setString(std::to_string(i+1)+". "+pqScoreBoard[i].second+" : "+std::to_string(pqScoreBoard[i].first));
						temp_text.setPosition(10,10*i);
						app->draw(temp_text);
					}
					fclose(skordb);
				}
			}
			
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace && player_name.size()!=0) {
				player_name.pop_back();
				playerNameTxt.setPosition(W / 2 - player_name.length() * 5, H / 2);

				//	std::cout << inputedTxt << std::endl;
			}
			else if (
				event.type == sf::Event::TextEntered && event.text.unicode < 128 && event.text.unicode!=8 && player_name.length()<14) {
				player_name.push_back(static_cast<char>(event.text.unicode));
				playerNameTxt.setPosition(W / 2 - player_name.length()*5, H / 2);
				//std::cout << inputedTxt << std::endl;
			}			
		}
		playerNameTxt.setString(player_name);
		app->draw(background);
		for (Entity *e : entities) {
			e->update();
			e->anim.update();
			e->draw(*app);
		}

		app->draw(startButton);
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

void Game::reset_game() {
	delete p;
	skor = 0;
	next_lvl_score = 100;
	p = new player();
	hpBoost_factor = 2000000;
	asteroid_factor = 12500000;
	sMode_factor = 135000000;
	timeBomb_factor = 2000000;	
	entities.clear();
	entities.push_back(p);
	before_t = current_t = std::chrono::high_resolution_clock::now();
}

double Game::compute_angle(double x1, double y1, double x2, double y2) {
	if(x1<x2)return atan(  (y1-y2)/(x1-x2)  )*180/phi;
	return -180+atan((y1 - y2) / (x1 - x2)) * 180 / phi;
}

void Game::increase_level() {
	asteroid_factor = std::max(50, asteroid_factor-8);
	timeBomb_factor = std::max(150, timeBomb_factor - 8);
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
	while (app->isOpen())
		{
			sf::Event event;
			
			if (!game_over) {
				while (app->pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						app->close();

					if (event.type == sf::Event::KeyPressed) {

						if (event.key.code == sf::Keyboard::Space && !spaceKeyPressed) {
							temp_bullet = new bullet(BLUE_BULLET,p->x, p->y, p->angle);
							entities.push_back(temp_bullet);
							temp_bullet = new bullet(BLUE_BULLET, p->x, p->y, p->angle+20);
							entities.push_back(temp_bullet);
							temp_bullet = new bullet(BLUE_BULLET, p->x, p->y, p->angle-20);
							temp_bullet->playSound();
							entities.push_back(temp_bullet);

							spaceKeyPressed = true;
						}
						if (event.key.code == sf::Keyboard::E) {
							ShotBoost *a = new ShotBoost();// (AstType::HARD_ASTEROID);
							a->dx = 0;
							a->dy = 0;
							a->x = 500;
							a->y = 300;
							entities.push_back(a);
						}
						if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
							p->move_direction = 3;
						}
						if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
							p->move_direction = 4;
						}
						if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
							p->move_direction = 1;
						}
						if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
							p->move_direction = 2;
						}
					}
					if (event.type == sf::Event::KeyReleased) {
						//printf("masuk\n");
						if (event.key.code == sf::Keyboard::Space)spaceKeyPressed = false;
						else if (event.key.code == sf::Keyboard::W || event.key.code == sf::Keyboard::Up
							|| event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down
							|| event.key.code == sf::Keyboard::A || event.key.code == sf::Keyboard::Left
							|| event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right

							) {
							p->move_direction = 0;// p->anim = sPlayer; //printf("masuk\n");
						}
						else if (event.key.code == sf::Mouse::Left) {
							spaceKeyPressed = false;
						}

					}
//					if (p->move_direction == 0)p->anim = sPlayer;
					if (event.type == sf::Event::MouseMoved) {
						double xx = sf::Mouse::getPosition().x;
						double yy = sf::Mouse::getPosition().y;
						double temp = compute_angle(p->get_possition().x /*+ 18*/, p->get_possition().y/* + 18*/, xx, yy);
						/*printf("%.2f %.2f %.2f %.2f set angle %f\n",
							xx,yy,p->get_possition().x,p->get_possition().y,
							temp);*/
						p->set_angle(temp);
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && !spaceKeyPressed) {//nembak 3
						temp_bullet = new bullet(BLUE_BULLET, p->x, p->y, p->angle);
						entities.push_back(temp_bullet);
						temp_bullet = new bullet(BLUE_BULLET, p->x, p->y, p->angle + 20);
						entities.push_back(temp_bullet);
						temp_bullet = new bullet(BLUE_BULLET, p->x, p->y, p->angle - 20);
						temp_bullet->playSound();
						entities.push_back(temp_bullet);
						spaceKeyPressed = true;
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !spaceKeyPressed) {//nembak satu
						spaceKeyPressed = true;
						temp_bullet = new bullet(RED_BULLET, p->x, p->y, p->angle);
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
					if ((a->getType() == EnType::BULLET || a->getType()==EnType::SHIP)&&
						b->getType()==EnType::ASTEROID) {
						if (a->hp < 1 || b->hp < 1)continue;
						if (isCollide(a, b))
						{	
//							printf("%d vs %d\n", a->hp,b->hp);
							int temp = a->hp;
							a->hp -= b->hp;
							b->hp -= temp;
							if (b->hp < 1) {
								temp_explode = new CollideEffect(CEffType::ROCK_EXLODE,b->x,b->y);
								temp_explode->playSound();
							}
							else {
								temp_explode = new CollideEffect(CEffType::RESIST, b->x, b->y);
								temp_explode->playSound();
							}
							entities.push_back(temp_explode);
							
							if (b->hp > 0)continue;
							if (b->R == 15)skor += 10;//jika tembak asteroid kecil
							else skor += 20;

							temp_ast = (asteroid*)a;
							if (b->R > 15 && temp_ast->get_asteroidType()==AstType::NORMAL_ASTEROID) {
								for (int i = 0;i < 2;i++)
								{
									temp_ast = new asteroid(AstType::SMALL_ASTEROID,b->x,b->y);
									entities.push_back(temp_ast);
								}
							}

						}
					}
					else if ( (a->getType()==EnType::BULLET || a->getType()==EnType::SHIP)&& 
						b->getType() == EnType::HP_BOOST) {
						
						if (a->hp < 1 || b->hp < 1)continue;
						if (isCollide(a, b)) {
							int temp = b->hp;
							b->hp -= a->hp;
							a->hp -= temp;
							if (b->hp < 1) {//penambahan darah kalau dapat
								p->hp += 100;
								temp_explode= new CollideEffect(CEffType::METAL_EXPLODE, b->x, b->y);
								temp_explode->playSound();
							}
							else {
								temp_explode = new CollideEffect(CEffType::RESIST, b->x, b->y);
								temp_explode->playSound();
							}
							entities.push_back(temp_explode);
						}
					}
					else if ( (a->getType() == EnType::BULLET || a->getType()==EnType::SHIP)&&
						b->getType() == EnType::SHOT_BOOST) {
						
						if (a->hp < 1 || b->hp < 1)continue;
						if (isCollide(a, b)) {
							int temp = b->hp;
							b->hp -= a->hp;
							a->hp -= temp;
							if (b->hp < 1) {
								skor += 35;
								p->superMode = true;
								temp_explode = new CollideEffect(CEffType::ROCK_EXLODE, b->x, b->y);
								temp_explode->playSound();
							}
							else {
								temp_explode = new CollideEffect(CEffType::RESIST, b->x, b->y);
								temp_explode->playSound();
							}
							before_t = std::chrono::high_resolution_clock::now();
							entities.push_back(temp_explode);
						}

					}
					else if ((a->getType() == EnType::BULLET || a->getType() == EnType::SHIP) && 
						b->getType() == EnType::TIME_BOMB) {
						
						if (a->hp < 1 || b->hp < 1) continue;
						if (isCollide(a, b)) {
							//printf("%d %d\n", p->hp, b->hp);
							int temp = b->hp;
							b->hp -= a->hp;
							a->hp -= temp;
							if (b->hp < 1) {
								if (a->getType()==EnType::BULLET) {
									skor += 45;
									temp_explode = new CollideEffect(CEffType::METAL_EXPLODE, b->x, b->y);
									temp_explode->playSound();
								}
								else {
									temp_explode = new CollideEffect(CEffType::BOMB_EXPLODE, b->x, b->y);
									temp_explode->playSound();
								}
								entities.push_back(temp_explode);
							}
							else {
								temp_explode = new CollideEffect(CEffType::RESIST, b->x, b->y);
								temp_explode->playSound();
								entities.push_back(temp_explode);
							}

							
						}
					}
					else if (a->getType()==EnType::SHIP && b->getType()==EnType::COLLIDE_EFFECT &&(
							( (CollideEffect*)b)->get_CEffType()==CEffType::BOMB_EXPLODE) ) {
					
						if (a->hp < 1 || b->hp < 1)continue;
						if (isCollide(a, b)) {
							a->hp -= 10;
						}
					}
				}
			}

			if (p->hp < 1&&!game_over) {
				temp_explode = new CollideEffect(CEffType::METAL_EXPLODE,p->x,p->y);
				temp_explode->playSound();
				entities.push_back(temp_explode);
				game_over = true;
				game_over_start = std::chrono::high_resolution_clock::now();
			}

			if (rand() % asteroid_factor == 0)
			{
				printf("masuk\n");
				if (rand() % 2 == 0) {
					asteroid *a = new asteroid(AstType::NORMAL_ASTEROID);
					entities.push_back(a);
				}
				else{
					asteroid *a = new asteroid(AstType::HARD_ASTEROID);
					entities.push_back(a);
				}
			}
			if (rand() % hpBoost_factor == 0)
			{
				printf("masuk\n");
				HpBoost *a = new HpBoost();
				entities.push_back(a);
			}
			if (rand() % sMode_factor == 0)
			{
				printf("masuk\n");
				ShotBoost *a = new ShotBoost();
				entities.push_back(a);
			}
			if (rand() % timeBomb_factor == 0)
			{
				printf("masuk\n");
				TimeBomb *a = new TimeBomb();
				entities.push_back(a);
			}

			if (p->superMode) {
				current_t = std::chrono::high_resolution_clock::now();
				comp = std::chrono::duration<double, std::milli>(current_t - before_t).count();
				if (comp > 5000) {//super mode dapat dari diamond,effect : peluru tembus
					p->superMode = false;
					//printf("supermode off");
				}
			}


			sprintf(rest_time, "%.2f", (5000 - comp) / 1000);
			//////draw//////
			if (p->superMode) {
				score_text.setString(
					"Score : " + std::to_string(skor) + "\nHp : " + std::to_string(p->hp)
					+ "\nsuperMode : " + std::string(rest_time)
				);
			}
			else {
				score_text.setString(
					"Score : " + std::to_string(skor) + "\nHp : " + std::to_string(p->hp)
				);
			}
			app->draw(background);
			app->draw(score_text);




			//control dead object
			for (auto i = entities.begin();i != entities.end();)
				{
					Entity *e = *i;
					if (e->name == "player"&&e->hp < 1) { i++; continue; }
					else if (e->getType()==EnType::COLLIDE_EFFECT && e->anim.isEnd()) {
						i = entities.erase(i);
						delete e;
						continue;
					}
					else if (e->name == "bullet") {
						bullet *temp = (bullet*)e;
						if (p->superMode) {
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
						sprintf(rest_time, "%d", (int)(1+(5000 - comp) / 1000));//atur waktu time bomb
						temp_text.setPosition({ e->x-4, e->y+3.5f });
						temp_text.setString(std::string(rest_time));
						e->update();
						e->anim.update();
						e->draw(*app);
						app->draw(temp_text);

						if (comp > 5000) {//atur waktu time bomb
							temp_explode = new CollideEffect(CEffType::BOMB_EXPLODE, e->x, e->y);
							temp_explode->playSound();
							temp_vEntity.push_back(temp_explode);
							i = entities.erase(i);
							delete e;
							continue;
						}
						if (e->hp < 1) { i = entities.erase(i); delete e; }
						i++;
						continue;
					}
					e->update();
					e->anim.update();
					e->draw(*app);

					if (e->hp < 1&&e->getType()!=EnType::SHIP) { i = entities.erase(i); delete e; }
					else i++;

				}
			
			for (auto x = temp_vEntity.begin();x != temp_vEntity.end();x++) {
					Entity *tm = *x;
					entities.push_back(tm);
				}
			temp_vEntity.clear();
			if(p->hp>0)p->draw(*app);

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





