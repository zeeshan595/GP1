/*
	Author: Zeeshan Abid
	Youtube
	http://en.cppreference.com/w/cpp/language/range-for
	http://opengameart.org/content/2d-spaceship-sprites-with-engines
	Jim Crawfard
*/
#include "Common.h"

list<Entity*> entities;
Input* input;

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, w, h, 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
}

void checkError()
{
	DWORD errorCode=GetLastError();
	if (errorCode)
	{
		LPVOID lpMsgBuf;
		FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorCode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf, 0, NULL);
		MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
		LocalFree(lpMsgBuf);
		SetLastError( 0);
	}
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//for (list<Entity>::iterator iter=entities.begin();iter!=entities.end();++iter)
	for (Entity* e : entities)
	{
		e->Render();
	}
	checkError();

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
	input->SetButtonState((KEYS)((int)toupper(k)), false);
	/*
	switch (k)
	{
	case 'w':
		(*entities.begin())->AddForce(vec2(sin((*entities.begin())->Rotation * 3.14 / 180), -cos((*entities.begin())->Rotation* 3.14 / 180)));
		break;
	case 's':
		(*entities.begin())->AddForce(vec2(-sin((*entities.begin())->Rotation * 3.14 / 180), cos((*entities.begin())->Rotation* 3.14 / 180)));
		break;
	case 'a':
		(*entities.begin())->AddTorque(-1);
		break;
	case 'd':
		(*entities.begin())->AddTorque(1);
		break;
	}
	*/
}

void KeyboardDown(unsigned char k, int x, int y)
{
	input->SetButtonState((KEYS)((int)toupper(k)), true);
}

void TestingMethod()
{
	cTexture* tex = new cTexture("Images/Ship1.png");
	Player1* e = new Player1(input);
	e->Position = vec2(50, 50);
	e->Rotation = 135;
	e->Scale = vec2(50, 50);
	e->SetTexture(tex->getTexture());
	e->Rigidbody = true;
	//entities.push_back(e);
}

int main(int argc, char **argv)
{
	//Initialize Glut
	glutInit(&argc, argv);

	//setup some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH);
	
	//Setup Glut Window
	glutInitWindowSize(800, 600);
	glutCreateWindow("My Awesome Game");
	
	input = new Input();

	TestingMethod();

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