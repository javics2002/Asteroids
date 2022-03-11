#pragma once
#include "../utils/Vector2D.h"
class Manager;
class Entity;

class AsteroidsManajer
{
	ecs::Manager* mngr_;
	unsigned int currentAsteroids;
	const unsigned int MAX_ASTEROIDS = 30;

	unsigned int lastGenerationTime;
	const unsigned int GENERATION_TIME = 5000;

	Transform* trFighter_;

	void createAsteroids(int n, unsigned int numGenerations, Vector2D pos, Vector2D vel, float r);
	void addAsteroidFrequently();
	void destroyAllAsteroids();
	void onCollision(ecs::Entity* a);

public:
	AsteroidsManajer(Transform* trFighter);
	~AsteroidsManajer();
};

