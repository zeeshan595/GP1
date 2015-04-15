#include "Bullet.h"

Bullet::Bullet(Input* input): Entity(input)
{
	//Set bullet timer and power
	power = 10;
	bulletTimer = 500;
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	//Count down the timer by 1
	bulletTimer--;
}