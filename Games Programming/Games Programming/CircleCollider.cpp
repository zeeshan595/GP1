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
	ISColliding();
}

bool CircleCollider::ISColliding()
{
	return false;
}