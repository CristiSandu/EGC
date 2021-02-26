#pragma once
#include <Component\SimpleScene.h>
#include <Core/Engine.h>
#include <vector>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>

class Ornament {
public:
	Ornament();
	~Ornament();

	Mesh* GetPiramide();
	Mesh* GetPiramideStyle();

	Mesh* piramida;
	Mesh* tetraedru;
	Mesh* stylishPiramide;
	Mesh* skull;
	glm::vec3 GREY = glm::vec3(.5, .5, .5); //grey

private:
protected:
};