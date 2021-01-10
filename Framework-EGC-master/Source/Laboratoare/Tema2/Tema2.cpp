#include "Tema2.h"
#include <vector>
#include <string>
#include <iostream>
#include <Core/Engine.h>

using namespace std;

Tema2::Tema2()
{
}

Tema2::~Tema2()
{
}

void Tema2::Init()
{
	renderCameraTarget = false;

	camera = new CameraTema::Camera();
	camera->Set(glm::vec3(2, 4, 3), glm::vec3(2, 1, -2), glm::vec3(0, 1, 0));
	player = new Player();
	platform = new Platform();
	startL = std::clock();
	startM = std::clock();
	startR = std::clock();
	platformCoord.push_back(glm::vec4(2, 2, 1, 7));
	platformCoord.push_back(glm::vec4(0, 2, -4, 7));
	platformCoord.push_back(glm::vec4(2, 2, -4, 7));
	platformCoord.push_back(glm::vec4(4, 2, -4, 7));

	platformColors.push_back(glm::vec3(200, 4, 29)); //rosu
	platformColors.push_back(glm::vec3(199, 199, 5)); //galben 
	platformColors.push_back(glm::vec3(200, 117, 4)); //portocaliu
	platformColors.push_back(glm::vec3(4, 200, 10)); //verde 


	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	{
		Shader* shader = new Shader("ShaderTema2");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}


void Tema2::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::Update(float deltaTimeSeconds)
{
	glLineWidth(3);
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);

	int w = (rand() % 5 + 2) / 1;
	double durationL = (std::clock() - startL) / (double)CLOCKS_PER_SEC;
	if (durationL >= 0.35) {
		platformCoord.push_back(glm::vec4(0, 2, -15, w));
		startL = std::clock();
	}

	double durationM = (std::clock() - startM) / (double)CLOCKS_PER_SEC;
	if (durationM >= 0.4) {
		platformCoord.push_back(glm::vec4(2, 2, -15, w));
		startM = std::clock();
	}

	double durationR = (std::clock() - startR) / (double)CLOCKS_PER_SEC;
	if (durationR >= 0.6) {
		platformCoord.push_back(glm::vec4(4, 2, -15, w));
		startR = std::clock();
	}

	RanderScene(deltaTimeSeconds);
	if (IntersectionCheck() == true || isBack == 0)
		RanderPlayer(deltaTimeSeconds);
	else
	{ 
		playerCoord.y -= deltaTimeSeconds * 3;
	RanderPlayer(deltaTimeSeconds);
	}

}

bool Tema2::IntersectionCheck() {
	isColide = 0;
	for (int i = 0; i < platformCoord.size(); i++)
	{
		float dist_squared = 0.5 * 0.5;
	  
		if (((playerCoord.x - 0.5) <= platformCoord[i].x + 0.5 && (playerCoord.x + 0.5) >= platformCoord[i].x - 0.5) &&
			((playerCoord.y - 0.5) <= platformCoord[i].y + (0.5 * .1) && (playerCoord.y + 0.5) >= platformCoord[i].y - (0.5 * .1)) &&
			((playerCoord.z - 0.5) <= platformCoord[i].z + (0.5 * platformCoord[i].w) && (playerCoord.z + 0.5) >= platformCoord[i].z - (0.5 * platformCoord[i].w)))
			isColide = 1;
	}

	if (isColide == 1)
		return true;
	else
		return false;
}

void Tema2::RanderScene(float deltaTimeSeconds) {
	for (int i = 0; i < platformCoord.size(); i++)
	{
		int colorIndex = rand() % 4;
		platformCoord[i].z += deltaTimeSeconds * speed;
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(platformCoord[i].x, platformCoord[i].y, platformCoord[i].z);
		modelMatrix *= Transform3D::Scale(1, .1f, platformCoord[i].w);
		if (platformCoord[i].z < 25)
		{
			RenderMesh(platform->GetPlatform(), shaders["ShaderTema2"], modelMatrix,platformColors[colorIndex]);
		}
		else
		{
			start = i - 1;
		}
	}
}

void Tema2::RanderPlayer(float deltaTimeSeconds) {

	if (playerCoord.w == 1)
	{
		if (playerCoord.y < 5)
		{
			playerCoord.y += deltaTimeSeconds * (speed - 2);
		}
		else
		{
			playerCoord.w = 0;
		}
	}

	if (playerCoord.w == 0)
	{
		if (playerCoord.y > 2.5)
		{
			playerCoord.y -= deltaTimeSeconds * (speed - 2);
		}
		else {
			isBack = 1;
		}
	}

	modelMatrix = glm::mat4(1);
	rotateAngle -= deltaTimeSeconds * speed;
	modelMatrix *= Transform3D::Translate(playerCoord.x, playerCoord.y, playerCoord.z);
	modelMatrix *= Transform3D::RotateOX(rotateAngle);

	RenderMesh(player->GetPlayer(), shaders["ShaderTema2"], modelMatrix, glm::vec3(1,0,0));
	
}

