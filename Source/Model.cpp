#include "Model.h"

Model::Model() {}

Model::~Model()
{
	for(int i=0; i<meshes.size(); i++)
		delete meshes[i];
}

void Model::draw(Program* program)
{
	for (std::vector<Mesh*>::iterator mesh = this->meshes.begin(); mesh != this->meshes.end(); ++mesh)
	{
		(*mesh)->draw(program);
	}
}

void Model::addMesh(Mesh* mesh)
{
	this->meshes.push_back(mesh);
}
