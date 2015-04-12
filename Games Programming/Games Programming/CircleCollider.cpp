#include "CircleCollider.h"


CircleCollider::CircleCollider()
{
	Radius = 100;
}


CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
	top = entity->Position.y + Radius;
	bottom = entity->Position.y - Radius;
	right = entity->Position.x + Radius;
	left = entity->Position.x - Radius;
}