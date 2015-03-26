#pragma once
#include "Common.h"
class Input;

class Player1 : public Entity
{
public:
	void Update();

	Player1(Input* input);
	~Player1();
};