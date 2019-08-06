#ifndef GPA_ASS2_MESH_H
#define GPA_ASS2_MESH_H

#include "Program.h"
#include "GLIncludes.h"

class Mesh
{
public:
	Mesh(GLuint VAO, GLuint VBO_POS, GLuint VBO_NORMAL, 
		GLuint VBO_TEXCOORD, GLuint EBO, GLuint TEXTURE, int MATERIAL_ID, int INDEX_COUNT);
	~Mesh();
	void draw(Program* program);
private:
	GLuint vao;
	GLuint vbo_pos, vbo_normal, vbo_texCoord;
	GLuint ebo;		// ELEMENT_ARRAY_BUFFER
	GLuint texure;
	int materialID, indexCount;

};
#endif

