#pragma once
#include "BaseState.h"
#include "Button.h"
#include "Text.h"
#include <memory>
#include "Main.h"

//State displaying credits and some other stuff
class AboutState : public BaseState
{
	std::unique_ptr<Texture> cursor;
	std::unique_ptr<AnimatedTexture> button_texture;
	std::unique_ptr<Button> but_back;
	std::unique_ptr<Texture> sdl_logo;

	TTF_Font* main_font;
	TTF_Font* small_font;
	std::unique_ptr<Text> credits1;
	std::unique_ptr<Text> version;

public:
	AboutState() = delete;
	~AboutState();
	AboutState(Window* _window, SDL_Renderer* _renderer, unsigned int* _frame_counter, SDL_Event* _e);

	void handleEvents();

	void logic();

	void render();
};

