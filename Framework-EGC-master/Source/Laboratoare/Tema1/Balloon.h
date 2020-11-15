#pragma once
#include <Core/Engine.h>

class Balloon {
public:
	Balloon();
	~Balloon();

	Mesh* GetBalloon();

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;
	Mesh* shuriken;
	glm::vec3  color = glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0);
	int spaceBow = 360;
	Mesh* balloon;
};