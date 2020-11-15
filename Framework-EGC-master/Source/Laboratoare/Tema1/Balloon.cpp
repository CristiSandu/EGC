#include "Balloon.h"


Balloon::Balloon() {
	{
		std::vector<VertexFormat> vertices =
		{
			VertexFormat(corner, color),//0
			VertexFormat(corner + glm::vec3(10, 0, 0), color),//1
			VertexFormat(corner + glm::vec3(0, 5, 0), color),//2
			VertexFormat(corner + glm::vec3(10, 15, 0), color),//3
			VertexFormat(corner + glm::vec3(0, 20, 0), color),//4
			VertexFormat(corner + glm::vec3(5, 30, 0), color),//5
			VertexFormat(corner + glm::vec3(15, 30, 0), color),//6
			VertexFormat(corner + glm::vec3(5, 40, 0), color),//7
			VertexFormat(corner + glm::vec3(-5, 30, 0), color),//8
			VertexFormat(corner + glm::vec3(5, 85, 0), color),//9

		};

		std::vector<unsigned short> indices = { 1,2,3,4,5,6
											   ,7 };
		GLfloat degree, DEG2RAD = 3.14159 / 180.0;
		for (int i = 9; i < spaceBow + 10; i++)
		{
			degree = i * DEG2RAD;
			vertices.emplace_back(glm::vec3(5 + (squareSide / 4) * cos(degree), 90 + (squareSide / 2) * sin(degree), 0), color);
			indices.push_back(i);
		}

		indices.push_back(spaceBow + 10);
		indices.push_back(9);

		indices.push_back(7);

		indices.push_back(8);
		indices.push_back(5);
		indices.push_back(4);
		indices.push_back(3);
		indices.push_back(2);
		indices.push_back(1);

		balloon = new Mesh("balloon");

		balloon->SetDrawMode(GL_LINE_LOOP);
		balloon->InitFromData(vertices, indices);
	}
}

Balloon::~Balloon() {
	delete balloon;
}

Mesh* Balloon::GetBalloon() {
	return balloon;
}