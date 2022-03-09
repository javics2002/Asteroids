#include "DisableOnExit.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

DisableOnExit::DisableOnExit()
{
}

DisableOnExit::~DisableOnExit()
{
}

void DisableOnExit::initComponent()
{
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void DisableOnExit::update()
{
	auto& pos = tr_->getPos();

	// check borders
	if (pos.getX() + tr_->getWidth() < 0 || pos.getX() > sdlutils().width() || 
		pos.getY() + tr_->getHeight() < 0 || pos.getY() > sdlutils().height()) {
		ent_->setAlive(false);
	}
}
