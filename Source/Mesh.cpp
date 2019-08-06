#include "Mesh.h"


Mesh::Mesh(GLuint VAO, GLuint VBO_POS, GLuint VBO_NORMAL, GLuint VBO_TEXCOORD, GLuint EBO, GLuint TEXTURE, int MATERIAL_ID, int INDEX_COUNT)
{
	vao = VAO;
	vbo_pos = VBO_POS;
	vbo_normal = VBO_NORMAL;
	vbo_texCoord = VBO_TEXCOORD;
	ebo = EBO;
	texure = TEXTURE;
	materialID = MATERIAL_ID;
	indexCount = INDEX_COUNT;
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &(this->vao));
	glDeleteBuffers(1, &(this->vbo_pos));
	glDeleteBuffers(1, &(this->vbo_normal));
	glDeleteBuffers(1, &(this->vbo_texCoord));
	glDeleteBuffers(1, &(this->ebo));
	glDeleteTextures(1, &(this->texure));
}

void Mesh::draw(Program* program)
{
	program->use();
	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, 0);
}