#include "Player1.h"

void Player1::Update()
{
	if (Entity::input->GetButton(W))
	{
		Entity::AddForce(vec2(sin(Rotation * 3.14 / 180), -cos(Rotation* 3.14 / 180)));
	}
	else if (Entity::input->GetButton(S))
	{
		Entity::AddForce(vec2(-sin(Rotation * 3.14 / 180), cos(Rotation* 3.14 / 180)));
	}

	if (input->GetButton(A))
	{
		Entity::AddTorque(-0.5);
	}
	else if (Entity::input->GetButton(D))
	{
		Entity::AddTorque(0.5);
	}
}

Player1::Player1(Input* input) : Entity(input)
{
	Entity::input = input;
}

Player1::~Player1()
{

}