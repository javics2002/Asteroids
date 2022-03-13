// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <array>

#include "../ecs/Component.h"
#include <string>

class Transform;

class GameState: public ecs::Component {
public:

	__CMPID_DECL__(ecs::_GAMESTATE)

	enum State {
		NEWGAME = 0, // just before starting a new game
		PAUSED, // between rounds
		RUNNING, // playing
		GAMEOVER, // game over
		WIN // win
	};

	GameState();
	virtual ~GameState();

	inline State getState() {
		return state_;
	}

	inline void setState(State state) {
		state_ = state;
	}

	void render() override;

	void showMessage(std::string key);

private:
	State state_;
};

