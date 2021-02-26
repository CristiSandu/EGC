#include "Tema3.h"
#include <Core/Engine.h>

using namespace std;

Tema3::Tema3()
{
}

Tema3::~Tema3()
{
}

void Tema3::Init()
{
	renderCameraTarget = false;
	const string textureLoc = "Source/Laboratoare/Tema3/Textures/";

	camera = new CameraTema::Camera();
	camera->Set(glm::vec3(2, 4, 3), glm::vec3(2, 3.7, 2), glm::vec3(0, 1, 0));

	player = new Player();
	platform = new Platform();
	combustibilBar = new CombustibilBar();
	ornament = new Ornament();

	startL = std::clock();
	startM = std::clock();
	startR = std::clock();
	startPowerUp = std::clock();

	// define color vector 
	platformColors.push_back(RED); //rosu
	platformColors.push_back(YELLOW); //galben 
	platformColors.push_back(ORANGE); //portocaliu
	platformColors.push_back(GREEN); //verde 
	platformColors.push_back(BLUE); //blue 

	// define posibile position of powerUps
	indexPowerUp.push_back(0);
	indexPowerUp.push_back(2);
	indexPowerUp.push_back(4);


	// put start eements in scheen
	platformCoord.push_back(glm::vec4(0, 2, 1, 7));
	platformsColors.push_back(platformColors[4]);

	platformCoord.push_back(glm::vec4(2, 2, 1, 7));
	platformsColors.push_back(platformColors[4]);

	platformCoord.push_back(glm::vec4(4, 2, 1, 7));
	platformsColors.push_back(platformColors[4]);

	ornamentCoord.push_back(glm::vec4(-4, 2, 1, 1));
	ornamentCoord.push_back(glm::vec4(6, 2, 1, 1));
	powerUps.push_back(glm::vec4(4, 2.1, -1, 1));

	obsacolsVect.push_back(glm::vec4(0, 2.5, 1, 1));

	rotationPowerUp.push_back(1);

	// load textures for objects 
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "bill-cipher-1.png").c_str(), GL_CLAMP_TO_BORDER);
		mapTextures["bill"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "vortex.jpg").c_str(), GL_REPEAT);
		mapTextures["vortex"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "stone.jpg").c_str(), GL_REPEAT);
		mapTextures["rockWall"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "galaxy.jpg").c_str(), GL_REPEAT);
		mapTextures["galaxy"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "metal.jpg").c_str(), GL_REPEAT);
		mapTextures["metal"] = texture;
	}

	// define light pozition and material constants 
	{
		lightPosition = glm::vec3(6, 2, -30);
		lightDirection = glm::vec3(-1, 0, 0);

		lightposition_spot_1 = glm::vec3(-4, 2, -30);
		lightdirection_spot_1 = glm::vec3(1, 0, 0);

		lightPosition_spot = glm::vec3(2, 8, 0);
		lightDirection_spot = glm::vec3(0, -1, 0);


		lightposition_spot_2 = glm::vec3(-4, 2, -20);
		lightdirection_spot_2 = glm::vec3(1, 0, 0);

		lightposition_spot_3 = glm::vec3(6, 2, -20);
		lightdirection_spot_3 = glm::vec3(-1, 0, 0);

		lightposition_spot_4 = glm::vec3(0, 7, -30);
		lightdirection_spot_4 = glm::vec3(-1, -1, -1);

		materialShininess = 30;
		materialKd = 0.5;
		materialKs = 0.5;
	}


	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

	// load shader
	{
		Shader* shader = new Shader("ShaderTema3");
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}

}


