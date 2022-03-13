#include "Generations.h"

Generations::Generations(unsigned int numGenerations) {
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
