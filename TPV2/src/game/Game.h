// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>

namespace ecs {
class Manager;
class Entity;
}
class AsteroidsSystem;
class FighterSystem;
class FighterGunSystem;
class BulletsSystem;
class RenderSystem;
class GameCtrlSystem;
class CollisionsSystem;

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();
private:
	void updateSystems();

	ecs::Manager *mngr_;

	AsteroidsSystem* asteroidsSys_;
	FighterSystem* fighterSys_;
	FighterGunSystem* fighterGunSys_;
	BulletsSystem* bulletsSys_;
	GameCtrlSystem* gameCtrlSys_;
	RenderSystem* renderSys_;
	CollisionsSystem* collisionsSys_;
};

