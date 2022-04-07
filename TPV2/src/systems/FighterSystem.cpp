#pragma once
#include "FighterSystem.h"
#include "../components/Health.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../components/Deacceleration.h"
#include "../components/FighterCtrl.h"

void FighterSystem::receive(const Message& m)
{
	switch (m.id)
	{
	case _m_ROUND_OVER:
		onRoundOver();
		break;
	case _m_ROUND_START:
		onRoundStart();
		break;
	case _m_ON_COLLISION_FIGHTER_ASTEROID:
		onCollision_FighterAsteroid();
		break;
	default:
		break;
	}
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
	mngr_->addComponent<Health>(caza, &sdlutils().images().at("heart"));
	mngr_->addComponent<Deacceleration>(caza);
	mngr_->addComponent<FighterCtrl>(caza);
}

void FighterSystem::update()
{
	if (active_)
		mngr_->getHandler(ecs::_hdlr_CAZA)->update();
}

void FighterSystem::onCollision_FighterAsteroid()
{
	auto cTR = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::_hdlr_CAZA));

	//Quitar vida
	auto health = mngr_->getComponent<Health>(mngr_->getHandler(ecs::_hdlr_CAZA));
	health->onAsteroidCollision();

	//Posición inicial
	cTR->init(Vector2D((sdlutils().width() - cTR->width_) / 2.0f, (sdlutils().height() - cTR->height_) / 2.0f), Vector2D(), cTR->width_, cTR->height_, 0.0f);
}

void FighterSystem::onRoundOver()
{
	active_ = false;
}

void FighterSystem::onRoundStart()
{
	active_ = true;
}
