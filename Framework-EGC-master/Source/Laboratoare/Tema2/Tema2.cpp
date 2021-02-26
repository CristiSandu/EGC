#include "Tema2.h"
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
	combustibilBar = new CombustibilBar();
	startL = std::clock();
	startM = std::clock();
	startR = std::clock();

	platformColors.push_back(RED); //rosu
	platformColors.push_back(YELLOW); //galben 
	platformColors.push_back(ORANGE); //portocaliu
	platformColors.push_back(GREEN); //verde 
	platformColors.push_back(BLUE); //blue 


	platformCoord.push_back(glm::vec4(0, 2, 1, 7));
	platformsColors.push_back(platformColors[4]);

	platformCoord.push_back(glm::vec4(2, 2, 1, 7));
	platformsColors.push_back(platformColors[4]);

	platformCoord.push_back(glm::vec4(4, 2, 1, 7));
	platformsColors.push_back(platformColors[4]);



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

	int colorIndex = rand() % 5;
	int w = (rand() % 5 + 2) / 1;

	if (platformCoord[platformCoord.size() - 3].z >= -200) {

		platformCoord.push_back(glm::vec4(0, 2, platformCoord[platformCoord.size() - 3].z - (0.5 * platformCoord[platformCoord.size() - 3].w) - (colorIndex + 3), w));
		platformsColors.push_back(platformColors[colorIndex]);


		colorIndex = rand() % 5 ;
		platformCoord.push_back(glm::vec4(2, 2, platformCoord[platformCoord.size() - 3].z - (0.5 * platformCoord[platformCoord.size() - 3].w) - (colorIndex + 3), w));
		platformsColors.push_back(platformColors[colorIndex]);


		colorIndex = rand() % 5;
		platformCoord.push_back(glm::vec4(4, 2, platformCoord[platformCoord.size() - 3].z - (0.5 * platformCoord[platformCoord.size() - 3].w) - (colorIndex + 4), w));
		platformsColors.push_back(platformColors[colorIndex]);
	}

	duration = (std::clock() - startL) / (double)CLOCKS_PER_SEC;
	if (duration >= 3 && blockOrange == 1)
	{
		speed = 7;
		blockOrange = 0;
	}
	if (ENDGAME == 1)
	{
		score = (std::clock() - startR) / (double)CLOCKS_PER_SEC;
		std::cout << "END GAME ! Score is :" << score * 10 << std::endl;
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
		{
			isColide = 1;
			colorposition = i;
		}
	}

	if (isColide == 1) {
		if (platformsColors[colorposition] == RED) // red
		{
			platformsColors[colorposition] = VIOLET;
			speed = 0;
			ENDGAME = 1;
			controlDeformationVar = 1;
			onRedPort = 1;
		}
		else if (platformsColors[colorposition] == YELLOW)// yellow
		{
			platformsColors[colorposition] = VIOLET;
			gasVall -= (25.0 / 100.0) * gasVall;
			controlDeformationVar = 1;
		}
		else if (platformsColors[colorposition] == ORANGE)// orange
		{
			platformsColors[colorposition] = VIOLET;
			blockOrange = 1;
			speed = 10;
			startL = std::clock();
			controlDeformationVar = 1;
		}
		else if (platformsColors[colorposition] == GREEN)// green 
		{
			platformsColors[colorposition] = VIOLET;
			gasVall += (25.0 / 100.0) * 37.5;

			if (gasVall > 37.5) {
				gasVall = 37.5;
			}
			controlDeformationVar = 1;
		}
		else if (platformsColors[colorposition] == BLUE)// blue 
		{
			platformsColors[colorposition] = VIOLET;
			controlDeformationVar = 0;
		}

		return true;
	}
	else
	{
		controlDeformationVar = 0;
		return false;
	}
}

