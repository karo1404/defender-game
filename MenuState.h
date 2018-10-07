#pragma once
#include "BaseState.h"
#include "Button.h"
#include "Text.h"
#include "Main.h"
#include "SoundEffect.h"
#include <memory>

class MenuState : public BaseState
{
	std::unique_ptr<Texture> cursor;
	std::unique_ptr<Texture> logo;
	std::unique_ptr<AnimatedTexture> but_start_tex;
	std::unique_ptr<AnimatedTexture> but_about_tex;
	std::unique_ptr<AnimatedTexture> but_quit_tex;
	std::unique_ptr<Button> but_start;
	std::unique_ptr<Button> but_about;
	std::unique_ptr<Button> but_quit;
	std::unique_ptr<AnimatedTexture> tex_light;
	std::unique_ptr<SoundEffect> menu_music;

	TTF_Font* main_font;
	std::unique_ptr<Text> text;
	double cos_of_present_frame;

public:
	MenuState() = delete;
	~MenuState();
	MenuState(Window* _window, SDL_Renderer* _renderer, unsigned int* _frame_counter, SDL_Event* _e);

	void handleEvents();

	void logic();

	void render();
};

