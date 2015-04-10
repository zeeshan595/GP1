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
	ISColliding();
}

bool CircleCollider::ISColliding()
{
	for (Entity* e : *entities)
	{
		if (&e != &entity)
		{
			CircleCollider* cCol = e->GetModule<CircleCollider>();
			BoxCollider* bCol = e->GetModule<BoxCollider>();
			if (cCol != NULL)
			{
				if (Distance(e->Position, entity->Position) != 0)
				{
					float dis = Distance(e->Position + offset.x, entity->Position + offset.y);
					if (((Radius / 2) + (cCol->Radius / 2)) > dis)
					{
						vec2 direction = e->Position - entity->Position;
						direction = NormalizeVector(direction);
						entity->Position -= direction;
						return true;
					}
				}
			}
			else if (bCol != NULL)
			{
				if (e->Position.x > entity->Position.x)
				{
					if (e->Position.y > entity->Position.y)
					{
						if (e->Position.x - (bCol->size.x / 2) < entity->Position.x + (Radius / 2))
						{
							entity->Position.x--;
							return true;
						}
						else if (e->Position.y - (bCol->size.y / 2) < entity->Position.y + (Radius / 2))
						{
							entity->Position.y--;
							return true;
						}
					}
					else
					{
						if (e->Position.x - (bCol->size.x / 2) < entity->Position.x + (Radius / 2))
						{
							entity->Position.x--;
							return true;
						}
						else if (e->Position.y + (bCol->size.y / 2) > entity->Position.y - (Radius / 2))
						{
							entity->Position.y++;
							return true;
						}
					}
				}
				else
				{
					if (e->Position.y > entity->Position.y)
					{
						if (e->Position.x + (bCol->size.x / 2) < entity->Position.x - (Radius / 2))
						{
							cout << "test" << endl;
							entity->Position.x++;
							return true;
						}
						else if (e->Position.y - (bCol->size.y / 2) < entity->Position.y + (Radius / 2))
						{
							entity->Position.y--;
							return true;
						}
					}
					else
					{
						if (e->Position.x + (bCol->size.x / 2) < entity->Position.x - (Radius / 2))
						{
							entity->Position.x++;
							return true;
						}
						else if (e->Position.y + (bCol->size.y / 2) < entity->Position.y - (Radius / 2))
						{
							entity->Position.y++;
							return true;
						}
					}
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