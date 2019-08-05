#ifndef GPA_ASS2_PROGRAM_H
#define GPA_ASS2_PROGRAM_H

#include "Shader.h"

#include "GLIncludes.h"

class Program
{
public:
	Program(const char* vsPath, const char* fsPath);
	~Program();
	void use();
	GLuint getID();

private:
	GLuint ID;
};

#endif
