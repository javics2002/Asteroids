#include "FramedImage.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"

FramedImage::FramedImage(Texture* tex) : Image(tex)
{
}

void FramedImage::update()
{
	deltatime = sdlutils().currRealTime() - deltatime;

	if (deltatime > FRAME_LENGTH)
	{
		framePosition = Vector2D(x, y);
		scr = build_sdlrect(framePosition, tr_->getWidth() / 6,
			tr_->getHeight() / 5);

		x = x + 85 % 510;
		y = y + 100 % 500;
	}
	else 
		deltatime = sdlutils().currRealTime();
}

void FramedImage::render()
{
	SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getWidth(),
		tr_->getHeight());

	assert(tex_ != nullptr);
	tex_->render(scr, dest, tr_->getRot());
}
