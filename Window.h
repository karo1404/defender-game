#pragma once
#include <SDL.h>
#include <iostream>
#include <string>

//Class responsible for creating and storing window information.
class Window
{
	std::string window_name;
	int width;
	int height;
	SDL_Window* window = nullptr;
	SDL_Surface* screen_surface = nullptr;

	bool mouse_focus;
	bool keyboard_focus;
	bool fullscreen;
	bool minimized;

public:

	Window() = delete;
	Window(std::string win_name,int width, int height);
	~Window();

	//Creates renderer of the window area
	SDL_Renderer* createRenderer();

	//Getters and setters

	inline SDL_Window* getWindow() { return window; };
	inline int getWidth() { return width; };
	inline int getHeight() { return height; };
	inline bool isMouseFocus() { return mouse_focus; };
	inline bool isKeyboardFocus() { return keyboard_focus; };
	inline bool isFullscreen() { return fullscreen; };
	inline bool isMininized() { return minimized; };

	//Method which allows window to handle events 
	void handleEvent(SDL_Event &e);
};