#include "AnimatedTexture.h"


AnimatedTexture::AnimatedTexture(SDL_Renderer * renderer, std::string _file_path, int _frames_num, int _animation_speed, const unsigned int* _passed_frames_counter)
{
	std::string ImageLoadError = "Couldn't load image!";
	renderer_ptr = renderer;
	frames_num = _frames_num;
	present_frame = 0;
	animation_speed = _animation_speed;
	passed_frames_counter = _passed_frames_counter;

	try
	{
	SDL_Surface* temp_surface = IMG_Load(_file_path.c_str());
	if (temp_surface == nullptr)
	{
		throw(ImageLoadError);
	}

	frame = position = { 0, 0, temp_surface->w/frames_num, temp_surface->h };

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

AnimatedTexture::AnimatedTexture(AnimatedTexture & object)
{
	frame = object.frame;
	animation_speed = object.animation_speed;
	frames_num = object.frames_num;
	passed_frames_counter = object.passed_frames_counter;
	present_frame = 0;
	renderer_ptr = object.renderer_ptr;
	texture = object.texture;
	position = object.position;
}

AnimatedTexture::~AnimatedTexture()
{
	//SDL_DestroyTexture(texture);
	texture = nullptr;
}

void AnimatedTexture::setColor(Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetTextureColorMod(texture, r, g, b);
}

void AnimatedTexture::render(int x, int y, double angle, SDL_Point* rotation_center, bool flip_horisontal, bool flip_vertical)
{
	position.x = x;
	position.y = y;

	if (present_frame == frames_num) 
	{
		present_frame = 0;
	}

	if (*passed_frames_counter%animation_speed == 0) 
	{
		frame.x = present_frame * frame.w; //changes frame of animation to render
		present_frame++;
	}

	if (!flip_horisontal && !flip_vertical)
	{
		SDL_RenderCopyEx(renderer_ptr, texture, &frame, &position, angle, rotation_center, SDL_FLIP_NONE);
	}
	else if (flip_horisontal && !flip_vertical)
	{
		SDL_RenderCopyEx(renderer_ptr, texture, &frame, &position, angle, rotation_center, SDL_FLIP_HORIZONTAL);
	}
	else if (!flip_horisontal && flip_vertical)
	{
		SDL_RenderCopyEx(renderer_ptr, texture, &frame, &position, angle, rotation_center, SDL_FLIP_VERTICAL);
	}
	else
	{
		SDL_RenderCopyEx(renderer_ptr, texture, &frame, &position, angle, rotation_center, SDL_FLIP_NONE);
	}

}

void AnimatedTexture::renderOnce(int x, int y, double angle, SDL_Point* rotation_center)
{
	if (present_frame == 0) 
	{
		present_frame = 1;
	}
	position.x = x;
	position.y = y;

	if (*passed_frames_counter%animation_speed == 0)
	{
		frame.x = (present_frame - 1) * frame.w; //changes frame of animation to render

		if (present_frame != frames_num)
		{
			present_frame++;
		}
	}

	SDL_RenderCopyEx(renderer_ptr, texture, &frame, &position, angle, rotation_center, SDL_FLIP_NONE);
}

void AnimatedTexture::renderFrame(int x, int y, int _frame, double angle, SDL_Point * rotation_center)
{
	std::string RenderError = "Selected frame to render is out of animation sequence!";
	try 
	{
		if(_frame > frames_num || _frame < 0)
		{
			throw(RenderError);
		}
		else
		{
			present_frame = (_frame - 1);
		}
	}
	catch (std::string err)
	{
		std::cout << err << " Error code:\n" << IMG_GetError() << std::endl;
	}

	position.x = x;
	position.y = y;

	frame.x = present_frame * frame.w; //changes frame of animation to render
	
	SDL_RenderCopyEx(renderer_ptr, texture, &frame, &position, angle, rotation_center, SDL_FLIP_NONE);
}

void AnimatedTexture::renderFragment(int x, int y, int w, int h, double angle, SDL_Point * rotation_center)
{
	position.x = x;
	position.y = y;

	position.w = w;
	position.h = h;

	frame.w = w;
	frame.h = h;

	SDL_RenderCopyEx(renderer_ptr, texture, &frame, &position, angle, rotation_center, SDL_FLIP_NONE);
}
