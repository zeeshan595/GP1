#include "PixelCollider.h"


PixelCollider::PixelCollider()
{

}


PixelCollider::~PixelCollider()
{
}

void PixelCollider::Update()
{
	IsColliding();
}

bool PixelCollider::IsColliding()
{
	return false;
}