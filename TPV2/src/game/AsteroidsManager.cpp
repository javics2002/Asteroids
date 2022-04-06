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
		auto generations = mngr_->addComponent<Generations>(asteroid);
		float dimension = 10.0f + 5.0f * generations->getGenerations();

		mngr_->addComponent<Transform>(asteroid, pos, vel, dimension, dimension, sdlutils().rand().nextInt(0, 360));
		mngr_->addComponent<ShowAtOppositeSide>(asteroid);

		//Tipo B
		if (sdlutils().rand().nextInt(0, 10) < 3) {
			mngr_->addComponent<FramedImage>(asteroid, &sdlutils().images().at("asteroid_gold"));
			mngr_->addComponent<Follow>(asteroid);
		}
		//Tipo A
		else {
			mngr_->addComponent<FramedImage>(asteroid, &sdlutils().images().at("asteroid"));
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
		mngr_->setAlive(asteroid, false);

	currentAsteroids = 0;
}

bool AsteroidsManager::onCollision(ecs::Entity* a)
{
	currentAsteroids--;
	Transform* trA = mngr_->getComponent<Transform>(a);
	Vector2D p = trA->pos_;
	Vector2D v = trA->vel_;
	unsigned int numGenerations = mngr_->getComponent<Generations>(a)->getGenerations() - 1;

	if (numGenerations > 0) {
		int i = 0;
		while (i < 2 && currentAsteroids < MAX_ASTEROIDS) {
			int r = sdlutils().rand().nextInt(0, 360);
			Vector2D pos = p + v.rotate(r) * 2 * std::max(trA->width_, trA->height_);
			Vector2D vel = v.rotate(r) * 1.1f;

			auto asteroid = mngr_->addEntity(ecs::_grp_ASTEROIDS);
			auto generations = mngr_->addComponent<Generations>(asteroid, numGenerations);
			float dimension = 10.0f + 5.0f * generations->getGenerations();
			mngr_->addComponent<Transform>(asteroid, pos, vel, dimension, dimension, sdlutils().rand().nextInt(0, 360));
			mngr_->addComponent<ShowAtOppositeSide>(asteroid);

			//Tipo B
			if (sdlutils().rand().nextInt(0, 10) < 3) {
				mngr_->addComponent<FramedImage>(asteroid, &sdlutils().images().at("asteroid_gold"));
				mngr_->addComponent<Follow>(asteroid);
			}
			//Tipo A
			else {
				mngr_->addComponent<FramedImage>(asteroid, &sdlutils().images().at("asteroid"));
			}

			currentAsteroids++;
			i++;
		}
	}

	mngr_->setAlive(a, false);

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
