#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <SDL.h>

struct Transform;
class Texture;

class FramedImage : public ecs::Component
{ 
	unsigned int frameLength_; // In miliseconds
	unsigned int frameWidth_; 
	unsigned int frameHeight_; 
	unsigned int framesX_, framesY_;
	unsigned int deltatime_;
	Vector2D framePosition_;
	Transform* tr_;
	Texture* tex_;

public:
	__CMPID_DECL__(ecs::_FRAMEDIMAGE)

	FramedImage(Texture* tex, unsigned int width, unsigned int height, 
		unsigned int framesX, unsigned int framesY, unsigned int frameLength);
	~FramedImage() {};

	void initComponent() override;
	void update() override;
	void render() override;
};

