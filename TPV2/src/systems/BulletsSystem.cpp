#include "BulletsSystem.h"
#include "../components/Transform.h"
#include "../components/Gun.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Image.h"
#include "../components/DisableOnExit.h"
#include "../utils/Vector2D.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"

void BulletsSystem::receive(const Message& m)
{
	switch (m.id)
	{
	case _m_ROUND_OVER:
		onRoundOver();
		break;
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_SHOOT:
		shoot(m.shoot_data.pos, m.shoot_data.vel, m.shoot_data.width, m.shoot_data.height);
		break;
	case _m_ON_COLLISION_BULLET_ASTEROID:
		onCollision_BulletAsteroid(m.bullet_hit_asteroid.a);
		break;
	default:
		break;
	}
}

void BulletsSystem::initSystem()
{
	active_ = false;
}

void BulletsSystem::update()
{
	if (active_)
	{
		auto& bullets = mngr_->getEntities(ecs::_grp_BULLETS);

		for (int i = 0u; i < bullets.size(); i++) {
			mngr_->getComponent<Transform>(bullets[i])->move();
		}
	}
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{

	{
		auto e = mngr_->addEntity(ecs::_grp_BULLETS);

		// add a Transform component, and initialise it with random size and position
		//
		auto bPos = pos + Vector2D(width / 2.0f, height / 2.0f) -
			Vector2D(0.0f, height / 2.0f + 5.0f + 12.0f).rotate(vel.angle(Vector2D(0.0f, -1.0f)));
		auto bVel = Vector2D(0.0f, -1.0f).rotate(vel.angle(Vector2D(0.0f, -1.0f)) * (vel.magnitude() + 5.0f));

		auto tr = mngr_->addComponent<Transform>(e);
		tr->init(bPos, bVel, 5.0f, 20.0f, vel.angle(Vector2D(0.0f, -1.0f)));

		// add an Image Component
		mngr_->addComponent<Image>(e, &sdlutils().images().at("bullet"));
		mngr_->addComponent<DisableOnExit>(e);

		sdlutils().soundEffects().at("fire").play(0, 1);
	}
}

void BulletsSystem::onCollision_BulletAsteroid(ecs::Entity* b)
{
	mngr_->setAlive(b, false);
}

void BulletsSystem::onRoundOver()
{
}

void BulletsSystem::onRoundStart()
{
}
