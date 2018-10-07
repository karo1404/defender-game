#include "Enemy.h"

Enemy::~Enemy()
{
	if (is_copy) 
	{
		delete this->texture_move;
		delete this->texture_attack;
		delete this->texture_death;
		delete this->hp_bar;
		delete this->se_death;
		delete this->se_attack;
	}
}

Enemy::Enemy(int _x, int _y, int _velocity, int hp, int ap, AnimatedTexture * _texture_move, AnimatedTexture * _texture_attack, AnimatedTexture * _texture_death, SoundEffect * _se_death, SoundEffect * _se_attack, ProgressBar* _hp_bar)
{
	velocity = _velocity;
	health_points = hp;
	attack_points = ap;
	texture_move = _texture_move;
	texture_attack = _texture_attack;
	texture_death = _texture_death;
	se_death = _se_death;
	se_attack = _se_attack;
	hp_bar = _hp_bar;
	exists = true;
	max_health_points = health_points;
	hp_bar->setValue(max_health_points);
	position.x = _x + int(0.5*texture_move->getWidth());
	position.y = _y + int(0.5*texture_move->getHeight());
	is_copy = false;
}

Enemy::Enemy(const Enemy & object)
{
	is_copy = true;

	position.x = object.position.x;
	position.y = object.position.y;
	velocity = object.velocity;
	health_points = object.health_points;
	attack_points = object.attack_points;
	max_health_points = object.max_health_points;
	exists = object.exists;
	state = object.state;
	
	hp_bar = new ProgressBar(*object.hp_bar);
	texture_move = new AnimatedTexture(*object.texture_move);
	texture_attack = new AnimatedTexture(*object.texture_attack);
	texture_death = new AnimatedTexture(*object.texture_death);
	se_death = new SoundEffect(*object.se_death);
	se_attack = new SoundEffect(*object.se_attack);
}

void Enemy::move(unsigned int* structure_value)
{
	switch (state)
	{
	case STATE_MOVE:
		{
			if (velocity < 0)
			{
				if (*(texture_move->getFrameCounter()) % abs(velocity) == 0)
				{
					position.x--;
				}
			}
			else
			{
				position.x -= velocity;
			}
			break;
		}
	case STATE_DEAD:
		{
			if (texture_death->getFrames() == texture_death->getPresentFrame()) //if death animation has finished
			{
				exists = false;
			}
			break;
		}
	case STATE_ATTACK:
		{
			if (texture_attack->getFrames() == texture_attack->getPresentFrame()) //if attack animation has finished
			{
				if (*structure_value <= unsigned(attack_points)) {
					*structure_value = 0;
				}
				else 
				{
					*structure_value -= attack_points;
				}
			}
			break;
		}
	}
}

void Enemy::render()
{
	switch (state)
	{
	case STATE_MOVE:
		texture_move->render(position.x - (texture_move->getWidth() / 2), position.y - (texture_move->getHeight() / 2));
		if (float(health_points) <= 0.5*float(max_health_points))
		{
			hp_bar->setColor(120, 0, 0);
		}
		else 
		{
			hp_bar->setColor(0, 120, 0);
		}
		hp_bar->render(position.x - int(hp_bar->getMaxWidth() / 2), position.y + int(texture_move->getHeight() / 2));
		break;
	case STATE_ATTACK:
		texture_attack->render(position.x - (texture_attack->getWidth() / 2), position.y - (texture_attack->getHeight() / 2));
		
		se_attack->play();
		se_attack->close();
		if (texture_attack->getFrames() == texture_attack->getPresentFrame()) 
		{
			se_attack->open();
		}

		if (float(health_points) <= float(max_health_points) / 2)
		{
			hp_bar->setColor(120, 0, 0);
		}
		else
		{
			hp_bar->setColor(0, 120, 0);
		}
		hp_bar->render(position.x - int(hp_bar->getMaxWidth() / 2), position.y + int(texture_move->getHeight() / 2));
		break;
	case STATE_DEAD:
		se_death->play();
		se_death->close();
		texture_death->renderOnce(position.x - (texture_death->getWidth() / 2), position.y - (texture_death->getHeight() / 2));
		break;
	}
}

void Enemy::attack(int & value)
{
	value -= attack_points;
}

void Enemy::hit()
{
	health_points--;
	hp_bar->setValue(health_points);
	if (health_points <= 0) 
	{
		state = STATE_DEAD;
	}

}

void Enemy::hit(int value)
{
	health_points -= value;
	if (health_points < 0) { health_points = 0; }
	hp_bar->setValue(health_points);
	if (health_points <= 0)
	{
		state = STATE_DEAD;
	}
}

bool Enemy::checkCollision(int _x, int _y)
{
	if (_x < getPosX() - getWidth() / 2 || _x > getPosX() + getWidth() / 2)
	{
		return false;
	}
	else if (_y < getPosY() - getWidth() / 2 || _y > getPosY() + getHeight() / 2)
	{
		return false;
	}
	return true;
}