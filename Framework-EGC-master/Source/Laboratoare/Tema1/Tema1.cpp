#include "Tema1.h"

#include <vector>
#include <iostream>
#include "Transform2D.h"
#include "RanderItems.h"
#include <Laboratoare\Tema1\Transform2D.h>

using namespace std;


Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;

	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;

	// initialize angularStep
	angularStep = 0;

	Mesh* arrow = RanderItems::CreateArrow("arrow", corner, squareSide, glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0), true);
	AddMeshToList(arrow);
	Mesh* bow = RanderItems::CreateBow("bow", corner, squareSide, glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0), false, spaceBow, scale);
	AddMeshToList(bow);
	
	/*

	

	Mesh* square2 = Object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
	AddMeshToList(square2);

	Mesh* square3 = Object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
	AddMeshToList(square3);

	Mesh* square4 = Object2D::CreateSquare("square4", corner, squareSide, glm::vec3(1, 0, 1));
	AddMeshToList(square4);
	*/
}

void Tema1::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{

	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	modelMatrix = glm::mat3(1);

	modelMatrix *= Transform2D::Translate(100, 250);
	//modelMatrix *= Transform2D::Scale(8, 8);
	modelMatrix *= Transform2D::Scale(2, 2);

	RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(25, 250);
	modelMatrix *= Transform2D::Scale(1, 1);
	//modelMatrix *= Transform2D::Scale(2, 2);
	modelMatrix *= Transform2D::Rotate(-1.5708);


	RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);



}

void Tema1::FrameEnd()
{
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}

void Tema1::OnKeyPress(int key, int mods)
{

	if (key == GLFW_KEY_SPACE)
	{
		switch (polygonMode)
		{
		case GL_POINT:
			polygonMode = GL_FILL;
			break;
		case GL_LINE:
			polygonMode = GL_POINT;
			break;
		default:
			polygonMode = GL_LINE;
			break;
		}
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}

