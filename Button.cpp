#include "Button.h"

Button::Button(AnimatedTexture * _texture,int x, int y)
{
	texture = _texture;
	state = STATE_IDLE;
	if (x != 0 || y != 0)
	{
		position.x = x;
		position.y = y;
	}
}


Button::~Button()
{
	texture = nullptr;
}

void Button::move(int dX, int dY)
{
	position.x += dX;
	position.y += dY;
}

void Button::handleEvent(SDL_Event * ev, int & mouse_pos_x, int & mouse_pos_y)
{
	if (mouse_pos_x > position.x && mouse_pos_x < position.x + texture->getWidth() && mouse_pos_y > position.y && mouse_pos_y < position.y + texture->getHeight()) //if cursor is on the button
	{
		if(ev->type == SDL_MOUSEBUTTONDOWN)
		{
			state = STATE_PRESSED;
		}
		else
		{
			state = STATE_HOVER;
		}
	}
	else
	{
		state = STATE_IDLE;
	}

}

void Button::render(int _x, int _y)
{
	if (_x != 0 || _y != 0) 
	{
		position.x = _x;
		position.y = _y;
	}

	if (texture->getFrames() <= 2)
	{
		texture->renderFrame(position.x, position.y, 1);
	}
	else
	{
		texture->renderFrame(position.x, position.y, state);
	}
}
