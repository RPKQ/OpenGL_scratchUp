#include "Shader.h"

Shader::Shader(GLenum shaderType, const char* filePath)
{
	this->ID = glCreateShader(shaderType);

	char** shaderSource = Shader::loadShaderSource(filePath);
	glShaderSource(this->ID, 1, shaderSource, NULL);
	freeShaderSource(shaderSource);

	glCompileShader(this->ID);
	shaderLog(this->ID);
}


Shader::~Shader()
{
	glDeleteShader(this->ID);
}

GLuint Shader::getID()
{
	return this->ID;
}

char** Shader::loadShaderSource(const char* filePath)
{
	FILE* fp = fopen(filePath, "rb");
	fseek(fp, 0, SEEK_END);
	long sz = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char *src = new char[sz + 1];
	fread(src, sizeof(char), sz, fp);
	src[sz] = '\0';
	char **srcp = new char*[1];
	srcp[0] = src;
	return srcp;
}

void Shader::freeShaderSource(char** shaderSource)
{
	delete shaderSource[0];
	delete shaderSource;
}
