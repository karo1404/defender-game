#include "AboutState.h"

AboutState::~AboutState()
{
}

AboutState::AboutState(Window * _window, SDL_Renderer * _renderer, unsigned int * _frame_counter, SDL_Event * _e)
{
	setState(STATE_ABOUT);

	main_window = _window;
	main_renderer = _renderer;
	frame_counter = _frame_counter;
	*frame_counter = 1;
	e = _e;

	cursor = std::unique_ptr<Texture>(new Texture(main_renderer, "res/cursor_19x19.png"));
	button_texture = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/menu_button_exit_100x50_3f.png", 3, 1, frame_counter));
	but_back = std::unique_ptr<Button>(new Button(button_texture.get()));
	sdl_logo = std::unique_ptr<Texture>(new Texture(main_renderer,"res/sdl_logo_220x128.png"));
	main_font = TTF_OpenFont("res/fonts/AmaticSC-Bold.ttf", 46);
	small_font = TTF_OpenFont("res/fonts/AmaticSC-Bold.ttf", 26);
	credits1 = std::unique_ptr<Text>(new Text(main_renderer, main_font, { 255, 255, 255, 255 }));
	version = std::unique_ptr<Text>(new Text(main_renderer, small_font, { 255, 255, 255, 255 }));
}

void AboutState::handleEvents()
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
			but_back->handleEvent(e, mouse_pos.x, mouse_pos.y);
		}
		if (e->type == SDL_KEYDOWN && e->key.keysym.sym == SDLK_ESCAPE)
		{
			setNextState(STATE_MENU);
		}
		main_window->handleEvent(*e);
	}
}

void AboutState::logic()
{
	if (but_back->getState() == STATE_PRESSED)
	{
		setNextState(STATE_MENU);
	}
}

void AboutState::render()
{
	if (!(main_window->isMininized())) //stop rendering when window is minimized
	{
		SDL_RenderClear(main_renderer);
		{
			but_back->render(20, 650);
			credits1->setText("Project created for programming course at Silesian University of Technology");
			credits1->render(GAME_WINDOW_WIDTH / 2 - credits1->getWidth() / 2,40);
			credits1->setText("Code, design, visuals: Karol Jazdrzyk (karol1404@vp.pl)");
			credits1->render(GAME_WINDOW_WIDTH / 2 - credits1->getWidth() / 2, 60 + credits1->getHeight());
			credits1->setText("Sound effects and music by Groundislava under creative commons license");
			credits1->render(GAME_WINDOW_WIDTH / 2 - credits1->getWidth() / 2, 120 + 2*credits1->getHeight());
			credits1->setText("Created with SDL 2.0 library under the zlib license");
			credits1->render(GAME_WINDOW_WIDTH / 2 - credits1->getWidth()/2, 140 + 3*credits1->getHeight());
			sdl_logo->render(GAME_WINDOW_WIDTH / 2 - sdl_logo->getWidth() / 2, 520);
			version->setText("version 1, 06.06.2018");
			version->render(GAME_WINDOW_WIDTH - version->getWidth() - 10, GAME_WINDOW_HEIGHT - version->getHeight() - 10);
		}
		cursor->render(mouse_pos.x - 9, mouse_pos.y - 9);
		SDL_RenderPresent(main_renderer);
	}
}
