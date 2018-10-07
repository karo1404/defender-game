#pragma once
#include "BaseState.h"
#include "Player.h"
#include "Music.h"
#include "Main.h"
#include "ProgressBar.h"
#include <vector>
#include <memory> 
#include <algorithm>
#include "EnemyMenager.h"
#include "Text.h"
#include "Button.h"

//Class of first stage state
class GameState : public BaseState
{
	//level
	std::unique_ptr<Texture> cursor;
	std::unique_ptr<Music> game_music;
	std::unique_ptr<AnimatedTexture> main_background;
	std::unique_ptr<AnimatedTexture> wall;
	TTF_Font* main_font;
	std::unique_ptr<Text> text;
	bool wall_was_damaged = false;
	bool enemies_on_the_field = true;
	bool pause = false;
	unsigned int structure;
	unsigned long score;
	unsigned int temp_counter = 0;

	SDL_Rect blackboard = { 0, 0, GAME_WINDOW_WIDTH, GAME_WINDOW_HEIGHT };
	unsigned int timestamp;
	bool timestamp_semaphore = true;
	std::unique_ptr<AnimatedTexture> but_exit_tex;
	std::unique_ptr<AnimatedTexture> but_retry_tex;
	std::unique_ptr<Button> but_exit;
	std::unique_ptr<Button> but_retry;

	//player
	std::unique_ptr<Player> player;
	std::unique_ptr<AnimatedTexture> char_body;
	std::unique_ptr<AnimatedTexture> char_arm;
	std::unique_ptr<SoundEffect> char_shot;
	std::unique_ptr<SoundEffect> se_arrow_explosion;

	//bars
	std::unique_ptr<AnimatedTexture> cd_bar;
	std::unique_ptr<AnimatedTexture> pow_bar;
	std::unique_ptr<AnimatedTexture> struct_bar;
	std::unique_ptr<AnimatedTexture> struct_bar_frame;
	std::unique_ptr<ProgressBar> bar_cooldown;
	std::unique_ptr<ProgressBar> bar_power;
	std::unique_ptr<ProgressBar> bar_structure;

	//projectiles
	std::unique_ptr<AnimatedTexture> proj_arr;
	std::unique_ptr<AnimatedTexture> proj_arr_coll;
	std::vector<Projectile*> proj_vec; //vector of mid-air projectiles

	//enemies
	std::vector<Enemy*> ene_vec; //vector of active enemies
	std::unique_ptr<EnemyMenager> enemy_menager;

public:
	GameState() = delete;
	~GameState();
	GameState(Window* _window, SDL_Renderer* _renderer, unsigned int* frame_counter, SDL_Event* _e);

	void handleEvents();

	void logic();

	void render();

};

