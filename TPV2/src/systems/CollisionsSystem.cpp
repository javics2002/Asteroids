// This file is part of the course TPV2@UCM - Samir Genaim

#include "CollisionsSystem.h"

#include "../components/Transform.h"
#include "../ecs/messages.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Collisions.h"
#include "GameCtrlSystem.h"

CollisionsSystem::CollisionsSystem() :
	active_(false) {
}

CollisionsSystem::~CollisionsSystem() {
}

void CollisionsSystem::initSystem() {
	active_ = true;
}

void CollisionsSystem::receive(const Message& m) {
	switch (m.id) {
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_ROUND_OVER:
		onRoundOver();
		break;
	default:
		break;
	}
}

void CollisionsSystem::update() {

	if (!active_)
		return;

	// the fighter Transform
	//
	auto fTR = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::_hdlr_FIGHTER));

	// For safety, we traverse with a normal loop until the current size. In this
	// particular case we could use a for-each loop since the list is not
	// modified.

	auto& asteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);
	auto n = asteroids.size();
	for (auto i = 0u; i < n; i++) {
		auto asteroidEntity = asteroids[i];
		if (mngr_->isAlive(asteroidEntity)) { // if the star is active (it might have died in this frame)

			// the asteroid Transform
			//
			auto eTR = mngr_->getComponent<Transform>(asteroidEntity);

			// check if fighter collides with the asteroid
			if (Collisions::collides(fTR->pos_, fTR->width_,
				fTR->height_, //
				eTR->pos_, eTR->width_, eTR->height_)) {

				Message m;
				m.id = _m_ON_COLLISION_FIGHTER_ASTEROID;
				mngr_->send(m);

				return;
			}

			// recorro el grupo de balas
			auto& bullets = mngr_->getEntities(ecs::_grp_BULLETS);
			for (auto i = 0u; i < bullets.size(); i++) {
				auto bulletEntity = bullets[i];

				if (mngr_->isAlive(bulletEntity)) {
					if (Collisions::collides(mngr_->getComponent<Transform>(bulletEntity)->pos_, mngr_->getComponent<Transform>(bulletEntity)->width_,
						mngr_->getComponent<Transform>(bulletEntity)->height_, //
						eTR->pos_, eTR->width_, eTR->height_)) {

						Message m;
						m.id = _m_ON_COLLISION_ASTEROID_BULLET;
						m.bullet_hit_asteroid.a = asteroidEntity;
						mngr_->send(m);


					}
				}
			}
		}
	}
}

void CollisionsSystem::onRoundOver()
{
	active_ = false;
}

void CollisionsSystem::onRoundStart()
{
	active_ = true;
}