#include "Music.h"


Music::Music(std::string _file_path)
{
	std::string MusicLoadError = "Couldn't load music file!";
	try
	{
		audio = Mix_LoadMUS(_file_path.c_str());
		if (audio == nullptr)
		{
			throw(MusicLoadError);
		}
	}
	catch (std::string err) 
	{
		std::cout << err << " Error code:\n" << Mix_GetError() << std::endl;
	}
}

Music::~Music()
{
	Mix_FreeMusic(audio);
	audio = nullptr;
}

void Music::play()
{
	Mix_PlayMusic(audio, -1); 
}

void Music::playLoop(int loops_num)
{
	Mix_PlayMusic(audio, loops_num - 1);
}

void Music::stop()
{
	Mix_HaltMusic();
}

void Music::playFadeIn(int duration, int loops_num)
{
	Mix_FadeInMusic(audio, loops_num - 1, duration);
}

void Music::stopFadeOut(int duration)
{
	Mix_FadeOutMusic(duration); 
}

