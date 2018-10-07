#include "EnemyMenager.h"

bool EnemyMenager::cmp_enemies_by_posY(const Enemy * A, const Enemy * B)
{
	if (A->getPosY() > B->getPosY())
	{
		return true;
	}
	return false;
}

EnemyMenager::EnemyMenager(std::vector<Enemy*>* _ene_vec, BaseState* game_state)
{
	srand(int(time(NULL)));
	ene_vec = _ene_vec;
	main_renderer = game_state->main_renderer;
	frame_counter = game_state->frame_counter;
	present_level = 0;

	//Yellow goo
	ene1_mov = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_goo_move_60x60_8f.png", 8, 4, frame_counter));
	ene1_att = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_goo_attack_60x60_12f.png", 12, 2, frame_counter));
	ene1_dth = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_goo_death_90x60_8f.png", 8, 3, frame_counter));
	ene1_bar_tex = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/hpbar_32x6.png", 1, 1, frame_counter));
	ene1_bar = std::unique_ptr<ProgressBar>(new ProgressBar(ene1_bar_tex.get(), 2));
	ene1_se_hit = std::unique_ptr<SoundEffect>(new SoundEffect("res/audio/enemy_hit.wav"));
	ene1_se_dth = std::unique_ptr<SoundEffect>(new SoundEffect("res/audio/enemy_death.wav"));

	enemy1 = std::unique_ptr<Enemy>(new Enemy(
			1280,
			600,
			-2,
			2,
			10,
			ene1_mov.get(),
			ene1_att.get(),
			ene1_dth.get(),
			ene1_se_dth.get(),
			ene1_se_hit.get(),
			ene1_bar.get()
		));
	enemy_templates.push_back(enemy1.get());


	//Red goo
	ene2_mov = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_goo_move_60x60_8f.png", 8, 2, frame_counter));
	ene2_att = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_goo_attack_60x60_12f.png", 12, 1, frame_counter));
	ene2_dth = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_goo_death_90x60_8f.png", 8, 3, frame_counter));
	ene2_bar_tex = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/hpbar_32x6.png", 1, 1, frame_counter));
	ene2_bar = std::unique_ptr<ProgressBar>(new ProgressBar(ene1_bar_tex.get(), 1));

	ene2_mov->setColor(255, 0, 0);
	ene2_att->setColor(255, 0, 0);
	ene2_dth->setColor(255, 0, 0);

	enemy2 = std::unique_ptr<Enemy>(new Enemy(
		1280,
		600,
		-1,
		1,
		7,
		ene2_mov.get(),
		ene2_att.get(),
		ene2_dth.get(),
		ene1_se_dth.get(),
		ene1_se_hit.get(),
		ene2_bar.get()
	));
	enemy_templates.push_back(enemy2.get());

	//Giant blue goo
	ene3_mov = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_giant_goo_move_100x100_8f.png", 8, 6, frame_counter));
	ene3_att = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_giant_goo_attack_100x100_12f.png", 12, 4, frame_counter));
	ene3_dth = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_giant_goo_death_150x100_8f.png", 8, 3, frame_counter));
	ene3_bar_tex = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/hpbar_32x6.png", 1, 1, frame_counter));
	ene3_bar = std::unique_ptr<ProgressBar>(new ProgressBar(ene1_bar_tex.get(), 5));

	enemy3 = std::unique_ptr<Enemy>(new Enemy(
		1280,
		600,
		-4,
		5,
		30,
		ene3_mov.get(),
		ene3_att.get(),
		ene3_dth.get(),
		ene1_se_dth.get(),
		ene1_se_hit.get(),
		ene3_bar.get()
	));
	enemy_templates.push_back(enemy3.get());

	//Small pink goo
	ene4_mov = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_small_goo_move_45x45_8f.png", 8, 4, frame_counter));
	ene4_att = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_small_goo_attack_45x45_12f.png", 12, 2, frame_counter));
	ene4_dth = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_small_goo_death_67x45_8f.png", 8, 3, frame_counter));
	ene4_bar_tex = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/hpbar_32x6.png", 1, 1, frame_counter));
	ene4_bar = std::unique_ptr<ProgressBar>(new ProgressBar(ene1_bar_tex.get(), 1));

	enemy4 = std::unique_ptr<Enemy>(new Enemy(
		1280,
		600,
		-2,
		1,
		10,
		ene4_mov.get(),
		ene4_att.get(),
		ene4_dth.get(),
		ene1_se_dth.get(),
		ene1_se_hit.get(),
		ene4_bar.get()
	));
	enemy_templates.push_back(enemy4.get());

	//Small black goo
	ene5_mov = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_small_goo_move_45x45_8f.png", 8, 4, frame_counter));
	ene5_att = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_small_goo_attack_45x45_12f.png", 12, 1, frame_counter));
	ene5_dth = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_small_goo_death_67x45_8f.png", 8, 3, frame_counter));
	ene5_bar_tex = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/hpbar_32x6.png", 1, 1, frame_counter));
	ene5_bar = std::unique_ptr<ProgressBar>(new ProgressBar(ene1_bar_tex.get(), 1));

	ene5_mov->setColor(0, 255, 55);
	ene5_att->setColor(0, 255, 55);
	ene5_dth->setColor(0, 255, 55);

	enemy5 = std::unique_ptr<Enemy>(new Enemy(
		1280,
		600,
		1,
		1,
		6,
		ene5_mov.get(),
		ene5_att.get(),
		ene5_dth.get(),
		ene1_se_dth.get(),
		ene1_se_hit.get(),
		ene5_bar.get()
	));
	enemy_templates.push_back(enemy5.get());
	
	//Giant green goo
	ene6_mov = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_giant_goo_move_100x100_8f.png", 8, 5, frame_counter));
	ene6_att = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_giant_goo_attack_100x100_12f.png", 12, 4, frame_counter));
	ene6_dth = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/enemy_giant_goo_death_150x100_8f.png", 8, 3, frame_counter));
	ene6_bar_tex = std::unique_ptr<AnimatedTexture>(new AnimatedTexture(main_renderer, "res/enemies/hpbar_32x6.png", 1, 1, frame_counter));
	ene6_bar = std::unique_ptr<ProgressBar>(new ProgressBar(ene1_bar_tex.get(), 3));

	ene6_mov->setColor(0, 255, 0);
	ene6_att->setColor(0, 255, 0);
	ene6_dth->setColor(0, 255, 0);
	ene6_mov->setOpacity(155);
	ene6_att->setOpacity(155);
	ene6_dth->setOpacity(155);

	enemy6 = std::unique_ptr<Enemy>(new Enemy(
		1280,
		600,
		-2,
		3,
		35,
		ene6_mov.get(),
		ene6_att.get(),
		ene6_dth.get(),
		ene1_se_dth.get(),
		ene1_se_hit.get(),
		ene6_bar.get()
	));
	enemy_templates.push_back(enemy6.get());

}

