#pragma once
#include "../ecs/Component.h"
#include "../ecs/ecs.h"

#define HEALTH_SIZE 25	
#define HEALTH_POS 20

class Texture;

struct Health : public ecs::Component {
public:

	// This line expands to the following (see the defintion of
	// __CMPID_DECL__ en ecs.h):
	//
	//    constexpr static ecs::cmpId_type id = ecs::_Health
	//
	__CMPID_DECL__(ecs::_HEALTH)

	Health() { tex_ = nullptr; };
	Health(Texture* tex) { setTexture(tex); };
	~Health() {};

	void setTexture(Texture* tex) {
		tex_ = tex;
	}

	int getLives() { return lives; };

	void resetLives() { lives = MAX_LIVES; };

	void onAsteroidCollision()
	{
		if (lives > 0)
			lives--;
	}

	Texture* tex_;

protected:
	
	const int MAX_LIVES = 3;
	int lives = MAX_LIVES;
};


