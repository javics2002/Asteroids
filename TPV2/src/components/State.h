#pragma once
#include "../ecs/Component.h"

class State : public ecs::Component
{



public:
	__CMPID_DECL__(ecs::_STATE)

	enum Estados { NEWGAME, PAUSED, RUNNING, GAMEOVER };
	Estados state;

	State();
	~State();

	void initComponent() override;
	void update() override;
	void render() override;
};

