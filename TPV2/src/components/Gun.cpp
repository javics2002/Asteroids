// This file is part of the course TPV2@UCM - Samir Genaim

#include "Gun.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "Image.h"
#include "Transform.h"
#include "DisableOnExit.h"

Gun::Gun() :
	tr_(nullptr) {
}

Gun::~Gun() {
}

void Gun::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void Gun::update() {

	auto& ihldr = ih();

	if (ihldr.keyDownEvent() && ihldr.isKeyDown(SDL_SCANCODE_S)) {
		if (sdlutils().currRealTime() - lastBulletTime > BULLET_CD)
		{
			lastBulletTime = sdlutils().currRealTime();

			auto e = mngr_->addEntity(ecs::_grp_BULLETS);

			// add a Transform component, and initialise it with random
			// size and position
			//
			auto bPos = tr_->pos_ + Vector2D(tr_->width_ / 2.0f, tr_->height_ / 2.0f) -
				Vector2D(0.0f, tr_->height_ / 2.0f + SPEED + 12.0f).rotate(tr_->rot_) - Vector2D(2.0f, 10.0f);
			auto bVel = Vector2D(0.0f, -1.0f).rotate(tr_->rot_) * (tr_->vel_.magnitude() + SPEED);

			auto tr = mngr_->addComponent<Transform>(e);
			tr->init(bPos, bVel, 5.0f, 20.0f, tr_->rot_);

			// add an Image Component
			mngr_->addComponent<Image>(e, &sdlutils().images().at("bullet"));
			mngr_->addComponent<DisableOnExit>(e);

			sdlutils().soundEffects().at("fire").play(0, 1);
		}
	}
}
