#include "Player2.h"

Player2::Player2(Input* input): Entity(input)
{
	Entity::input = input;
	Speed = 1;
	RotationSpeed = 1;
}


Player2::~Player2()
{

}

void Player2::Update()
{
	if (Entity::input->GetKey(KEYS::I))
	{
		Entity::AddForce(vec2(sin(Rotation * 3.14 / 180) * Speed, -cos(Rotation* 3.14 / 180) * Speed));
	}
	else if (Entity::input->GetKey(KEYS::K))
	{
		Entity::AddForce(vec2(-sin(Rotation * 3.14 / 180) * Speed, cos(Rotation* 3.14 / 180) * Speed));
	}

	if (input->GetKey(KEYS::J))
	{
		Entity::Rotation += -RotationSpeed;
	}
	else if (Entity::input->GetKey(KEYS::L))
	{
		Entity::Rotation += RotationSpeed;
	}
}