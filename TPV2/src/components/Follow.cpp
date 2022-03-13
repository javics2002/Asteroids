#include "Follow.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

Follow::Follow() {
	tr_ = nullptr;
}

void Follow::initComponent()
{
	tr_ = ent_->getComponent<Transform>();
	trFighter_ = mngr_->getHandler(ecs::_hdlr_CAZA)->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Follow::update()
{
    auto& currentVel = tr_->getVel();

    if (currentVel.angle(trFighter_->getPos() - tr_->getPos()) > 0) {
        currentVel = currentVel.rotate(1.0f);
    }
    else {
        currentVel = currentVel.rotate(-1.0f);
    }
}
