// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameCtrl.h"

#include <algorithm>

#include "../components/GameState.h"
#include "../components/Health.h"
#include "../components/FighterCtrl.h"
#include "../components/Gun.h"
#include "../components/Deacceleration.h"

#include "../game/AsteroidsManager.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/Texture.h"
#include "Image.h"
#include "Transform.h"

GameCtrl::GameCtrl(AsteroidsManager* aMngr) : currentState_(nullptr) {
	aMngr_ = aMngr;
}

GameCtrl::~GameCtrl() {
}

void GameCtrl::initComponent() {
	currentState_ = ent_->getComponent<GameState>();
	assert(currentState_ != nullptr);
}

void GameCtrl::update() {
	if (currentState_->getState() != GameState::RUNNING) {
		auto& inhdlr = ih();
		if (inhdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
			switch (currentState_->getState()) {
			case GameState::NEWGAME:
			case GameState::PAUSED:
				currentState_->setState(GameState::RUNNING);

				aMngr_->createAsteroids(10);

				// añadir al fighter sus cosas para jugar
				mngr_->getHandler(ecs::_hdlr_CAZA)->addComponent<FighterCtrl>();
				mngr_->getHandler(ecs::_hdlr_CAZA)->addComponent<Gun>();

				break;
			case GameState::GAMEOVER:
			case GameState::WIN:
				currentState_->setState(GameState::NEWGAME);

				mngr_->getHandler(ecs::_hdlr_CAZA)->getComponent<Health>()->resetLives();
				break;
			default:
				
				break;
			}
		}
	}
}