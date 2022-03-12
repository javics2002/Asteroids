#include "Follow.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"

Follow::Follow(Transform* trFighter) {
	trFighter_ = trFighter;
	tr_ = nullptr;
}

void Follow::initComponent()
{
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void Follow::update()
{
	auto& pos = tr_->getPos();
	auto& vel = tr_->getVel();
	auto& posCaza = trFighter_->getVel();

	vel.rotate(vel.angle(posCaza - pos) > 0 ? 1.0f : -1.0f);
}
