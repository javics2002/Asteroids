#include "FramedImage.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "../ecs/Manager.h"

FramedImage::FramedImage(Texture* tex, unsigned int width, unsigned int height,
    unsigned int framesX, unsigned int framesY, unsigned int frameLength) : tr_(nullptr), tex_(tex),
    frameWidth_(width), frameHeight_(height), framesX_(framesX), framesY_(framesY), frameLength_(frameLength) {
    deltatime_ = sdlutils().currRealTime();
}

void FramedImage::initComponent()
{
    deltatime_ = sdlutils().currRealTime();
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}
