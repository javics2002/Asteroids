#include "DisableOnExit.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "Transform.h"
#include "../ecs/Manager.h"

using namespace std;

DisableOnExit::DisableOnExit() : tr_(nullptr)
{
}

DisableOnExit::~DisableOnExit()
{
}

void DisableOnExit::initComponent()
{
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void DisableOnExit::update()
{
	auto& pos = tr_->pos_;

	// check borders
	if (pos.getX() + tr_->width_ < 0 || pos.getX() > sdlutils().width() ||
		pos.getY() + tr_->height_ < 0 || pos.getY() > sdlutils().height())
	{
		mngr_->setAlive(ent_, false);
	}
}
