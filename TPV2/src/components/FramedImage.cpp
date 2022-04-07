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

void FramedImage::update()
{
}

void FramedImage::render()
{
    if (deltatime_ + frameLength_ > sdlutils().currRealTime()) {
        deltatime_ = sdlutils().currRealTime();

        framePosition_.setY(framePosition_.getY() + 1);
        if (framePosition_.getY() > framesY_) {
            framePosition_.setY(0);

            framePosition_.setX(framePosition_.getX() + 1);
            if (framePosition_.getX() > framesX_) {
                framePosition_.setX(0);
            }
        }
        /*framePosition_.setX(framePosition_.getX() + 1 % framesX_);
        framePosition_.setY(framePosition_.getY() + 1 % framesY_);*/
    }

    SDL_Rect dest = build_sdlrect(tr_->pos_, tr_->width_, tr_->height_);

    // x, y
    // filas, columnas
    Vector2D framePos(framePosition_.getY() * 85, framePosition_.getX() * 100);

    SDL_Rect src = build_sdlrect(framePos, 85, 100);

    assert(tex_ != nullptr);
    tex_->render(src, dest, tr_->rot_);
}
