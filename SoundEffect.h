#pragma once
#include <SDL_mixer.h>
#include <string>
#include <iostream>

//Class responsible for playing loaded sound effect in wav format
class SoundEffect
{
	Mix_Chunk* audio;
	bool semaphore; //allows for playback of the sound
public:

	SoundEffect() = delete;
	SoundEffect(std::string _file_path);
	SoundEffect(SoundEffect& object);
	~SoundEffect();

	inline void open() { semaphore = true; };
	inline void close() { semaphore = false; };

	//plays the sound
	inline void play() { if (semaphore) { Mix_PlayChannel(-1, audio, 0); } };

	//plays looped sound, -1 for infinite looping
	inline void playLoop(int loops_num) {if (semaphore) { Mix_PlayChannel(-1, audio, loops_num); } };

	//stops playing sound with optional fade-out effect in ms
	void stop(int fadeout = 0);

};