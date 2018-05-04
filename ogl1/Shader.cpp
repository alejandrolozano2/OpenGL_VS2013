#include "Shader.h"

/*Global variables with class scope. Same variables for each Shader object. They can only be accesed by the object as they are defined as private
  Static members of a class are not associated with the objects of the class: they are independent objects
*/
GLuint Shader::vertex_shader = 0;
GLuint Shader::fragment_shader = 0;

GLint Shader::CompileShader(GLuint & id, int shader, const char * path_to_shader)
{

	/*Read Vertex Shader progeam*/
	std::ifstream File(path_to_shader);
	std::string source_shader((std::istreambuf_iterator<char>(File)),
		std::istreambuf_iterator<char>());
	const char * source = source_shader.c_str();


	/*Create vertex Shader object, bind it to source and compile it*/
	id = glCreateShader(shader);
	glShaderSource(id, 1, &source, NULL);
	glCompileShader(id);
	/*Get Compiling status*/
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(id, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	File.close();
	return success;
}

GLint Shader::CreateProgram(const char * path_to_vertex , const char * path_to_fragment)
{
	GLint ret;

	ret = CompileShader(vertex_shader, GL_VERTEX_SHADER, path_to_vertex);
	if (!ret)
	{ 
		glDeleteShader(vertex_shader);
		return ret;
	}
	
	ret = CompileShader(fragment_shader, GL_FRAGMENT_SHADER, path_to_fragment);
	if (!ret)
	{
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		return ret;
	}

	ret = CreateShaderProgram();
	if (!ret)
	{
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);
		return ret;
	}

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	
	return CreateShaderProgram();
}


GLint Shader::CreateShaderProgram()
{
	/*Link shaders*/
	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shader);
	glAttachShader(shader_program, fragment_shader);
	glLinkProgram(shader_program);

	GLint success;
	GLchar infoLog[512];
	/*Check Linking Status*/
	glGetShaderiv(shader_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader_program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::LINKING_FAILED\n" << infoLog << std::endl;
	}

	return success;
}

void Shader::UseShader()
{
	glUseProgram(shader_program);
	 
}