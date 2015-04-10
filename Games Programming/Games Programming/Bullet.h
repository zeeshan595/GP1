#pragma once
#include "Common.h"
#include "Entity.h"
#include "CircleCollider.h"

class Bullet: public Entity
{
public:
	int power;

	void Update();

	Bullet(Input* input);
	~Bullet();
};
