#include "SoundEffect.h"


SoundEffect::SoundEffect(std::string _file_path)
{
	semaphore = true;
	std::string SELoadError = "Couldn't load sound effect file!";
	try
	{
		audio = Mix_LoadWAV(_file_path.c_str());
		if (audio == nullptr) 
		{
			throw(SELoadError);
		}
	}
	catch (std::string err)
	{
		std::cout << err << " Error code:\n" << Mix_GetError() << std::endl;
	}
}

SoundEffect::SoundEffect(SoundEffect & object)
{
	audio = object.audio;
	semaphore = true;
}

SoundEffect::~SoundEffect()
{
	//Mix_FreeChunk(audio);
	audio = nullptr;
}

void SoundEffect::stop(int fadeout)
{
	if (fadeout == 0)
	{
		Mix_HaltChannel(-1); 
	}
	else
	{
		Mix_FadeOutChannel(-1, fadeout);
	}
}
