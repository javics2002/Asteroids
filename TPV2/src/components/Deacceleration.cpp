#include "Health.h"
#include <cassert>

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Image.h"
#include "Transform.h"
#include "Deacceleration.h"

Deacceleration::Deacceleration() :
	tr_(nullptr) {
}

Deacceleration::~Deacceleration() {
}

void Deacceleration::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void Deacceleration::update()
{
	auto& vel_ = tr_->vel_;

	if (vel_.magnitude() < 0.05)
	{
		vel_.set(0, 0);
	}
	else
	{
		vel_.setX(vel_.getX() * DEACC);
		vel_.setY(vel_.getY() * DEACC);
	}
}
