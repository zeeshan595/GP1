#ifndef CIRCLECOLLIDER_H
#define CIRCLECOLLIDER_H

#include "Common.h"
#include "Entity.h"
#include "BoxCollider.h"

class CircleCollider: public Module
{
private:
	vector<Entity*>* entities;

public:
	vec2 offset;
	float Radius;

	virtual void Update();
	float Distance(vec2 v1, vec2 v2);
	vec2 NormalizeVector(vec2 v);
	bool ISColliding();

	CircleCollider(vector<Entity*>* e);
	~CircleCollider();
};

#endif