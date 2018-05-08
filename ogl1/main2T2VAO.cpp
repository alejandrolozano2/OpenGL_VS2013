#include <iostream>
#include <fstream>
//#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

//Callback for keyboard
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);


// The MAIN function, from here we start the application and run the game loop
int main()
{

	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;

	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow * window = glfwCreateWindow(WIDTH, HEIGHT, "My First VS OpenGL ", nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;

	/*Initialise GLEW*/
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	/*Tell openGL about size of rendering window*/
	glViewport(0, 0, WIDTH, HEIGHT);
	/*Set key callback function*/
	glfwSetKeyCallback(window, key_callback);

	Shader myShader;
	myShader.CreateProgram("Vertex.hlsl", "Frag.hlsl");

	//My triangle vertices
	GLfloat vertices1[] =
	{
		/*Square*/
		-0.25f, -0.25f, 0.0f,
		0.25f, -0.25f, 0.0f,
		0.25f, 0.25f, 0.0f,

	};

	//My triangle vertices
	GLfloat vertices2[] =
	{
		/*Square*/
		-0.1f, -0.1f, 0.0f,
		0.1f, 0.1f, 0.0f,
		-0.1f, 0.1f, 0.0f
	};

	GLuint VBO[2], VAO[2];
	//Create Vertex Array Object to store attributespointer and disable/enable attributes and EBO
	glGenVertexArrays(2, VAO);
	//Generate Buffer object, batch of data.. ussually vertices
	glGenBuffers(2, VBO);

	//Bind Vertex Array Object
	glBindVertexArray(VAO[0]);
	//Bind VBO as Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	//Copy Data, in this case vertices to the bound buffer. Data will not change or very rarely
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices1), vertices1, GL_STATIC_DRAW);
	/*Point to  Attrib pointer*/
	/* Attrib 0,  3 elements, type of element, not normalized,  stride next element after 3 GL_FLOATS, offset of firsrt element */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	/*Enable Vertex Attribute*/
	glEnableVertexAttribArray(0);
	//Unbind VBO. VBO binding is stored in Attributes
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//Unbind Vertex Array
	glBindVertexArray(0);


	//Bind Vertex Array Object
	glBindVertexArray(VAO[1]);
	//Bind VBO as Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	//Copy Data, in this case vertices to the bound buffer. Data will not change or very rarely
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	/*Point to  Attrib pointer*/
	/* Attrib 0,  3 elements, type of element, not normalized,  stride next element after 3 GL_FLOATS, offset of firsrt element */
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid *)0);
	/*Enable Vertex Attribute*/
	glEnableVertexAttribArray(0);
	//Unbind VBO. VBO binding is stored in Attributes
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//Unbind Vertex Array
	glBindVertexArray(0);


	while (!glfwWindowShouldClose(window))
	{
		/*poll for events like key press*/
		glfwPollEvents();

		/*Rendering Commands*/
		glClearColor(0.5f, 0.0f, 0.1f, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		/*Use this Shader program*/
		myShader.UseShader();
		glBindVertexArray(VAO[0]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		/*swap double buffer*/
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}


