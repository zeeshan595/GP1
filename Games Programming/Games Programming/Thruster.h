#ifndef THRUSTER_H
#define THRUSTER_H

#include "Entity.h"
#include "Input.h"

//Thrusters that will be childeren of players
class Thruster : public Entity
{
private:
	double movment;

public:
	void Update();

	Thruster(Input* input);
	~Thruster();
};

#endif