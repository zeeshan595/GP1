#ifndef PLAYER1_H
#define PLAYER1_H

#include "Input.h"
#include "Entity.h"
#include "Texture.h"
#include "CircleCollider.h"

class Player1: public Entity
{
public:
	int Health;
	float Speed;
	float RotationSpeed;

	void Update();

	Player1(Input* input);
	~Player1();
};

#endif