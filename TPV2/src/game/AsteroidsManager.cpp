#include "AsteroidsManager.h"
#include "../ecs/Manager.h"
#include "../components/Follow.h"
#include "../components/Transform.h"
#include "../components/ShowAtOppositeSide.h"
//#include "../components/FramedImage.h"
#include "../components/Generations.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

void AsteroidsManager::createAsteroids(int n, unsigned int numGenerations , 
	Vector2D pos , Vector2D vel , float r )
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
		Transform* tr = asteroid->addComponent<Transform>(pos, vel, dimension, dimension, r);
		asteroid->addComponent<ShowAtOppositeSide>();
		asteroid->addComponent<Generations>(numGenerations);

		Texture* t;
		//Tipo B
		if (sdlutils().rand().nextInt(0, 10) < 3) {
			//asteroid->addComponent<FramedImage>(&sdlutils().images().at("asteroids_gold"));
			asteroid->addComponent<Follow>(trFighter_);
		}
		//Tipo A
		else {
			//asteroid->addComponent<FramedImage>(&sdlutils().images().at("asteroids"));
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

void AsteroidsManager::onCollision(ecs::Entity* a)
{
	currentAsteroids--;
	Transform* trA = a->getComponent<Transform>();
	Vector2D p = trA->getPos();
	Vector2D v = trA->getVel();
	unsigned int numGenerations = a->getComponent<Generations>()->getGenerations();

	for (int i = 0; i < 2; i++) {
		int r = sdlutils().rand().nextInt(0, 360);
		Vector2D pos = p + v.rotate(r) * 2 * std::max(trA->getWidth(), trA->getHeight());
		Vector2D vel = v.rotate(r) * 1.1f;
		createAsteroids(1, numGenerations - 1, pos, vel, r);
	}

	a->setAlive(false);
}

AsteroidsManager::AsteroidsManager(Transform* trFighter)
{
	trFighter_ = trFighter;
}

AsteroidsManager::~AsteroidsManager()
{
}
