// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <cstdint>
#include "../ecs/ecs.h"

using msgId_type = uint8_t;
enum msgId : msgId_type {
	_m_ROUND_START, //
	_m_ROUND_OVER, //
	_m_GAME_START, //
	_m_GAME_OVER, //
	_m_NEW_GAME, //
	_m_ON_COLLISION_FIGHTER_ASTEROID, // 
	_m_ASTEROIDS_EXTINCTION, //
	_m_ON_COLLISION_ASTEROID_BULLET
};


struct Message {
	msgId_type id;

	union {

		struct {
			uint8_t winner;
		} asteroid_extinction;

		struct {
			ecs::Entity* a;
		} bullet_hit_asteroid;

	};
};
