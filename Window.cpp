#include "Window.h"


Window::Window(std::string _window_name, int _width, int _height)
{
	//initialize class fields
	std::string WindowCreateError = "Couldn't create window!";
	window_name = _window_name;
	width = _width;
	height = _height;
	mouse_focus = true;
	keyboard_focus = true;
	fullscreen = false;
	minimized = false;

	//generate window
	try 
	{
		window = SDL_CreateWindow(window_name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
		if (window == nullptr)
		{
			throw(WindowCreateError);
		}

	}
	catch (std::string err)
	{
		std::cout << err << " Error code:\n" << SDL_GetError() << std::endl;
	}
}

Window::~Window()
{
	SDL_DestroyWindow(window);
	window = nullptr;
}

SDL_Renderer * Window::createRenderer()
{
		return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
}

void Window::handleEvent(SDL_Event & e)
{
	//query of window status changes
	if (e.type == SDL_WINDOWEVENT) 
	{
		switch (e.window.event) 
		{
		case SDL_WINDOWEVENT_LEAVE:
			mouse_focus = false;
			break;

		case SDL_WINDOWEVENT_ENTER:
			mouse_focus = true;
			break;

		case SDL_WINDOWEVENT_FOCUS_GAINED: 
			keyboard_focus = true;
			break; 

		case SDL_WINDOWEVENT_FOCUS_LOST: 
			keyboard_focus = false;
			break;

		case SDL_WINDOWEVENT_MINIMIZED: 
			minimized = true; 
			break; 
		
		case SDL_WINDOWEVENT_MAXIMIZED: 
			minimized = false; 
			fullscreen = true;
			break; 
		
		case SDL_WINDOWEVENT_RESTORED: 
			minimized = false; 
			break;
		}
	}
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_f)
	{
		if (!fullscreen)
		{
			SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
			fullscreen = true;
		}
		else
		{
			SDL_SetWindowFullscreen(window, 0);
			fullscreen = false;
		}
	}
}