void Tema2::FrameEnd()
{
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix,const glm::vec3& color)
{
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	//glUseProgram(shader->program);

	/*glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));*/
	glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));

	GLint modelLocation = shader->GetUniformLocation("Model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// get shader location for uniform mat4 "View"
	GLint viewLocation = shader->GetUniformLocation("View");
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	//  get shader location for uniform mat4 "Projection"
	GLint projectionLocation = shader->GetUniformLocation("Projection");

	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	
	mesh->Render();
}

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema2::OnInputUpdate(float deltaTime, int mods)
{
	// move the camera only if MOUSE_RIGHT button is pressed
	float cameraSpeed = 2.0f;

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{

		if (window->KeyHold(GLFW_KEY_W)) {
			// TODO : translate the camera forward
			camera->TranslateForward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// TODO : translate the camera to the left
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// TODO : translate the camera backwards
			camera->TranslateForward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// TODO : translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// TODO : translate the camera down
			camera->TranslateUpword(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// TODO : translate the camera up
			camera->TranslateUpword(deltaTime * cameraSpeed);
		}

	}


	if (window->KeyHold(GLFW_KEY_F))
	{
		fov += deltaTime * cameraSpeed;

		if (projectionType)
		{
			projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);
		}
	}
	if (window->KeyHold(GLFW_KEY_G))
	{
		fov -= deltaTime * cameraSpeed;

		if (projectionType)
		{
			projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);
		}
	}
}

void Tema2::OnKeyPress(int key, int mods)
{
	// add key press event
	if (key == GLFW_KEY_T)
	{
		renderCameraTarget = !renderCameraTarget;
	}

	if (key == GLFW_KEY_O)
	{
		projectionType = false;
		projectionMatrix = glm::ortho(left, right, bottom, top, Z_NEAR, Z_FAR);
	}
	if (key == GLFW_KEY_P)
	{
		projectionType = true;
		projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);
	}
	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		if (key == GLFW_KEY_A)
		{
			if (playerCoord.x == 2)
			{
				playerCoord.x = 0;
			}
			else if (playerCoord.x == 4)
			{
				playerCoord.x = 2;
			}
		}

		if (key == GLFW_KEY_D)
		{
			if (playerCoord.x == 0)
			{
				playerCoord.x = 2;
			}
			else if (playerCoord.x == 2)
			{
				playerCoord.x = 4;
			}
		}

		if (key == GLFW_KEY_W)
		{
			if (speed <= 10)
				speed += 1;
		}

		if (key == GLFW_KEY_S)
		{
			if (speed >= .02f)
				speed -= 1;
		}

		if (key == GLFW_KEY_SPACE)
		{
			playerCoord.w = 1;
			isBack = 0;
		}
	}
	if (key == GLFW_KEY_V)
	{
		if (firstLook == 1)
		{
			camera->Set(glm::vec3(5, 4, 3), glm::vec3(0, 1, -2), glm::vec3(0, 1, 0));
			firstLook = 0;
		}
		else
		{
			camera->Set(glm::vec3(2, 4, 3), glm::vec3(2, 1, -2), glm::vec3(0, 1, 0));
			firstLook = 1;

		}
	}

}

void Tema2::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(sensivityOX * -deltaY);
			camera->RotateFirstPerson_OY(sensivityOY * -deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
			camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
		}

	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema2::OnWindowResize(int width, int height)
{
}


/*{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));

		// Attention! The RenderMesh function overrides the usual RenderMesh that we used until now
		// It uses the viewMatrix from Laborator::Camera instance and the local projectionMatrix
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.5f, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 0, 0));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0.5f, 0));
		RenderMesh(meshes["box"], shaders["Simple"], modelMatrix);
	}


	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.f, 2.5f, 0));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(90.f), glm::vec3(1.f, 1.f, 0));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f, .5f, .3f));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, glm::vec3(2.f, 2.5f, 3.f));
		modelMatrix = glm::rotate(modelMatrix, RADIANS(180.f), glm::vec3(0.8f, 0, 0.5f));
		modelMatrix = glm::scale(modelMatrix, glm::vec3(.8f, 1.f, .9f));
		RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
	}

	// Render the camera target. Useful for understanding where is the rotation point in Third-person camera movement
	if (renderCameraTarget)
	{
		glm::mat4 modelMatrix = glm::mat4(1);
		modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
		modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
		RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
	}*/