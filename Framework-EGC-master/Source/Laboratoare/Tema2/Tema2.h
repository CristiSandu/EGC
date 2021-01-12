#pragma once

#include <vector>
#include <iostream>
#include <Component/SimpleScene.h>
#include <Laboratoare\Tema2\LabCamera.h>
#include <Laboratoare\Tema2\Transform3D.h>
#include <vector>
#include <cstdio>
#include <ctime>
#include "Player.h"
#include <cmath>
#include "Platform.h"
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include <string>

#include "CombustibilBar.h"





#define Z_FAR		(200.f)
#define Z_NEAR		(.01f)

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();
	void Init();
	std::vector<glm::vec4> platformCoord;
	std::vector<glm::vec3> platformColors;
	std::vector<glm::vec3> platformsColors;

	glm::vec3 RED = glm::vec3(0.9, .04, .29); //red
	glm::vec3 YELLOW = glm::vec3(.9, .9, .5); //yellow
	glm::vec3 ORANGE = glm::vec3(1, .56, .3); //orange
	glm::vec3 GREEN = glm::vec3(.4, .9, .10); //green
	glm::vec3 BLUE = glm::vec3(0, 0, .9); //blue
	glm::vec3 VIOLET = glm::vec3(.25, .01, .5); //violet 
	glm::vec3 GREY = glm::vec3(.5, .5, .5); //grey

	glm::vec4 combustibilPos = glm::vec4(1.05, 3, 2.1, 15);
	///glm::vec4(1.05, 3, 2.1,15)
	//glm::vec4(.01, .01, 2.1,15)
	GLfloat xCameraCoord = 0, yCameraCoord = 0;
	glm::vec4 playerCoord = glm::vec4(2, 2.5, 0,0);
	GLfloat speed = .01f;
	int blockOrange = 0;
	int firstLook = 1;
	int start;
	int isBack = 1;
	int isColide = 0;
	int ENDGAME = 0;
	int colorposition = -5, onRedPort = 0;
	GLfloat gasVall = 37.5;
	float rotateAngle = .00f;
	double duration = 0,score =0;
	std::clock_t startL, startM, startR;
	
	

	int controlDeformationVar = 0;


private:
	void FrameStart();
	void Update(float deltaTimeSeconds);
	GLfloat max_min(GLfloat a, GLfloat b, int c);
	bool IntersectionCheck();
	void RanderScene(float deltaTimeSeconds);
	void RanderPlayer(float deltaTimeSeconds);
	void FrameEnd();
	Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
	void RenderMesh(Mesh* mesh, int name_mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
	//void RenderMesh(Mesh* mesh, string name_mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
	//void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color);
	void OnInputUpdate(float deltaTime, int mods);
	void OnKeyPress(int key, int mods);
	void OnKeyRelease(int key, int mods);
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY);
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods);
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods);
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY);
	void OnWindowResize(int width, int height);

protected:
	CameraTema::Camera* camera;
	bool renderCameraTarget;
	glm::mat4 projectionMatrix;
	glm::mat4 modelMatrix;
	bool projectionType;
	GLfloat right;
	GLfloat left;
	GLfloat bottom;
	GLfloat top;
	GLfloat fov;
	GLenum polygonMode;
	Player* player;
	Platform* platform;
	CombustibilBar* combustibilBar;

};
