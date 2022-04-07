#pragma once
#include "FighterSystem.h"
#include "../components/Health.h"
#include "../ecs/Manager.h"
#include "../game/Game.h"
#include "../utils/Vector2D.h"
#include "../sdlutils/SDLUtils.h"
#include "../components/Transform.h"
#include "../components/Image.h"
#include "../sdlutils/InputHandler.h"

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
	case _m_NEW_GAME:
		mngr_->getComponent<Health>(mngr_->getHandler(ecs::_hdlr_CAZA))->resetLives();
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
	tr_ = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::_hdlr_CAZA));
	mngr_->addComponent<Health>(caza, &sdlutils().images().at("heart"));
	mngr_->addComponent<Image>(caza, &sdlutils().images().at("fighter"));
}

void FighterSystem::update()
{
	if (active_)
	{
		mngr_->getHandler(ecs::_hdlr_CAZA)->update();

		Transform* tr = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::_hdlr_CAZA));

		deaccelerate();
		move();
		showAtOppositeSide();
	}
}

void FighterSystem::onCollision_FighterAsteroid()
{
	auto cTR = mngr_->getComponent<Transform>(mngr_->getHandler(ecs::_hdlr_CAZA));

	//Quitar vida
	mngr_->getComponent<Health>(mngr_->getHandler(ecs::_hdlr_CAZA))->onAsteroidCollision();

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

void FighterSystem::deaccelerate()
{
	auto& vel_ = tr_->vel_;

	if (vel_.magnitude() < 0.05)
		vel_.set(0, 0);
	else
		vel_ = vel_ * deacceleration.DEACC;
}

void FighterSystem::move()
{
	auto& ihldr = ih();

	if (ihldr.keyDownEvent()) {

		auto& vel_ = tr_->vel_;
		auto rot = tr_->rot_;

		if (ihldr.isKeyDown(SDL_SCANCODE_RIGHT)) { // rotate right
			tr_->rot_ = (rot + 5.0f);
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_LEFT)) { // rotate left
			tr_->rot_ = (rot - 5.0f);
		}
		else if (ihldr.isKeyDown(SDL_SCANCODE_UP)) { // increase speed

			/*float speed = std::min(3.0f, vel_.magnitude() + 1.0f);*/

			Vector2D newVel = vel_ + Vector2D(0, -1).rotate(rot) * ctrl.THRUST;

			if (newVel.magnitude() > ctrl.SPEED_LIMIT)
				newVel = newVel.normalize() * ctrl.SPEED_LIMIT;

			vel_ = newVel;

			sdlutils().soundEffects().at("thrust").play(0);
		}
	}

	tr_->pos_ = tr_->pos_ + tr_->vel_;
}

void FighterSystem::showAtOppositeSide()
{
	auto& pos = tr_->pos_;

	// check left/right borders
	if (pos.getX() + tr_->width_ < 0) {
		pos.setX(sdlutils().width());
	}
	else if (pos.getX() > sdlutils().width()) {
		pos.setX(-tr_->width_);
	}

	// check upper/lower borders
	if (pos.getY() + tr_->height_ < 0) {
		pos.setY(sdlutils().height());
	}
	else if (pos.getY() > sdlutils().height()) {
		pos.setY(-tr_->height_);
	}
}
