#include "Entity.h"


Entity::Entity(Input* input)
{
	Entity::input = input;
	Position = vec2(0, 0);
	Rotation = 0;
	Scale = vec2(10, 10);
	IsStatic = false;
	PivotOffset = vec2(0, 0);
	Velocity = vec2(0, 0);
	Torque = 0;
	Mass = 1;
	childOffset = vec2(0, 0);
	childRotation = 0;
	Enabled = true;
	UV[0] = vec2(0, 0);
	UV[1] = vec2(1, 0);
	UV[2] = vec2(1, 1);
	UV[3] = vec2(0, 1);
}


Entity::~Entity()
{

}

void Entity::Render()
{
	if (Enabled)
	{
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);

		for (Module* m : modules)
		{
			m->Update();
		}

		glTranslatef(Position.x + childOffset.x, Position.y + childOffset.y, 0);
		glRotatef(Rotation + childRotation, 0, 0, 1);
		glTranslatef((-Scale.x / 2) + PivotOffset.x, (-Scale.y / 2) + PivotOffset.y, 0);
		glScalef(Scale.x, Scale.y, 0);

		glBegin(GL_QUADS);
	
		glColor3f(255, 255, 255);
	
		glTexCoord2i(UV[0].x, UV[0].y);
		glVertex2i(0, 0);
	
		glTexCoord2i(UV[1].x, UV[1].y);
		glVertex2i(1, 0);
	
		glTexCoord2i(UV[2].x, UV[2].y);
		glVertex2i(1, 1);
	
		glTexCoord2i(UV[3].x, UV[3].y);
		glVertex2i(0, 1);


		glEnd();

		glDisable(GL_TEXTURE_2D);
		glDisable(GL_BLEND);
		glPopMatrix();

		for (Entity* c : child)
		{
			if (c != NULL)
			{
				c->Render();
			}
		}
	}
}

void Entity::Update(){ }

void Entity::FixedUpdate()
{
	if (Enabled)
	{
		if (!IsStatic)
		{
			Position += Velocity;
			Rotation += Torque;
		}

		for (Entity* c : child)
		{
			if (c != NULL)
			{
				c->childOffset = Position;
				c->childRotation = Rotation;
			}
		}
		Update();
	}
}

void Entity::AddForce(vec2 f)
{
	Velocity += f / Mass;
}

void Entity::AddTorque(float t)
{
	Torque = t / Mass;
}

void Entity::AddModule(Module* m)
{
	modules.push_back(m);
	m->entity = this;
}

void Entity::AddChild(Entity* e)
{
	child.push_back(e);
}

Entity* Entity::GetChild(int i)
{
	return child.at(i);
}