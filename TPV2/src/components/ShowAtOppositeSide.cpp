#include "ShowAtOppositeSide.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../ecs/Manager.h"

ShowAtOppositeSide::ShowAtOppositeSide() : tr_() {
}

ShowAtOppositeSide::~ShowAtOppositeSide() {
}

void ShowAtOppositeSide::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void ShowAtOppositeSide::update() {
	auto& pos = tr_->pos_;

	// check left/right borders
	if (pos.getX() + tr_->width_ < 0) {
		pos.setX(sdlutils().width());
	}
	else if (pos.getX() > sdlutils().width()) {
		pos.setX(-tr_->width_);
	}

	// check upper/lower borders
	if (pos.getY() + tr_->height_ < 0) {
		pos.setY(sdlutils().height());
	}
	else if (pos.getY() > sdlutils().height()) {
		pos.setY(-tr_->height_);
	}
}
