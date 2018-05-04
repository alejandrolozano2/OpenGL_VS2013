#ifndef SHADER_H
#define SHADE_H

#include <iostream>
#include <fstream>
// GLEW
#include <GL/glew.h>



class Shader
{

private:
	GLuint shader_program;
	static GLuint vertex_shader;
	static GLuint fragment_shader;
	GLint CompileShader(GLuint & id, int, const char *);
	GLint CreateShaderProgram();


public:
	GLint CreateProgram(const char *, const char *);
	void UseShader();

};



#endif