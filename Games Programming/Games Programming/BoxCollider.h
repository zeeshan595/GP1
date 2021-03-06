#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Common.h"
#include "Entity.h"
#include "CircleCollider.h"
#include "Collider.h"


//Makes a box collider
class BoxCollider: public Collider
{
public:
	vec2 size;

	void Update();

	BoxCollider();
	~BoxCollider();
};

#endif