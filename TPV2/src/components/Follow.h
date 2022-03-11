#pragma once
#include "../ecs/Component.h"

class Transfrom;

class Follow : public ecs::Component
{
	__CMPID_DECL__(ecs::_FOLLOW)

	Follow(Transform* trFighter);
	virtual ~Follow() {};

	void initComponent() override;
	void update() override;

protected:
	Transform* tr_;
	Transform* trFighter_;
};

