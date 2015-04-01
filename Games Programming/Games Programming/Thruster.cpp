#include "Thruster.h"


Thruster::Thruster(Input* input): Entity(input)
{
	Entity::input = input;
	movment = 0;
}


Thruster::~Thruster(void)
{
}

void Thruster::Update()
{
	Position = vec2(sin(movment) * 1.5, cos(movment * 0.5) * 1.5);

	movment += 0.1;
}
