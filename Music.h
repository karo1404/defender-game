#pragma once
#include <SDL_mixer.h>
#include <string>
#include <iostream>

//Class responsible for playing and stopping loaded music file 
class Music
{
	Mix_Music* audio;

public:

	Music() = delete;
	Music(std::string _file_path);
	~Music();

	//plays the music, infinitely looped
	void play();

	//plays music, loops_num determines number of playbacks before stopping
	void playLoop(int loops_num);

	//stops the music, starts from the beginning when resumed
	void stop();

	//plays the music starting with Fade In effect
	//duration - duration of the effect [ms]
	//loops_num - number of playbacks before stopping, 0 for infinite loop
	void playFadeIn(int duration, int loops_num);

	//stops the music with Fade Out effect
	//starts from the beginning when resumed
	//duration - duration of the effect [ms]
	void stopFadeOut(int duration);

};

