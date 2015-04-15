#ifndef INPUT_H
#define INPUT_H

#include "Common.h"
#include "KEYS.h"

//Input manager handles all keys being pressed
class Input
{
private:
	//maps the keys with a boolean weather if the button is pressed or not
	map<KEYS , bool> keysPressed;

public:
	//Store mouse position
	vec2 mousePosition;

	//Get Key, returns if its being pressed or not
	bool GetKey(KEYS k);

	//Map a key
	void SetKey(KEYS k, bool b);

	Input();
	~Input();
};

#endif