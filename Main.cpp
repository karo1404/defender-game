#include "StateMenager.h"
//#include <vld.h> //- memory leaks detection

SDL_Point mouse_pos = { 0,0 };

//function enabling library components
bool initialize() 
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) 
	{ 
		std::cout << "Couldn't initialize SDL library! \nError code: " << SDL_GetError() << std::endl;
		return 1;
	}
	else 
	{
		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{
			std::cout << "Couldn't initialize IMG library! \nError code: " << SDL_GetError() << std::endl;
			return 1;
		}
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			std::cout << "Couldn't initialize Mixer library! \nError code: " << Mix_GetError() << std::endl;
			return 1;
		}
		if( TTF_Init() == -1 ) 
		{
			std::cout << "Couldn't initialize TTF library! \nError code: " << TTF_GetError() << std::endl;
			return 1;
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	//allocation of resources

	if (initialize() == 1)
	{ 
		std::cout << "Fatal error! Closing the program." << std::endl;
		return 1; 
	}
		Window* main_window = new Window(GAME_TITLE, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT);
		SDL_Renderer* main_renderer = main_window->createRenderer();
		SDL_Event e;
		unsigned int frame_sync_time;
		unsigned int frame_sync_time_difference;
		unsigned int frame_counter = 1;
		SDL_ShowCursor(SDL_DISABLE);

		std::unique_ptr<BaseState> game_state(new MenuState(main_window, main_renderer, &frame_counter, &e));

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//main game loop

	while (game_state != nullptr) 
	{
		//frame render sync
		frame_sync_time = SDL_GetTicks();

		//events
		game_state->handleEvents();

		//logic
		game_state->logic();

		//rendering
		game_state->render();

		//change game state
		changeState(game_state);

		//frame render sync
		frame_sync_time_difference = SDL_GetTicks() - frame_sync_time;
		if (frame_sync_time_difference < 16)
		{
			SDL_Delay(16 - frame_sync_time_difference);
		}
		frame_counter++;
	}

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	//deallocation of resources
	
		delete main_window;
		main_window = nullptr;

		SDL_DestroyRenderer(main_renderer);
		main_renderer = nullptr;

		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
		Mix_Quit();
	
	return 0;
}