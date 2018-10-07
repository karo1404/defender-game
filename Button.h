#pragma once
#include "AnimatedTexture.h"

enum ButtonState
{
	STATE_IDLE = 1,
	STATE_HOVER,
	STATE_PRESSED
};

//Class responsible for handling buttons
//Passed animated texture should have 3 frames where:
//1-idle, 2-hover, 3-pressed
class Button
{
	AnimatedTexture* texture;
	ButtonState state;
	SDL_Point position;

public:

	Button() = delete;
	Button(AnimatedTexture* _texture, int x = 0, int y = 0);
	~Button();

	inline ButtonState getState() { return state; };

	void move(int dX, int dY);

	void handleEvent(SDL_Event* ev, int &mouse_pos_x, int &mouse_pos_y);

	void render(int _x = 0, int _y = 0);
};

