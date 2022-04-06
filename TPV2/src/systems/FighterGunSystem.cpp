#include "FighterGunSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../game/ecs_defs.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/DisableOnExit.h"
#include "../systems/BulletsSystem.h"

void FighterGunSystem::receive(const Message& m)
{
	switch (m.id)
	{
		case _m_UPDATE:
			update();
			break;
		case _m_OVER:
			onRoundOver();
			break;
		case _m_START:
			onRoundStart();
			break;
		default:
			break;
	}
}

void FighterGunSystem::initSystem()
{
}

void FighterGunSystem::update()
{
	if (active_)
	{
		auto& ihldr = ih();

		if (ihldr.keyDownEvent()) 
		{

			//auto& vel_ = tr_->getVel();
			//auto rot = tr_->getRot();

			if (ihldr.isKeyDown(SDL_SCANCODE_S))
			{
				if (sdlutils().currRealTime() - lastBulletTime > BULLET_CD)
				{
					lastBulletTime = sdlutils().currRealTime();

					Message m;
					m.id = _m_SHOOT;
					//m.shoot_data.e = {};
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
