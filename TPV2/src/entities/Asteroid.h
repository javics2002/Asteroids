#pragma once
#include "../ecs/Entity.h"

using namespace ecs;

class Asteroid : public Entity {
public:
	enum Tipo {A, B};

	Asteroid(Tipo tipo);
	virtual ~Asteroid();
private:
	Tipo tipo_;
};
