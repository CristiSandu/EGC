#include "Laborator3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

void Laborator3::Init()
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
	

	Mesh* square1 = Object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);
	
	Mesh* square2 = Object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
	AddMeshToList(square2);

	Mesh* square3 = Object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
	AddMeshToList(square3);

	Mesh* square4 = Object2D::CreateSquare("square4", corner, squareSide, glm::vec3(1, 0, 1));
	AddMeshToList(square4);

}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator3::Update(float deltaTimeSeconds)
{
	// TODO: update steps for translation, rotation, scale, in order to create animations
	
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(150, 250) ;
	
	if ((tx >= 1280) || (ty >= 420))
	{
		ok = 1;
	}
	else if ((tx <= -50) || (ty <= -250))
	{
		ok = 0;
	}

	if (ok == 1)
	{
		tx -= deltaTimeSeconds * 150;
		ty -= deltaTimeSeconds * 550;
	}
	else
	{
		tx += deltaTimeSeconds * 150;
		ty += deltaTimeSeconds * 550;
	}


	modelMatrix *= Transform2D::Translate(tx, ty);

	//modelMatrix *= Transform2D::Translate(tx, ty);

	//modelMatrix *= Transform2D::Scale(2, 2) ;
	
	//modelMatrix *= Transform2D::Translate(0, 0);
	/*
	modelMatrix *= Transform2D::Rotate(deltaTimeSeconds * 25);
	modelMatrix *= Transform2D::Scale(2, 2);
	modelMatrix *= Transform2D::Rotate(deltaTimeSeconds * 25);
	modelMatrix *= Transform2D::Scale(1, 1);*/
	/*modelMatrix *= Transform2D::Rotate(deltaTimeSeconds*25);
	modelMatrix *= Transform2D::Rotate(deltaTimeSeconds * 25);
	modelMatrix *= Transform2D::Rotate(deltaTimeSeconds * 25);*/


	// TODO: create animations by multiplying current transform matrix with matrices from Transform 2D

	RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(400, 250);
	//TODO create animations by multiplying current transform matrix with matrices from Transform 2D
	if (tx2 >= 4)
	{
		ok2 = 1;
	}
	else if (tx2 <= 1)
	{
		ok2 = 0;
	}

	if (ok2 == 1)
	{
		tx2 -= deltaTimeSeconds * 2;
		ty2 -= deltaTimeSeconds * 2;
	}
	else
	{
		tx2 += deltaTimeSeconds * 2;
		ty2 += deltaTimeSeconds * 2;
	}

	
	modelMatrix *= Transform2D::Translate(squer_l / 2.f, squer_l / 2.f);
	modelMatrix *= Transform2D::Scale(tx2,ty2);
	modelMatrix *= Transform2D::Translate(-squer_l / 2.f, -squer_l / 2.f);


	//modelMatrix *= Transform2D::Scale(tx2, ty2);

	RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(650, 250);

	rad += deltaTimeSeconds;
	modelMatrix *= Transform2D::Translate(squer_l / 2.f, squer_l / 2.f);
	modelMatrix *= Transform2D::Rotate(rad);
	modelMatrix *= Transform2D::Translate(-squer_l / 2.f, -squer_l / 2.f);


	//TODO create animations by multiplying current transform matrix with matrices from Transform 2D
	RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);


	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(10, 10);

	rad += 0.1f * deltaTimeSeconds;

	

	if (speedy * speedy >= 0)
	{
		ok3 = 0;
	}
	else if (speedy * speedy >= 300)
	{
		ok3 = 1;
	}

	if (ok3 == 1)
	{
		speedy += 500 * deltaTimeSeconds;
		speedx += 100 * deltaTimeSeconds;
	}
	else {
		speedy -= 500 * deltaTimeSeconds;
		speedx -= 100 * deltaTimeSeconds;
	}

	modelMatrix *= Transform2D::Translate(squer_l / 2.f, squer_l / 2.f);
	modelMatrix *= Transform2D::Translate(speedx,speedy* speedy);

	modelMatrix *= Transform2D::Rotate(rad);
	modelMatrix *= Transform2D::Translate(-squer_l / 2.f, -squer_l / 2.f);


	//TODO create animations by multiplying current transform matrix with matrices from Transform 2D
	RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);
}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Laborator3::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{
}



// un patrat -> o saritura in dreapta ai sa cada pe pamant cu muchia de sus