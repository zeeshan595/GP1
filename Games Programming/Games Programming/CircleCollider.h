#pragma once
#include "Common.h"
#include "Module.h"
#include "Entity.h"

class CircleCollider: public Module
{
private:
	vector<Entity*>* entities;

public:
	float radius;

	void Update();

	CircleCollider(vector<Entity*>* e, Entity* e);
	~CircleCollider();
};