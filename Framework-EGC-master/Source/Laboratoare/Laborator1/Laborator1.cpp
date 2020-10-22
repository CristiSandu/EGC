#include "Laborator1.h"

#include <vector>
#include <iostream>
#include <time.h>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp


struct obiect
{
	string Nume;
	glm::vec3 scala;
};


Laborator1::Laborator1()
{
	//intializare color 
	color = glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0);
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

	{
		Mesh* mesh = new Mesh("Archer");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Characters/Archer", "Archer.fbx");
		meshes[mesh->GetMeshID()] = mesh;
	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(color.x, color.y, color.z, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));
    //RenderMesh(meshes["quad"], glm::vec3(2, 0.75f, 1), glm::vec3(0.75f));
	
	RenderMesh(meshes["Archer"], glm::vec3(2, 0.5f, 1), glm::vec3(0.01f));
	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));
	RenderMesh(meshes["quad"], glm::vec3(-1, 0.5f, 0));

	RenderMesh(meshes[obiectNou],objects_pos ,scalaObj);

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
	
	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {

		if (window->KeyHold(GLFW_KEY_W))
		{
			objects_pos.y += deltaTime * 2.f;
		}

		if (window->KeyHold(GLFW_KEY_S))
		{
			objects_pos.y -= deltaTime * 2.f;
		}

		if (window->KeyHold(GLFW_KEY_A))
		{
			objects_pos.x -= deltaTime * 2.f;
		}

		if (window->KeyHold(GLFW_KEY_D))
		{
			objects_pos.x += deltaTime * 2.f;
		}

		if (window->KeyHold(GLFW_KEY_Q))
		{
			objects_pos.z -= deltaTime * 2.f;
		}

		if (window->KeyHold(GLFW_KEY_E))
		{
			objects_pos.z += deltaTime * 2.f;
		}		
	}

	if (window->KeyHold(GLFW_KEY_Z))
	{
		degrees += deltaTime * 2.f;
		objects_pos.x += .02f * cos(degrees);
		objects_pos.y += .02f * sin(degrees);
		objects_pos.z += .02f * tanhl(degrees);
	}

	if (window->KeyHold(GLFW_KEY_H))
	{
		degrees += deltaTime * 2.f;
		objects_pos.x -= .02f * cos(degrees);
		objects_pos.y -= .02f * sin(degrees);
		objects_pos.z -= .02f * tanhl(degrees);
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_F) {
		 color = glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0);
	}

	if (key == GLFW_KEY_C) {
		randomObj = rand() % 5;
		changeObj(randomObj);

	}
};

void Laborator1::changeColor(int nr)
{
}

void Laborator1::changeObj(int nr)
{
	vector<obiect> obj;

	obj.push_back({ "quad",glm::vec3(0.5f)});
	obj.push_back({ "sphere",glm::vec3(0.5f)});
	obj.push_back({ "Archer",glm::vec3(0.01f)});
	obj.push_back({ "teapot",glm::vec3(0.5f)});
	obj.push_back({ "screen_quad",glm::vec3(0.5f)});
	obj.push_back({ "plane50",glm::vec3(0.5f)});

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
