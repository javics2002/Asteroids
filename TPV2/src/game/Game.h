// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <vector>

namespace ecs {
class Manager;
class Entity;
}
class AsteroidsManager;

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();
private:
	void checkCollisions();
	ecs::Manager *mngr_;
	AsteroidsManager* aManager_;
	ecs::Entity* gameController_;
};

