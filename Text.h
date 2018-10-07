#pragma once
#include <SDL_ttf.h>
#include "Texture.h"

//Class responsible for generating TTF texts in a form of texture
class Text : public Texture
{
	TTF_Font* font;
	std::string text;
	SDL_Color text_color;

public:
	Text() = delete;
	Text(SDL_Renderer* _renderer, TTF_Font* _font, SDL_Color color, std::string _text = "NO_TEXT");
	~Text();

	//change text of the object
	void setText(std::string _text);
	inline std::string getText() { return text; };


	//refresh text on the screen
	void render(int x, int y, double angle = 0.0, SDL_Point* rotation_center = NULL,bool flip_horisontal = false, bool flip_vertical = false) override;
};