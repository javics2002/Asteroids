#include "ShowAtOppositeSide.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

ShowAtOppositeSide::ShowAtOppositeSide() : tr_() {
}

ShowAtOppositeSide::~ShowAtOppositeSide() {
}

void ShowAtOppositeSide::initComponent() {
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void ShowAtOppositeSide::update() {
	auto& pos = tr_->getPos();
	auto& vel = tr_->getVel();

	// check left/right borders
	if (pos.getX() + tr_->getWidth() < 0) {
		pos.setX(sdlutils().width());
	}
	else if (pos.getX() > sdlutils().width()) {
		pos.setX(-tr_->getWidth());
	}

	// check upper/lower borders
	if (pos.getY() + tr_->getHeight() < 0) {
		pos.setY(sdlutils().height());
	}
	else if (pos.getY() > sdlutils().height()) {
		pos.setY(-tr_->getHeight());
	}
}
