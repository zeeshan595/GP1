#pragma once
#include "Common.h"

class Input
{
private:
	map<KEYS, bool> keysPressed;

public:
	void SetButtonState(KEYS k, bool b);
	bool GetButton(KEYS key);

	Input();
	~Input();
};