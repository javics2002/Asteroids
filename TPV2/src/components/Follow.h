#pragma once
#include "../ecs/Component.h"

struct Transform;

struct Follow : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::_FOLLOW)

	Follow();
	virtual ~Follow() {};
};

