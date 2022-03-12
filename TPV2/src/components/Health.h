#pragma once
#include "../ecs/Component.h"
#include "../ecs/ecs.h"

class Texture;

class Health : public ecs::Component {
public:

	// This line expands to the following (see the defintion of
	// __CMPID_DECL__ en ecs.h):
	//
	//    constexpr static ecs::cmpId_type id = ecs::_Health
	//
	__CMPID_DECL__(ecs::_HEALTH)

		Health();
	Health(Texture* tex);
	virtual ~Health();

	void setTexture(Texture* tex) {
		tex_ = tex;
	}

	void initComponent() override;
	void render() override;
	void onAsteroidCollision();

protected:
	Texture* tex_;
	
	const int MAX_LIVES = 3;
	int lives = MAX_LIVES;
};