void Tema3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema3::Update(float deltaTimeSeconds)
{
	int colorIndex = rand() % 5;
	int w = (rand() % 5 + 2) / 1;


	// rander new platforms, ornaments and powerUps
	if (platformCoord[platformCoord.size() - 3].z >= -200) {

		platformCoord.push_back(glm::vec4(0, 2, platformCoord[platformCoord.size() - 3].z - (0.5 * platformCoord[platformCoord.size() - 3].w) - (colorIndex + 3), w));
		platformsColors.push_back(platformColors[colorIndex]);


		colorIndex = rand() % 5;
		platformCoord.push_back(glm::vec4(2, 2, platformCoord[platformCoord.size() - 3].z - (0.5 * platformCoord[platformCoord.size() - 3].w) - (colorIndex + 3), w));
		platformsColors.push_back(platformColors[colorIndex]);


		colorIndex = rand() % 5;
		platformCoord.push_back(glm::vec4(4, 2, platformCoord[platformCoord.size() - 3].z - (0.5 * platformCoord[platformCoord.size() - 3].w) - (colorIndex + 4), w));
		platformsColors.push_back(platformColors[colorIndex]);

		duration = (std::clock() - startPowerUp) / (double)CLOCKS_PER_SEC;
		if (duration > 1.5) {
			powerUps.push_back(glm::vec4(indexPowerUp[rand() % 3], 2.1, platformCoord[platformCoord.size() - 3].z - (0.5 * platformCoord[platformCoord.size() - 3].w) - (colorIndex + 4), 1));
			rotationPowerUp.push_back(1);
			obsacolsVect.push_back(glm::vec4(indexPowerUp[rand() % 3], 2.5, platformCoord[platformCoord.size() - 3].z - (0.5 * platformCoord[platformCoord.size() - 3].w) - (colorIndex + 4), 1));
			startPowerUp = std::clock();
		}

		ornamentCoord.push_back(glm::vec4(-4, 2, ornamentCoord[ornamentCoord.size() - 2].z - 10, 1));
		ornamentCoord.push_back(glm::vec4(6, 2, ornamentCoord[ornamentCoord.size() - 2].z - 10, 1));

	}

	// orange powerUp duration 
	duration = (std::clock() - startL) / (double)CLOCKS_PER_SEC;
	if (duration >= 3 && blockOrange == 1)
	{
		speed = 7;
		blockOrange = 0;
	}

	// check end of game
	if (ENDGAME == 1)
	{
		// and print the score
		if (prinScore == 0) {
			std::cout << "END GAME ! Score is :" << endSocre << std::endl;
			prinScore = 1;
		}
	}


	RanderScene(deltaTimeSeconds);
	RanderOrnament(deltaTimeSeconds);
	RanderPowerUp(deltaTimeSeconds);
	RanderBackground(deltaTimeSeconds);

	// verify colision 
	if (IntersectionCheck() == true || isBack == 0)
		RanderPlayer(deltaTimeSeconds);
	else
	{
		playerCoord.y -= deltaTimeSeconds * 3;
		RanderPlayer(deltaTimeSeconds);
	}
}

