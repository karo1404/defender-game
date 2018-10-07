#include "MenuState.h"

MenuState::~MenuState()
{
	menu_music->stop(2000);
}

MenuState::MenuState(Window * _window, SDL_Renderer * _renderer, unsigned int * _frame_counter, SDL_Event * _e)
{
	setState(STATE_MENU);

	main_window = _window;
	main_renderer = _renderer;
	frame_counter = _frame_counter;
	*frame_counter = 1;
	e = _e;

	//allocation of resources
	cursor = std::unique_ptr<Texture>(new Texture(main_renderer, "res/cursor_19x19.png"));
	logo = std::unique_ptr<Texture>(new Texture(main_renderer, "res/logo_400x120.png"));
	menu_music = std::unique_ptr<SoundEffect>(new SoundEffect("res/audio/menu_music.ogg"));
	but_start_tex = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/menu_button1_300x100_3f.png", 3, 1, frame_counter));
	but_about_tex = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/menu_button2_300x100_3f.png", 3, 1, frame_counter));
	but_quit_tex = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/menu_button3_300x100_3f.png", 3, 1, frame_counter));
	but_start = std::unique_ptr<Button>(new Button(but_start_tex.get(), -but_start_tex->getWidth(), GAME_WINDOW_HEIGHT / 2 - but_start_tex->getHeight() / 2 - 150));
	but_about = std::unique_ptr<Button>(new Button(but_about_tex.get(), -but_about_tex->getWidth(), GAME_WINDOW_HEIGHT / 2 - but_about_tex->getHeight() / 2));
	but_quit = std::unique_ptr<Button>(new Button(but_quit_tex.get(), -but_quit_tex->getWidth(), GAME_WINDOW_HEIGHT / 2 - but_quit_tex->getHeight() / 2 + 150));
	tex_light = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/menu_light_1280x380.png", 1, 1, frame_counter));
	main_font = TTF_OpenFont("res/fonts/AmaticSC-Bold.ttf", 32);
	text = std::unique_ptr<Text>(new Text(main_renderer, main_font, { 120, 120, 120, 120 }));

	menu_music->playLoop(-1);
}

void MenuState::handleEvents()
{
	while (SDL_PollEvent(e) != 0)
	{
		if (e->type == SDL_QUIT)
		{
			setNextState(STATE_QUIT);
		}
		if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
		{
			SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y); //checks position of the mouse
			but_start->handleEvent(e, mouse_pos.x, mouse_pos.y);
			but_about->handleEvent(e, mouse_pos.x, mouse_pos.y);
			but_quit->handleEvent(e, mouse_pos.x, mouse_pos.y);
		}
		main_window->handleEvent(*e);
	}
}

void MenuState::logic()
{
	if (*frame_counter < 60)
	{
		if (*frame_counter < 40 && *frame_counter > 10)
		{
			but_start->move(12, 0);
		}
		if (*frame_counter < 50 && *frame_counter > 20)
		{
			but_about->move(12, 0);
		}
		if (*frame_counter > 30)
		{
			but_quit->move(12, 0);
		}
	}

	if(but_start->getState() == STATE_PRESSED)
	{
		setNextState(STATE_GAME);
	}
	else if(but_about->getState() == STATE_PRESSED)
	{
		setNextState(STATE_ABOUT);
	}
	else if (but_quit->getState() == STATE_PRESSED)
	{
		setNextState(STATE_QUIT);
	}
}

void MenuState::render()
{
	if (!(main_window->isMininized())) //stop rendering when window is minimized
	{
		SDL_RenderClear(main_renderer);
		{
			//background
			if (tex_light->getPosX() <= 0) 
			{
				tex_light->render(1280 - tex_light->getWidth() + *frame_counter / 3, GAME_WINDOW_HEIGHT / 2 - 190);
			}
			else
			{
				tex_light->render(1, GAME_WINDOW_HEIGHT / 2 - 190);
			}
			cos_of_present_frame = cos(double(*frame_counter % 628) / 100.0);
			logo->rescale(400 + int(50 * cos_of_present_frame), 120 + int(16 * cos_of_present_frame));
			logo->render(GAME_WINDOW_WIDTH / 2 - int(25 * cos_of_present_frame), GAME_WINDOW_HEIGHT / 2 - 60 - int(8 * cos_of_present_frame), 10 * sin(double(*frame_counter % 628) / 100.0));

			//buttons
			but_start->render();
			but_about->render();
			but_quit->render();

			//text
			text->setText("Fullscreen toggle - F");
			text->render(GAME_WINDOW_WIDTH - text->getWidth() - 10, GAME_WINDOW_HEIGHT - text->getHeight() - 10);
		}
		cursor->render(mouse_pos.x - 9, mouse_pos.y - 9);
		SDL_RenderPresent(main_renderer);
	}
}
