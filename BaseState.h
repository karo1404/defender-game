#pragma once
#include <SDL.h>
#include "Window.h"

enum BaseStates 
{
	STATE_EMPTY,
	STATE_MENU,
	STATE_GAME,
	STATE_ABOUT,
	STATE_QUIT
};

//Virtual class providing base for state classes
class BaseState
{
protected:

	int state;
	int next_state;

public:
	Window* main_window;
	SDL_Renderer* main_renderer;
	unsigned int* frame_counter;
	SDL_Event* e;

	virtual ~BaseState() {};

	virtual void handleEvents() = 0;

	virtual void logic() = 0; 

	virtual void render() = 0;

	inline int getState() { return state; };
	inline int getNextState() { return next_state; };
	inline void setState(BaseStates _state) { state = _state; };
	inline void setNextState(BaseStates _state) { next_state = _state; };
};
