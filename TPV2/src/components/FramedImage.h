#pragma once

#include "Image.h"
#include <SDL.h>
#include "../utils/Vector2D.h"

class FramedImage : Image
{ 
	const Uint32 FRAME_LENGTH = 50; // In miliseconds
	Uint32 deltatime;
	Vector2D framePosition;
	int x = 0, y = 0;
	SDL_Rect scr;

public:
	__CMPID_DECL__(ecs::_FRAMEDIMAGE)

	FramedImage(Texture* tex);
	~FramedImage() {};

	void update() override;
	void render() override;
};

