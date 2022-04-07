#include "RenderSystem.h"
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"
#include "../components/Health.h"
#include "../components/FramedImage.h"
#include "../components/Image.h"
#include "../components/Transform.h"

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
		winner_ = 1;
		state_ = GAMEOVER;
		break;
	case _m_NEW_GAME:
		initSystem();
		break;
	case _m_ASTEROIDS_EXTINCTION:
		winner_ = 2;
		state_ = WIN;
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
		for (auto asteroid : mngr_->getEntities(ecs::_grp_ASTEROIDS)) {
			auto framedImage_ = mngr_->getComponent<FramedImage>(asteroid);
			auto tr_ = mngr_->getComponent<Transform>(asteroid);

			animation(framedImage_, tr_);
		}

		for (auto bullet : mngr_->getEntities(ecs::_grp_BULLETS)) {
			render(mngr_->getComponent<Transform>(bullet), mngr_->getComponent<Image>(bullet));
		}

		auto fighter = mngr_->getHandler(ecs::_hdlr_CAZA);
		render(mngr_->getComponent<Transform>(fighter), mngr_->getComponent<Image>(fighter));

		renderLives(fighter);
	}
		break;
	default:
		break;
	}
}

void RenderSystem::renderLives(ecs::Entity* fighter)
{
	auto health = mngr_->getComponent<Health>(fighter);
	for (int i = 0; i < health->getLives(); i++)
	{
		SDL_Rect dest = build_sdlrect(HEALTH_POS + i * HEALTH_SIZE, HEALTH_POS, HEALTH_SIZE, HEALTH_SIZE);

		assert(health->tex_ != nullptr);
		health->tex_->render(dest);
	}
}

void RenderSystem::render(Transform* tr_, Image* image_)
{
	SDL_Rect dest = build_sdlrect(tr_->pos_, tr_->width_,
		tr_->height_);

	assert(image_->tex_ != nullptr);
	image_->tex_->render(dest, tr_->rot_);
}

void RenderSystem::animation(FramedImage* framedImage_, Transform* tr_)
{
	if (framedImage_->deltatime_ + framedImage_->frameLength_ > sdlutils().currRealTime()) {
		framedImage_->deltatime_ = sdlutils().currRealTime();
		framedImage_->framePositionX_ = (framedImage_->framePositionX_ + 1) % framedImage_->framesX_;
		framedImage_->framePositionY_ = (framedImage_->framePositionY_ + 1) % framedImage_->framesY_;
	}

	SDL_Rect dest = build_sdlrect(tr_->pos_, tr_->width_, tr_->height_);

	// x, y
	// filas, columnas
	Vector2D framePos(framedImage_->framePositionX_ * framedImage_->frameWidth_, framedImage_->framePositionY_ * framedImage_->frameHeight_);

	SDL_Rect src = build_sdlrect(framePos, framedImage_->frameWidth_, framedImage_->frameHeight_);

	assert(framedImage_->tex_ != nullptr);
	framedImage_->tex_->render(src, dest, tr_->rot_);
}

void RenderSystem::showMessage(std::string key)
{
	auto& t = sdlutils().msgs().at(key);
	t.render((sdlutils().width() - t.width()) / 2, sdlutils().height() / 2 + t.height() * 2);
}
