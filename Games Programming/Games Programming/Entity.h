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
	vec2 childOffset;
	float childRotation;
	Entity* child;

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
	Module* GetModule(const type_info &i);
	void SetChild(Entity* e);
	Entity* GetChild();

	//Virtual
	virtual void Update();

	//Physics
	void AddForce(vec2 f);
	void AddTorque(float t);

	Entity(Input* input);
	~Entity();
};