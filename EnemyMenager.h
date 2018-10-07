#pragma once
#include "BaseState.h"
#include "Main.h"
#include "Enemy.h"
#include <memory>
#include <random>
#include <time.h>

//Class responsible for menaging enemy generation
//additionally allocates memory for enemy media and groups them into templates
class EnemyMenager
{
	unsigned short level[10] = //represented in frames needed to achieve (3600 = 60 sec)
	{0,3600,7200,10800,14400,18000,21600,25200,28800,36000};

	SDL_Renderer* main_renderer;
	unsigned int* frame_counter;
	std::vector<Enemy*>* ene_vec; //vector of active enemies
	const unsigned short X_AXIS_SPAWN_OFFSET = 60; //max offset of x-axis spawn position
	const unsigned short Y_AXIS_SPAWN_OFFSET = 100; //max offset of y-axis spawn position
	const unsigned short X_AXIS_MIN_SPAWN_VALUE = GAME_WINDOW_WIDTH + 30;
	const unsigned short Y_AXIS_MIN_SPAWN_VALUE = 520;
	unsigned short present_level;

	static bool cmp_enemies_by_posY(const Enemy * A, const Enemy * B);
	void create(unsigned short enemy_id); //generates enemy from enemy_templates using given id number
	void checkLevel(); //checks if there is need to increment level

	//ENEMY1 - yellow goo
	std::unique_ptr<Enemy> enemy1;
	std::unique_ptr<AnimatedTexture> ene1_mov;
	std::unique_ptr<AnimatedTexture> ene1_att;
	std::unique_ptr<AnimatedTexture> ene1_dth;
	std::unique_ptr<AnimatedTexture> ene1_bar_tex;
	std::unique_ptr<ProgressBar> ene1_bar;
	std::unique_ptr<SoundEffect> ene1_se_hit;
	std::unique_ptr<SoundEffect> ene1_se_dth;

	//ENEMY2 - red goo
	std::unique_ptr<Enemy> enemy2;
	std::unique_ptr<AnimatedTexture> ene2_mov;
	std::unique_ptr<AnimatedTexture> ene2_att;
	std::unique_ptr<AnimatedTexture> ene2_dth;
	std::unique_ptr<AnimatedTexture> ene2_bar_tex;
	std::unique_ptr<ProgressBar> ene2_bar;

	//ENEMY3 - giant blue goo
	std::unique_ptr<Enemy> enemy3;
	std::unique_ptr<AnimatedTexture> ene3_mov;
	std::unique_ptr<AnimatedTexture> ene3_att;
	std::unique_ptr<AnimatedTexture> ene3_dth;
	std::unique_ptr<AnimatedTexture> ene3_bar_tex;
	std::unique_ptr<ProgressBar> ene3_bar;

	//ENEMY4 - small pink goo
	std::unique_ptr<Enemy> enemy4;
	std::unique_ptr<AnimatedTexture> ene4_mov;
	std::unique_ptr<AnimatedTexture> ene4_att;
	std::unique_ptr<AnimatedTexture> ene4_dth;
	std::unique_ptr<AnimatedTexture> ene4_bar_tex;
	std::unique_ptr<ProgressBar> ene4_bar;

	//ENEMY5 - small black goo
	std::unique_ptr<Enemy> enemy5;
	std::unique_ptr<AnimatedTexture> ene5_mov;
	std::unique_ptr<AnimatedTexture> ene5_att;
	std::unique_ptr<AnimatedTexture> ene5_dth;
	std::unique_ptr<AnimatedTexture> ene5_bar_tex;
	std::unique_ptr<ProgressBar> ene5_bar;

	//ENEMY6 - giant black goo
	std::unique_ptr<Enemy> enemy6;
	std::unique_ptr<AnimatedTexture> ene6_mov;
	std::unique_ptr<AnimatedTexture> ene6_att;
	std::unique_ptr<AnimatedTexture> ene6_dth;
	std::unique_ptr<AnimatedTexture> ene6_bar_tex;
	std::unique_ptr<ProgressBar> ene6_bar;

	std::vector<Enemy*> enemy_templates; //vector of possible enemy types

public:
	EnemyMenager() = delete;
	EnemyMenager(std::vector<Enemy*>* _ene_vec, BaseState* game_state);
	~EnemyMenager();

	//main method of the class generating new monsters
	void spawn();
};