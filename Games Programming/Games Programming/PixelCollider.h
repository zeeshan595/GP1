#ifndef PIXELCOLLIDER_H
#define PIXELCOLLIDER_H

#include "Common.h"
#include "Entity.h"
#include "Collider.h"

class PixelCollider : public Collider
{
public:
	void Update();

	PixelCollider();
	~PixelCollider();
};

#endif