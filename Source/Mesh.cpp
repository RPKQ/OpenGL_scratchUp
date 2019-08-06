#include "Mesh.h"


Mesh::Mesh(tinyobj::shape_t shape)
{
	glGenVertexArrays(1, &(this->vao));
	glBindVertexArray(this->vao);

	// position
	glGenBuffers(1, &(this->vbo_pos));
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_pos);
	glBufferData(GL_ARRAY_BUFFER, shape.mesh.positions.size() * sizeof(float), shape.mesh.positions.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// normal
	glGenBuffers(1, &(this->vbo_normal));
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_normal);
	glBufferData(GL_ARRAY_BUFFER, shape.mesh.positions.size() * sizeof(float), shape.mesh.normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// texCoord
	glGenBuffers(1, &(this->vbo_texCoord));
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo_texCoord);
	glBufferData(GL_ARRAY_BUFFER, shape.mesh.positions.size() * sizeof(float), shape.mesh.texcoords.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// index buffer
	glGenBuffers(1, &(this->ebo));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.mesh.indices.size() * sizeof(unsigned int), shape.mesh.indices.data(), GL_STATIC_DRAW);
	
	// others
	this->materialID = shape.mesh.material_ids[0];
	this->indexCount= shape.mesh.indices.size();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}


Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &(this->vao));
	glDeleteBuffers(1, &(this->vbo_pos));
	glDeleteBuffers(1, &(this->vbo_normal));
	glDeleteBuffers(1, &(this->vbo_texCoord));
	glDeleteBuffers(1, &(this->ebo));
}

void Mesh::draw(Program* program)
{
	program->use();
	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, 0);
}