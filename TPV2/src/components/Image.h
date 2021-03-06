// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

struct Transform;
class Texture;

struct Image: public ecs::Component {
public:

	// This line expands to the following (see the defintion of
	// __CMPID_DECL__ en ecs.h):
	//
	//    constexpr static ecs::cmpId_type id = ecs::_IMAGE
	//
	__CMPID_DECL__(ecs::_IMAGE)

	Image();
	Image(Texture *tex);
	virtual ~Image();

	void setTexture(Texture *tex) {
		tex_ = tex;
	}

	Texture *tex_;
};

