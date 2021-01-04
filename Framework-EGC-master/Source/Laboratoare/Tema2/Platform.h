#pragma once
#include <Component\SimpleScene.h>
#include <Core/Engine.h>

class Platform {
public:
	Platform();
	~Platform();
	Mesh* GetPlatform();
	Mesh* platform;
	float baseWidth = 1.0f, baseHeight = 0.1f, baseLength = 2.0f;
	glm::vec3 color = glm::vec3(1, 4, 2);
private:
protected:

};