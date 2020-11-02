#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

namespace RanderItems
{

	// Create square with given bottom left corner, length and color
	Mesh* CreateArrow(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);

	Mesh* CreateBow(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill);

}

