#pragma once
#include "../ecs/Component.h"

class Transform;

class Follow : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::_FOLLOW)

	Follow(Transform* trFighter);
	virtual ~Follow() {};

	void initComponent() override;
	void update() override;

protected:
	Transform* tr_;
	Transform* trFighter_;
};

