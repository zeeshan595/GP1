#ifndef PLAYER2_H
#define PLAYER2_H

#include "Input.h"
#include "Entity.h"
#include "Texture.h"

//Creates a player from Entity
class Player2: public Entity
{
public:
	//Used to trake players health
	int Health;
	//How fast does the palyer go
	float Speed;
	//How fast does the player rotate
	float RotationSpeed;

	void Update();

	Player2(Input* input);
	~Player2();
};

#endif