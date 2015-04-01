#include "CircleCollider.h"


CircleCollider::CircleCollider(vector<Entity*>* es, Entity* e): Module(e)
{
	entities = es;
	entity = e;
}


CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
	for (Entity* e : *entities)
	{
		CircleCollider* m = static_cast<CircleCollider*>(e->GetModule(typeid(CircleCollider)));
		if (m != NULL)
		{
			if ((radius + m->radius) < Distance(e->Position, entity->Position))
			{
				vec2 totalVelocity = e->Velocity + entity->Velocity;
				float totalMass = e->Mass + entity->Mass;
				vec2 momentum = vec2(totalVelocity.x / totalMass, totalVelocity.y / totalMass);
				entity->Velocity.x = momentum.x * entity->Mass;
				entity->Velocity.y = momentum.y * entity->Mass;
			}
		}
	}
}

float Distance(vec2 v1, vec2 v2)
{
	return sqrt(((v2.x * v2.x) - (v1.x * v1.x)) + ((v2.y * v2.y) - (v1.y * v1.y)));
}