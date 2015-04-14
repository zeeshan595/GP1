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
	vector<Entity*> child;
	vec2 childOffset;
	float childRotation;

public:
	//Varibles
	vec2 Position;
	float Rotation;
	vec2 Scale;
	bool IsStatic;
	vec2 UV[4];
	vec2 PivotOffset;
	bool Enabled;

	//Physics
	vec2 Velocity;
	float Torque;
	float Mass;

	//Methods
	virtual void Render();
	void FixedUpdate();
	void AddModule(Module* m);
	void AddChild(Entity* e);
	Entity* GetChild(int i);

	//Virtual
	virtual void Update();

	//Physics
	void AddForce(vec2 f);
	void AddTorque(float t);

	//Template Method
	template <typename T>
	T* GetModule()
	{
		for (Module* m :modules)
		{
			if (dynamic_cast<T*>(m) != NULL)
			{
				return dynamic_cast<T*>(m);
			}
		}
		return NULL;
	}

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