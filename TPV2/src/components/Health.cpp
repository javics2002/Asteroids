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
		SDL_Rect dest = build_sdlrect(HEALTH_POS + i * HEALTH_SIZE, HEALTH_POS, HEALTH_SIZE, HEALTH_SIZE);

		assert(tex_ != nullptr);
		tex_->render(dest);
	}
}

void Health::onAsteroidCollision()
{
	if (lives > 0)
		lives--;
}
