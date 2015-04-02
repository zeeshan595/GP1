#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include "Common.h"
#include "Entity.h"

class CircleCollider: public Module
{
private:
	vector<Entity*>* entities;

public:
	float Radius;

	void Update();
	float Distance(vec2 v1, vec2 v2);

	CircleCollider(vector<Entity*>* e);
	~CircleCollider();
};

#endif