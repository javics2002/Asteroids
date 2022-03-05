#include "Asteroid.h"

#include <cassert>

#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/FramedImage.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Generations.h"
#include "../components/Follow.h"

Asteroid::Asteroid(Tipo tipo) : Entity(_grp_ASTEROIDS)
{
	tipo_ = tipo;
	addComponet<Transform>();
	addComponet<FramedImage>(sdlutils().images().at(tipo_ == Tipo::A ? "asteroids" : "asteroids_gold"));
	addComponet<ShowAtOppositeSide>();
	addComponet<Generations>();

	if(tipo_ == Tipo::B)
		addComponet<Follow>();
}

Asteroid::~Asteroid()
{
}