bool Tema3::IntersectionCheck() {
	isColide = 0;

	// check intersecrtion of player with platforms 
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

	isColidePowerUp = 0;
	isColideObstacle = 0;
	// check intersection of player with powerUps and obstacles (number of obstacles = number of powerUps)
	for (int i = 0; i < powerUps.size(); i++)
	{
		float dist_squared = 0.5 * 0.5;

		if (((playerCoord.x - 0.5) <= powerUps[i].x + 0.5 && (playerCoord.x + 0.5) >= powerUps[i].x - 0.5) &&
			((playerCoord.y - 0.5) <= powerUps[i].y + (0.5) && (playerCoord.y + 0.5) >= powerUps[i].y - (0.5)) &&
			((playerCoord.z - 0.5) <= powerUps[i].z + (0.5) && (playerCoord.z + 0.5) >= powerUps[i].z - (0.5)))
		{
			isColidePowerUp = 1;
			idexPowerUp = i;
		}


		if (((playerCoord.x - 0.5) <= obsacolsVect[i].x + 0.5 && (playerCoord.x + 0.5) >= obsacolsVect[i].x - 0.5) &&
			((playerCoord.y - 0.5) <= obsacolsVect[i].y + (0.5 * 0.9) && (playerCoord.y + 0.5) >= obsacolsVect[i].y - (0.5 * 0.9)) &&
			((playerCoord.z - 0.5) <= obsacolsVect[i].z + (0.5) && (playerCoord.z + 0.5) >= obsacolsVect[i].z - (0.5)))
		{
			isColideObstacle = 1;
			indexObsatcoles = i;
		}
	}

	// if colide with powerUp add to score and check colision with it 
	if (isColidePowerUp == 1)
	{
		score += 100;
		powerUps[idexPowerUp].w = 0;
	}

	// if colide with obstacle game stor 
	if (isColideObstacle == 1)
	{
		score = (std::clock() - startR) / (double)CLOCKS_PER_SEC;
		ENDGAME = 1;
		endSocre = score * 10;
	}


	// if colide with a platform  
	if (isColide == 1) {
		// check color 
		// if red end game 
		if (platformsColors[colorposition] == RED) // red
		{
			platformsColors[colorposition] = VIOLET;
			speed = 0;
			ENDGAME = 1;
			score = (std::clock() - startR) / (double)CLOCKS_PER_SEC;
			endSocre = score * 10;

			controlDeformationVar = 1;
			onRedPort = 1;
		}// if yellow lose gas 
		else if (platformsColors[colorposition] == YELLOW)// yellow
		{
			platformsColors[colorposition] = VIOLET;
			gasVall -= (25.0 / 100.0) * gasVall;
			controlDeformationVar = 1;
		}// if orange lock speed at 10 for a period of time 
		else if (platformsColors[colorposition] == ORANGE)// orange
		{
			platformsColors[colorposition] = VIOLET;
			blockOrange = 1;
			speed = 10;
			startL = std::clock();
			controlDeformationVar = 1;
		}// if green add gas 
		else if (platformsColors[colorposition] == GREEN)// green 
		{
			platformsColors[colorposition] = VIOLET;
			gasVall += (25.0 / 100.0) * 37.5;

			if (gasVall > 37.5) {
				gasVall = 37.5;
			}
			controlDeformationVar = 1;
		}// if blue stai the same
		else if (platformsColors[colorposition] == BLUE)// blue 
		{
			platformsColors[colorposition] = VIOLET;
			controlDeformationVar = 0;
		}

		// in every check of color if is a sepcial platform make a deformation in VertexShader

		return true;
	}
	else
	{
		controlDeformationVar = 0;
		return false;
	}
}

void Tema3::RanderOrnament(float deltaTimeSeconds) {

	for (int i = 0; i < ornamentCoord.size(); i++)
	{
		if (ENDGAME == 0)
			ornamentCoord[i].z += deltaTimeSeconds * speed;
		ornamentCoord[i].w += deltaTimeSeconds * 1;
		modelMatrix = glm::mat4(1);

		modelMatrix *= Transform3D::Translate(ornamentCoord[i].x, ornamentCoord[i].y, ornamentCoord[i].z);
		modelMatrix *= Transform3D::Scale(.31f, .31f, .31f);
		modelMatrix *= Transform3D::Translate(4 / 2, 0, 4 / 2);
		modelMatrix *= Transform3D::RotateOY(ornamentCoord[i].w);
		modelMatrix *= Transform3D::Translate(-4 / 2, 0, -4 / 2);


		if (lightPosition.z > 10)
		{
			if (ornamentCoord[i].z < -90) {
				lightPosition.z = ornamentCoord[i].z;
				lightposition_spot_1.z = ornamentCoord[i].z;
			}

		}

		if (lightposition_spot_3.z > 10)
		{
			if (ornamentCoord[i].z < -100) {
				lightposition_spot_3.z = ornamentCoord[i].z;
				lightposition_spot_2.z = ornamentCoord[i].z;
			}
		}

		{
			glm::mat4 modelMatrix = glm::mat4(1);
			modelMatrix = glm::translate(modelMatrix, lightposition_spot_4);
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f));
			modelMatrix *= Transform3D::Translate(4 / 2, 0, 4 / 2);
			modelMatrix *= Transform3D::RotateOY(ornamentCoord[i].w);
			modelMatrix *= Transform3D::Translate(-4 / 2, 0, -4 / 2);

			RenderMesh(ornament->GetPiramide(), shaders["ShaderTema3"], modelMatrix, RED, nullptr, nullptr);
		}



		if (ornamentCoord[i].z < 25)
		{

			RenderMesh(ornament->GetPiramide(), shaders["ShaderTema3"], modelMatrix, GREY, mapTextures["bill"], mapTextures["vortex"]);
		}
		else
		{
			start = i - 1;
		}
	}

	if (ENDGAME == 1) {
		lightPosition.z += deltaTimeSeconds * 0;
		lightposition_spot_1.z += deltaTimeSeconds * 0;
		lightposition_spot_3.z += deltaTimeSeconds * speed;
		lightposition_spot_2.z += deltaTimeSeconds * speed;
	}
	else {
		lightPosition.z += deltaTimeSeconds * speed;
		lightposition_spot_1.z += deltaTimeSeconds * speed;
		lightposition_spot_3.z += deltaTimeSeconds * speed;
		lightposition_spot_2.z += deltaTimeSeconds * speed;
	}

}
void Tema3::RanderBackground(float deltaTimeSeconds) {
	modelMatrix = glm::mat4(1);
	modelMatrix *= Transform3D::Translate(0, 0, 0);
	modelMatrix *= Transform3D::Scale(250, 250, 250);
	modelMatrix *= Transform3D::RotateOX(-20);
	RenderMesh(platform->GetPlatform(), shaders["ShaderTema3"], modelMatrix, glm::vec3(0, 0, 0), mapTextures["galaxy"], nullptr);
}

