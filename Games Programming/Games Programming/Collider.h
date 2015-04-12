#pragma once
#include "Entity.h"

class Collider: public Module
{
public:
	bool colliding;

	float top;
	float bottom;
	float right;
	float left;

	float bounceRatio;

	virtual void Update()
	{

	}
	virtual bool IsColliding()
	{
		return colliding;
	}

	Collider()
	{
		bounceRatio = 0;
		top = 0;
		left = 0;
		right = 0;
		bottom = 0;
	}
	~Collider()
	{

	}
};