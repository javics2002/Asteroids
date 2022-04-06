#include "BulletsSystem.h"
#include "../components/Transform.h"
#include "../components/Gun.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Image.h"
#include "../components/DisableOnExit.h"

void BulletsSystem::receive(const Message& m)
{
}

void BulletsSystem::initSystem()
{
}

void BulletsSystem::update()
{
}

void BulletsSystem::shoot(Vector2D pos, Vector2D vel, float rot, double width, double height)
{
	if (sdlutils().currRealTime() - lastBulletTime > BULLET_CD)
	{
		lastBulletTime = sdlutils().currRealTime();

		auto e = mngr_->addEntity(ecs::_grp_BULLETS);

		// add a Transform component, and initialise it with random
		// size and position
		//
		auto bPos = pos + Vector2D(width / 2.0f, height / 2.0f) -
			Vector2D(0.0f, height / 2.0f + 5.0f + 12.0f).rotate(rot) - Vector2D(2.0f, 10.0f);
		auto bVel = Vector2D(0.0f, -1.0f).rotate(rot) * (vel.magnitude() + 5.0f);

		//What I think is happening: You now tell the manager to add a component to the entity in the paremeters, 
		//instead of telling the Entity to add a component to itself!
		auto tr = mngr_->addComponent<Transform>(e);
		tr->init(bPos, bVel, 5.0f, 20.0f, rot);

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
