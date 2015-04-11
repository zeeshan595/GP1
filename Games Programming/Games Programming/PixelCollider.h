#ifndef PIXELCOLLIDER_H
#define PIXELCOLLIDER_H

#include "Common.h"
#include "Entity.h"

class PixelCollider : Module
{
public:
	void Update();

	bool IsColliding();

	PixelCollider();
	~PixelCollider();
};

#endif