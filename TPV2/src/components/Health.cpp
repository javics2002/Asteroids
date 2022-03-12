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

	for (int i = 0; i < lives; i++)
	{
		SDL_Rect dest = build_sdlrect(20 + i * 30, 20, 25, 25);

		assert(tex_ != nullptr);
		tex_->render(dest);
	}
}

void Health::onAsteroidCollision()
{
	if (lives > 0)
		lives--;
}
