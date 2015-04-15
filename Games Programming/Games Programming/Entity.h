#ifndef ENTITY_H
#define ENTITY_H

#include "Common.h"
#include "Input.h"

class Module;

//Creates a entity. That will be rendered on the screen
class Entity
{
protected:
	//A way to access the input manager
	Input* input;
	//Modules that will change the entity
	vector<Module*> modules;
	//Childeren that will be attached to the entity
	vector<Entity*> child;
	//Varibles for childeren since there 0,0 will be the parent
	vec2 childOffset;
	float childRotation;

public:
	//Varibles
	vec2 Position;
	float Rotation;
	vec2 Scale;
	//The object won't have physics calculations applied
	bool IsStatic;
	//UV is used to map textures on entity
	vec2 UV[4];
	//pivot offset is used to change 0, 0 of the objects. by defualt it is set to the middle
	vec2 PivotOffset;
	//Is this entity enabled or not
	bool Enabled;

	//Physics
	vec2 Velocity;
	float Torque;
	float Mass;

	//Methods
	//Repeats every 10 miliseconds and all physics calculations are done here
	void FixedUpdate();
	//Add a module to the entity
	void AddModule(Module* m);
	//Add a child to this entity
	void AddChild(Entity* e);
	//Get a child that is attached to this entity
	Entity* GetChild(int i);

	//Virtual
	virtual void Update();
	virtual void Render();

	//Physics
	//Adds force applied to the entity
	void AddForce(vec2 f);
	//Rotates the entity with the torque applied
	void AddTorque(float t);

	//Template Method
	//Gets a module type that is attached to the entity
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

//Modules are used to attach to entity to manepulate them
class Module
{
public:
	//The entity this module is attached to
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