#include "Projectile.h"



Projectile::Projectile()
{
	texture = nullptr;
	position = { 0,0 };
	velocity = { 0,0 };
	angle = 0.0;
}


Projectile::~Projectile()
{
	se_exp->open();
}

Projectile::Projectile(int _x, int _y, AnimatedTexture * _texture, SoundEffect* _se_explosion, Uint16 _velocity, double _angle, AnimatedTexture* _collision_texture)
{
	air_time = 0;
	position = { _x,_y };
	texture = _texture;
	collision_texture = _collision_texture;
	se_exp = _se_explosion;
	angle = -_angle*DEG2RAD_CONST;

	exists = true;
	collided = false;

	if (_velocity >= entry_vel_limit_max) 
	{
		_velocity = entry_vel_limit_max;
		velocity = { int(cos(angle)*double(_velocity*0.05)) , int(sin(-angle)*double(_velocity*0.05)) };
	}
	else if (_velocity <= entry_vel_limit_min)
	{
		_velocity = entry_vel_limit_min;
		velocity = { int(cos(angle)*double(_velocity*0.05) ) , int(sin(-angle)*double(_velocity*0.05) ) };
	}
	else
	{
		velocity = { int(cos(angle)*double(_velocity*0.05)) , int(sin(-angle)*double(_velocity*0.05)) };
	}
}

void Projectile::move()
{
	air_time++;
	if (position.x > GAME_WINDOW_WIDTH || position.x < 0) 
	{
		exists = false;
	}
	else if (position.y > 650) 
	{
		collided = true;
	}

	if (collided == false) 
	{
			velocity.y = velocity.y + GRAVITY_CONST;
			position.x += velocity.x;
			position.y += velocity.y;
			angle = atan2(velocity.y, velocity.x)*RAD2DEG_CONST;
	}
	else 
	{
		if (collision_texture->getFrames() == collision_texture->getPresentFrame()) //if collision animation has finished
		{
			exists = false;
		}
	}
	
}

void Projectile::render()
{
	if (collided == false) 
	{
		texture->render(position.x - (texture->getWidth() / 2), position.y - (texture->getHeight() / 2), angle);
	}
	else
	{
		se_exp->play();
		se_exp->close();
		collision_texture->render(position.x - (texture->getWidth() / 2), position.y - (texture->getHeight() / 2));
	}
}
