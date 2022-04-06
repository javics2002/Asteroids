// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cstdint>
#include "../ecs/ecs.h"
#include "../utils/Vector2D.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_ROUND_START, //
	_m_ROUND_OVER, //
	_m_GAME_START, //
	_m_GAME_OVER, //
	_m_NEW_GAME, //
	_m_ON_COLLISION_FIGHTER_ASTEROID, // 
	_m_ASTEROIDS_EXTINCTION, //
	_m_ON_COLLISION_ASTEROID_BULLET, //
	_m_ON_COLLISION_BULLET_ASTEROID, //
	_m_SHOOT
};


struct Message 
{
	Message() 
	{
		this->id = 0;

		this->asteroid_extinction.winner = 0;
		this->bullet_hit_asteroid.a = nullptr;
		this->shoot_data.pos = { 0,0 };
		this->shoot_data.vel = { 0,0 };
		this->shoot_data.height = 0;
		this->shoot_data.width = 0;
	};
	Message(const Message& m)
	{
		this->id = m.id;

		this->asteroid_extinction = m.asteroid_extinction;
		this->bullet_hit_asteroid = m.bullet_hit_asteroid;
		this->shoot_data = m.shoot_data;
	}

	~Message() {};

	Message& operator=(const Message& m)
	{
		this->id = m.id;

		this->asteroid_extinction = m.asteroid_extinction;
		this->bullet_hit_asteroid = m.bullet_hit_asteroid;
		this->shoot_data = m.shoot_data;
	}

	msgId_type id;

	union 
	{
		struct 
		{
			uint8_t winner;
		} asteroid_extinction;

		struct 
		{
			ecs::Entity* a;
		} bullet_hit_asteroid;

		struct
		{
			Vector2D pos;
			Vector2D vel;
			double width;
			double height;
		} shoot_data;
	};
};
