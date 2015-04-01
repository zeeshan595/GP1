#pragma once
#include "Entity.h"

class Module
{
protected:
	Entity* entity;

public:

	bool Enabled;

	virtual void Update();

	Module(Entity* e);
	~Module();
};