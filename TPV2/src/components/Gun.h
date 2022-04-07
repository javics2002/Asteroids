#pragma once
#include "../ecs/Component.h"

struct Transform;

class Gun : public ecs::Component {
public:

	// This line expands to the following (see the defintion of
	// __CMPID_DECL__ en ecs.h):
	//
	//    constexpr static ecs::cmpId_type id = ecs::_Gun
	//
	__CMPID_DECL__(ecs::_GUN)

		Gun();
	virtual ~Gun();
	void initComponent() override;
	void update() override;

private:
	Transform* tr_;
	unsigned int lastBulletTime = 0;

	const unsigned int BULLET_CD = 250;
	const float SPEED = 0.5f;
};

