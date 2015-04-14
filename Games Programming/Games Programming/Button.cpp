#include "Button.h"


Button::Button(Input* i, Texture* normal, Texture* hover)
{
	Hovering = false;
	Enabled = true;
	IsPressed = false;
	Position = vec2(0, 0);
	Rotation = 0;
	Scale = vec2(100 , 100);

	input = i;

	NEntity = new Entity(input);
	NEntity->AddModule(normal);

	HEntity = new Entity(input);
	HEntity->AddModule(hover);
}


Button::~Button()
{
}

void Button::Render()
{
	if (Enabled)
	{
		if (input->mousePosition.x > Position.x - (Scale.x / 2) && input->mousePosition.x < Position.x + (Scale.x / 2) && input->mousePosition.y > Position.y - (Scale.y / 2) && input->mousePosition.y < Position.y + (Scale.y / 2))
		{
			Hovering = true;
			if (input->GetKey(KEYS::MouseLeft))
			{
				IsPressed = true;
			}
			else
				IsPressed = false;
		}
		else
		{
			Hovering = false;
			IsPressed = false;
		}

		HEntity->Position = Position;
		HEntity->Rotation = Rotation;
		HEntity->Scale = Scale;

		NEntity->Position = Position;
		NEntity->Rotation = Rotation;
		NEntity->Scale = Scale;

		if (Hovering)
		{
			HEntity->Render();
		}
		else
		{
			NEntity->Render();
		}
	}
}