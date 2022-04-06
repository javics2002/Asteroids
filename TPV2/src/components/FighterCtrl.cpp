// This file is part of the course TPV2@UCM - Samir Genaim

#include "FighterCtrl.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Image.h"
#include "Transform.h"

FighterCtrl::FighterCtrl() :
		tr_(nullptr) {
}

FighterCtrl::~FighterCtrl() {
}

void FighterCtrl::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void FighterCtrl::update() {

	auto &ihldr = ih();

	if (ihldr.keyDownEvent()) {

		auto &vel_ = tr_->vel_;
		auto rot = tr_->rot_;

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
			tr_->rot_ = (rot + 5.0f);

			// also rotate the Fighter so it looks in the same
			// direction where it moves
			//
			vel_ = vel_.rotate(5.0f);
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
			tr_->rot_ = (rot - 5.0f);

			// also rotate the Fighter so it looks in the same
			// direction where it moves
			//
			vel_ = vel_.rotate(-5.0f);
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // increase speed

			/*float speed = std::min(3.0f, vel_.magnitude() + 1.0f);*/

			Vector2D newVel = vel_ + Vector2D(0, -1).rotate(rot) * THRUST;

			if (newVel.magnitude() > SPEED_LIMIT)
				newVel = newVel.normalize()* SPEED_LIMIT;

			vel_ = newVel;

			sdlutils().soundEffects().at("thrust").play(0);
		}
	}
}
