#include "Common.h"
#include "Input.h"
#include "Texture.h"
#include "CircleCollider.h"
#include "BoxCollider.h"
#include "PixelCollider.h"
#include "Entity.h"
#include "Player1.h"
#include "Player2.h"
#include "Bullet.h"
#include "Thruster.h"
#include "AudioClip.h"

//Public Varibles
vector<Entity*> background;
vector<Entity*> entities;
Input* input;
float cameraSize = 1;
int WINDOW_WIDTH = 1600;
int WINDOW_HEIGHT = 1200;

//Open GL Methods
void Reshape(int w, int h);
void Render();
void Update(int i);
void KeyboardUp(unsigned char k, int x, int y);
void KeyboardDown(unsigned char k, int x, int y);
void SetupPlayers();
void SetupLevel();
void CalculateCollision();

int main(int argc, char **argv)
{
	//Initialize Glut
	glutInit(&argc, argv);

	//Initialize Core
	input = new Input();

	//setup some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);

	//Setup Glut Window
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("2D Fight");

	//Create Game
	SetupLevel();

	//Setup OpenGL Methods
	glutReshapeFunc(Reshape);
	glutDisplayFunc(Render);
	glutTimerFunc( 10 , Update, 0);
	glutKeyboardUpFunc(KeyboardUp);
	glutKeyboardFunc(KeyboardDown);

	//Very important! This initializes the entry point in the OpenGL driver so we can 
	//call the functions in the api
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "GLEW error");
		return 1;
	}

	//Start up a loop that runs in the background
	glutMainLoop();
	return 0;
}

void SetupLevel()
{
	SetupPlayers();
	//Player Background Music
	AudioClip* c = new AudioClip("Audio/Music.wav", "Music");
	//c->Play();

	//Generate Level
	int LEVEL_WIDTH = 10000;
	int LEVEL_HEIGHT = 10000;

	//Create Background
	Texture* bck_T1 = new Texture("Images/Background1.png");
	Texture* bck_T2 = new Texture("Images/Background2.png");

	Entity* bck = new Entity(input);
	bck->AddModule(bck_T2);
	bck->Scale = vec2(LEVEL_WIDTH, LEVEL_HEIGHT);
	bck->Position = vec2(0, 0);
	
	background.push_back(bck);

	//Add detail to background
	srand(static_cast<int>(time(NULL)));
	int rnd1 = clamp(rand() % 500, 250, 500);

	for (int i = 0; i < rnd1; i++)
	{
		int x = rand() % 10000;
		int y = rand() % 10000;
		int size = rand() % 500;

		Entity* bck2 = new Entity(input);
		bck2->AddModule(bck_T1);
		bck2->Scale = vec2(size, size);
		bck2->Position = vec2(x - 5000, y - 5000);

		background.push_back(bck2);
	}

	//Create Boundries
	BoxCollider* tallBox = new BoxCollider();
	tallBox->size = vec2(100, 10000);
	tallBox->bounceRatio = 0.5;

	BoxCollider* wideBox = new BoxCollider();
	tallBox->size = vec2(10000, 100);
	tallBox->bounceRatio = 0.5;

	Entity* borderLeft = new Entity(input);
	borderLeft->IsStatic = true;
	borderLeft->AddModule(tallBox);
	borderLeft->Scale = vec2(100, 10000);
	borderLeft->Position = vec2(-5050, 0);
	entities.push_back(borderLeft);

	Entity* borderRight = new Entity(input);
	borderRight->IsStatic = true;
	borderRight->AddModule(tallBox);
	borderRight->Scale = vec2(100, 10000);
	borderRight->Position = vec2(5050, 0);
	entities.push_back(borderRight);

	Entity* boderTop = new Entity(input);
	boderTop->IsStatic = true;
	boderTop->AddModule(wideBox);
	boderTop->Scale = vec2(10000, 100);
	boderTop->Position = vec2(0, -5050);
	entities.push_back(boderTop);

	Entity* borderBottom = new Entity(input);
	borderLeft->IsStatic = true;
	borderLeft->AddModule(wideBox);
	borderLeft->Scale = vec2(10000, 100);
	borderLeft->Position = vec2(0, 5050);
	entities.push_back(borderLeft);

	//Add objects
}

