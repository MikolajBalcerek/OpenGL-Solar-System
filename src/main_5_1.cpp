#include "glew.h"
#include "freeglut.h"
#include "glm.hpp"
#include "ext.hpp"
#include <iostream>
#include <cmath>

#include "Shader_Loader.h"
#include "Render_Utils.h"
#include "Camera.h"
#include "Texture.h"

GLuint programColor;
GLuint programTexture;

GLuint GLOBAL_VARIABLE;
GLuint SHIP_TEXTURE;
GLuint THE_SUN;
GLuint MERKURY;
GLuint WENUS;
GLuint ZIEMIA;
GLuint MARS;
GLuint JOWISZ;
GLuint SATURN;
GLuint URAN;
GLuint NEPTUN;
GLuint STONE;
GLuint DEATHSTAR;

Core::Shader_Loader shaderLoader;

obj::Model shipModel;
obj::Model sphereModel;
obj::Model square;

float cameraAngle = 0;
glm::vec3 cameraPos = glm::vec3(-5, 0, 0);
glm::vec3 cameraDir;

glm::mat4 cameraMatrix, perspectiveMatrix;

glm::vec3 lightDir = glm::normalize(glm::vec3(1.0f, -0.9f, -1.0f));

void keyboard(unsigned char key, int x, int y)
{
	float angleSpeed = 0.1f;
	float moveSpeed = 0.1f;
	switch(key)
	{
	case 'z': cameraAngle -= angleSpeed; break;
	case 'x': cameraAngle += angleSpeed; break;
	case 'w': cameraPos += cameraDir * moveSpeed; break;
	case 's': cameraPos -= cameraDir * moveSpeed; break;
	case 'd': cameraPos += glm::cross(cameraDir, glm::vec3(0,1,0)) * moveSpeed; break;
	case 'a': cameraPos -= glm::cross(cameraDir, glm::vec3(0,1,0)) * moveSpeed; break;
	}
}

glm::mat4 createCameraMatrix()
{
	// Obliczanie kierunku patrzenia kamery (w plaszczyznie x-z) przy uzyciu zmiennej cameraAngle kontrolowanej przez klawisze.
	cameraDir = glm::vec3(cosf(cameraAngle), 0.0f, sinf(cameraAngle));
	glm::vec3 up = glm::vec3(0,1,0);

	return Core::createViewMatrix(cameraPos, cameraDir, up);
}

void drawObjectColor(obj::Model * model, glm::mat4 modelMatrix, glm::vec3 color)
{
	GLuint program = programColor;

	glUseProgram(program);

	glUniform3f(glGetUniformLocation(program, "objectColor"), color.x, color.y, color.z);
	glUniform3f(glGetUniformLocation(program, "lightDir"), lightDir.x, lightDir.y, lightDir.z);

	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);

	Core::DrawModel(model);

	glUseProgram(0);
}

void drawObjectTexture(obj::Model * model, glm::mat4 modelMatrix, GLuint textureID)
{
	GLuint program = programTexture;
	
	glUseProgram(program);
	Core::SetActiveTexture(textureID, "sampler2dtype", 1, 0);
	/*glUniform3f(glGetUniformLocation(program, "objectColor"), textureColor.x, textureColor.y, textureColor.z); */
	glUniform3f(glGetUniformLocation(program, "lightDir"), lightDir.x, lightDir.y, lightDir.z);

	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);

	Core::DrawModel(model);

	glUseProgram(0);
}


void drawObjectProceduralTexture(obj::Model * model, glm::mat4 modelMatrix, GLuint textureID)
{



}

