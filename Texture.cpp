#include "Texture.h"


Texture::Texture()
{
	//texture = nullptr;
	renderer_ptr = nullptr;
}

Texture::Texture(SDL_Renderer * renderer, std::string _file_path)
{
	std::string ImageLoadError = "Couldn't load image!";
	renderer_ptr = renderer;
	try
	{
	SDL_Surface* temp_surface = IMG_Load(_file_path.c_str());
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
		texture = SDL_CreateTextureFromSurface(renderer, temp_surface);
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

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
	texture = nullptr;
}

void Texture::rescale(int _w, int _h)
{
	position.w = _w;
	position.h = _h;
}

void Texture::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(Texture::texture, r, g, b);
}

void Texture::setOpacity(Uint8 val)
{
	SDL_SetTextureAlphaMod(texture, val);
}

void Texture::render(int x, int y, double angle, SDL_Point* rotation_center, bool flip_horisontal, bool flip_vertical)
{
	position.x = x;
	position.y = y;

	if(!flip_horisontal && !flip_vertical)
	{
		SDL_RenderCopyEx(renderer_ptr, texture, NULL, &position, angle, rotation_center, SDL_FLIP_NONE);
	}
	else if (flip_horisontal && !flip_vertical)
	{
		SDL_RenderCopyEx(renderer_ptr, texture, NULL, &position, angle, rotation_center, SDL_FLIP_HORIZONTAL);
	}
	else if (!flip_horisontal && flip_vertical)
	{
		SDL_RenderCopyEx(renderer_ptr, texture, NULL, &position, angle, rotation_center, SDL_FLIP_VERTICAL);
	}
	else
	{
		SDL_RenderCopyEx(renderer_ptr, texture, NULL, &position, angle, rotation_center, SDL_FLIP_NONE);
	}
}