void SetupPlayers()
{
	//Main Players
	Player1* p1 = new Player1(input);
	Texture* t1 = new Texture("Images/Ship1.png");
	CircleCollider* c1 = new CircleCollider();
	c1->Radius = 100;
	p1->AddModule(c1);
	p1->AddModule(t1);
	p1->Scale = vec2(100, 100);
	p1->Position = vec2(-500, -500);
	p1->Mass = 50;
	p1->Rotation = 135;
	entities.push_back(p1);

	Player2* p2 = new Player2(input);
	Texture* t2 = new Texture("Images/Ship2.png");
	CircleCollider* c2 = new CircleCollider();
	c2->Radius = 100;
	p2->AddModule(c2);
	p2->AddModule(t2);
	p2->Scale = vec2(100, 100);
	p2->Position = vec2(500, 500);
	p2->Mass = 50;
	p2->Rotation = -45;
	entities.push_back(p2);

	//Health Bars
	Texture* healthTexture = new Texture("Images/health.png");

	Entity* h1 = new Entity(input);
	h1->AddModule(healthTexture);
	h1->Scale = vec2(100, 10);
	h1-> Position = entities[0]->Position + vec2(0, -100);
	entities.push_back(h1);

	Entity* h2 = new Entity(input);
	h2->AddModule(healthTexture);
	h2->Scale = vec2(100, 10);
	h2-> Position = entities[1]->Position + vec2(0, -100);
	entities.push_back(h2);

	//Extra's
	Thruster* p1_T = new Thruster(input);
	Texture* t1_T = new Texture("Images/Ship1_Thruster.png");
	p1_T->AddModule(t1_T);
	p1_T->Scale = vec2(100, 46);
	p1_T->PivotOffset = vec2(0, 65);

	p1->AddChild(p1_T);
	

	Thruster* p2_T = new Thruster(input);
	Texture* t2_T = new Texture("Images/Ship2_Thruster.png");
	p2_T->AddModule(t2_T);
	p2_T->Scale = vec2(100, 46);
	p2_T->PivotOffset = vec2(0, 60);

	p2->AddChild(p2_T);
}

void Reshape(int w, int h)
{
	WINDOW_WIDTH = w;
	WINDOW_HEIGHT = h;

	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, w, h, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//Change camera position to  be in the center of the 2 players
	vec2 CamereaPosition = (entities[0]->Position + entities[1]->Position);
	CamereaPosition = CamereaPosition * 0.5f;
	glTranslatef(static_cast<GLfloat>(WINDOW_WIDTH / 2),static_cast<GLfloat>(WINDOW_HEIGHT / 2), 0);

	//Scale depending on how far the 2 space ships are
	cameraSize = glm::distance(entities[0]->Position, entities[1]->Position);
	cameraSize = 1 / (cameraSize / 1000);
	cameraSize = glm::clamp(cameraSize, 0.5f, 5.0f);
	glScalef(cameraSize, cameraSize, 0);
	//Change the position so we can scale from the center of the screen
	glTranslatef(-CamereaPosition.x, -CamereaPosition.y, 0);

	//Make sure we render background first
	//for (list<Entity>::iterator iter=entities.begin();iter!=entities.end();++iter)
	for (Entity* e : background)
	{
		e->Render();
	}
	for (Entity* e : entities)
	{
		e->Render();
	}

	glutSwapBuffers();
}
	
