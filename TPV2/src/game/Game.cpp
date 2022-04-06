// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/GameCtrl.h"
#include "../components/Image.h"
#include "../components/FighterCtrl.h"
#include "../components/StopOnBorders.h"
#include "../components/Transform.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/GameState.h"
#include "../components/GameCtrl.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"
#include "../components/Health.h"
#include "../components/Deacceleration.h"
#include "../components/Gun.h"
#include "../ecs/ecs.h"
#include "AsteroidsManager.h"

#include "../systems/AsteroidsSystem.h"
#include "../systems/FighterSystem.h"
#include "../systems/FighterGunSystem.h"
#include "../systems/BulletsSystem.h"
#include "../systems/RenderSystem.h"
#include "../systems/GameCtrlSystem.h"
#include "../systems/CollisionsSystem.h"

using ecs::Entity;
using ecs::Manager;

Game::Game() :
		mngr_(nullptr) {
}

Game::~Game() {
	delete mngr_;
}

void Game::init() {

	// initialise the SDLUtils singleton
	SDLUtils::init("Demo", 800, 600, "resources/config/resources.json");

	// Create the manager
	mngr_ = new Manager();

	//Systems
	fighterSys_ = new FighterSystem();
	fighterSys_->setContext(mngr_);
	fighterSys_->initSystem();
	mngr_->addSystem<FighterSystem>(*fighterSys_);

	asteroidsSys_ = new AsteroidsSystem();
	asteroidsSys_->setContext(mngr_);
	asteroidsSys_->initSystem();
	mngr_->addSystem<AsteroidsSystem>(*asteroidsSys_);

	fighterGunSys_ = new FighterGunSystem();
	fighterGunSys_->setContext(mngr_);
	fighterGunSys_->initSystem();
	mngr_->addSystem<FighterGunSystem>(*fighterGunSys_);

	bulletsSys_ = new BulletsSystem();
	bulletsSys_->setContext(mngr_);
	bulletsSys_->initSystem();
	mngr_->addSystem<BulletsSystem>(*bulletsSys_);

	gameCtrlSys_ = new GameCtrlSystem();
	gameCtrlSys_->setContext(mngr_);
	gameCtrlSys_->initSystem();
	mngr_->addSystem<GameCtrlSystem>(*gameCtrlSys_);

	collisionsSys_ = new CollisionsSystem();
	collisionsSys_->setContext(mngr_);
	collisionsSys_->initSystem();
	mngr_->addSystem<CollisionsSystem>(*collisionsSys_);

	renderSys_ = new RenderSystem();
	renderSys_->setContext(mngr_);
	renderSys_->initSystem();
	mngr_->addSystem<RenderSystem>(*renderSys_);

	gameController_ = mngr_->addEntity();
	mngr_->addComponent<GameState>(gameController_)->setState(GameState::NEWGAME);
	//mngr_->addComponent<GameCtrl>(gameController_, aManager_);
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) 
	{
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) 
		{
			exit = true;
			continue;
		}

		updateSystems();

		//mngr_->update();
		mngr_->refresh();

		checkCollisions();

		if (mngr_->getComponent<GameState>(gameController_)->getState() == GameState::RUNNING)
			;//aManager_->addAsteroidFrequently();

		sdlutils().clearRenderer();
		//mngr_->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}

void Game::checkCollisions() 
{
	auto caza = mngr_->getHandler(ecs::_hdlr_CAZA);
	auto cTR = mngr_->getComponent<Transform>(caza);

	auto &asteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);
	auto n = asteroids.size();
	for (auto i = 0u; i < n; i++) 
	{
		auto e = asteroids[i];
		if (mngr_->isAlive(e)) 
		{ 
			auto eTR = mngr_->getComponent<Transform>(e);

			//Si un asteroide colisiona con una bala
			auto& bullets = mngr_->getEntities(ecs::_grp_BULLETS);
			auto m = bullets.size();
			for (auto i = 0u; i < m; i++) 
			{
				auto b = bullets[i];
				if (mngr_->isAlive(b)) 
				{
					auto bTR = mngr_->getComponent<Transform>(b);

					if (Collisions::collidesWithRotation(bTR->pos_, bTR->width_, bTR->height_, bTR->rot_,
						eTR->pos_, eTR->width_, eTR->height_, eTR->rot_)) 
					{
						//Destruir bala
						Message m;
						m.id = _m_ON_COLLISION_BULLET_ASTEROID;
						m.bullet_hit_asteroid.a = b;
						mngr_->getSystem<BulletsSystem>()->receive(m);

						if (mngr_->isAlive(e))
						{
							//Destruir asteroide
							Message m;
							m.id = _m_ON_COLLISION_BULLET_ASTEROID;
							m.bullet_hit_asteroid.a = e;
							mngr_->getSystem<AsteroidsSystem>()->receive(m);
						}
						
						//if (aManager_->onCollision(e)) 
						{
							//Ganamos!
							mngr_->getComponent<GameState>(gameController_)->setState(GameState::WIN);

							//Posición inicial
							cTR->init(Vector2D((sdlutils().width() - cTR->width_) / 2.0f,
								(sdlutils().height() - cTR->height_) / 2.0f), Vector2D(), cTR->width_, cTR->height_, 0.0f);

							//Ya no podemos controlar al caza
							mngr_->removeComponent<FighterCtrl>(mngr_->getHandler(ecs::_hdlr_CAZA));
							mngr_->removeComponent<Gun>(mngr_->getHandler(ecs::_hdlr_CAZA));
						}
					}
				}
			}

			//Si un asteroide colisiona con el caza
			if (Collisions::collidesWithRotation(cTR->pos_, cTR->width_, cTR->height_, cTR->rot_, 
				eTR->pos_, eTR->width_, eTR->height_, eTR->rot_)) 
			{
				//Destruir entidades
				//aManager_->destroyAllAsteroids();
				for (auto i = 0u; i < m; i++)
					mngr_->setAlive(bullets[i], false);

				//LLamar a FighterSystem

				//Cambio de estado
				mngr_->getComponent<GameState>(gameController_)->
					setState(mngr_->getComponent<Health>(mngr_->getHandler(ecs::_hdlr_CAZA))->getLives() > 0 ? GameState::PAUSED : GameState::GAMEOVER);
				
				//Posición inicial
				cTR->init(Vector2D((sdlutils().width() - cTR->width_) / 2.0f, 
					(sdlutils().height() - cTR->height_) / 2.0f), Vector2D(), cTR->width_, cTR->height_, 0.0f);

				//Ya no podemos controlar al caza
				mngr_->removeComponent<FighterCtrl>(mngr_->getHandler(ecs::_hdlr_CAZA));
				mngr_->removeComponent<Gun>(mngr_->getHandler(ecs::_hdlr_CAZA));
			}
		}
	}
}

void Game::updateSystems()
{
	asteroidsSys_->update();
	fighterSys_->update();
	fighterGunSys_->update();
	bulletsSys_->update();
	gameCtrlSys_->update();
	collisionsSys_->update();
	renderSys_->update();
}
