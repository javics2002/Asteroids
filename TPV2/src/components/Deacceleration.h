#pragma once
#include "../ecs/Component.h"

struct Transform;

class Deacceleration : public ecs::Component {
public:

	// This line expands to the following (see the defintion of
	// __CMPID_DECL__ en ecs.h):
	//
	//    constexpr static ecs::cmpId_type id = ecs::_Deacceleration
	//
	__CMPID_DECL__(ecs::_DEACCELERATION)

		Deacceleration();
	virtual ~Deacceleration();
	void initComponent() override;
	void update() override;

private:
	void createStart();
	Transform* tr_;

	const float DEACC = 0.995f;
};

