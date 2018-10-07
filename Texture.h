#pragma once
#include <SDL_image.h>
#include <string>
#include <iostream>


//Class responsible for storing static images.
class Texture
{
protected:
	SDL_Texture* texture;
	std::string file_path;
	SDL_Renderer* renderer_ptr;
	SDL_Rect position;

public:
	Texture();
	Texture(SDL_Renderer* renderer, std::string _file_path);
	~Texture();

	inline int getPosX() { return position.x; };
	inline int getPosY() { return position.y; };
	inline int getWidth() { return position.w; };
	inline int getHeight() { return position.h; };

	//rescale texture
	void rescale(int _w, int _h);

	//sets hue & saturation of image
	void setColor(Uint8 r, Uint8 g, Uint8 b);

	//sets opacity (alpha channel) of image
	void setOpacity(Uint8 alpha);

	//refresh image
	virtual void render(int x, int y, double angle = 0.0, SDL_Point* rotation_center = NULL, bool flip_horisontal = false, bool flip_vertical = false);
};