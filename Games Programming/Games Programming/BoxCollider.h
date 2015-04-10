#ifndef BOXCOLLIDER_H
#define BOXCOLLIDER_H

#include "Common.h"
#include "Entity.h"
#include "CircleCollider.h"

class BoxCollider: public Module
{
private:
	vector<Entity*>* entities;

public:
	vec2 offset;
	vec2 size;

	bool ISColliding();
	float Distance(vec2 v1, vec2 v2);
	vec2 NormalizeVector(vec2 v);
	void Update();

	BoxCollider(vector<Entity*>* e);
	~BoxCollider();
};

#endif