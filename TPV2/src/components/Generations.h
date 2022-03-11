#pragma once
#include "../ecs/Component.h"

class Generations : public ecs::Component
{
	__CMPID_DECL__(ecs::_GENERATIONS)

	Generations(unsigned int numGenerations);
	virtual ~Generations() {};

	void initComponent() override;

	unsigned int numGenerations_;

public:
	unsigned int getGenerations();
	void decreaseGenerations();
};

