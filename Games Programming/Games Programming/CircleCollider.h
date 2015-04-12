#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include "Common.h"
#include "Entity.h"
#include "BoxCollider.h"
#include "Collider.h"

class CircleCollider: public Collider
{
public:
	float Radius;

	void Update();

	CircleCollider();
	~CircleCollider();
};

#endif