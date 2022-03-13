#include "State.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

State::State()
{
	state = NEWGAME;
}

State::~State()
{
}

void State::initComponent() {
}

void State::update() {
	auto& ihldr = ih();

	if (state != RUNNING)
	{
		if (ihldr.keyDownEvent()) {
			if (ihldr.isKeyDown(SDL_SCANCODE_SPACE))
			{
				state = static_cast<Estados>(state + 1);
			}
		}
	}
}

void State::render() {

	switch (state)
	{
	case(NEWGAME):
		sdlutils().msgs().at("newgame").render(500, 10);
		break;
	case(RUNNING):
		sdlutils().msgs().at("running").render(500, 10);
		break;
	case(PAUSED):
		sdlutils().msgs().at("paused").render(500, 10);
		break;
	case(GAMEOVER):
		sdlutils().msgs().at("gameover").render(500, 10);
		break;
	}
}
