#include "GameState.h"

void GameState::handleEvents()
{
	temp_counter = *frame_counter; //for pause handling

	while (SDL_PollEvent(e) != 0)
	{
		if (e->type == SDL_QUIT)
		{
			setNextState(STATE_QUIT);
		}
		else
		{
			if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
			{
				SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y); //checks position of the mouse
				if (structure != 0 && enemies_on_the_field && !pause) 
				{
						player->handleEvent(e, mouse_pos.x, mouse_pos.y);	
				}
				else
				{
					but_retry->handleEvent(e, mouse_pos.x, mouse_pos.y);
					but_exit->handleEvent(e, mouse_pos.x, mouse_pos.y);
				}
			}
			if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
			{

				if (!pause)
				{
					but_retry->handleEvent(e, mouse_pos.x, mouse_pos.y);
					but_exit->handleEvent(e, mouse_pos.x, mouse_pos.y);
					pause = true;
				}
				else
				{
					pause = false;
				}
			}
		}
		main_window->handleEvent(*e);
	}
}

void GameState::logic()
{
	if (!pause)
	{
		enemy_menager->spawn();

		if (!proj_vec.empty())
		{
			for (unsigned int i = 0; i < proj_vec.size(); i++)
			{
				if (proj_vec[i]->exist() == true)
				{
					if (!ene_vec.empty())
					{
						for (unsigned int o = 0; o < ene_vec.size(); o++)
						{
							if (ene_vec[o]->checkCollision(proj_vec[i]->getPosX(), proj_vec[i]->getPosY()) && ene_vec[o]->exist() && !proj_vec[i]->collide())
							{
								ene_vec[o]->hit();
								proj_vec[i]->collide(true);
								if (ene_vec[o]->getHealth() == 0)
								{
									score += (ene_vec[o]->getMaxHealth())*(proj_vec[i]->getAirTime()) * 10;
								}
								else
								{
									score += (proj_vec[i]->getAirTime()) * 10;
								}
							}
						}
					}
					proj_vec[i]->move();
				}
				else
				{
					delete proj_vec[i];
					proj_vec.erase(proj_vec.begin() + i);
				}
			}
		}
		if (!ene_vec.empty())
		{
			for (unsigned int o = 0; o < ene_vec.size(); o++)
			{
				unsigned int temp = structure;
				ene_vec[o]->move(&structure);
				if (temp > structure)
				{
					wall_was_damaged = true;
				}
				if (ene_vec[o]->exist())
				{
					if (ene_vec[o]->getPosX() <= 400)
					{
						if (ene_vec[o]->getState() == STATE_MOVE && structure != 0)
						{
							ene_vec[o]->setState(STATE_ATTACK);
						}
						else if (ene_vec[o]->getState() == STATE_ATTACK && structure <= 0)
						{
							ene_vec[o]->setState(STATE_MOVE);
						}
					}
				}
			}
		}
	}
	else
	{
		*frame_counter = temp_counter;
	}
	if (!timestamp_semaphore || pause) //if ending fade-to-black effect has finished
	{
		if (but_exit->getState() == STATE_PRESSED)
		{
			setNextState(STATE_MENU);
		}
		if (but_retry->getState() == STATE_PRESSED)
		{
			setNextState(STATE_GAME);
		}
	}
}

