#ifndef GPA_ASS2_MESH_H
#define GPA_ASS2_MESH_H

#include "Program.h"
#include "GLIncludes.h"

struct Texture {
	GLuint id;
	std::string path;
	std::string type;
};

class Mesh
{
public:
	Mesh();
	~Mesh();
	void draw(Program program);
private:
	GLuint vao;
	GLuint vbo_pos, vbo_normal, vbo_texCoord;
	GLuint ebo;		// ELEMENT_ARRAY_BUFFER
	GLuint texure;
	int materialID, indexCount;

};
#endif

