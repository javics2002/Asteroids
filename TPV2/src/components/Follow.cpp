#include "Follow.h"

void Follow::initComponent()
{
}

void Follow::update()
{
	v.rotate(v.angle(q - p) > 0 ? 1.0f : -1.0f);
}
