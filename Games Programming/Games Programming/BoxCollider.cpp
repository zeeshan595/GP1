#include "BoxCollider.h"


BoxCollider::BoxCollider(vector<Entity*>* e)
{
	entities = e;
	size = vec2(1, 1);
	offset = vec2(0, 0);
}


BoxCollider::~BoxCollider()
{
}

void BoxCollider::Update()
{
	ISColliding();
}

bool BoxCollider::ISColliding()
{
	for (Entity* e : *entities)
	{
		if (&e != &entity)
		{
			CircleCollider* cCol = e->GetModule<CircleCollider>();
			BoxCollider* bCol = e->GetModule<BoxCollider>();
			if (cCol != NULL)
			{
				if (e->Position.x > entity->Position.x)
				{
					if (e->Position.y > entity->Position.y)
					{
						if (entity->Position.x - size.x < e->Position.x + cCol->Radius)
						{
							entity->Position.x++;
							return true;
						}
						else if (entity->Position.y - size.y < e->Position.y + cCol->Radius)
						{
							entity->Position.y++;
							return true;
						}
					}
					else
					{
						if (entity->Position.x - size.x < e->Position.x + cCol->Radius)
						{
							entity->Position.x++;
							return true;
						}
						else if (entity->Position.y + size.y < e->Position.y - cCol->Radius)
						{
							entity->Position.y--;
							return true;
						}
					}
				}
				else
				{
					if (e->Position.y > entity->Position.y)
					{
						if (entity->Position.x + size.x < e->Position.x - cCol->Radius)
						{
							entity->Position.x--;
							return true;
						}
						else if (entity->Position.y - size.y < e->Position.y + cCol->Radius)
						{
							entity->Position.y++;
							return true;
						}
					}
					else
					{
						if (entity->Position.x + size.x < e->Position.x - cCol->Radius)
						{
							entity->Position.x--;
							return true;
						}
						else if (entity->Position.y + size.y < e->Position.y - cCol->Radius)
						{
							entity->Position.y--;
							return true;
						}
					}
				}
			}
			else if (bCol != NULL)
			{
				if (e->Position.x > entity->Position.x)
				{
					if (e->Position.y > entity->Position.y)
					{
						if (entity->Position.x - size.x < e->Position.x + bCol->size.x)
						{
							entity->Position.x++;
							return true;
						}
						else if (entity->Position.y - size.y < e->Position.y + bCol->size.y)
						{
							entity->Position.y++;
							return true;
						}
					}
					else
					{
						if (entity->Position.x - size.x < e->Position.x + bCol->size.x)
						{
							entity->Position.x++;
							return true;
						}
						else if (entity->Position.y + size.y < e->Position.y - bCol->size.y)
						{
							entity->Position.y--;
							return true;
						}
					}
				}
				else
				{
					if (e->Position.y > entity->Position.y)
					{
						if (entity->Position.x + size.x < e->Position.x - bCol->size.x)
						{
							entity->Position.x--;
							return true;
						}
						else if (entity->Position.y - size.y < e->Position.y + bCol->size.y)
						{
							entity->Position.y++;
							return true;
						}
					}
					else
					{
						if (entity->Position.x + size.x < e->Position.x - bCol->size.x)
						{
							entity->Position.x--;
							return true;
						}
						else if (entity->Position.y + size.y < e->Position.y - bCol->size.y)
						{
							entity->Position.y--;
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

float BoxCollider::Distance(vec2 v1, vec2 v2)
{
	return abs(sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y))));
}

vec2 BoxCollider::NormalizeVector(vec2 v)
{
	float mag = sqrt((v.x * v.x) + (v.y * v.y));
	return vec2(v.x / mag, v.y / mag);
}