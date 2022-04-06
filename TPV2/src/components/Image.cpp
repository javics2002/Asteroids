// This file is part of the course TPV2@UCM - Samir Genaim

#include "Image.h"

#include <cassert>

#include "../ecs/Entity.h"
#include "../sdlutils/macros.h"
#include "../sdlutils/Texture.h"
#include "Transform.h"
#include "../ecs/Manager.h"

Image::Image() :
		tr_(), tex_() {
}

Image::Image(Texture *tex) :
		tr_(), tex_(tex) {
}

Image::~Image() {
}

void Image::initComponent() {
	tr_ = mngr_->getComponent<Transform>(ent_);
	assert(tr_ != nullptr);
}

void Image::render() {

	SDL_Rect dest = build_sdlrect(tr_->pos_, tr_->width_,
			tr_->height_);

	assert(tex_ != nullptr);
	tex_->render(dest, tr_->rot_);
}
