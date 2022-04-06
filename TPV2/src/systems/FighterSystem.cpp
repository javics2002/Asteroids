#pragma once
#include "FighterSystem.h"
#include "../components/Health.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"
#include "../components/GameState.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/ShowAtOppositeSide.h"
#include "../components/Deacceleration.h"

void FighterSystem::receive(const Message& m)
{
}

void FighterSystem::initSystem()
{
	// create the Fighter entity
	auto caza = mngr_->addEntity();
	mngr_->setHandler(ecs::_hdlr_CAZA, caza);
	auto tr = mngr_->addComponent<Transform>(caza);
	auto s = 50.0f;
	auto x = (sdlutils().width() - s) / 2.0f;
	auto y = (sdlutils().height() - s) / 2.0f;
	tr->init(Vector2D(x, y), Vector2D(), s, s, 0.0f);

	//Añadir componentes
	mngr_->addComponent<Image>(caza, &sdlutils().images().at("fighter"));
	mngr_->addComponent<ShowAtOppositeSide>(caza);
	mngr_->addComponent<Health>(caza, &sdlutils().images().at("heart"));
	mngr_->addComponent<Deacceleration>(caza);
}

void FighterSystem::update()
{
	if (active_)
	{

	}
}

void FighterSystem::onCollision_FighterAsteroid()
{
	auto cTR = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::_hdlr_CAZA));

	//Quitar vida
	auto health = mngr_->getComponent<Health>(mngr_->getHandler(ecs::_hdlr_CAZA));
	health->onAsteroidCollision();

	//Posición inicial
	cTR->init(Vector2D((sdlutils().width() - cTR->getWidth()) / 2.0f,
		(sdlutils().height() - cTR->getHeight()) / 2.0f), Vector2D(), cTR->getWidth(), cTR->getHeight(), 0.0f);
}

void FighterSystem::onRoundOver()
{
	active_ = false;
}

void FighterSystem::onRoundStart()
{
	active_ = true;
}
