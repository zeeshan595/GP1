#include "Player2.h"

Player2::Player2(Input* input): Entity(input)
{
	Entity::input = input;
	Speed = 1;
	RotationSpeed = 1;
	Health = 100;
}


Player2::~Player2()
{

}

void Player2::Update()
{
	//If pressed w move in the direction player is facing
	if (Entity::input->GetKey(KEYS::I))
	{
		Entity::AddForce(vec2(sin(Rotation * 3.14 / 180) * Speed, -cos(Rotation* 3.14 / 180) * Speed));
		child[0]->Enabled = true;
	}
	else if (Entity::input->GetKey(KEYS::K))
	{
		Entity::AddForce(vec2(-sin(Rotation * 3.14 / 180) * Speed, cos(Rotation* 3.14 / 180) * Speed));
		child[0]->Enabled = true;
	}
	else
	{
		child[0]->Enabled = false;
	}

	//Rotate player with A & D
	if (input->GetKey(KEYS::J))
	{
		Entity::Rotation += -RotationSpeed;
	}
	else if (Entity::input->GetKey(KEYS::L))
	{
		Entity::Rotation += RotationSpeed;
	}
}