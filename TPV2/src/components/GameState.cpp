// This file is part of the course TPV2@UCM - Samir Genaim

#include "GameState.h"

#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "Transform.h"

GameState::GameState() : state_(NEWGAME) {
}

GameState::~GameState() {
}

void GameState::render() {
	if (state_ != RUNNING) {
		switch (state_) {
		case NEWGAME:
			showMessage("start");
			break;
		case PAUSED:
			showMessage("continue");
			break;
		case GAMEOVER:
			showMessage("gameover");
			break;
		case WIN:
			showMessage("win");
			break;
		default:
			break;
		}
	}
}

void GameState::showMessage(std::string key)
{
	auto& t = sdlutils().msgs().at(key);
	t.render((sdlutils().width() - t.width()) / 2, sdlutils().height() / 2 + t.height() * 2);
}

