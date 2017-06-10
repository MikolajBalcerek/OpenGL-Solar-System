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
GLuint sunTexture;
GLuint sunColor;

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
GLuint MOON;
GLuint SPACE;



Core::Shader_Loader shaderLoader;

obj::Model shipModel;
obj::Model sphereModel;
obj::Model square;

float cameraAngle = 0;
glm::vec3 cameraPos = glm::vec3(-5, 0, 0);
glm::vec3 cameraDir;

glm::mat4 cameraMatrix, perspectiveMatrix;

glm::vec3 lightDir = glm::normalize(glm::vec3(1.0f, -0.9f, -1.0f));

float angleSpeed = 0.1f;
float moveSpeed = 0.1f;

void keyboard(unsigned char key, int x, int y)
{

	switch(key)
	{
	case 'z': cameraAngle -= angleSpeed; break;
	case 'x': cameraAngle += angleSpeed; break;
	case 'w': cameraPos += cameraDir * moveSpeed; break;
	case 's': cameraPos -= cameraDir * moveSpeed; break;
	case 'd': cameraPos += glm::cross(cameraDir, glm::vec3(0,1,0)) * moveSpeed; break;
	case 'a': cameraPos -= glm::cross(cameraDir, glm::vec3(0,1,0)) * moveSpeed; break;
	case 't': moveSpeed = 0.5f; break;
	case 'y': moveSpeed = 0.1f; break;
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
	/*
	glm::mat4 rotation;
	float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	rotation[0][0] = cos(time);
	rotation[2][0] = sin(time);
	rotation[0][2] = -sin(time);
	rotation[2][2] = cos(time);
	
	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * modelMatrix * rotation;
	*/
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
	
	
	glm::mat4 rotation;
	/*
	float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	rotation[0][0] = cos(time);
	rotation[2][0] = sin(time);
	rotation[0][2] = -sin(time);
	rotation[2][2] = cos(time);
	*/
	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * modelMatrix;
	

//	glm::mat4 transformation = perspectiveMatrix * cameraMatrix * modelMatrix ;
	
	glUniformMatrix4fv(glGetUniformLocation(program, "modelViewProjectionMatrix"), 1, GL_FALSE, (float*)&transformation);
	glUniformMatrix4fv(glGetUniformLocation(program, "modelMatrix"), 1, GL_FALSE, (float*)&modelMatrix);

	Core::DrawModel(model);

	glUseProgram(0);
}

void drawObjectTextureShip(obj::Model * model, glm::mat4 modelMatrix, GLuint textureID)
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

void drawObjectTextureSun(obj::Model * model, glm::mat4 modelMatrix, GLuint textureID)
{
	GLuint program = sunTexture;

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

	glm::mat4 rotation;
	glm::mat4 translationMerkury;
	glm::mat4 translationWenus;
	glm::mat4 translationZiemia;
	glm::mat4 translationMars;
	glm::mat4 translationJowisz;
	glm::mat4 translationSaturn;
	glm::mat4 translationUran;
	glm::mat4 translationNeptun;
	glm::mat4 translationKsiezyc;


	//Rotation odpowiada za rotacjê dooko³a w³asnej osi planet
	float time = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	rotation[0][0] = cos(time);
	rotation[2][0] = sin(time);
	rotation[0][2] = -sin(time);
	rotation[2][2] = cos(time);

	//translation odpowiada za rotacjê wobec wybranego punktu (0,0,0) s³oñce
	/*
	translationMerkury[3][0] = 10 * sin(1 / (sqrt(pow(10, 3)*c) * time));
	translationMerkury[3][2] = 10 * cos(1 / (sqrt(pow(10, 3)*c) * time));
	*/
	translationMerkury[3][0] = 10 * sin(0.9 * time);
	translationMerkury[3][2] = 10 * cos(0.9 * time);
	translationWenus[3][0] = 15 * sin(0.7 * time);
	translationWenus[3][2] = 15 * cos(0.7 * time);
	translationZiemia[3][0] = 20 *sin(0.5 * time);
	translationZiemia[3][2] = 20 *cos(0.5 * time);
	translationMars[3][0] = 25 * sin(0.3 * time);
	translationMars[3][2] = 25 * cos(0.3 * time);
	translationJowisz[3][0] = 30 * sin(0.1 * time);
	translationJowisz[3][2] = 30 * cos(0.1 * time);
	translationSaturn[3][0] = 35 * sin(0.05 * time);
	translationSaturn[3][2] = 35 * cos(0.05 * time);
	translationUran[3][0] = 40 * sin(0.02 * time);
	translationUran[3][2] = 40 * cos(0.02 * time);
	translationNeptun[3][0] = 45 * sin(0.005 * time);
	translationNeptun[3][2] = 45 * cos(0.005 * time);
	translationKsiezyc[3][0] = 4 * sin(0.1 * time);
	translationKsiezyc[3][2] = 4 * cos(0.1 * time);

	//Sun korzysta ze specjalnej funkcji drawObjectTextureSun, gdzie ignorowane jest oœwietlenie (ca³y obiekt jest oœwietlony)
	drawObjectTextureSun(&sphereModel, glm::translate(glm::vec3(0, 0, 0)) * glm::scale(glm::vec3(2.8f)), THE_SUN);

	//Reszta planet jest prawid³owo oœwietlana
	//Merkury
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 0))*translationMerkury*rotation*glm::scale(glm::vec3(0.5f)), MERKURY);
	//Wenus
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0,0,0))*translationWenus* rotation*glm::scale(glm::vec3(0.8f)), WENUS);
	//Ziemia
	glm::mat4 finalmatrixZiemia = glm::translate(glm::vec3(0, 0, 0))*translationZiemia* rotation*glm::scale(glm::vec3(1.0f));
	drawObjectTexture(&sphereModel, finalmatrixZiemia, ZIEMIA);
	//Ksiezyc dodatkowo kreci sie dookola Ziemi
	drawObjectTexture(&sphereModel, (finalmatrixZiemia * translationKsiezyc * glm::scale(glm::vec3(0.4f))), MOON);
	//Mars
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 0))*translationMars* rotation*glm::scale(glm::vec3(0.7f)), MARS);
	//Jowisz
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 0))*translationJowisz* rotation*glm::scale(glm::vec3(2.0f)), JOWISZ);
	//Saturn
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 0))*translationSaturn* rotation* glm::scale(glm::vec3(1.8f)), SATURN);
	//Uran
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 0))*translationUran* rotation*glm::scale(glm::vec3(1.6f)), URAN);
	//Neptun
	drawObjectTexture(&sphereModel, glm::translate(glm::vec3(0, 0, 0))*translationNeptun* rotation*glm::scale(glm::vec3(1.4f)), NEPTUN);

	//drawObjectColor(&sphereModel, glm::translate(glm::vec3(0, 0, 30))* rotation*glm::scale(glm::vec3(1.4f)), glm::vec3(0.9f, 0.2f, 0.3f));
	//drawObjectTexture(&square, glm::translate(glm::vec3(0, 2, 5))* glm::scale(glm::vec3(0.5f)), STONE);

	//Outer space - olbrzymia kula na zewnatrz modelu ukladu sloneczego
	drawObjectTextureSun(&sphereModel, glm::translate(glm::vec3(0, 0, 0))* glm::scale(glm::vec3(70.0f)), SPACE);

	//Statek jest dodatkowo oteksturowany
	drawObjectTextureShip(&shipModel, shipModelMatrix, SHIP_TEXTURE);
	drawObjectColor(&shipModel, shipModelMatrix, glm::vec3(20.0f));


	glutSwapBuffers();
}

void init()
{
	glEnable(GL_DEPTH_TEST);
	programColor = shaderLoader.CreateProgram("shaders/shader_color.vert", "shaders/shader_color.frag");
	programTexture = shaderLoader.CreateProgram("shaders/shader_tex.vert", "shaders/shader_tex.frag");
	sunTexture = shaderLoader.CreateProgram("shaders/shader_tex_sun.vert", "shaders/shader_tex_sun.frag");
	//sunColor = shaderLoader.CreateProgram("shaders/shader_color_sun.vert", "shaders/shader_color_sun.frag");
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
	MOON = Core::LoadTexture("textures/deathstar.png");
	SPACE = Core::LoadTexture("textures/SPACE.PNG");


}

void shutdown()
{
	shaderLoader.DeleteProgram(programColor);
	shaderLoader.DeleteProgram(programTexture);
	shaderLoader.DeleteProgram(sunTexture);
	//shaderLoader.DeleteProgram(sunColor);
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