void GameState::render()
{
	if (!(main_window->isMininized())) //stop rendering when window is minimized
	{
			SDL_RenderClear(main_renderer);
		{
			main_background->render(0, 0);
			if (wall_was_damaged == false)
			{
				wall->renderFrame(150, 400, 1);
			}
			else
			{
				wall->renderFrame(150, 400, 2);
				wall_was_damaged = false;
			}
			if (structure > 0)
			{
				text->setText("score: " + std::to_string(score));
				text->render(10, 10);
			}
			
			player->render();

			if (!ene_vec.empty())
			{
				unsigned short battlefield_check = 0;
				for (std::vector<Enemy*>::reverse_iterator it = ene_vec.rbegin(); it != ene_vec.rend(); it++)
				{
					if ((*it)->exist()) 
					{
						(*it)->render();
						battlefield_check++;
					}
				}
				if (battlefield_check == 0)
				{
					enemies_on_the_field = false;
				}
			}
			if (!proj_vec.empty())
			{
				for (unsigned int i = 0; i < proj_vec.size(); i++)
				{
					proj_vec[i]->render();
				}
			}

			//cooldown bar
			bar_cooldown->render(20, 702, SDL_GetTicks() - player->getShotStart());
			//power bar
			player->refreshShotPower();
			bar_power->render(20, 680, player->getShotPower());
			//structure bar
			bar_structure->render(440, 20, structure);
			struct_bar_frame->render(440, 20);


			if (*frame_counter <= 510)
			{
				SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 255 - *frame_counter / 2);
				SDL_RenderFillRect(main_renderer, &blackboard);
			}

			if (structure <= 0) //fade-to-black efect
			{
				game_music->stopFadeOut(3000);
				wall->setOpacity(0);
				if (timestamp_semaphore)
				{
					timestamp = *frame_counter;
					timestamp_semaphore = false;
				}
				if ((*frame_counter - timestamp) < 255)
				{
					SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, (*frame_counter - timestamp));
					SDL_RenderFillRect(main_renderer, &blackboard);
					text->setText("GAME OVER");
					text->render(GAME_WINDOW_WIDTH / 2 - text->getWidth() / 2, GAME_WINDOW_HEIGHT / 2-100);
				}
				else
				{
					SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 255);
					SDL_RenderFillRect(main_renderer, &blackboard);
					text->setText("your score: " + std::to_string(score));
					text->render(GAME_WINDOW_WIDTH / 2 - text->getWidth() / 2, GAME_WINDOW_HEIGHT / 2);
					text->setText("GAME OVER");
					text->render(GAME_WINDOW_WIDTH / 2 - text->getWidth() / 2, GAME_WINDOW_HEIGHT / 2-100);
					but_exit->render(GAME_WINDOW_WIDTH / 2 - 150, GAME_WINDOW_HEIGHT / 2 + 200);
					but_retry->render(GAME_WINDOW_WIDTH / 2 + 50, GAME_WINDOW_HEIGHT / 2 + 200);
				}
			}
			else if (*frame_counter >= 36000 && !enemies_on_the_field)
			{
				game_music->stopFadeOut(3000);
				if (timestamp_semaphore)
				{
					score += structure * 50;
					timestamp = *frame_counter;
					timestamp_semaphore = false;
				}
				if ((*frame_counter - timestamp) < 255)
				{
					SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, (*frame_counter - timestamp));
					SDL_RenderFillRect(main_renderer, &blackboard);
					text->setText("YOU WIN!");
					text->render(GAME_WINDOW_WIDTH / 2 - text->getWidth() / 2, GAME_WINDOW_HEIGHT / 2 - 100);
				}
				else
				{
					SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 255);
					SDL_RenderFillRect(main_renderer, &blackboard);
					text->setText("your score: " + std::to_string(score));
					text->render(GAME_WINDOW_WIDTH / 2 - text->getWidth() / 2, GAME_WINDOW_HEIGHT / 2);
					text->setText("YOU WIN!");
					text->render(GAME_WINDOW_WIDTH / 2 - text->getWidth() / 2, GAME_WINDOW_HEIGHT / 2 - 100);
					but_exit->render(GAME_WINDOW_WIDTH / 2 - 150, GAME_WINDOW_HEIGHT / 2 + 200);
					but_retry->render(GAME_WINDOW_WIDTH / 2 + 50, GAME_WINDOW_HEIGHT / 2 + 200);
				}
			}
			else if (pause)
			{
				SDL_SetRenderDrawColor(main_renderer, 0, 0, 0, 155);
				SDL_RenderFillRect(main_renderer, &blackboard);
				text->setText("your score: " + std::to_string(score));
				text->render(GAME_WINDOW_WIDTH / 2 - text->getWidth() / 2, GAME_WINDOW_HEIGHT / 2);
				text->setText("GAME PAUSED");
				text->render(GAME_WINDOW_WIDTH / 2 - text->getWidth() / 2, GAME_WINDOW_HEIGHT / 2 - 100);
				but_exit->render(GAME_WINDOW_WIDTH / 2 - 150, GAME_WINDOW_HEIGHT / 2 + 200);
				but_retry->render(GAME_WINDOW_WIDTH / 2 + 50, GAME_WINDOW_HEIGHT / 2 + 200);
			}
		}
		cursor->render(mouse_pos.x - 9, mouse_pos.y - 9);
		SDL_RenderPresent(main_renderer);
	}
}



