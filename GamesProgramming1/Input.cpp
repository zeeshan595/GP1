#include "Input.h"


Input::Input()
{

}


Input::~Input()
{
}

void Input::SetButtonState(KEYS k, bool b)
{
	keysPressed[k] = b;
}

bool Input::GetButton(KEYS k)
{
	return keysPressed[k];
}