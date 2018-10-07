#pragma once
#include "Texture.h"

// Class responsible for holding and rendering animated sequentions of images.
//
//Animations are based on one image with animation frames on it
//placed horisontaly next to each other.
//Rendered image is switched between frames based on animation_speed 
//which uses passed_frames_counter to count delay in frames.
class AnimatedTexture : public Texture
{
	int frames_num;
	int present_frame;
	SDL_Rect frame;
	int animation_speed = 1; //determines how many render frames are needed to change one frame of animation
	const unsigned int* passed_frames_counter; //pointer to counter incrementing after every passage of the game loop

public:

	AnimatedTexture() = delete;
	AnimatedTexture(SDL_Renderer* renderer, std::string _file_path, int _frames_num, int _animation_speed,const unsigned int* _passed_frames_counter);
	AnimatedTexture(AnimatedTexture &object);
	~AnimatedTexture();

	inline int getPresentFrame() { return present_frame; };
	inline int getFrames() { return frames_num; };
	inline const unsigned int* getFrameCounter() { return passed_frames_counter; };

	//sets hue & saturation of image
	void setColor(Uint8 r, Uint8 g, Uint8 b);

	//refresh image, keeps repeating animation
	void render(int x, int y, double angle = 0.0, SDL_Point* rotation_center = NULL, bool flip_horisontal = false , bool flip_vertical = false) override;

	//refresh image, goes through animation sequence once and stops on the last frame
	void renderOnce(int x, int y, double angle = 0.0, SDL_Point* rotation_center = NULL);

	//refresh image with selected frame of animation
	//numering of frames starts from 1
	void renderFrame(int x, int y, int frame, double angle = 0.0, SDL_Point* rotation_center = NULL);

	//render fragment of texture with frame = {w,h}
	void renderFragment(int x, int y, int w, int h, double angle = 0.0, SDL_Point* rotation_center = NULL);
};