GameState::~GameState()
{
	if (!proj_vec.empty())
	{
		for (unsigned int i = 0; i < proj_vec.size(); i++)
		{
			delete proj_vec[i];
		}
	}
	proj_vec.clear();
	if (!ene_vec.empty())
	{
		for (unsigned int k = 0; k < ene_vec.size(); k++)
		{
			delete ene_vec[k];
		}
	}
	ene_vec.clear();
}

GameState::GameState(Window * _window, SDL_Renderer * _renderer, unsigned int* _frame_counter, SDL_Event*  _e)
{
	setState(STATE_GAME);

	main_window = _window;
	main_renderer = _renderer;
	frame_counter = _frame_counter;
	*frame_counter = 1;
	score = 0;
	structure = 1000;
	e = _e;

	cursor = std::unique_ptr<Texture>(new Texture(main_renderer, "res/cursor_19x19.png"));
	game_music = std::unique_ptr<Music>(new Music("res/audio/game_music.ogg"));
	char_body = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/char_body_40x100_8f.png", 8, 10, frame_counter));
	char_arm = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/char_arm_40x60_4f.png", 4, 20, frame_counter));
	char_shot = std::unique_ptr<SoundEffect>(new SoundEffect("res/audio/shot.wav"));
	se_arrow_explosion = std::unique_ptr<SoundEffect>(new SoundEffect("res/audio/projectile_explosion.wav"));
	cd_bar = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/cdbar_100x5.png", 1, 1, frame_counter));
	pow_bar = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/powbar_300x20.png", 1, 1, frame_counter));
	proj_arr = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/arrow_32x16_5f.png", 5, 2, frame_counter));
	proj_arr_coll = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/arrow_collision1_32x32_7f.png", 7, 2, frame_counter));
	player = std::unique_ptr<Player>(new Player(100, 500, char_body.get(), char_arm.get(), proj_arr.get(), proj_arr_coll.get(), { 3, 30 }, char_shot.get(), se_arrow_explosion.get(), &proj_vec, &pause));

	main_background = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/background_1280x720_8f.png",8,8,frame_counter));
	wall = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/wall_360x320_2f.png", 2, 1, frame_counter));
	main_font = TTF_OpenFont("res/fonts/AmaticSC-Bold.ttf", 46);
	text = std::unique_ptr<Text>(new Text(main_renderer, main_font, { 255, 255, 255, 255 }));
	struct_bar = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/structbar_400x20.png", 1, 1, frame_counter));
	struct_bar_frame = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/structbar_frame_400x20.png", 1, 1, frame_counter));
	bar_structure = std::unique_ptr<ProgressBar>(new ProgressBar(struct_bar.get(), structure));
	
	bar_cooldown = std::unique_ptr<ProgressBar>(new ProgressBar(cd_bar.get(), player->getShotCooldown()));
	bar_power = std::unique_ptr<ProgressBar>(new ProgressBar(pow_bar.get(), player->getMaxPower()));
	enemy_menager = std::unique_ptr<EnemyMenager>(new EnemyMenager(&ene_vec, this));

	but_exit_tex = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/menu_button_exit_100x50_3f.png", 3, 1, frame_counter));
	but_retry_tex = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/menu_button_retry_100x50_3f.png", 3, 1, frame_counter));
	but_exit = std::unique_ptr<Button>(new Button(but_exit_tex.get()));
	but_retry = std::unique_ptr<Button>(new Button(but_retry_tex.get()));

	text->setText("score: " + std::to_string(score));
	SDL_SetRenderDrawBlendMode(main_renderer, SDL_BLENDMODE_BLEND);
	game_music->play();
}