void Update(int i)
{
	//Make health bars apear on top of the players
	entities[2]->Scale = vec2(static_cast<Player1*>(entities[0])->Health, 10);
	entities[2]-> Position = entities[0]->Position + vec2(0, -100);

	entities[3]->Scale = vec2(static_cast<Player1*>(entities[1])->Health, 10);
	entities[3]-> Position = entities[1]->Position + vec2(0, -100);

	//If Q or P is pressed shoot
	if (input->GetKey(KEYS::Q))
	{
		CircleCollider* c = new CircleCollider();
		Texture* t = new Texture("Images/Rocket.png");

		Bullet* bullet = new Bullet(input);
		bullet->AddModule(t);
		bullet->AddModule(c);
		bullet->Position = entities[0]->Position + vec2(sin(entities[0]->Rotation * 3.14 / 180) * 150, -cos(entities[0]->Rotation* 3.14 / 180) * 150);
		bullet->Scale = vec2(20, 76);
		bullet->Rotation = entities[0]->Rotation;
		bullet->AddForce(vec2(sin(entities[0]->Rotation * 3.14 / 180) * 5, -cos(entities[0]->Rotation* 3.14 / 180) * 5));
		bullet->Mass = 10;
		entities.push_back(bullet);
	}

	//If Q or P is pressed shoot
	if (input->GetKey(KEYS::N))
	{
		CircleCollider* c = new CircleCollider();
		Texture* t = new Texture("Images/Rocket.png");

		Bullet* bullet = new Bullet(input);
		bullet->AddModule(t);
		bullet->AddModule(c);
		bullet->Position = entities[1]->Position + vec2(sin(entities[1]->Rotation * 3.14 / 180) * 150, -cos(entities[1]->Rotation* 3.14 / 180) * 150);
		bullet->Scale = vec2(20, 76);
		bullet->Rotation = entities[1]->Rotation;
		bullet->AddForce(vec2(sin(entities[1]->Rotation * 3.14 / 180) * 5, -cos(entities[1]->Rotation* 3.14 / 180) * 5));
		bullet->Mass = 10;
		entities.push_back(bullet);
	}

	CalculateCollision();

	for (Entity* e : entities)
	{
		e->FixedUpdate();
	}

	// Reset timer
	glutTimerFunc( 10, Update, 0);
	//Update the display
	glutPostRedisplay();
}

void KeyboardUp(unsigned char k, int x, int y)
{
	input->SetKey((KEYS)((int)toupper(k)), false);
}

void KeyboardDown(unsigned char k, int x, int y)
{
	input->SetKey((KEYS)((int)toupper(k)), true);
}

#pragma region

bool CircleCollision(CircleCollider* collider, CircleCollider* cCol2, PixelCollider* pCol2, BoxCollider* bCol2, vec2* point)
{
	if (cCol2 != NULL)
	{
		if (((collider->Radius / 2) + (cCol2->Radius / 2)) > glm::distance(collider->entity->Position, cCol2->entity->Position))
		{
			point->x = (collider->entity->Position.x + cCol2->entity->Position.x) / 2.0f;
			point->y = (collider->entity->Position.y + cCol2->entity->Position.y) / 2.0f;
			return true;
		}

	}
	else if (pCol2 != NULL)
	{
		//PIXEL COLLISION
	}
	else if (bCol2 != NULL)
	{
		if (glm::abs(bCol2->top - collider->entity->Position.y) <= collider->Radius / 2)
		{
			point->x = collider->entity->Position.x;
			point->y = bCol2->top;
			return true;
		}
		else if (glm::abs(bCol2->bottom - collider->entity->Position.y) <= collider->Radius / 2)
		{
			point->x = collider->entity->Position.x;
			point->y = bCol2->bottom;
			return true;
		}
		else if (glm::abs(bCol2->right - collider->entity->Position.x) <= collider->Radius / 2)
		{
			point->x = bCol2->right;
			point->y = collider->entity->Position.y;
			return true;
		}
		else if (glm::abs(bCol2->left - collider->entity->Position.x) <= collider->Radius / 2)
		{
			point->x = bCol2->left;
			point->y = collider->entity->Position.y;
			return true;
		}
	}
	else
	{
		cout << "--ERROR CALCULATING COLLISION (entity)--" << endl;
		return false;
	}

	return false;
}

