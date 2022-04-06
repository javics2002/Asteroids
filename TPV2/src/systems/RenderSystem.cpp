#include "RenderSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/Health.h"

RenderSystem::RenderSystem() : winner_(0), state_(NEWGAME)
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::receive(const Message& m)
{
	switch (m.id)
	{
	case _m_ROUND_START:
	case _m_GAME_START:
		state_ = RUNNING;
		break;
	case _m_ROUND_OVER:
		state_ = PAUSED;
		break;
	case _m_GAME_OVER:
		state_ = GAMEOVER;
		winner_ = 1;
		break;
	case _m_NEW_GAME:
		initSystem();
		break;
	case _m_ASTEROIDS_EXTINCTION:
		state_ = WIN;
		winner_ = 2;
	default:
		break;
	}
}

void RenderSystem::initSystem()
{
	winner_ = 0;
	state_ = NEWGAME;
}

void RenderSystem::update()
{
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
	case RUNNING:
	{
		for (auto asteroid : mngr_->getEntities(ecs::_grp_ASTEROIDS))
			asteroid->render();

		for (auto bullet : mngr_->getEntities(ecs::_grp_BULLETS))
			bullet->render();

		auto fighter = mngr_->getHandler(ecs::_hdlr_CAZA);
		fighter->render();
	}
		break;
	default:
		break;
	}
}

void RenderSystem::showMessage(std::string key)
{
	auto& t = sdlutils().msgs().at(key);
	t.render((sdlutils().width() - t.width()) / 2, sdlutils().height() / 2 + t.height() * 2);
}
