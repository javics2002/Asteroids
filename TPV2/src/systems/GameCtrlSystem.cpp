#include "GameCtrlSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Manager.h"

GameCtrlSystem::GameCtrlSystem() : winner_(0), state_(NEWGAME) {
}

GameCtrlSystem::~GameCtrlSystem() {
}

void GameCtrlSystem::receive(const Message& m)
{
	switch (m.id) {
	case _m_ON_COLLISION_FIGHTER_ASTEROID:
		onCollision_FighterAsteroid();
		break;
	case _m_ASTEROIDS_EXTINCTION:
		onAsteroidsExtinction();
		winner_ = m.asteroid_extinction.winner;
		break;
	default:
		break;
	}
}

void GameCtrlSystem::initSystem()
{
	winner_ = 0;
	state_ = NEWGAME;
}

void GameCtrlSystem::update()
{
	if (state_ != RUNNING) {
		auto& inhdlr = ih();

		if (inhdlr.isKeyDown(SDL_SCANCODE_SPACE)) {
			switch (state_) {
			case NEWGAME:
			case PAUSED:
				startRound();
				break;
			case GAMEOVER:
				startGame();
				break;
			default:
				break;
			}
		}
	}
}

void GameCtrlSystem::onCollision_FighterAsteroid()
{
	state_ = PAUSED;
	
	Message m;
	m.id = _m_ROUND_OVER;
	mngr_->send(m);
}

void GameCtrlSystem::onAsteroidsExtinction()
{
	Message m;
	state_ = GAMEOVER;
	m.id = _m_ROUND_OVER;
	mngr_->send(m);
	m.id = _m_GAME_OVER;
	mngr_->send(m);
}

void GameCtrlSystem::startRound()
{
	state_ = RUNNING;

	Message m;
	m.id = _m_ROUND_START;
	mngr_->send(m);
}

void GameCtrlSystem::startGame()
{
	state_ = RUNNING;

	Message m;
	m.id = _m_NEW_GAME;
	mngr_->send(m);
}
