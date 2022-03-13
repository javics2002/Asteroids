#include "FramedImage.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

FramedImage::FramedImage(Texture* tex) : tr_(), tex_(tex) {
}

void FramedImage::initComponent()
{
    deltatime = sdlutils().currRealTime();
	tr_ = ent_->getComponent<Transform>();
	assert(tr_ != nullptr);
}

void FramedImage::update()
{
	/*deltatime = sdlutils().currRealTime() - deltatime;

	if (deltatime > FRAME_LENGTH)
	{
		framePosition = Vector2D(x, y);
		scr = build_sdlrect(framePosition, FRAME_WIDTH, FRAME_HEIGHT);

		x = (x + FRAME_WIDTH) % (FRAME_WIDTH * 6);
		y = (y + FRAME_HEIGHT) % (FRAME_HEIGHT * 5);
	}
	
	deltatime = sdlutils().currRealTime();*/
}

void FramedImage::render()
{
    if (deltatime + 50 > sdlutils().currRealTime()) {
        deltatime = sdlutils().currRealTime();

        framePosition.setY(framePosition.getY() + 1);
        if (framePosition.getY() > 5) {
            framePosition.setY(0);

            framePosition.setX(framePosition.getX() + 1);
            if (framePosition.getX() > 4) {
                framePosition.setX(0);
            }
        }
    }

    SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getWidth(),
        tr_->getHeight());

    // x, y
    // filas, columnas
    Vector2D framePos(framePosition.getY() * 85, framePosition.getX() * 100);

    SDL_Rect src = build_sdlrect(framePos, 85,
        100);


    assert(tex_ != nullptr);
    tex_->render(src, dest, tr_->getRot());
}
