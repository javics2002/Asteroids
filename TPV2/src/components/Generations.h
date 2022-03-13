#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/SDLUtils.h"

class Generations : public ecs::Component
{public:
	__CMPID_DECL__(ecs::_GENERATIONS)

	Generations(unsigned int numGenerations = sdlutils().rand().nextInt(1, 4));
	virtual ~Generations() {};

	void initComponent() override;

	unsigned int numGenerations_;


	unsigned int getGenerations();
	void decreaseGenerations();
};

