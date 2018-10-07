#include "Player.h"


void Player::refreshShotPower()
{
	if (!*is_paused)
	{
		if (shot_possible == false)
		{
			shot_power = SDL_GetTicks() - shot_start;
		}
	}
}

Player::Player(int x, int y, AnimatedTexture * _body, AnimatedTexture * _arm, AnimatedTexture* _arrow, AnimatedTexture* _arrow_coll, SDL_Point _arm_base, SoundEffect * _se_shot, SoundEffect * _se_arrow_exp, std::vector<Projectile*>* _proj_list, bool* pause)
{
	position.x = x;
	position.y = y;

	arm_base = _arm_base;
	body = _body;
	arm = _arm;
	arm_base = _arm_base;
	se_shot = _se_shot;
	arm_angle = 0.0;
	proj_list = _proj_list;
	arrow = _arrow;
	arrow_collision = _arrow_coll;
	se_arrow_exp = _se_arrow_exp;
	is_paused = pause;

	position.w = body->getWidth();
	position.h = body->getHeight();
}

void Player::handleEvent(SDL_Event* ev, int &mouse_pos_x, int &mouse_pos_y)
{
	if (!*is_paused)
	{
		switch (ev->type)
		{
		case SDL_MOUSEBUTTONDOWN:
			if (shot_possible)
			{
				shot_possible = false;
				shot_start = SDL_GetTicks();
			}

			break;

		case SDL_MOUSEBUTTONUP:
			if (!shot_possible)
			{
				shot_power = SDL_GetTicks() - shot_start; //time of pressing shot button

				if (SDL_GetTicks() - shot_start >= shot_cooldown)
				{
					//action when arrow is relased
					se_shot->play();
					Projectile* new_proj = new Projectile(arm->getPosX(), arm->getPosY() + 30, arrow, se_arrow_exp, Uint16(double(shot_power)*0.4), arm_angle, arrow_collision);
					proj_list->push_back(new_proj);
				}
				shot_possible = true;
			}
			break;
		}
	}
}

void Player::render()
{
	if (*is_paused)
	{
		shot_start = SDL_GetTicks();
	}

	if (mouse_pos.x < position.x) 
	{
		body->render(position.x, position.y, 0.0, 0, true);
	}
	else
	{
		body->render(position.x, position.y);
	}


	//calculate arm angle in deg
	arm_angle = atan2(mouse_pos.y - arm_base.y - (position.y - 5), mouse_pos.x - (position.x+position.w/2))*RAD2DEG_CONST;
	if (mouse_pos.x < position.x)
	{
		if (!shot_possible) 
		{
			arm->renderOnce(position.x + 24, position.y - 5, arm_angle, &arm_base);
		}
		else
		{
			arm->renderFrame(position.x + 24, position.y - 5, 1, arm_angle, &arm_base);
		}
	}
	else
		if(!shot_possible)
		{
			arm->renderOnce(position.x + 16, position.y - 5, arm_angle, &arm_base);
		}
		else
		{
			arm->renderFrame(position.x + 16, position.y - 5, 1, arm_angle, &arm_base);
		}
}

Player::~Player()
{
}