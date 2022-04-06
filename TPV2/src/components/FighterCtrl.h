// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"

class Transform;

class FighterCtrl: public ecs::Component {
public:

	// This line expands to the following (see the defintion of
	// __CMPID_DECL__ en ecs.h):
	//
	//    constexpr static ecs::cmpId_type id = ecs::_FighterCTRL
	//
	__CMPID_DECL__(ecs::_FIGHTERCTRL)

	FighterCtrl();
	virtual ~FighterCtrl();
	void initComponent() override;
	void update() override;
	void move();

private:
	void createStart();
	Transform *tr_;

	const float THRUST = 0.2;
	const float SPEED_LIMIT = 3.0;
};

