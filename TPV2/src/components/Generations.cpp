#include "Generations.h"
#include "../sdlutils/SDLUtils.h"

Generations::Generations(unsigned int numGenerations = sdlutils().rand().nextInt(0, 3)) {
	numGenerations_ = numGenerations;
}

void Generations::initComponent()
{
}

unsigned int Generations::getGenerations()
{
	return numGenerations_;
}

void Generations::decreaseGenerations()
{
	numGenerations_--;
}
