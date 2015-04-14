#include "Bullet.h"

Bullet::Bullet(Input* input): Entity(input)
{
	power = 10;
	bulletTimer = 500;
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	bulletTimer--;
}