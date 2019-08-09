#include "AssimpMesh.h"

AssimpMesh::AssimpMesh(aiMesh* mesh)
{
	/////////////////// VAO ///////////////////
	glGenBuffers(1, &this->vao);
	glBindVertexArray(this->vao);


	/////////////////// VBO ///////////////////
	std::vector<Vertex> vertices;
	for (unsigned int v = 0; v < mesh->mNumVertices; ++v)
	{
		glm::vec3 pos = glm::vec3(mesh->mVertices[v].x, mesh->mVertices[v].y, mesh->mVertices[v].z);
		glm::vec3 normal = glm::vec3(mesh->mNormals[v].x, mesh->mNormals[v].y, mesh->mNormals[v].z);
		glm::vec2 texcoord = glm::vec2(mesh->mTextureCoords[0][v].x, mesh->mTextureCoords[0][v].y);
		Vertex newVertex(pos, normal, texcoord);
		vertices.push_back(newVertex);
	}

	glGenBuffers(1, &this->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	// vertex pos, normal, texcoord
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));


	///////////////// VEO /////////////////////
	std::vector<unsigned int> indices;
	for (unsigned int f = 0; f < mesh->mNumFaces; ++f)
	{
		// mesh->mFaces[f].mIndices[0~2] => index
		aiFace face = mesh->mFaces[f];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	glGenBuffers(1, &this->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


	////////////////// OTHERS /////////////////
	this->materialID = mesh->mMaterialIndex;
	this->indexCount = mesh->mNumFaces * 3;
}

AssimpMesh::~AssimpMesh()
{

}

void AssimpMesh::draw()
{
	glBindVertexArray(this->vao);
	glBindTexture(GL_TEXTURE_2D, (*this->materialArray)[materialID]);	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);	glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, 0);
}

void AssimpMesh::setMaterialsArray(std::vector<GLuint>* material_array)
{
	this->materialArray = material_array;
}

