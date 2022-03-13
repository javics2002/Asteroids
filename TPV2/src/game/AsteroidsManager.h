#pragma once
#include "../utils/Vector2D.h"
#include "../ecs/ecs.h"
#include "../sdlutils/SDLUtils.h"

class Manager;
class Entity;
class Transform;

class AsteroidsManager
{
	ecs::Manager* mngr_;
	unsigned int currentAsteroids;
	const unsigned int MAX_ASTEROIDS = 30;

	unsigned int lastGenerationTime;
	const unsigned int GENERATION_TIME = 5000;

	Transform* trFighter_;

	//void createAsteroids(int n, unsigned int numGenerations, Vector2D pos, Vector2D vel, float r);
	void createAsteroids(int n, unsigned int numGenerations = sdlutils().rand().nextInt(0, 3),
		Vector2D pos = Vector2D(0, 0), Vector2D vel = Vector2D(0, 0), float r = sdlutils().rand().nextInt(0, 360));
	void addAsteroidFrequently();
	void destroyAllAsteroids();
	void onCollision(ecs::Entity* a);

public:
	AsteroidsManager(Transform* trFighter);
	~AsteroidsManager();
};