void renderScene()
{
	// Aktualizacja macierzy widoku i rzutowania. Macierze sa przechowywane w zmiennych globalnych, bo uzywa ich funkcja drawObject.
	// (Bardziej elegancko byloby przekazac je jako argumenty do funkcji, ale robimy tak dla uproszczenia kodu.
	//  Jest to mozliwe dzieki temu, ze macierze widoku i rzutowania sa takie same dla wszystkich obiektow!)
	cameraMatrix = createCameraMatrix();
	perspectiveMatrix = Core::createPerspectiveMatrix();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	// Macierz statku "przyczepia" go do kamery. Warto przeanalizowac te linijke i zrozumiec jak to dziala.
	glm::mat4 shipModelMatrix = glm::translate(cameraPos + cameraDir * 0.5f + glm::vec3(0,-0.25f,0)) * glm::rotate(-cameraAngle + glm::radians(90.0f), glm::vec3(0,1,0)) * glm::scale(glm::vec3(0.25f));


	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 0)) * glm::scale(glm::vec3(2.8f)), THE_SUN);
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0,0,4))* glm::scale(glm::vec3(0.5f)), MERKURY);
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0,0,7))* glm::scale(glm::vec3(0.8f)), WENUS);
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 10))* glm::scale(glm::vec3(1.0f)), ZIEMIA);
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 14))* glm::scale(glm::vec3(0.7f)), MARS);
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 18))* glm::scale(glm::vec3(2.0f)), JOWISZ);
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 22))* glm::scale(glm::vec3(1.8f)), SATURN);
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 26))* glm::scale(glm::vec3(1.6f)), URAN);
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 30))* glm::scale(glm::vec3(1.4f)), NEPTUN);
	//drawObjectTexture(&square, glm::translate(glm::vec3(0, 2, 5))* glm::scale(glm::vec3(0.5f)), STONE);
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 5, 5))* glm::scale(glm::vec3(0.5f)), DEATHSTAR);


	
	


	//Tektura statku - Mikolaj
	drawObjectTexture(&shipModel, shipModelMatrix, SHIP_TEXTURE);
	drawObjectColor(&shipModel, shipModelMatrix, glm::vec3(0.6f));


	glutSwapBuffers();
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	programColor = shaderLoader.CreateProgram("shaders/shader_color.vert", "shaders/shader_color.frag");
	programTexture = shaderLoader.CreateProgram("shaders/shader_tex.vert", "shaders/shader_tex.frag");
	sphereModel = obj::loadModelFromFile("models/sphere.obj");
	shipModel = obj::loadModelFromFile("models/spaceship.obj");
	square = obj::loadModelFromFile("models/square.obj");
	GLOBAL_VARIABLE = Core::LoadTexture("textures/earth.png");
	THE_SUN = Core::LoadTexture("textures/sun.png");
	SHIP_TEXTURE = Core::LoadTexture("textures/spaceshiptexture.png");
	MERKURY = Core::LoadTexture("textures/merkury.png");
	WENUS = Core::LoadTexture("textures/wenus.png");
	ZIEMIA = Core::LoadTexture("textures/earth.png");
	MARS = Core::LoadTexture("textures/mars.png");
	JOWISZ = Core::LoadTexture("textures/jowisz.png");
	SATURN = Core::LoadTexture("textures/saturn.png");
	URAN = Core::LoadTexture("textures/uran.png");
	NEPTUN = Core::LoadTexture("textures/neptun.png");
	STONE = Core::LoadTexture("textures/minecraft.png");
	DEATHSTAR = Core::LoadTexture("textures/deathstar.png");
	
}

void shutdown()
{
	shaderLoader.DeleteProgram(programColor);
	shaderLoader.DeleteProgram(programTexture);
}

void idle()
{
	glutPostRedisplay();
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	//Mikolaj
	glutInitWindowPosition(0, 0); //gdzie na ekranie wyrzuci program
	glutInitWindowSize(1200, 800); //rozmiar ekranu
	glutCreateWindow("Solar System. Mikolaj Balcerek s416040, Rafal Piotrowski"); //podpis
	glewInit();

	init();
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(renderScene);
	glutIdleFunc(idle);

	glutMainLoop();

	shutdown();

	return 0;
}
