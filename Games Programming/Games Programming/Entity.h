#ifndef ENTITY_H
#define ENTITY_H

#include "Common.h"
#include "Input.h"

class Module;

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
	vec2 textCords[4];

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

class Module
{
public:
	Entity* entity;

	bool Enabled;

	virtual void Update()
	{

	}

	Module()
	{
		Enabled = true;
	}
	~Module()
	{

	}
};

#endif