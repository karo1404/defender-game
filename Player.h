#pragma once
#include "AnimatedTexture.h"
#include "Projectile.h"
#include "SoundEffect.h"
#include "Main.h"
#include <vector>

extern SDL_Point mouse_pos;

//Class responsible for player character and input interface
class Player
{
	//sub-classes

	SDL_Rect position;
	AnimatedTexture* body;
	AnimatedTexture* arm;
	SDL_Point arm_base; //pivot point of character arm
	AnimatedTexture* arrow;
	AnimatedTexture* arrow_collision;
	SoundEffect* se_shot;
	SoundEffect* se_arrow_exp;
	std::vector<Projectile*>* proj_list;
	double arm_angle;
	bool* is_paused;

	//shooting system variables

	unsigned int shot_cooldown = 500; //shortest time in ms between shots 
	bool shot_possible = true; 
	unsigned int shot_start = 0; //timestamp of player pressing shot key
	unsigned int shot_power = 0; //time of arrow pulling
	Uint16 max_power = 1500; //limit of shot power


public:

	inline unsigned int getShotStart() { return shot_start; };
	inline unsigned int getShotCooldown() { return shot_cooldown; };
	inline void setShotCooldown(unsigned int value) { shot_cooldown = value; };
	inline Uint16 getMaxPower() { return max_power; };
	inline void setMaxPower(Uint16 value) { max_power = value; };
	inline unsigned int getShotPower() { return shot_power; };
	inline double getArmAngle() { return arm_angle; };

	void refreshShotPower();

	Player() = delete;
	Player(	int x, 
			int y,
			AnimatedTexture* _body,
			AnimatedTexture* _arm,
			AnimatedTexture* _arrow,
			AnimatedTexture* _arrow_coll,
			SDL_Point _arm_base,
			SoundEffect* _se_shot,
			SoundEffect * _se_arrow_exp,
			std::vector<Projectile*>* _proj_list,
			bool* pause
			);

	void handleEvent(SDL_Event* ev, int &mouse_pos_x, int &mouse_pos_y);

	void render();

	~Player();
};

