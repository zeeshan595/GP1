#include "Entity.h"

//Constructor
Entity::Entity()
{
	Position = vec2(0, 0);
	Rotation = 0;
	Scale = vec2(1, 1);
	Velocity = vec2(0, 0);
	Torque = 0;
	Rigidbody = false;
}

//Deconstructor
Entity::~Entity()
{

}

void Entity::Update()
{
	if (Rigidbody)
	{
		Position += Velocity;
		Rotation += Torque;
	}
	
	//if (input->GetButton(W))
	//{
	//	AddForce(vec2(sin(Rotation * 3.14 / 180), -cos(Rotation* 3.14 / 180)));
	//}
}

void Entity::AddForce(vec2 Force)
{
	Velocity += Force;
	
	if (ClampVelocity)
	{
		Velocity.x = Clamp(Velocity.x, -1, 1);
		Velocity.y = Clamp(Velocity.y, -1, 1);
	}
}

void Entity::AddTorque(float Torque)
{
	Entity::Torque += Torque;
	if (ClampVelocity)
	{
		Entity::Torque = Clamp(Entity::Torque, -5, 5);
	}
}

float Entity::GetTorque()
{
	return Torque;
}

vec2 Entity::GetVelocity()
{
	return Velocity;
}

float Entity::Clamp(float c, float min, float max)
{
	float rtn = c;

	if (rtn > max)
	{
		rtn = max;
	}
	else if (rtn < min)
	{
		rtn = min;
	}

	return rtn;
}

void Entity::Render()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindTexture(GL_TEXTURE_2D, TextureID);


	glTranslatef(Position.x, Position.y, 0);
	glRotatef(Rotation, 0, 0, 1);
	glTranslatef((-Scale.x / 2) + Offset.x, (-Scale.y / 2) + Offset.y, 0);
	glScalef(Scale.x, Scale.y, 0);

	glBegin(GL_QUADS);
	
	glColor3f(255, 255, 255);
	
	glTexCoord2i(0 , 0);
	glVertex2i(0, 0);
	
	glTexCoord2i(1, 0);
	glVertex2i(1, 0);
	
	glTexCoord2i(1, 1);
	glVertex2i(1, 1);
	
	glTexCoord2i(0, 1);
	glVertex2i(0, 1);


	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Entity::SetTexture(GLuint TextureID)  // set the image of the sprite
{
	Entity::TextureID = TextureID;
}