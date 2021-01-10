#include "CombustibilBar.h"


CombustibilBar::CombustibilBar() {
	{
		combustibilBar = new Mesh("sphere");
		combustibilBar->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		{
			combustibilBar = new Mesh("combustibilBar");
			glm::vec3  color = glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0);

			std::vector<VertexFormat> vertices =
			{
				VertexFormat(corner, color),//0
				VertexFormat(corner + glm::vec3(75, 0, 0), color),//1
				VertexFormat(corner + glm::vec3(75, 10, 0), color),//3
				VertexFormat(corner + glm::vec3(0, 10, 0), color),//2

			};

			std::vector<unsigned short> indices = { 0,1,2,3,0 };
			combustibilBar->SetDrawMode(GL_LINE_LOOP);
			combustibilBar->InitFromData(vertices, indices);
		}

		{
			powerLine = new Mesh("powerLine");
			glm::vec3  color = glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0);

			std::vector<VertexFormat> vertices =
			{
				VertexFormat(corner, color),//0
				VertexFormat(corner + glm::vec3(2, 0, 0), color),//1
				VertexFormat(corner + glm::vec3(2, 10, 0), color),//2
				VertexFormat(corner + glm::vec3(0, 10, 0), color),//3
			};

			std::vector<unsigned short> indices = { 1,0,3,
				3,2,1 };
			//powerLine->SetDrawMode(GL_LINE_LOOP);
			powerLine->InitFromData(vertices, indices);
		}

	}
}

CombustibilBar::~CombustibilBar() {
	delete combustibilBar;
}

Mesh* CombustibilBar::GetCombustibilBar() {
	return combustibilBar;
}

Mesh* CombustibilBar::GetPowerLine() {
	return powerLine;
}