#pragma once
#include "AnimatedTexture.h"
#include "Main.h"
#include "SoundEffect.h"

//Class responsible for handling projectiles
class Projectile
{
	Uint16 entry_vel_limit_max = 650;
	Uint16 entry_vel_limit_min = 200;
	AnimatedTexture* texture;
	AnimatedTexture* collision_texture;
	SoundEffect* se_exp;

	SDL_Point position, collision_position_front, collision_position_back; //position of center of the projectile + front and back positions
	SDL_Point velocity; //x,y offset in position every frame
	double angle;
	bool exists; //tells if projectile is out of game area and should be removed
	bool collided; //tells if projectile collided with an object
	unsigned int air_time;



public:
	Projectile();
	~Projectile();

	Projectile(int _x, int _y, AnimatedTexture* _texture, SoundEffect* _se_explosion, Uint16 _velocity = 0, double _angle = 0, AnimatedTexture* _collision_texture = nullptr);

	//calculate position for the next frame
	void move();

	//refresh projectile position on the screen
	void render();

	//returns exists value
	inline bool exist() { return exists; };
	//returns collided value
	inline bool collide() { return collided; };
	inline void collide(bool value) { collided = value; };

	//getters

	inline int getPosX() { return position.x; };
	inline int getPosY() { return position.y; };
	inline int getWidth() { return texture->getWidth(); };
	inline int getHeight() { return texture->getHeight(); };
	inline int getAirTime() { return air_time; };
};