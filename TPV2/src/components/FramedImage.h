#pragma once
#include "../ecs/Component.h"
#include "../utils/Vector2D.h"
#include <SDL.h>

class Transform;
class Texture;

class FramedImage : public ecs::Component
{ 
	const unsigned int FRAME_LENGTH = 50; // In miliseconds
	const unsigned int FRAME_WIDTH = 85; 
	const unsigned int FRAME_HEIGHT = 100; 
	unsigned int deltatime;
	Vector2D framePosition;
	int x = 0, y = 0;
	SDL_Rect scr;
	Transform* tr_;
	Texture* tex_;

public:
	__CMPID_DECL__(ecs::_FRAMEDIMAGE)

	FramedImage(Texture* tex);
	~FramedImage() {};

	void initComponent() override;
	void update() override;
	void render() override;
};

