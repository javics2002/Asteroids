#pragma once
#include "../utils/Vector2D.h"
#include "../ecs/ecs.h"
#include "../sdlutils/SDLUtils.h"

namespace ecs {
	class Manager;
	class Entity;
}
class Transform;

class AsteroidsManager
{
	ecs::Manager* mngr_;
	unsigned int currentAsteroids;
	const unsigned int MAX_ASTEROIDS = 30;

	unsigned int lastGenerationTime;
	const unsigned int GENERATION_TIME = 5000;

public:
	void createAsteroids(int n);
	void addAsteroidFrequently();
	void destroyAllAsteroids();
	bool onCollision(ecs::Entity* a);

	AsteroidsManager(ecs::Manager* mngr);
	~AsteroidsManager();
};

