#include "Health.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

Health::Health() :
tex_() {
}

Health::Health(Texture* tex) :
    tex_(tex) {
}

Health::~Health() {
}

void Health::initComponent() {

}

void Health::render() {

	//SDL_Rect dest = build_sdlrect(new Vector2D(0, 0), (float)1,
	//	(float)0);

	Texture scoreTex(sdlutils().renderer(), std::to_string(lives),
		sdlutils().fonts().at("ARIAL24"), build_sdlcolor(0x444444ff));

	SDL_Rect dest = build_sdlrect( //
		(sdlutils().width() - scoreTex.width()) / 2.0f, //
		10.0f, //
		scoreTex.width(), //
		scoreTex.height());

	scoreTex.render(dest);

	assert(tex_ != nullptr);
	//tex_->render(dest, tr_->getRot());

}

void Health::onAsteroidCollision()
{
	if (lives > 0)
		lives--;
}
