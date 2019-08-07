#ifndef GPA_ASS2_MODEL_H
#define GPA_ASS2_MODEL_H

#include "Mesh.h"
#include "Program.h"
#include "Camera.h"
#include "GLIncludes.h"
#include <vector>

class Model
{
public:
	Model();
	~Model();
	void draw(Program* program);
	void addMesh(Mesh* mesh);
private:
	std::vector<Mesh*> meshes;
};

#endif

