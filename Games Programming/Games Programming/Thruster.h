#pragma once
#include "Entity.h"
#include "Input.h"

class Thruster : public Entity
{
private:
	double movment;

public:
	void Update();

	Thruster(Input* input);
	~Thruster();
};