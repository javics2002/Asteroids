#include "AsteroidsManajer.h"
#include "../ecs/Manager.h"
#include "../components/Follow.h"
#include "../components/Transform.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/FramedImage.h"
#include "../components/Generations.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

void AsteroidsManajer::createAsteroids(int n, unsigned int numGenerations = sdlutils().rand().nextInt(0, 3), 
	Vector2D pos = Vector2D(0, 0), Vector2D vel = Vector2D(0, 0), float r = sdlutils().rand().nextInt(0, 360))
{
	auto i = 0;
	while (i < n && currentAsteroids < MAX_ASTEROIDS) {
		//Posicion aleatoria
		if (pos.getX() == 0 && pos.getY() == 0)
		{
			if (sdlutils().rand().nextInt(0, 2) < 1) {
				pos.setX(sdlutils().rand().nextInt(0, sdlutils().width()));
				pos.setY(sdlutils().rand().nextInt(0, 2) < 1 ? 0 : sdlutils().height());
			}
			else {
				pos.setX(sdlutils().rand().nextInt(0, 2) < 1 ? 0 : sdlutils().width());
				pos.setY(sdlutils().rand().nextInt(0, sdlutils().height()));
			}

			Vector2D c = Vector2D(sdlutils().width() / 2 + sdlutils().rand().nextInt(-100, 100),
				sdlutils().height() / 2 + sdlutils().rand().nextInt(-100, 100));

			float speed = sdlutils().rand().nextInt(1, 10) / 10.0f;
			vel = (c - pos).normalize() * speed;
		}
		
		float dimension = 10.0f + 5.0f * numGenerations;
			
		auto asteroid = mngr_->addEntity(ecs::_grp_ASTEROIDS);
		Transform* tr = asteroid->addComponet<Transform>(pos, vel, dimension, dimension, r);
		asteroid->addComponet<ShowAtOppositeSide>();
		asteroid->addComponet<Generations>(numGenerations);

		//Tipo B
		if (sdlutils().rand().nextInt(0, 10) < 3) {
			asteroid->addComponet<FramedImage>(sdlutils().images().at("asteroids_gold"));
			asteroid->addComponet<Follow>();
		}
		//Tipo A
		else {
			asteroid->addComponet<FramedImage>(sdlutils().images().at("asteroids"));
		}

		currentAsteroids++;
		i++;
	}
}

void AsteroidsManajer::addAsteroidFrequently()
{
	if (sdlutils().currRealTime() - lastGenerationTime > GENERATION_TIME) {
		createAsteroids(1);
		lastGenerationTime = sdlutils().currRealTime();
	}
}

void AsteroidsManajer::destroyAllAsteroids()
{
	auto groupAsteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);

	for (auto asteroid : groupAsteroids)
		asteroid->setAlive(false);

	currentAsteroids = 0;
}

void AsteroidsManajer::onCollision(ecs::Entity* a)
{
	currentAsteroids--;
	auto trA = a->getComponent<Transform>();
	auto p = trA->getPos();
	auto v = trA->getVel();
	auto numGenerations = a->getComponent<Generations>()->getGenerations();

	for (int i = 0; i < 2; i++) {
		auto r = sdlutils().rand().nextInt(0, 360);
		auto pos = p + v.rotate(r) * 2 * std::max(trA->getWidth(), trA->getHeight());
		auto vel = v.rotate(r) * 1.1f;
		createAsteroids(1, numGenerations - 1, pos, vel, r);
	}

	a->setAlive(false);
}

AsteroidsManajer::AsteroidsManajer(Transform* trFighter)
{
	trFighter_ = trFighter;
}

AsteroidsManajer::~AsteroidsManajer()
{
}
