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
vector<Entity*> bullets;
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
float Distance(vec2 v1, vec2 v2);

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
	SetupPlayers();
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
	//Player Background Music
	AudioClip* c = new AudioClip("Audio/Music.wav");
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
	srand(time(NULL));
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
	BoxCollider* boxLeft = new BoxCollider();
	boxLeft->size = vec2(10, 10000);

	Entity* borderLeft = new Entity(input);
	borderLeft->AddModule(boxLeft);
	borderLeft->Scale = vec2(10, 10000);
	borderLeft->Position = vec2(-5000, 0);
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
	c1->offset = vec2(0, 0);
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
	c2->offset = vec2(0, 0); 
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
	float distance = Distance(entities[0]->Position, entities[1]->Position);
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
	glTranslatef((WINDOW_WIDTH / 2),(WINDOW_HEIGHT / 2), 0);

	//Scale depending on how far the 2 space ships are
	cameraSize = Distance(entities[0]->Position, entities[1]->Position);
	cameraSize = 1 / (cameraSize / 1000);
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
		bullet->Position = entities[0]->Position + vec2(sin(entities[0]->Rotation * 3.14 / 180) * 100, -cos(entities[0]->Rotation* 3.14 / 180) * 100);
		bullet->Scale = vec2(20, 76);
		bullet->Rotation = entities[0]->Rotation;
		bullet->AddForce(vec2(sin(entities[0]->Rotation * 3.14 / 180) * 50, -cos(entities[0]->Rotation* 3.14 / 180) * 50));
		bullet->Mass = 10;
		entities.push_back(bullet);
		bullets.push_back(bullet);
	}

	for (Entity* e : entities)
	{
		e->FixedUpdate();
	}

	for (Entity* e : bullets)
	{
		CircleCollider* coll = e->GetModule<CircleCollider>();
		if (coll != NULL)
		{
			if (coll->ISColliding())
			{
				//delete e;
			}
		}
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
	if (k == 'm')
		cameraSize += 0.1f;
	else if (k == 'n')
		cameraSize -= 0.1f;
}

//Helper Functions
float Distance(vec2 v1, vec2 v2)
{
	return abs(sqrt(((v1.x - v2.x) * (v1.x - v2.x)) + ((v1.y - v2.y) * (v1.y - v2.y))));
}