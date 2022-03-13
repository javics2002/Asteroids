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
#include "AsteroidsManager.h"

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

	// create the Fighter entity
	//
	auto caza = mngr_->addEntity();
	mngr_->setHandler(ecs::_hdlr_CAZA, caza);
	auto tr = caza->addComponent<Transform>();
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	tr->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);

	//A�adir componentes
	caza->addComponent<Image>(&sdlutils().images().at("fighter"));
	caza->addComponent<ShowAtOppositeSide>();
	caza->addComponent<Health>(&sdlutils().images().at("heart"));
	caza->addComponent<Deacceleration>();

	aManager_ = new AsteroidsManager(mngr_);

	gameController_ = mngr_->addEntity();
	gameController_->setHandler(ecs::_hdlr_GAMEINFO, gameController_);
	gameController_->addComponent<GameState>()->setState(GameState::NEWGAME);
	gameController_->addComponent<GameCtrl>(aManager_);
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;

	auto &ihdlr = ih();

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		// refresh the input handler
		ihdlr.refresh();

		if (ihdlr.isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		mngr_->update();
		mngr_->refresh();

		checkCollisions();

		if(gameController_->getComponent<GameState>()->getState() == GameState::RUNNING)
			aManager_->addAsteroidFrequently();

		sdlutils().clearRenderer();
		mngr_->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}

void Game::checkCollisions() {
	auto cTR = mngr_->getHandler(ecs::_hdlr_CAZA)->getComponent<Transform>();

	auto &asteroids = mngr_->getEntities(ecs::_grp_ASTEROIDS);
	auto n = asteroids.size();
	for (auto i = 0u; i < n; i++) {
		auto e = asteroids[i];
		if (e->isAlive()) { 
			auto eTR = e->getComponent<Transform>();

			//Si un asteroide colisiona con una bala
			auto& bullets = mngr_->getEntities(ecs::_grp_BULLETS);
			auto m = bullets.size();
			for (auto i = 0u; i < m; i++) {
				auto b = bullets[i];
				if (b->isAlive()) {
					auto bTR = b->getComponent<Transform>();

					if (Collisions::collidesWithRotation(bTR->getPos(), bTR->getWidth(), bTR->getHeight(), bTR->getRot(),
						eTR->getPos(), eTR->getWidth(), eTR->getHeight(), eTR->getRot())) {
						b->setAlive(false);
						
						if (aManager_->onCollision(e)) {
							//Gamamos!
							gameController_->getComponent<GameState>()->setState(GameState::WIN);

							//Posici�n inicial
							cTR->init(Vector2D((sdlutils().width() - cTR->getWidth()) / 2.0f,
								(sdlutils().height() - cTR->getHeight()) / 2.0f), Vector2D(), cTR->getWidth(), cTR->getHeight(), 0.0f);
						}
					}
				}
			}

			//Si un asteroide colisiona con el caza
			if (Collisions::collidesWithRotation(cTR->getPos(), cTR->getWidth(), cTR->getHeight(), cTR->getRot(), 
				eTR->getPos(), eTR->getWidth(), eTR->getHeight(), eTR->getRot())) {
				//Destruir entidades
				aManager_->destroyAllAsteroids();
				for (auto i = 0u; i < m; i++)
					bullets[i]->setAlive(false);

				//Quitar vida
				auto health = mngr_->getHandler(ecs::_hdlr_CAZA)->getComponent<Health>();
				health->onAsteroidCollision();

				//Cambio de estado
				gameController_->getComponent<GameState>()->
					setState(health->getLives() > 0 ? GameState::PAUSED : GameState::GAMEOVER);
				
				//Posici�n inicial
				cTR->init(Vector2D((sdlutils().width() - cTR->getWidth()) / 2.0f, 
					(sdlutils().height() - cTR->getHeight()) / 2.0f), Vector2D(), cTR->getWidth(), cTR->getHeight(), 0.0f);
			}
		}
	}
}
