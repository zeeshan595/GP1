#pragma once
#include "Common.h"
#include "Entity.h"
#include "Texture.h"

//Create a button
class Button
{
private:
	//Hover Entity
	Entity* HEntity;
	//Normal Entity
	Entity* NEntity;
	//input manager
	Input* input;
	//Is mouse over button
	bool Hovering;

public:
	//Button is pressed
	bool IsPressed;
	vec2 Position;
	float Rotation;
	vec2 Scale;

	bool Enabled;

	void Update();
	void Render();

	Button(Input* input, Texture* normal, Texture* hover);
	~Button();
};