#pragma once
#include "Common.h"
#include "Input.h"
#include "Module.h"
#include "Texture.h"

class Entity
{
protected:
	Input* input;
	vector<Module*> modules;

public:
	//Varibles
	vec2 Position;
	float Rotation;
	vec2 Scale;
	bool IsStatic;

	vec2 PivotOffset;

	//Physics
	vec2 Velocity;
	float Torque;
	float Mass;

	//Methods
	void Render();
	void FixedUpdate();
	void AddModule(Module* m);

	//Virtual
	virtual void Update();

	//Physics
	void AddForce(vec2 f);
	void AddTorque(float t);

	Entity(Input* input);
	~Entity();
};