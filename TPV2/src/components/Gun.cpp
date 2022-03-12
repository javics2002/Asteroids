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
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Gun::update() {

	auto& ihldr = ih();

	if (ihldr.keyDownEvent()) {

		auto& vel_ = tr_->getVel();
		auto rot = tr_->getRot();

		if (ihldr.isKeyDown(SDL_SCANCODE_S)) 
		{
			if (sdlutils().currRealTime() - lastBulletTime > BULLET_CD)
			{
				lastBulletTime = sdlutils().currRealTime();

				auto e = mngr_->addEntity(ecs::_grp_BULLETS);

				// add a Transform component, and initialise it with random
				// size and position
				//
				auto bPos = tr_->getPos() + Vector2D(tr_->getWidth() / 2.0f, tr_->getHeight() / 2.0f) -
					Vector2D(0.0f, tr_->getHeight() / 2.0f + 5.0f + 12.0f).rotate(tr_->getRot()) - Vector2D(2.0f, 10.0f);
				auto bVel = Vector2D(0.0f, -1.0f).rotate(tr_->getRot()) * (tr_->getVel().magnitude() + 5.0f);

				auto tr = e->addComponent<Transform>();
				tr->init(bPos, bVel, 5.0f, 20.0f, tr_->getRot());

				// add an Image Component
				e->addComponent<Image>(&sdlutils().images().at("bullet"));
				e->addComponent<DisableOnExit>();

				sdlutils().soundEffects().at("fire").play(0, 1);
			}
		}
	}
}
