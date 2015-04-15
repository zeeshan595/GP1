#include "PixelCollider.h"


PixelCollider::PixelCollider()
{

}


PixelCollider::~PixelCollider()
{
}

void PixelCollider::Update()
{
	//Update top, bottom, right & left sides of the collider
	top = entity->Position.y + (entity->Scale.y / 2);
	bottom = entity->Position.y - (entity->Scale.y / 2);
	right = entity->Position.x + (entity->Scale.x / 2);
	left = entity->Position.x - (entity->Scale.x / 2);
}