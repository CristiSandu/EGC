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

	//Mesh* arrow = RanderItems::CreateArrow("arrow", corner, squareSide, glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0), true);
	//AddMeshToList(arrow);

	Mesh* bow = RanderItems::CreateBow("bow", corner, squareSide, glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0), false, spaceBow, scale);
	AddMeshToList(bow);

	Mesh* Shuriken = RanderItems::CreateShuriken("Shuriken", corner, squareSide / 2, glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0), false, spaceBow, scale);
	AddMeshToList(Shuriken);

	Mesh* Balloon = RanderItems::CreateBalloon("Balloon", corner, squareSide / 2, squareSide / 4, glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0), false, 360, scale);
	AddMeshToList(Balloon);

}

void Tema1::FrameStart()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{

	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	if (verify == 1) {
		arrowX += 100 * deltaTimeSeconds;
	}

	if (arrowX > 1280)
	{
		verify = 0;
		arrowX = 100;
		translationyArrow = translationy;
	}

	//arrow Transaltion / Render
	
	RanderElements();

	//Bow Transaltion / Render
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(translationx, translationy);
	modelMatrix *= Transform2D::Scale(1, 1);
	//modelMatrix *= Transform2D::Scale(2, 2);
	modelMatrix *= Transform2D::Rotate(-1.5708);
	RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);
	

	//Shuriken Transaltion / Render
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(650, 250);
	modelMatrix *= Transform2D::Scale(1, 1);
	//modelMatrix *= Transform2D::Scale(2, 2);
	degre += deltaTimeSeconds;
	modelMatrix *= Transform2D::Translate(squer_l / 4.f, squer_l / 4.f);
	modelMatrix *= Transform2D::Rotate(degre);
	modelMatrix *= Transform2D::Translate(-squer_l / 4.f, -squer_l / 4.f);
	RenderMesh2D(meshes["Shuriken"], shaders["VertexColor"], modelMatrix);


	//balloon Transaltion / Render
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(950, 150);
	modelMatrix *= Transform2D::Scale(1, 1);
	RenderMesh2D(meshes["Balloon"], shaders["VertexNormal"], modelMatrix);
}

void Tema1::FrameEnd()
{
}

void Tema1::RanderElements() {

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(arrowX, translationyArrow);
	//modelMatrix *= Transform2D::Scale(8, 8);
	modelMatrix *= Transform2D::Scale(2, 2);
	Mesh* mes = arrow->arrowM;
	RenderMesh2D(mes, shaders["VertexColor"], modelMatrix);
}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{

	if (window->KeyHold(GLFW_KEY_W))
	{
		if (verify == 0) {
			translationyArrow += 150 * deltaTime;
			translationy += 150 * deltaTime;

		}
		else
		{
			translationy += 150 * deltaTime;

		}
	}

	if (window->KeyHold(GLFW_KEY_S))
	{
		if (verify == 0) {
			translationyArrow -= 150 * deltaTime;
			translationy -= 150 * deltaTime;

		}
		else
		{
			translationy -= 150 * deltaTime;

		}
	}

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		arrowSpeed += 25 * deltaTime;
	}
	if (window->MouseHold(GLFW_MOUSE_BUTTON_LEFT))
	{

		arrowX -= 150 * deltaTime;
	}
}


void Tema1::ArrowRelese(GLfloat relese)
{
	for (GLfloat i = 0; i < relese; i++)
	{
		arrowX += i;
	}
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

	if (GLFW_KEY_K == key)
	{
		verify = 1;
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
	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		ArrowRelese(arrowSpeed);
		arrowSpeed = 0;
	}
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}


