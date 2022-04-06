#include "FighterGunSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../game/ecs_defs.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/DisableOnExit.h"
#include "../systems/BulletsSystem.h"
#include "../sdlutils/InputHandler.h"

void FighterGunSystem::receive(const Message& m)
{
	switch (m.id)
	{
		case _m_ROUND_OVER:
			onRoundOver();
			break;
		case _m_ROUND_START:
			onRoundStart();
			break;
		default:
			break;
	}
}

void FighterGunSystem::initSystem()
{
	active_ = false;
}

void FighterGunSystem::update()
{
	if (active_)
	{
		auto& ihldr = ih();

		if (ihldr.keyDownEvent()) 
		{
			auto ent_ = mngr_->getHandler(ecs::_hdlr_CAZA);

			Vector2D vel = mngr_->getComponent<Transform>(ent_)->vel_;
			Vector2D pos = mngr_->getComponent<Transform>(ent_)->pos_;
			

			if (ihldr.isKeyDown(SDL_SCANCODE_S))
			{
				if (sdlutils().currRealTime() - lastBulletTime > BULLET_CD)
				{
					lastBulletTime = sdlutils().currRealTime();

					Message m;
					m.id = _m_SHOOT;
					m.shoot_data.vel = vel;
					m.shoot_data.pos = pos;
					m.shoot_data.width = BULLET_W;
					m.shoot_data.height = BULLET_H;
					mngr_->getSystem<BulletsSystem>()->receive(m);
				}
			}
		}
	}
}

void FighterGunSystem::onRoundOver()
{
	active_ = false;
}

void FighterGunSystem::onRoundStart()
{
	active_ = true;
}
