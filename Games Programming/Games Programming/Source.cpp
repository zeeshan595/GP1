#include "Common.h"
#include "Input.h"
#include "Texture.h"
#include "CircleCollider.h"
#include "Entity.h"
#include "Player1.h"
#include "Player2.h"
#include "Thruster.h"

//Public Varibles
vector<Entity*> entities;
Input* input;
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

}

void SetupPlayers()
{
	Thruster* p1_T = new Thruster(input);
	Texture* t1_T = new Texture("Images/Ship1_Thruster.png");
	p1_T->AddModule(t1_T);
	p1_T->Scale = vec2(100, 46);
	p1_T->PivotOffset = vec2(0, 65);
	entities.push_back(p1_T);

	
	Player1* p1 = new Player1(input);
	Texture* t1 = new Texture("Images/Ship1.png");
	CircleCollider* c1 = new CircleCollider(&entities);
	p1->AddModule(c1);
	p1->AddModule(t1);
	p1->Scale = vec2(100, 100);
	p1->Position = vec2(50, 50);
	p1->Mass = 50;
	p1->Rotation = 135;
	entities.push_back(p1);

	p1->SetChild(p1_T);

	Thruster* p2_T = new Thruster(input);
	Texture* t2_T = new Texture("Images/Ship2_Thruster.png");
	p2_T->AddModule(t2_T);
	p2_T->Scale = vec2(100, 46);
	p2_T->PivotOffset = vec2(0, 60);
	entities.push_back(p2_T);

	Player2* p2 = new Player2(input);
	Texture* t2 = new Texture("Images/Ship2.png");
	CircleCollider* c2 = new CircleCollider(&entities);
	p2->AddModule(c2);
	p2->AddModule(t2);
	p2->Scale = vec2(100, 100);
	p2->Position = vec2(750, 550);
	p2->Mass = 50;
	p2->Rotation = -45;
	entities.push_back(p2);

	p2->SetChild(p2_T);
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

	//Camera Follow
	glTranslatef(((-entities[1]->Position.x - entities[3]->Position.x) / 2) + (WINDOW_WIDTH / 2), ((-entities[1]->Position.y - entities[3]->Position.y) / 2) + (WINDOW_HEIGHT / 2), 0);

	//for (list<Entity>::iterator iter=entities.begin();iter!=entities.end();++iter)
	for (Entity* e : entities)
	{
		e->Render();
	}

	glutSwapBuffers();
}
	
void Update(int i)
{
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