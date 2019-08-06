#ifndef GPA_ASS2_MODEL_H
#define GPA_ASS2_MODEL_H

#include "Mesh.h"
#include "Program.h"
#include "GLIncludes.h"

class Model
{
public:
	Model(const char* filePath);
	~Model();
	void draw(Program* program);
private:
	std::vector<Mesh*> meshes;
};

#endif

