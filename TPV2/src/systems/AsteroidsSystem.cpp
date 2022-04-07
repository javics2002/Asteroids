#include "AsteroidsSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/Transform.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Generations.h"
#include "../components/FramedImage.h"
#include "../components/Follow.h"

AsteroidsSystem::AsteroidsSystem() : numOfAsteroids_(0), lastGenerationTime_(0), active_(false) {
}

AsteroidsSystem::~AsteroidsSystem() {
}

void AsteroidsSystem::receive(const Message& m)
{
	switch (m.id)
	{
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_ROUND_OVER:
		onRoundOver();
		break;
	case _m_ON_COLLISION_ASTEROID_BULLET:
		onCollision_AsteroidBullet(m.bullet_hit_asteroid.a);
		break;
	default:
		break;
	}
}

void AsteroidsSystem::initSystem()
{
	numOfAsteroids_ = 0;
	active_ = false;
}

void AsteroidsSystem::update()
{
	if (active_) {
		auto& asteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);

		for (int i = 0u; i < asteroids.size(); i++) {
			mngr_->getComponent<Transform>(asteroids[i])->move();
			asteroids[i]->update();
		}

		addAsteroidFrequently();
	}
}

void AsteroidsSystem::onCollision_AsteroidBullet(ecs::Entity* a)
{
	numOfAsteroids_--;
	Transform* trA = mngr_->getComponent<Transform>(a);
	Vector2D p = trA->pos_;
	Vector2D v = trA->vel_;
	unsigned int numGenerations = mngr_->getComponent<Generations>(a)->getGenerations() - 1;

	if (numGenerations > 0) {
		int i = 0;
		while (i < 2 && numOfAsteroids_ < MAX_ASTEROIDS) {
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
				mngr_->addComponent<FramedImage>(asteroid, &sdlutils().images().at("asteroid_gold"),
					85u, 100u, 4u, 5u, 50u);
				mngr_->addComponent<Follow>(asteroid);
				new FramedImage(&sdlutils().images().at("asteroid_gold"),
					85u, 100u, 4u, 5u, 50u);
			}
			//Tipo A
			else {
				mngr_->addComponent<FramedImage>(asteroid, &sdlutils().images().at("asteroid"), 85u, 100u, 4u, 5u, 50u);
			}

			numOfAsteroids_++;
			i++;
		}
	}

	mngr_->setAlive(a, false);
}

void AsteroidsSystem::onRoundOver()
{
	active_ = false;

	auto groupAsteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);

	for (auto asteroid : groupAsteroids)
		mngr_->setAlive(asteroid, false);

	numOfAsteroids_ = 0;
}

void AsteroidsSystem::onRoundStart()
{
	active_ = true;

	createAsteroids(10);
}

void AsteroidsSystem::addAsteroidFrequently()
{
	if (sdlutils().currRealTime() - lastGenerationTime_ > GENERATION_TIME) {
		createAsteroids(1);
		lastGenerationTime_ = sdlutils().currRealTime();
	}
}

void AsteroidsSystem::createAsteroids(int n)
{
	auto i = 0;
	while (i < n && numOfAsteroids_ < MAX_ASTEROIDS) {
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
			mngr_->addComponent<FramedImage>(asteroid, &sdlutils().images().at("asteroid_gold"), 
				85u, 100u, 4u, 5u, 50u);
			mngr_->addComponent<Follow>(asteroid);
		}
		//Tipo A
		else {
			mngr_->addComponent<FramedImage>(asteroid, &sdlutils().images().at("asteroid"), 85u, 100u, 4u, 5u, 50u);
		}

		numOfAsteroids_++;
		i++;
	}
}
