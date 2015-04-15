#include "Player1.h"

Player1::Player1(Input* input): Entity(input)
{
	//set input manager, speed, rotation speed and health of the player
	Entity::input = input;
	Speed = 1;
	RotationSpeed = 1;
	Health = 100;
}


Player1::~Player1()
{

}

void Player1::Update()
{
	//If pressed w move in the direction player is facing
	if (Entity::input->GetKey(KEYS::W))
	{
		Entity::AddForce(vec2(sin(Rotation * 3.14 / 180) * Speed, -cos(Rotation* 3.14 / 180) * Speed));
		child[0]->Enabled = true;
	}
	else if (Entity::input->GetKey(KEYS::S))
	{
		Entity::AddForce(vec2(-sin(Rotation * 3.14 / 180) * Speed, cos(Rotation* 3.14 / 180) * Speed));
		child[0]->Enabled = true;
	}
	else
	{
		child[0]->Enabled = false;
	}

	//Rotate player with A & D
	if (input->GetKey(KEYS::A))
	{
		Entity::Rotation += -RotationSpeed;
	}
	else if (Entity::input->GetKey(KEYS::D))
	{
		Entity::Rotation += RotationSpeed;
	}
}