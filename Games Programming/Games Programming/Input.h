#pragma once
#include "Common.h"
#include "KEYS.h"

class Input
{
private:
	map<KEYS , bool> keysPressed;

public:
	vec2 mousePosition;

	bool GetKey(KEYS k);

	void SetKey(KEYS k, bool b);

	Input();
	~Input();
};