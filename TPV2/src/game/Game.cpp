// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/GameCtrl.h"
#include "../components/Image.h"
#include "../components/FighterCtrl.h"
#include "../components/StopOnBorders.h"
#include "../components/Transform.h"
#include "../components/ShowAtOppositeSide.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"
#include "../utils/Collisions.h"
#include "../components/Health.h"
#include "../components/Deacceleration.h"
#include "../components/Gun.h"
#include "../components/State.h"

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

	//Añadir componentes
	caza->addComponent<Image>(&sdlutils().images().at("fighter"));
	caza->addComponent<FighterCtrl>();
	caza->addComponent<ShowAtOppositeSide>();
	caza->addComponent<Health>(&sdlutils().images().at("heart"));
	caza->addComponent<Deacceleration>();
	caza->addComponent<Gun>();

	// create the game info entity
	auto ginfo = mngr_->addEntity();
	mngr_->setHandler(ecs::_hdlr_GAMEINFO, ginfo);
	ginfo->addComponent<GameCtrl>();
	ginfo->addComponent<State>();
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

		sdlutils().clearRenderer();
		mngr_->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}

}

void Game::checkCollisions() {

	// the Fighter's Transform
	//
	auto cTR = mngr_->getHandler(ecs::_hdlr_CAZA)->getComponent<Transform>();

	// For safety, we traverse with a normal loop until the current size. In this
	// particular case we could use a for-each loop since the list stars is not
	// modified.
	//
	auto &stars = mngr_->getEntities(ecs::_grp_STARS);
	auto n = stars.size();
	for (auto i = 0u; i < n; i++) {
		auto e = stars[i];
		if (e->isAlive()) { // if the star is active (it might have died in this frame)

			// the Star's Transform
			//
			auto eTR = e->getComponent<Transform>();

			// check if PacMan collides with the Star (i.e., eat it)
			if (Collisions::collides(cTR->getPos(), cTR->getWidth(),
					cTR->getHeight(), //
					eTR->getPos(), eTR->getWidth(), eTR->getHeight())) {
				e->setAlive(false);
				mngr_->getHandler(ecs::_hdlr_CAZA)->getComponent<Health>()->onAsteroidCollision();

				// play sound on channel 1 (if there is something playing there
				// it will be cancelled
				sdlutils().soundEffects().at("pacman_eat").play(0, 1);
			}
		}
	}
}
