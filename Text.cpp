#include "Text.h"

Text::Text(SDL_Renderer * _renderer, TTF_Font * _font,SDL_Color color, std::string _text)
{
	font = _font;
	text = _text;
	text_color = color;

	std::string ImageLoadError = "Couldn't load image!";
	renderer_ptr = _renderer;
	try
	{
		SDL_Surface* temp_surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
		if (temp_surface == nullptr)
		{
			throw(ImageLoadError);
		}

		position = { 0, 0, temp_surface->w, temp_surface->h };


		if (renderer_ptr == nullptr)
		{
			throw(ImageLoadError);
		}
		else if (temp_surface == nullptr)
		{
			throw(ImageLoadError);
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(renderer_ptr, temp_surface);
			if (texture == nullptr)
			{
				throw(ImageLoadError);
			}
			SDL_FreeSurface(temp_surface);
		}
	}
	catch (std::string err)
	{
		std::cout << err << " Error code:\n" << IMG_GetError() << std::endl;
	}

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

	
}

Text::~Text()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void Text::setText(std::string _text)
{
	SDL_DestroyTexture(texture);
	text = _text;

	std::string ImageLoadError = "Couldn't load image!";
	try
	{
		SDL_Surface* temp_surface = TTF_RenderText_Solid(font, text.c_str(), text_color);
		if (temp_surface == nullptr)
		{
			throw(ImageLoadError);
		}

		position = { 0, 0, temp_surface->w, temp_surface->h };


		if (renderer_ptr == nullptr)
		{
			throw(ImageLoadError);
		}
		else if (temp_surface == nullptr)
		{
			throw(ImageLoadError);
		}
		else
		{
			texture = SDL_CreateTextureFromSurface(renderer_ptr, temp_surface);
			if (texture == nullptr)
			{
				throw(ImageLoadError);
			}
			SDL_FreeSurface(temp_surface);
		}
	}
	catch (std::string err)
	{
		std::cout << err << " Error code:\n" << IMG_GetError() << std::endl;
	}

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

}

void Text::render(int x, int y, double angle, SDL_Point * rotation_center,bool flip_horisontal, bool flip_vertical)
{
	Texture::render(x, y, angle, rotation_center, flip_horisontal, flip_vertical);
}
