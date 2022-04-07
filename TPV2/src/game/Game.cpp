// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/Image.h"
#include "../components/FighterCtrl.h"
#include "../components/Transform.h"
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
	fighterSys_ = mngr_->addSystem<FighterSystem>();
	asteroidsSys_ = mngr_->addSystem<AsteroidsSystem>();
	fighterGunSys_ = mngr_->addSystem<FighterGunSystem>();
	bulletsSys_ = mngr_->addSystem<BulletsSystem>();
	gameCtrlSys_ = mngr_->addSystem<GameCtrlSystem>();
	collisionsSys_ = mngr_->addSystem<CollisionsSystem>();
	renderSys_ = mngr_->addSystem<RenderSystem>();
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

		sdlutils().clearRenderer();

		updateSystems();

		mngr_->refresh();

		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void Game::updateSystems()
{
	fighterSys_->update();
	fighterGunSys_->update();
	bulletsSys_->update();
	asteroidsSys_->update();
	collisionsSys_->update();
	gameCtrlSys_->update();
	renderSys_->update();
}
