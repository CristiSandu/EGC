#include "Ornament.h"

using namespace std;

Ornament::Ornament() {
	{
		piramida = new Mesh("piramida");
		vector<VertexFormat> vertices
		{
			VertexFormat(glm::vec3(0, 0, 0), glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0)),
			VertexFormat(glm::vec3(4, 0, 0), glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0)),
			VertexFormat(glm::vec3(4, 0, 4), glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0)),
			VertexFormat(glm::vec3(0, 0, 4), glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0)),
			VertexFormat(glm::vec3(2, 4, 2), glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0)),

			// TODO: Complete the information for the cube
		};

		vector<unsigned short> indices =
		{
			2, 1, 0,	// indices for second triangle
			0, 3, 2,
			4, 3, 0,	// indices for first triangle
			4, 0, 1,
			2, 3, 4,
			4, 1, 2,
			// TODO: Complete indices data
		};
		

		piramida->InitFromData(vertices,indices);
		/*Mesh* piramida = CreateMesh("piramida", vertices, indices);
		meshes[piramida->GetMeshID()] = piramida;*/
	}
}


Ornament::~Ornament() {
	delete piramida;
}

Mesh* Ornament::GetPiramide() {
	return piramida;
}