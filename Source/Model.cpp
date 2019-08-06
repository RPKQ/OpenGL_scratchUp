#include "Model.h"

Model::Model(const char* filePath)
{
	// Load the .obj using "tinyobj"
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	bool ret = tinyobj::LoadObj(shapes, materials, err, filePath);
	if (err.size() > 0)
	{
		printf("Load Models Fail! Please check the solution path");
		return;
	}
	printf("Load Models Success ! Shapes size %d Maerial size %d\n", shapes.size(), materials.size());

	// Load them into meshes
	int size = shapes.size();
	for (int i = 0; i < size; i++)
	{
		Mesh* newMesh = new Mesh(shapes[i]);
		this->meshes.push_back(newMesh);
	}
}

Model::~Model()
{

}

void Model::draw(Program* program)
{
	for (int i = 0; i < this->meshes.size(); i++)
	{
		meshes[i]->draw(program);
	}
}
