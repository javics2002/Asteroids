#include "Health.h"
#include <cassert>

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Image.h"
#include "StarMotion.h"
#include "Transform.h"
#include "Deacceleration.h"

Deacceleration::Deacceleration() :
	tr_(nullptr) {
}

Deacceleration::~Deacceleration() {
}

void Deacceleration::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Deacceleration::update()
{
	auto& vel_ = tr_->getVel();

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
