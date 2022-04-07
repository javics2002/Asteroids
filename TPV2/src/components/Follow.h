#pragma once
#include "../ecs/Component.h"

struct Transform;

class Follow : public ecs::Component
{
public:
	__CMPID_DECL__(ecs::_FOLLOW)

	Follow();
	virtual ~Follow() {};

	void initComponent() override;
	void update() override;

protected:
	Transform* tr_;
	Transform* trFighter_;
};

