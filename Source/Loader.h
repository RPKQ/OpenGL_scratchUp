#ifndef GPA_ASS2_LOADER_H
#define GPA_ASS2_LOADER_H

#include "Model.h"
#include "Mesh.h"

#ifndef STB_IMAGE_IMPLEMENTATION_HH
#define STB_IMAGE_IMPLEMENTATION_HH
#define STB_IMAGE_IMPLEMENTATION
#endif // !STB_IMAGE_IMPLEMENTATION
#ifndef TINYOBJLOADER_IMPLMENTATION_HH
#define TINYOBJLOADER_IMPLMENTATION_HH
#define TINYOBJLOADER_IMPLEMENTATION
#endif // !TINYOBJLOADER_IMPLMENTATION

#include "../Include/TinyOBJ/tiny_obj_loader.h"
#include "../Include/STB/stb_image.h"

namespace Loader
{
	typedef struct _texture_data
	{
		_texture_data() : width(0), height(0), data(0) {}
		int width;
		int height;
		unsigned char* data;
	} texture_data;

	texture_data load_png(const char* path)
	{
		texture_data texture;
		int n;
		stbi_uc *data = stbi_load(path, &texture.width, &texture.height, &n, 4);
		if (data != NULL)
		{
			texture.data = new unsigned char[texture.width * texture.height * 4 * sizeof(unsigned char)];
			memcpy(texture.data, data, texture.width * texture.height * 4 * sizeof(unsigned char));
			// vertical-mirror image data
			for (size_t i = 0; i < texture.width; i++)
			{
				for (size_t j = 0; j < texture.height / 2; j++)
				{
					for (size_t k = 0; k < 4; k++) {
						std::swap(texture.data[(j * texture.width + i) * 4 + k], texture.data[((texture.height - j - 1) * texture.width + i) * 4 + k]);
					}
				}
			}
			stbi_image_free(data);
		}
		return texture;
	}

	Mesh* loadMesh(tinyobj::shape_t shape)
	{
		GLuint vao = 0;
		GLuint vbo_pos = 0;
		GLuint vbo_normal = 0;
		GLuint vbo_texCoord = 0;
		GLuint ebo = 0;
		GLuint texture = 0;
		int materialID = 0, indexCount = 0;

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// position
		glGenBuffers(1, &vbo_pos);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_pos);
		glBufferData(GL_ARRAY_BUFFER, shape.mesh.positions.size() * sizeof(float), shape.mesh.positions.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// normal
		glGenBuffers(1, &vbo_normal);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_normal);
		glBufferData(GL_ARRAY_BUFFER, shape.mesh.normals.size() * sizeof(float), shape.mesh.normals.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// texCoord
		glGenBuffers(1, &vbo_texCoord);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_texCoord);
		glBufferData(GL_ARRAY_BUFFER, shape.mesh.texcoords.size() * sizeof(float), shape.mesh.texcoords.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

		// index buffer
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.mesh.indices.size() * sizeof(unsigned int), shape.mesh.indices.data(), GL_STATIC_DRAW);

		// others
		materialID = shape.mesh.material_ids[0];
		indexCount = shape.mesh.indices.size();

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		Mesh* mesh = new Mesh(vao, vbo_pos, vbo_normal, vbo_texCoord, ebo, texture, materialID, indexCount);
		return mesh;
	}

	Model* loadModel(const char* filePath)
	{
		// Load the .obj using "tinyobj"
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string err;

		bool ret = tinyobj::LoadObj(shapes, materials, err, filePath);
		if (err.size() > 0)
		{
			printf("Load Models Fail! Please check the solution path");
			system("pause");
			exit(1);
		}
		printf("Load Model %s Success ! Shapes size %d Maerial size %d\n", filePath, shapes.size(), materials.size());

		// Load them into meshes
		Model* model = new Model();
		int size = shapes.size();
		for (int i = 0; i < size; i++)
		{
			Mesh* mesh = loadMesh(shapes[i]);
			model->addMesh(mesh);
		}
		return model;
	}


}

#endif // !GPA_ASS2_LOADER_H
