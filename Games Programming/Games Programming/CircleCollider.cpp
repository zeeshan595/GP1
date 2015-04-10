#include "CircleCollider.h"


CircleCollider::CircleCollider(vector<Entity*>* e)
{
	Radius = 100;
	entities = e;
}


CircleCollider::~CircleCollider()
{
}

void CircleCollider::Update()
{
	for (Entity* e : *entities)
	{
		CircleCollider* m = e->GetModule<CircleCollider>();
		if (m != NULL)
		{
			if (Distance(e->Position, entity->Position) != 0)
			{
				float dis = Distance(e->Position + offset.x, entity->Position + offset.y);
				if (((Radius / 2) + (m->Radius / 2)) > dis)
				{
					entity->Velocity = vec2((e->Mass * e->Velocity.x) / entity->Mass,(e->Mass * e->Velocity.y) / entity->Mass);
					e->Velocity = vec2((entity->Mass * entity->Velocity.x) / e->Mass,(entity->Mass * entity->Velocity.y) / e->Mass);
					
					vec2 direction = e->Position - entity->Position;
					direction = NormalizeVector(direction);
					entity->Position -= direction;
				}
			}
		}
	}
}

bool CircleCollider::ISColliding()
{
	for (Entity* e : *entities)
	{
		CircleCollider* m = e->GetModule<CircleCollider>();
		if (m != NULL)
		{
			if (Distance(e->Position, entity->Position) != 0)
			{
				float dis = Distance(e->Position + offset.x, entity->Position + offset.y);
				if (((Radius / 2) + (m->Radius / 2)) > dis)
				{
					return true;
				}
			}
		}
	}

	return false;
}

float CircleCollider::Distance(vec2 v1, vec2 v2)
{
	return abs(sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y))));
}

vec2 CircleCollider::NormalizeVector(vec2 v)
{
	float mag = sqrt((v.x * v.x) + (v.y * v.y));
	return vec2(v.x / mag, v.y / mag);
}