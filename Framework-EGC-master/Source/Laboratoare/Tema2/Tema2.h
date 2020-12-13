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
#include "Platform.h"


#define Z_FAR		(200.f)
#define Z_NEAR		(.01f)

class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();
	void Init();
	std::vector<glm::vec4> platformCoord;
	glm::vec4 playerCoord = glm::vec4(2, 2.5, 0,0);
	GLfloat speed = .01f;
	int firstLook = 1;
	int start;
	float rotateAngle = .00f;
	std::clock_t startL, startM, startR;


private:
	void FrameStart();
	void Update(float deltaTimeSeconds);
	bool IntersectionCheck();
	void RanderScene(float deltaTimeSeconds);
	void RanderPlayer(float deltaTimeSeconds);
	void FrameEnd();
	void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix);
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


};