void Tema2::RanderScene(float deltaTimeSeconds) {

	for (int i = 0; i < platformCoord.size(); i++)
	{

		platformCoord[i].z += deltaTimeSeconds * speed;
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(platformCoord[i].x, platformCoord[i].y, platformCoord[i].z);
		modelMatrix *= Transform3D::Scale(1, .1f, platformCoord[i].w);
		if (platformCoord[i].z < 25)
		{
			RenderMesh(platform->GetPlatform(), 0, shaders["ShaderTema2"], modelMatrix, platformsColors[i]);
		}
		else
		{
			start = i - 1;
		}

	}

	modelMatrix = glm::mat4(1);
	gasVall -= deltaTimeSeconds * speed / 20;
	if (gasVall <= 0)
	{
		gasVall = 0;
	}
	if (gasVall == 0)
	{
		speed = 0;
	}

	if (combustibilPos.w == 15) {
		modelMatrix *= Transform3D::Translate(combustibilPos.x, combustibilPos.y, combustibilPos.z);
		modelMatrix *= Transform3D::RotateOX(combustibilPos.w);
		modelMatrix *= Transform3D::Scale(.01, .01, .01);

		RenderMesh(combustibilBar->GetCombustibilBar(), 1, shaders["ShaderTema2"], modelMatrix, GREEN);
		modelMatrix *= Transform3D::Scale(gasVall, 1, 1);
		RenderMesh(combustibilBar->GetPowerLine(), 1, shaders["ShaderTema2"], modelMatrix, GREY);
	}
	else {
		modelMatrix *= Transform3D::Translate(4, 3.32, 3.12);
		modelMatrix *= Transform3D::RotateOY(45);
		modelMatrix *= Transform3D::RotateOX(3);
		modelMatrix *= Transform3D::Scale(.01, .01, .01);

		RenderMesh(combustibilBar->GetCombustibilBar(), 1, shaders["ShaderTema2"], modelMatrix, GREEN);
		modelMatrix *= Transform3D::Scale(gasVall, 1, 1);

		RenderMesh(combustibilBar->GetPowerLine(), 1, shaders["ShaderTema2"], modelMatrix, GREY);
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

		if (playerCoord.w == 0 )
		{
			if (playerCoord.y > 2.5)
			{
				playerCoord.y -= deltaTimeSeconds * (speed - 2);
			}
			else {
				isBack = 1;
			}
		}


		if (playerCoord.y >= 2) {

			modelMatrix = glm::mat4(1);
			rotateAngle -= deltaTimeSeconds * speed;
			modelMatrix *= Transform3D::Translate(playerCoord.x, playerCoord.y, playerCoord.z);
			modelMatrix *= Transform3D::RotateOX(rotateAngle);

			RenderMesh(player->GetPlayer(), 3, shaders["ShaderTema2"], modelMatrix, glm::vec3(1, 1, 0));
		}
		else {
			modelMatrix = glm::mat4(1);
			rotateAngle -= deltaTimeSeconds * speed;
			modelMatrix *= Transform3D::Translate(playerCoord.x, playerCoord.y, playerCoord.z);
			modelMatrix *= Transform3D::Scale(.1,.1,.1);
			modelMatrix *= Transform3D::RotateOX(rotateAngle);

			RenderMesh(player->GetPlayer(), 3, shaders["ShaderTema2"], modelMatrix, glm::vec3(1, 1, 0));
			ENDGAME = 1;
		}
	
}

void Tema2::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh* mesh, int name_mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;


	if (name_mesh == 2) {
		shader->Use();
		glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
		glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		mesh->Render();
	}
	else {
		glUseProgram(shader->program);
		if (name_mesh == 3) {
			if (controlDeformationVar == 1) {
				GLint deformation = glGetUniformLocation(shader->GetProgramID(), "deformation");
				glUniform1i(deformation, 1);
				
			}
			else if (blockOrange == 1) {
				GLint deformation = glGetUniformLocation(shader->GetProgramID(), "deformation");
				glUniform1i(deformation, 1);
			}
			
		}
		else {
			GLint deformation = glGetUniformLocation(shader->GetProgramID(), "deformation");
			glUniform1i(deformation, 0);
			glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));
		}
		GLint modelLocation = glGetUniformLocation(shader->GetProgramID(), "Model");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

		GLint viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");
		glm::mat4 viewMatrix = camera->GetViewMatrix();
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

		GLint projLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");
		glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
		glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		

		GLint timeLocation = glGetUniformLocation(shader->GetProgramID(), "Time");
		glUniform1f(timeLocation, (GLfloat)Engine::GetElapsedTime());

		if (name_mesh == 1)
		{
			GLint combustibilBool = glGetUniformLocation(shader->GetProgramID(), "combustibilBool");
			glUniform1f(combustibilBool, 1);
		}
		else {
			GLint combustibilBool = glGetUniformLocation(shader->GetProgramID(), "combustibilBool");
			glUniform1f(combustibilBool, 0);
		}



		glBindVertexArray(mesh->GetBuffers()->VAO);
		glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
	}
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
			// translate the camera forward
			camera->TranslateForward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// translate the camera to the left
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// translate the camera backwards
			camera->TranslateForward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// translate the camera down
			camera->TranslateUpword(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// translate the camera up
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
			if (speed <= 10 && blockOrange == 0 && ENDGAME == 0)
				speed += 1;
		}

		if (key == GLFW_KEY_S)
		{
			if (speed >= .02f && blockOrange == 0 && ENDGAME == 0)
				speed -= 1;
		}

		if (isBack == 1 ) {
			if (playerCoord.y >= 2 ) {
				if (speed > .01f) {
					if (key == GLFW_KEY_SPACE)
					{
						playerCoord.w = 1;
						isBack = 0;
					}
				}
			}
			else {
				speed = 0;
			}
		}
	}
	if (key == GLFW_KEY_C)
	{
		if (firstLook == 1)
		{
			camera->Set(glm::vec3(5, 4, 3), glm::vec3(0, 1, -2), glm::vec3(0, 1, 0));
			firstLook = 0;
			combustibilPos = glm::vec4(5, 3, 2.1, 20);

		}
		else
		{
			camera->Set(glm::vec3(2, 4, 3), glm::vec3(2, 1, -2), glm::vec3(0, 1, 0));
			firstLook = 1;
			combustibilPos = glm::vec4(1.05, 3, 2.1, 15);

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
			//rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			xCameraCoord = sensivityOX * -deltaY;
			yCameraCoord = sensivityOY * -deltaX;

			camera->RotateFirstPerson_OX(sensivityOX * -deltaY);
			camera->RotateFirstPerson_OY(sensivityOY * -deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
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
