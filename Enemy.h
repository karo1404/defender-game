#pragma once
#include <vector>
#include "AnimatedTexture.h"
#include "SoundEffect.h"
#include "ProgressBar.h"
#include <memory>

enum EnemyState {
	STATE_MOVE,
	STATE_ATTACK,
	STATE_DEAD
};

//Class responsible for handling enemy actions and behaviour
class Enemy
{
	SDL_Point position;//position of center of the entity
	int velocity; // horisontal speed of the entity, negative values are interpreted as 1/abs(n)

	AnimatedTexture* texture_move;
	AnimatedTexture* texture_attack;
	AnimatedTexture* texture_death;
	SoundEffect* se_death;
	SoundEffect* se_attack;
	ProgressBar* hp_bar;

	EnemyState state; //state of the entity
	bool exists; //tells if entity should be removed
	int health_points; //number of points needed to kill the entity
	int max_health_points;
	int attack_points;

	bool is_copy; //tells if object is a copy of existing one

public:
	Enemy() = delete;
	~Enemy();

	Enemy(  int _x, 
			int _y, 
			int _velocity, 
			int hp, 
			int ap,
			AnimatedTexture* _texture_move,
			AnimatedTexture* _texture_attack,
			AnimatedTexture* _texture_death,
			SoundEffect* _se_death,
			SoundEffect* _se_attack,
			ProgressBar* _hp_bar
			);

	Enemy(const Enemy & object);

	//calculate position and action for the next frame, needs structure_value for attack move
	void move(unsigned int* structure_value);

	//refresh entity position and animation frame on the screen
	void render();

	//method removing health points from selected field
	void attack(int &value);

	//remove one point of health
	void hit();
	//remove set value of health
	void hit(int value);

	inline int getWidth() { return texture_move->getWidth(); }
	inline int getHeight() { return texture_move->getHeight(); }
	inline int getPosX() const { return position.x; }
	inline int getPosY() const { return position.y; }
	inline EnemyState getState() { return state; }
	inline int getHealth() { return health_points; }
	inline int getMaxHealth() { return max_health_points; }

	inline void setState(EnemyState _state) { state = _state; };
	inline void setPosition(int _x, int _y) { position.x = _x; position.y = _y; };
	inline void setVelocity(int value) { velocity = value; };

	//returns exists value
	inline bool exist() { return exists; };

	//check if a point is colliding with entity
	//returns true on collision
	bool checkCollision(int _x, int _y);
	
};