#include "AsteroidsManager.h"
#include "../ecs/Manager.h"
#include "../components/Follow.h"
#include "../components/Transform.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/FramedImage.h"
#include "../components/Generations.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

void AsteroidsManager::createAsteroids(int n)
{
	auto i = 0;
	while (i < n && currentAsteroids < MAX_ASTEROIDS) {
		//Posicion aleatoria
		Vector2D pos;
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
		Vector2D vel = (c - pos).normalize() * speed;

		auto asteroid = mngr_->addEntity(ecs::_grp_ASTEROIDS);
		auto generations = asteroid->addComponent<Generations>();
		float dimension = 10.0f + 5.0f * generations->getGenerations();

		asteroid->addComponent<Transform>(pos, vel, dimension, dimension, sdlutils().rand().nextInt(0, 360));
		asteroid->addComponent<ShowAtOppositeSide>();

		//Tipo B
		if (sdlutils().rand().nextInt(0, 10) < 3) {
			asteroid->addComponent<FramedImage>(&sdlutils().images().at("asteroid_gold"));
			asteroid->addComponent<Follow>();
		}
		//Tipo A
		else {
			asteroid->addComponent<FramedImage>(&sdlutils().images().at("asteroid"));
		}

		currentAsteroids++;
		i++;
	}
}

void AsteroidsManager::addAsteroidFrequently()
{
	if (sdlutils().currRealTime() - lastGenerationTime > GENERATION_TIME) {
		createAsteroids(1);
		lastGenerationTime = sdlutils().currRealTime();
	}
}

void AsteroidsManager::destroyAllAsteroids()
{
	auto groupAsteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);

	for (auto asteroid : groupAsteroids)
		asteroid->setAlive(false);

	currentAsteroids = 0;
}

bool AsteroidsManager::onCollision(ecs::Entity* a)
{
	currentAsteroids--;
	Transform* trA = a->getComponent<Transform>();
	Vector2D p = trA->getPos();
	Vector2D v = trA->getVel();
	unsigned int numGenerations = a->getComponent<Generations>()->getGenerations() - 1;

	if (numGenerations > 0) {
		int i = 0;
		while (i < 2 && currentAsteroids < MAX_ASTEROIDS) {
			int r = sdlutils().rand().nextInt(0, 360);
			Vector2D pos = p + v.rotate(r) * 2 * std::max(trA->getWidth(), trA->getHeight());
			Vector2D vel = v.rotate(r) * 1.1f;

			auto asteroid = mngr_->addEntity(ecs::_grp_ASTEROIDS);
			auto generations = asteroid->addComponent<Generations>(numGenerations);
			float dimension = 10.0f + 5.0f * generations->getGenerations();
			asteroid->addComponent<Transform>(pos, vel, dimension, dimension, sdlutils().rand().nextInt(0, 360));
			asteroid->addComponent<ShowAtOppositeSide>();

			//Tipo B
			if (sdlutils().rand().nextInt(0, 10) < 3) {
				asteroid->addComponent<FramedImage>(&sdlutils().images().at("asteroid_gold"));
				asteroid->addComponent<Follow>();
			}
			//Tipo A
			else {
				asteroid->addComponent<FramedImage>(&sdlutils().images().at("asteroid"));
			}

			currentAsteroids++;
			i++;
		}
	}

	a->setAlive(false);

	//¿Hemos ganado?
	return currentAsteroids == 0;
}

AsteroidsManager::AsteroidsManager(ecs::Manager* mngr)
{
	mngr_ = mngr;
	currentAsteroids = 0;
	lastGenerationTime = sdlutils().currRealTime();
}

AsteroidsManager::~AsteroidsManager()
{
}
