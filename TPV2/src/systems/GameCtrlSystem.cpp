#include "GameCtrlSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"

void GameCtrlSystem::receive(const Message& m)
{
	switch (m.id) {
	default: 
		break;
	}
}

void GameCtrlSystem::initSystem()
{
}

void GameCtrlSystem::update()
{
	if (getState() != RUNNING) {
		auto& inhdlr = ih();
		if (inhdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
			switch (getState()) {
			case NEWGAME:
			case PAUSED:
				setState(RUNNING);

				aMngr_->createAsteroids(10);

				// añadir al fighter sus cosas para jugar
				mngr_->getHandler(ecs::_hdlr_CAZA)->addComponent<FighterCtrl>();
				mngr_->getHandler(ecs::_hdlr_CAZA)->addComponent<Gun>();

				break;
			case GAMEOVER:
			case WIN:
				setState(NEWGAME);

				mngr_->getHandler(ecs::_hdlr_CAZA)->getComponent<Health>()->resetLives();
				break;
			default:
				break;
			}
		}
	}
}

void GameCtrlSystem::onCollision_AsteroidBullet(Entity* a)
{
}

void GameCtrlSystem::onRoundOver()
{
}

void GameCtrlSystem::onRoundStart()
{
}

void GameCtrlSystem::showMessage(std::string key)
{
	auto& t = sdlutils().msgs().at(key);
	t.render((sdlutils().width() - t.width()) / 2, sdlutils().height() / 2 + t.height() * 2);
}

//void GameState::render() {
//	if (state_ != RUNNING) {
//		switch (state_) {
//		case NEWGAME:
//			showMessage("start");
//			break;
//		case PAUSED:
//			showMessage("continue");
//			break;
//		case GAMEOVER:
//			showMessage("gameover");
//			break;
//		case WIN:
//			showMessage("win");
//			break;
//		default:
//			break;
//		}
//	}
//}
