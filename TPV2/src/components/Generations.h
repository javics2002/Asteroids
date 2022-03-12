#pragma once
#include "../ecs/Component.h"

class Generations : public ecs::Component
{public:
	__CMPID_DECL__(ecs::_GENERATIONS)

	Generations(unsigned int numGenerations);
	virtual ~Generations() {};

	void initComponent() override;

	unsigned int numGenerations_;


	unsigned int getGenerations();
	void decreaseGenerations();
};