EnemyMenager::~EnemyMenager()
{
	enemy_templates.clear();
}

void EnemyMenager::create(unsigned short enemy_id)
{
	Enemy* temp_buddy = new Enemy(*enemy_templates[enemy_id]);
	temp_buddy->setPosition(X_AXIS_MIN_SPAWN_VALUE + rand() % X_AXIS_SPAWN_OFFSET, Y_AXIS_MIN_SPAWN_VALUE + rand() % Y_AXIS_SPAWN_OFFSET);
	ene_vec->push_back(temp_buddy);
	std::sort(ene_vec->begin(), ene_vec->end(), cmp_enemies_by_posY);
}

void EnemyMenager::checkLevel()
{
	if(present_level == 9)
	{
		return;
	}
	else if (*frame_counter >= level[present_level + 1])
		present_level++;
}

void EnemyMenager::spawn()
{
	checkLevel();
	switch (present_level)
	{
	case 0:
		if (*frame_counter % 300 == 0) 
		{
			create(0);
		}
		break;
	case 1:
		if (*frame_counter % 200 == 0) 
		{
			create(0);
		}
		break;
	case 2:
		if (*frame_counter % 200 == 0) 
		{
			create(rand() % 2);
		}
		break;
	case 3:
		if (*frame_counter % 300 == 0)
		{
			create(rand() % 2);
		}
		if (*frame_counter % 600 == 0)
		{
			create(2);
		}
		break;
	case 4:
		if (*frame_counter % 100 == 0)
		{
			create(3);
		}
		break;
	case 5:
		if (*frame_counter % 200 == 0)
		{
			create(rand() % 2);
		}
		if (*frame_counter % 1100 == 0)
		{
			create(2);
		}
		if (*frame_counter % 400 == 0)
		{
			create(4);
		}
		break;
	case 6:
		if (*frame_counter % 100 == 0)
		{
			create(4);
		}
		break;
	case 7:
		if (*frame_counter % 300 == 0)
		{
			create(rand() % 2);
		}
		if (*frame_counter % 400 == 0)
		{
			create(5);
		}
		if (*frame_counter % 2000 == 0)
		{
			create(4);
			create(4);
			create(4);
			create(4);
		}
		break;
	case 8:
		if (*frame_counter % 150 == 0)
		{
			create(rand() % 5);
		}
		break;
	case 9:

		//game over
		break;
	}
}