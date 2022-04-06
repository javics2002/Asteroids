// This file is part of the course TPV2@UCM - Samir Genaim
#include "StopOnBorders.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../ecs/Manager.h"

StopOnBorders::StopOnBorders() :
		tr_() {
}

StopOnBorders::~StopOnBorders() {
}

void StopOnBorders::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void StopOnBorders::update() {
	auto &pos = tr_->pos_;
	auto &vel = tr_->vel_;

	// check left/right borders
	if (pos.getX() < 0) {
		pos.setX(0.0f);
		vel.set(0.0f, 0.0f);
	} else if (pos.getX() + tr_->width_ > sdlutils().width()) {
		pos.setX(sdlutils().width() - tr_->width_);
		vel.set(0.0f, 0.0f);
	}

	// check upper/lower borders
	if (pos.getY() < 0) {
		pos.setY(0.0f);
		vel.set(0.0f, 0.0f);
	} else if (pos.getY() + tr_->height_ > sdlutils().height()) {
		pos.setY(sdlutils().height() - tr_->height_);
		vel.set(0.0f, 0.0f);
	}
}
