#include "Asteroid.h"

#include <cassert>

#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Generations.h"
#include "../components/Follow.h"

Asteroid::Asteroid() : Entity(_grp_ASTEROIDS)
{
	addComponet<Transform>();
	addComponet<FramedImage>();
	addComponet<ShowAtOppositeSide>();
	addComponet<Generations>();
	addComponet<Follow>();
}

Asteroid::~Asteroid()
{
}
