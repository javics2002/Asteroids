#include "BulletsSystem.h"
#include "../components/Transform.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Image.h"
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
	case _m_ON_COLLISION_ASTEROID_BULLET:
		onCollision_BulletAsteroid(m.bullet_hit_asteroid.b);
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

		for (int i = 0u; i < bullets.size(); i++) 
		{
			mngr_->getComponent<Transform>(bullets[i])->move();
			disabledOnExit(bullets[i]);
		}
	}
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, double width, double height)
{
	auto e = mngr_->addEntity(ecs::_grp_BULLETS);

	//// add a Transform component, and initialize it with random size and position

	tr_ = mngr_->addComponent<Transform>(e);
	tr_->init(pos, vel, width, height, vel.angle(Vector2D(0.0f, -1.0f)));

	// add an Image Component
	mngr_->addComponent<Image>(e, &sdlutils().images().at("bullet"));
	//mngr_->addComponent<DisableOnExit>(e);

	sdlutils().soundEffects().at("fire").play(0, 1);
}

void BulletsSystem::onCollision_BulletAsteroid(ecs::Entity* b)
{
	mngr_->setAlive(b, false);
}

void BulletsSystem::onRoundOver()
{
	active_ = false;
}

void BulletsSystem::onRoundStart()
{
	active_ = true;
}

void BulletsSystem::disabledOnExit(ecs::Entity* b)
{
	auto& pos = tr_->pos_;

	// check borders
	if (pos.getX() + tr_->width_ < 0 || pos.getX() > sdlutils().width() ||
		pos.getY() + tr_->height_ < 0 || pos.getY() > sdlutils().height())
	{
		mngr_->setAlive(b, false);
	}
}
