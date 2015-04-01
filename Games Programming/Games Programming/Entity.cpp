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
	child = NULL;
}


Entity::~Entity()
{

}

void Entity::Render()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	
	vec2 textCords[4] = { vec2(0, 0), vec2(1, 0), vec2(1, 1), vec2(0, 1) };

	for (Module* m : modules)
	{
		m->Update();

		if (m->Enabled && typeid(&m) == typeid(Texture))
		{
			Texture* t = (Texture*)m;
			textCords[0] = t->textCords[0];
			textCords[1] = t->textCords[1];
			textCords[2] = t->textCords[2];
			textCords[3] = t->textCords[3];
		}
	}

	glTranslatef(Position.x + childOffset.x, Position.y + childOffset.y, 0);
	glRotatef(Rotation + childRotation, 0, 0, 1);
	glTranslatef((-Scale.x / 2) + PivotOffset.x, (-Scale.y / 2) + PivotOffset.y, 0);
	glScalef(Scale.x, Scale.y, 0);

	glBegin(GL_QUADS);
	
	glColor3f(255, 255, 255);
	
	glTexCoord2i(textCords[0].x, textCords[0].y);
	glVertex2i(0, 0);
	
	glTexCoord2i(textCords[1].x, textCords[1].y);
	glVertex2i(1, 0);
	
	glTexCoord2i(textCords[2].x, textCords[2].y);
	glVertex2i(1, 1);
	
	glTexCoord2i(textCords[3].x, textCords[3].y);
	glVertex2i(0, 1);


	glEnd();

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	Update();
}

void Entity::Update(){ }

void Entity::FixedUpdate()
{
	if (!IsStatic)
	{
		Position += Velocity;
		Rotation += Torque;
	}

	if (child != NULL)
	{
		child->childOffset = Position;
		child->childRotation = Rotation;
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
}

Module* Entity::GetModule(const type_info &i)
{
	for (Module* m : modules)
	{
		if (typeid(&m) == i)
		{
			return m;
		}
	}

	return NULL;
}

void Entity::SetChild(Entity* e)
{
	child = e;
}

Entity* Entity::GetChild()
{
	return child;
}