#include "Program.h"

Program::Program(const char* vsPath, const char* fsPath)
{
	this->ID = glCreateProgram();
	
	// Shader
	Shader* vs = new Shader(GL_VERTEX_SHADER, vsPath);
	Shader* fs = new Shader(GL_VERTEX_SHADER, fsPath);
	glAttachShader(this->ID, vs->getID());
	glAttachShader(this->ID, fs->getID());
	//delete vs;
	//delete fs;

	// Link Program
	GLint Success = 0;
	GLchar ErrorLog[1024] = { 0 };
	glLinkProgram(this->ID);
	/*glGetProgramiv(this->ID, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(this->ID, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", ErrorLog);
		system("pause");
		//exit(1);
	}

	// Validate Program
	glValidateProgram(this->ID);
	glGetProgramiv(this->ID, GL_VALIDATE_STATUS, &Success);
	if (!Success) {
		glGetProgramInfoLog(this->ID, sizeof(ErrorLog), NULL, ErrorLog);
		fprintf(stderr, "Invalid shader program: '%s'\n", ErrorLog);
		system("pause");
		//exit(1);
	}*/
}

Program::~Program()
{
	glDeleteProgram(this->ID);
}

void Program::Use()
{
	glUseProgram(this->ID);
}

GLuint Program::getID()
{
	return this->ID;
}