void Tema3::RanderPowerUp(float deltaTimeSeconds) {
	for (int i = 0; i < powerUps.size(); i++)
	{
		if (ENDGAME == 0) {
			powerUps[i].z += deltaTimeSeconds * speed;
			obsacolsVect[i].z += deltaTimeSeconds * speed;
		}
		rotationPowerUp[i] += deltaTimeSeconds * 3;
		modelMatrix = glm::mat4(1);

		modelMatrix *= Transform3D::Translate(powerUps[i].x, powerUps[i].y, powerUps[i].z);

		modelMatrix *= Transform3D::Scale(.11f, .11f, .11f);
		modelMatrix *= Transform3D::Translate(2 / 2, 0, 2 / 2);
		modelMatrix *= Transform3D::RotateOY(rotationPowerUp[i]);
		modelMatrix *= Transform3D::Translate(-2 / 2, 0, -2 / 2);

		modelMatrixObs = glm::mat4(1);
		modelMatrixObs *= Transform3D::Translate(obsacolsVect[i].x, obsacolsVect[i].y, obsacolsVect[i].z);
		if (obsacolsVect[i].w == 0) {
			modelMatrixObs *= Transform3D::Scale(.001f, .001f, .001f);
		}
		else
			modelMatrixObs *= Transform3D::Scale(1, .9f, 1);



		if (powerUps[i].w == 0) {
			modelMatrix *= Transform3D::Scale(.001f, .001f, .001f);

		}

		if (powerUps[i].z < 25)
		{
			RenderMesh(ornament->GetPiramideStyle(), shaders["ShaderTema3"], modelMatrix, GREEN, mapTextures["vortex"], nullptr);
			RenderMesh(platform->GetPlatform(), shaders["ShaderTema3"], modelMatrixObs, glm::vec3(0, 0, 0), mapTextures["rockWall"], nullptr);
		}
		else
		{
			start = i - 1;
		}
	}
}

