#pragma once
#include "Common.h"

class Entity
{
private:
	//Variable
	GLuint TextureID;
	vec2 Velocity;
	float Torque;
	bool ClampVelocity;
	bool ClampTorque;

	//Methods
	float Clamp(float c, float min, float max);

public:
	//Variables
	vec2 Position;
	float Rotation;
	vec2 Scale;
	bool Rigidbody;
	vec2 Offset;

	//Methods
	void Update();
	void Render();
	void AddForce(vec2 force);
	void AddTorque(float torque);
	vec2 GetVelocity();
	float GetTorque();
	void SetTexture(GLuint TextureID);

	Entity();
	~Entity();
};