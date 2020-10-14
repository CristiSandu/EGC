#include "Laborator1.h"

#include <vector>
#include <iostream>
#include <time.h>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

struct Triple
{
	GLfloat x, y, z;
};

struct obiect 
{
	string Nume;
	glm::vec3 scala;
};

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;

		Mesh* mesh2 = new Mesh("quad");
		mesh2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "quad.obj");
		meshes[mesh2->GetMeshID()] = mesh2;

		Mesh* mesh3 = new Mesh("sphere");
		mesh3->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh3->GetMeshID()] = mesh3;

		Mesh* mesh4 = new Mesh("teapot");
		mesh4->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh4->GetMeshID()] = mesh4;

		Mesh* mesh5 = new Mesh("screen_quad");
		mesh5->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "screen_quad.obj");
		meshes[mesh5->GetMeshID()] = mesh5;

	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(red, green, blue, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	//RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));
//RenderMesh(meshes["quad"], glm::vec3(1, 0.75f, 0), glm::vec3(0.75f));
   
	// render the object again but with different properties
	//RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));
	//RenderMesh(meshes["quad"], glm::vec3(-1, 0.5f, 0));

	RenderMesh(meshes[obiectNou],glm::vec3(posX,posY,posZ) ,scalaObj);

}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	// treat continuous update based on input
	
	/*if (window->KeyHold(GLFW_KEY_R))
	{
		degrees += 2.f * deltaTime;
		if (degrees > 360.f)
		{
			degrees = 0.f;
		}

		posX += .02f * cos(degrees);
		posY += .02f * sin(degrees);
		posZ += .02f * tanhl(degrees);

	}*/
	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {

		

		if (window->KeyHold(GLFW_KEY_W))
		{
			posY += deltaTime * 2.f;
		}

		if (window->KeyHold(GLFW_KEY_S))
		{
			posY -= deltaTime * 2.f;
		}

		if (window->KeyHold(GLFW_KEY_A))
		{
			posX -= deltaTime * 2.f;
		}

		if (window->KeyHold(GLFW_KEY_D))
		{
			posX += deltaTime * 2.f;
		}

		if (window->KeyHold(GLFW_KEY_Q))
		{
			posZ -= deltaTime * 2.f;
		}

		if (window->KeyHold(GLFW_KEY_E))
		{
			posZ += deltaTime * 2.f;
		}
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		int randomColor = rand() % 5 ;
		changeColor(randomColor	);
	}

	if (key == GLFW_KEY_C) {
		int randomObj = rand() % 5;
		changeObj(randomObj);

	}
};

void Laborator1::changeColor(int nr)
{
	vector<Triple> vect;
	Triple ast, agf, atf;
	ast.x = 0.174f;
	ast.y = 1.074f;
	ast.z = 0.774f;
	vect.push_back(ast);
	agf.x = 2.174f;
	agf.y = 1.574f;
	agf.z = 1.754f;
	vect.push_back(agf);
	atf.x = 1.074f;
	atf.y = 1.500f;
	atf.z = 0.704f;
	vect.push_back(atf);
	vect.push_back({ 1.074f ,1.074f ,1.074f });
	vect.push_back({ 1.070f ,0.054f ,1.174f });
	
	Triple out = vect.at(nr);
	red = out.x;
	green = out.y;
	blue = out.z;

}

void Laborator1::changeObj(int nr)
{
	vector<obiect> obj;
	obj.push_back({ "quad",glm::vec3(0.5f) });
	obj.push_back({ "sphere",glm::vec3(0.5f) });
	obj.push_back({ "teapot",glm::vec3(0.5f) });
	obj.push_back({ "screen_quad",glm::vec3(0.5f) });
	obj.push_back({ "plane50",glm::vec3(0.5f) });

	obiect out;
	if( (nr >=0)||(nr <= 4))
		out = obj.at(nr);
	else 
		out = obj.at(1);

	obiectNou = out.Nume;
	scalaObj = out.scala;

}

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
