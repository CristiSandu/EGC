#include "RanderItems.h"

#include <Core/Engine.h>

Mesh* RanderItems::CreateArrow(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),//0
		VertexFormat(corner + glm::vec3(5, 0, 0), color),//1
		VertexFormat(corner + glm::vec3(10, 0, 0), color),//2
		VertexFormat(corner + glm::vec3(90, 0, 0), color),//3
		VertexFormat(corner + glm::vec3(100, 0, 0), color),//4

		VertexFormat(corner + glm::vec3(0, -2.5, 0), color),//5
		VertexFormat(corner + glm::vec3(80, -5, 0), color),//6
		VertexFormat(corner + glm::vec3(80, 5, 0), color),//7
		VertexFormat(corner + glm::vec3(0, 2.5, 0), color),//8
		VertexFormat(corner + glm::vec3(9, 0.3, 0), color),//9
		VertexFormat(corner + glm::vec3(9, -0.3, 0), color),//10
		VertexFormat(corner + glm::vec3(90, 0.3, 0), color),//11
		VertexFormat(corner + glm::vec3(90, -0.3, 0), color),//12


	};

	Mesh* arrow = new Mesh(name);
	std::vector<unsigned short> indices = { 
		1,5,2,
		1,8,2,
		9,10,11,
		11,10,12,
		4,7,3,
		3,6,4
		};

	if (!fill) {
		arrow->SetDrawMode(GL_LINE_LOOP);

	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	arrow->InitFromData(vertices, indices);
	return arrow;
}

Mesh* RanderItems::CreateBow(std::string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill)
{
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices =
	{
		VertexFormat(corner, color),//0
		VertexFormat(corner + glm::vec3(5, 0, 0), color),//1
		VertexFormat(corner + glm::vec3(10, 0, 0), color),//2
		VertexFormat(corner + glm::vec3(90, 0, 0), color),//3
		VertexFormat(corner + glm::vec3(100, 0, 0), color),//4

		VertexFormat(corner + glm::vec3(0, -2.5, 0), color),//5
		VertexFormat(corner + glm::vec3(80, -5, 0), color),//6
		VertexFormat(corner + glm::vec3(80, 5, 0), color),//7
		VertexFormat(corner + glm::vec3(0, 2.5, 0), color),//8
		VertexFormat(corner + glm::vec3(9, 0.3, 0), color),//9
		VertexFormat(corner + glm::vec3(9, -0.3, 0), color),//10
		VertexFormat(corner + glm::vec3(90, 0.3, 0), color),//11
		VertexFormat(corner + glm::vec3(90, -0.3, 0), color),//12


	};

	Mesh* bow = new Mesh(name);
	std::vector<unsigned short> indices = {
		1,5,2,
		1,8,2,
		9,10,11,
		11,10,12,
		4,7,3,
		3,6,4
	};

	if (!fill) {
		bow->SetDrawMode(GL_LINE_LOOP);

	}
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}

	bow->InitFromData(vertices, indices);
	return bow;
}
