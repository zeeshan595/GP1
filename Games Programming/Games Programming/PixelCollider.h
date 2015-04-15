#ifndef PIXELCOLLIDER_H
#define PIXELCOLLIDER_H

#include "Common.h"
#include "Entity.h"
#include "Collider.h"

//Pixel Collider uses texture to calculate if a pixel is transparent or not. If not it can collide with others
class PixelCollider : public Collider
{
public:
	void Update();

	PixelCollider();
	~PixelCollider();
};

#endif