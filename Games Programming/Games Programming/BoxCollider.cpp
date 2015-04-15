#include "BoxCollider.h"


BoxCollider::BoxCollider()
{
	size = vec2(1, 1);
}


BoxCollider::~BoxCollider()
{
}

void BoxCollider::Update()
{
	//Update top, bottom, right & left sides of the collider
	top = entity->Position.y + (size.y / 2);
	bottom = entity->Position.y - (size.y / 2);
	right = entity->Position.x + (size.x / 2);
	left = entity->Position.x - (size.x / 2);
}