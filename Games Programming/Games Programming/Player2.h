#ifndef PLAYER2_H
#define PLAYER2_H

#include "Input.h"
#include "Entity.h"
#include "Texture.h"

class Player2: public Entity
{
public:
	int Health;
	float Speed;
	float RotationSpeed;

	void Update();

	Player2(Input* input);
	~Player2();
};

#endif