#include "BoxCollider.h"


BoxCollider::BoxCollider()
{
	size = vec2(1, 1);
	offset = vec2(0, 0);
}


BoxCollider::~BoxCollider()
{
}

void BoxCollider::Update()
{
	ISColliding();
}

bool BoxCollider::ISColliding()
{
	return false;
}