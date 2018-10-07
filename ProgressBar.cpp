#include "ProgressBar.h"


ProgressBar::ProgressBar(AnimatedTexture * image, int max_val)
{
	texture = image;
	max_value = max_val;
	max_texture_width = texture->getWidth();
}

ProgressBar::ProgressBar(ProgressBar & object)
{
	texture = object.texture;
	max_value = object.max_value;
	present_value = max_value;
	max_texture_width = object.max_texture_width;
}


ProgressBar::~ProgressBar()
{
}

void ProgressBar::render(int x, int y)
{
	texture->renderFragment(x, y, int(std::ceil((double(present_value) / double(max_value))*max_texture_width)), texture->getHeight());
}

void ProgressBar::render(int x, int y, Uint16 value)
{

	if(value >= max_value)
	{
		texture->renderFragment(x, y, max_texture_width, texture->getHeight());
	}
	else
	{
		texture->renderFragment(x, y, int(std::ceil((double(value) / double(max_value))*max_texture_width)), texture->getHeight());
	}
}
