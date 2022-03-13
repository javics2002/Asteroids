// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"

class GameState;
class AsteroidsManager;

class GameCtrl: public ecs::Component {
public:

	__CMPID_DECL__(ecs::_GAMECTRL)

	GameCtrl(AsteroidsManager* aMngr);
	virtual ~GameCtrl();

	void initComponent() override;
	void update() override;

private:
	GameState* currentState_;

	AsteroidsManager* aMngr_;
};

