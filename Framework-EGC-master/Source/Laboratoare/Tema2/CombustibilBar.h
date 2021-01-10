#pragma once
#include <Component\SimpleScene.h>
#include <Core/Engine.h>

class CombustibilBar {
public:
	CombustibilBar();
	~CombustibilBar();
	Mesh* GetCombustibilBar();
	Mesh* GetPowerLine();
	Mesh* combustibilBar;
	Mesh* powerLine;
	glm::vec3 corner = glm::vec3(0, 0, 0);
private:
protected:

};