bool BoxCollision(BoxCollider* collider, CircleCollider* cCol2, PixelCollider* pCol2, BoxCollider* bCol2)
{
	if (cCol2 != NULL)
	{
		if (glm::abs(collider->top - cCol2->entity->Position.y) <= cCol2->Radius)
		{
			return true;
		}
		else if (glm::abs(collider->bottom - cCol2->entity->Position.y) <= cCol2->Radius)
		{
			return true;
		}
		else if (glm::abs(collider->right - cCol2->entity->Position.y) <= cCol2->Radius)
		{
			return true;
		}
		else if (glm::abs(collider->left - cCol2->entity->Position.y) <= cCol2->Radius)
		{
			return true;
		}
	}
	else if (pCol2 != NULL)
	{
		//PIXEL COLLISION
	}
	else if (bCol2 != NULL)
	{
		return true;
	}
	else
	{
		cout << "--ERROR CALCULATING COLLISION (entity)--" << endl;
		return false;
	}

	return false;
}

void CalculateCollision()
{
	for (Entity* e : entities)
	{
		for (Entity* entity : entities)
		{
			if (entity != e && !e->IsStatic)
			{
				Collider* c1 = e->GetModule<Collider>();
				Collider* c2 = entity->GetModule<Collider>();

				if (c1 != NULL && c2 != NULL)
				{
					//check if the 2 objects are near each other
					if (c1->top > c2->bottom || c1->bottom < c2->top)
					{
						if (c1->right > c2->left || c1->left < c2->right)
						{
							CircleCollider* cCol = dynamic_cast<CircleCollider*>(c1);
							PixelCollider* pCol = dynamic_cast<PixelCollider*>(c1);
							BoxCollider* bCol = dynamic_cast<BoxCollider*>(c1);
							if (cCol != NULL)
							{
								CircleCollider* cCol2 = dynamic_cast<CircleCollider*>(c2);
								PixelCollider* pCol2 = dynamic_cast<PixelCollider*>(c2);
								BoxCollider* bCol2 = dynamic_cast<BoxCollider*>(c2);
								vec2* point = new vec2(0, 0);
								c1->colliding = CircleCollision(cCol, cCol2, pCol2, bCol2, point);
								if (c1->colliding)
								{
									if (!entity->IsStatic)
									{
										float xRatio = (e->Velocity.x + entity->Velocity.x) / (e->Mass + entity->Mass);
										float yRatio = (e->Velocity.y + entity->Velocity.y) / (e->Mass + entity->Mass);

										vec2 normal = glm::normalize(*point - e->Position);
										e->Position -= normal;

										e->Velocity = (vec2(xRatio, yRatio) * e->Mass) - (e->Velocity * c2->bounceRatio);
										entity->Velocity = (vec2(xRatio, yRatio) * entity->Mass) - (entity->Velocity * c1->bounceRatio);
									}
									else
									{
										vec2 normal = glm::normalize(*point - e->Position);
										e->Position -= normal;
										e->Velocity *= -c2->bounceRatio;
									}
								}
							}
							else if (pCol != NULL)
							{

							}
							else if (bCol != NULL)
							{
								CircleCollider* cCol2 = static_cast<CircleCollider*>(c2);
								PixelCollider* pCol2 = static_cast<PixelCollider*>(c2);
								BoxCollider* bCol2 = static_cast<BoxCollider*>(c2);
								c1->colliding = BoxCollision(bCol, cCol2, pCol2, bCol2);
								if (c1->colliding)
								{
									float xRatio = (e->Velocity.x + entity->Velocity.x) / (e->Mass + entity->Mass);
									float yRatio = (e->Velocity.y + entity->Velocity.y) / (e->Mass + entity->Mass);

									vec2 normal = glm::normalize(entity->Position - e->Position);
									e->Position -= normal;

									e->Velocity = vec2(xRatio, yRatio) * e->Mass;
								}
								else
								{

								}
							}
							else
							{
								cout << "--ERROR CALCULATING COLLISION (e)--" << endl;
							}
						}
					}
					else
					{
						c1->colliding = false;
					}
				}
			}
		}
	}
}

#pragma endregion