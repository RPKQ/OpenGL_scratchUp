#ifndef GPA_ASS2_ASSIMP_MESH_H
#define GPA_ASS2_ASSIMP_MESH_H

#include "GLIncludes.h"
#include <vector>
#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/postprocess.h>

typedef struct Vertex {
	glm::vec3 pos;
	glm::vec3 normal;
	glm::vec2 texCoord;
	Vertex(glm::vec3 Pos, glm::vec3 Normal, glm::vec2 TexCoord) {
		pos = Pos;
		normal = Normal;
		texCoord = TexCoord;
	}
} Vertex;

class AssimpMesh
{
public:
	AssimpMesh(aiMesh* mesh);
	~AssimpMesh();
private:

	GLuint vao;
	GLuint ebo;
	GLuint vbo;
	int materialID, indexCount;
};

#endif