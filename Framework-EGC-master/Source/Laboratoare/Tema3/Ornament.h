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

	Mesh* piramida;
private:
protected:
};