void Tema3::RanderScene(float deltaTimeSeconds) {

	for (int i = 0; i < platformCoord.size(); i++)
	{
		if (ENDGAME == 0)
			platformCoord[i].z += deltaTimeSeconds * speed;
		modelMatrix = glm::mat4(1);
		modelMatrix *= Transform3D::Translate(platformCoord[i].x, platformCoord[i].y, platformCoord[i].z);
		modelMatrix *= Transform3D::Scale(1, .1f, platformCoord[i].w);
		if (platformCoord[i].z < 25)
		{
			RenderMesh(platform->GetPlatform(), shaders["ShaderTema3"], modelMatrix, platformsColors[i], mapTextures["vortex"], nullptr);
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

		RenderMesh(combustibilBar->GetCombustibilBar(), shaders["ShaderTema3"], modelMatrix, GREEN, mapTextures["rockWall"], nullptr);
		modelMatrix *= Transform3D::Scale(gasVall, 1, 1);
		RenderMesh(combustibilBar->GetPowerLine(), shaders["ShaderTema3"], modelMatrix, GREY, mapTextures["rockWall"], nullptr);
	}
	else {
		modelMatrix *= Transform3D::Translate(combustibilPos.x, combustibilPos.y, combustibilPos.z);
		modelMatrix *= Transform3D::RotateOY(combustibilPos.w);
		modelMatrix *= Transform3D::RotateOX(3);
		modelMatrix *= Transform3D::Scale(.01, .01, .01);

		RenderMesh(combustibilBar->GetCombustibilBar(), shaders["ShaderTema3"], modelMatrix, GREEN, mapTextures["rockWall"], nullptr);
		modelMatrix *= Transform3D::Scale(gasVall, 1, 1);

		RenderMesh(combustibilBar->GetPowerLine(), shaders["ShaderTema3"], modelMatrix, GREY, mapTextures["rockWall"], nullptr);
	}
}

void Tema3::RanderPlayer(float deltaTimeSeconds) {

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
	if (playerCoord.y >= 2) {

		modelMatrix = glm::mat4(1);
		rotateAngle -= deltaTimeSeconds * speed;
		modelMatrix *= Transform3D::Translate(playerCoord.x, playerCoord.y, playerCoord.z);
		modelMatrix *= Transform3D::RotateOX(rotateAngle);
		//
		RenderMesh(player->GetPlayer(), shaders["ShaderTema3"], modelMatrix, glm::vec3(1, 1, 0), mapTextures["metal"], nullptr);
	}
	else {
		modelMatrix = glm::mat4(1);
		rotateAngle -= deltaTimeSeconds * speed;
		modelMatrix *= Transform3D::Translate(playerCoord.x, playerCoord.y, playerCoord.z);
		modelMatrix *= Transform3D::Scale(.1, .1, .1);
		modelMatrix *= Transform3D::RotateOX(rotateAngle);

		RenderMesh(player->GetPlayer(), shaders["ShaderTema3"], modelMatrix, glm::vec3(1, 1, 0), mapTextures["metal"], nullptr);
		ENDGAME = 1;
		score = (std::clock() - startR) / (double)CLOCKS_PER_SEC;
		endSocre = score * 10;
	}

}

void Tema3::FrameEnd()
{
	//DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema3::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, Texture2D* texture1, Texture2D* texture2)
{
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glUseProgram(shader->program);
	if (mesh == player->GetPlayer()) {
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
		int object_color = glGetUniformLocation(shader->program, "object_color");
		glUniform3f(object_color, color.r, color.g, color.b);
	}
	GLint modelLocation = glGetUniformLocation(shader->GetProgramID(), "Model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	GLint viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	GLint projLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	int material_shininess = glGetUniformLocation(shader->program, "material_shininess");
	glUniform1i(material_shininess, materialShininess);

	int material_kd = glGetUniformLocation(shader->program, "material_kd");
	glUniform1f(material_kd, materialKd);

	int material_ks = glGetUniformLocation(shader->program, "material_ks");
	glUniform1f(material_ks, materialKs);


	// send lights pozitions 
	int light_position = glGetUniformLocation(shader->program, "light_position");
	glUniform3f(light_position, lightPosition.x, lightPosition.y, lightPosition.z);

	int light_direction = glGetUniformLocation(shader->program, "light_direction");
	glUniform3f(light_direction, lightDirection.x, lightDirection.y, lightDirection.z);

	int light_position_spot = glGetUniformLocation(shader->program, "light_position_spot");
	glUniform3f(light_position_spot, lightPosition_spot.x, lightPosition_spot.y, lightPosition_spot.z);

	int light_direction_spot = glGetUniformLocation(shader->program, "light_direction_spot");
	glUniform3f(light_direction_spot, lightDirection_spot.x, lightDirection_spot.y, lightDirection_spot.z);

	int light_position_spot_1 = glGetUniformLocation(shader->program, "light_position_spot_1");
	glUniform3f(light_position_spot_1, lightposition_spot_1.x, lightposition_spot_1.y, lightposition_spot_1.z);
	int light_direction_spot_1 = glGetUniformLocation(shader->program, "light_direction_spot_1");

	glUniform3f(light_direction_spot_1, lightdirection_spot_1.x, lightdirection_spot_1.y, lightdirection_spot_1.z);
	int light_position_spot_2 = glGetUniformLocation(shader->program, "light_position_spot_2");
	glUniform3f(light_position_spot_2, lightposition_spot_2.x, lightposition_spot_2.y, lightposition_spot_2.z);
	int light_direction_spot_2 = glGetUniformLocation(shader->program, "light_direction_spot_2");

	glUniform3f(light_direction_spot_2, lightdirection_spot_2.x, lightdirection_spot_2.y, lightdirection_spot_2.z);
	int light_position_spot_3 = glGetUniformLocation(shader->program, "light_position_spot_3");
	glUniform3f(light_position_spot_3, lightposition_spot_3.x, lightposition_spot_3.y, lightposition_spot_3.z);
	int light_direction_spot_3 = glGetUniformLocation(shader->program, "light_direction_spot_3");

	glUniform3f(light_direction_spot_3, lightdirection_spot_3.x, lightdirection_spot_3.y, lightdirection_spot_3.z);
	int light_position_spot_4 = glGetUniformLocation(shader->program, "light_position_spot_4");
	glUniform3f(light_position_spot_4, lightposition_spot_4.x, lightposition_spot_4.y, lightposition_spot_4.z);
	int light_direction_spot_4 = glGetUniformLocation(shader->program, "light_direction_spot_4");
	glUniform3f(light_direction_spot_4, lightdirection_spot_4.x, lightdirection_spot_4.y, lightdirection_spot_4.z);
	// -- 


	glm::vec3 eyePosition = GetSceneCamera()->transform->GetWorldPosition();
	int eye_position = glGetUniformLocation(shader->program, "eye_position");
	glUniform3f(eye_position, eyePosition.x, eyePosition.y, eyePosition.z);

	GLint cut_off_angle = glGetUniformLocation(shader->program, "cut_off_angle");
	glUniform1f(cut_off_angle, cutoffAngle);

	if (mesh == ornament->GetPiramide())
		glUniform1i(glGetUniformLocation(shader->program, "mix_textures"), true);
	else
		glUniform1i(glGetUniformLocation(shader->program, "mix_textures"), false);

	if (onlySpot == 1)
		glUniform1i(glGetUniformLocation(shader->program, "only_spot"), true);
	else
		glUniform1i(glGetUniformLocation(shader->program, "only_spot"), false);

	if (onlyPunct == 1)
		glUniform1i(glGetUniformLocation(shader->program, "only_punct"), true);
	else
		glUniform1i(glGetUniformLocation(shader->program, "only_punct"), false);


	if (mesh == ornament->GetPiramideStyle())
		glUniform1i(glGetUniformLocation(shader->program, "isSkull"), true);
	else
		glUniform1i(glGetUniformLocation(shader->program, "isSkull"), false);

	if (texture1)
	{
		//activate texture location 0
		glActiveTexture(GL_TEXTURE0);
		// Bind the texture1 ID
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		//Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}

	if (texture2)
	{
		//activate texture location 1
		glActiveTexture(GL_TEXTURE1);
		//Bind the texture2 ID
		glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
		//Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
	}


	GLint timeLocation = glGetUniformLocation(shader->GetProgramID(), "Time");
	glUniform1f(timeLocation, (GLfloat)Engine::GetElapsedTime());

	if (mesh == combustibilBar->GetCombustibilBar() ||
		mesh == combustibilBar->GetPowerLine())
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

// Documentation for the input functions can be found in: "/Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Tema3::OnInputUpdate(float deltaTime, int mods)
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
			//translate the camera backwards
			camera->TranslateForward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			//  translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// translate the camera down
			camera->TranslateUpword(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			//translate the camera up
			camera->TranslateUpword(deltaTime * cameraSpeed);
		}


		if (window->KeyHold(GLFW_KEY_UP))
		{
			angleOX += deltaTime * 20;
		}
		if (window->KeyHold(GLFW_KEY_DOWN))
		{
			angleOX -= deltaTime * 20;
		}
		if (window->KeyHold(GLFW_KEY_LEFT))
		{
			angleOY += deltaTime * 20;
		}
		if (window->KeyHold(GLFW_KEY_RIGHT))
		{
			angleOY -= deltaTime * 20;
		}


		if (window->KeyHold(GLFW_KEY_R))
		{
			cutoffAngle += deltaTime * ANGLE_SPEEDUP;
			cutoffAngle = cutoffAngle > 360.f ? 360.f : cutoffAngle;
		}
		if (window->KeyHold(GLFW_KEY_T))
		{
			cutoffAngle -= deltaTime * ANGLE_SPEEDUP;
			cutoffAngle = cutoffAngle < 0.f ? 0.f : cutoffAngle;
		}

	}

	angleOX += deltaTime * .00001;
	angleOY += deltaTime * .00001;

	glm::mat4 turn = glm::mat4(1);
	turn = glm::rotate(turn, sin(angleOY), glm::vec3(0, 1, 0));
	turn = glm::rotate(turn, cos(angleOX), glm::vec3(1, 0, 0));

	lightDirection_spot = glm::vec3(0, -1, 0);
	lightDirection_spot = glm::vec3(turn * glm::vec4(lightDirection_spot, 0));
	lightdirection_spot_1 = glm::vec3(turn * glm::vec4(lightdirection_spot_1, 0));
	lightdirection_spot_2 = glm::vec3(turn * glm::vec4(lightdirection_spot_2, 0));
	lightdirection_spot_3 = glm::vec3(turn * glm::vec4(lightdirection_spot_3, 0));
	lightdirection_spot_4 = glm::vec3(turn * glm::vec4(lightdirection_spot_4, 0));


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

void Tema3::OnKeyPress(int key, int mods)
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

		if (isBack == 1) {
			if (playerCoord.y >= 2) {
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
			camera->Set(glm::vec3(5, 4, 3), glm::vec3(2, 3, -2), glm::vec3(0, 1, 0));
			firstLook = 0;
			combustibilPos = glm::vec4(3.8, 3.5, 2.7, 44.7);
		}
		else
		{

			camera->Set(glm::vec3(2, 4, 3), glm::vec3(2, 3.7, 2), glm::vec3(0, 1, 0));
			firstLook = 1;
			combustibilPos = glm::vec4(1.15, 3.4, 2.1, powerBarAngel);

		}
	}

	if (key == GLFW_KEY_O)
	{
		if (onlySpot == 0)
		{
			onlySpot = 1;
		}
		else
		{
			onlySpot = 0;
		}
	}


	if (key == GLFW_KEY_P)
	{
		if (onlyPunct == 0)
		{
			onlyPunct = 1;
		}
		else
		{
			onlyPunct = 0;
		}
	}

}

void Tema3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
	{
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			//rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			//use the sensitivity variables for setting up the rotation speed
			xCameraCoord = sensivityOX * -deltaY;
			yCameraCoord = sensivityOY * -deltaX;

			camera->RotateFirstPerson_OX(sensivityOX * -deltaY);
			camera->RotateFirstPerson_OY(sensivityOY * -deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			//rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			//use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
			camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
		}

	}
}

void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema3::OnWindowResize(int width, int height)
{
}
