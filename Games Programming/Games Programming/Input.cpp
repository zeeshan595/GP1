#include "Input.h"


Input::Input()
{
	mousePosition = vec2(0, 0);
}


Input::~Input()
{
}

bool Input::GetKey(KEYS k)
{
	return keysPressed[k];
}

void Input::SetKey(KEYS k, bool b)
{
	keysPressed[k] = b;
}