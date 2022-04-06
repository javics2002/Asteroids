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
	tr_ = mngr_->getComponent<Transform>(ent_);
	trFighter_ = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::_hdlr_CAZA));
	assert(tr_ != nullptr);
}

void Follow::update()
{
    auto& currentVel = tr_->vel_;

    if (currentVel.angle(trFighter_->pos_ - tr_->pos_) > 0) {
        currentVel = currentVel.rotate(1.0f);
    }
    else {
        currentVel = currentVel.rotate(-1.0f);
    }
}
