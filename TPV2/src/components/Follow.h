#pragma once
#include "../ecs/Component.h"

class Follow : public ecs::Component
{
	__CMPID_DECL__(ecs::_FOLLOW)

		Follow() {};
	virtual ~Follow() {};

	void initComponent() override;
	void update() override;

protected:
	Transform* tr_;
};

