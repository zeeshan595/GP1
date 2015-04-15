#include "Input.h"


Input::Input()
{
	//Set mouse position to 0, 0
	mousePosition = vec2(0, 0);
}


Input::~Input()
{
}

bool Input::GetKey(KEYS k)
{
	//return if the key is pressed or not
	return keysPressed[k];
}

void Input::SetKey(KEYS k, bool b)
{
	keysPressed[k] = b;
}