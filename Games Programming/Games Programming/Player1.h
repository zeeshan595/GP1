#ifndef PLAYER1_H
#define PLAYER1_H

#include "Input.h"
#include "Entity.h"
#include "Texture.h"
#include "CircleCollider.h"

//Creates a player from Entity
class Player1: public Entity
{
public:
	//Used to trake players health
	int Health;
	//How fast does the palyer go
	float Speed;
	//How fast does the player rotate
	float RotationSpeed;

	void Update();

	Player1(Input* input);
	~Player1();
};

#endif