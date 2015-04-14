#pragma once
#include "Common.h"
#include "Entity.h"
#include "Texture.h"

class Button
{
private:
	Entity* HEntity;
	Entity* NEntity;
	Input* input;
	bool Hovering;

public:
	bool IsPressed;
	vec2 Position;
	float Rotation;
	vec2 Scale;
	string text;

	bool Enabled;

	void Update();
	void Render();

	Button(Input* input, Texture* normal, Texture* hover);
	~Button();
};