#include "Graphics.h"

#include <math.h>
#include "Utilities.h"
#include "ShaderProgram.h"

#include <iostream>

#include "glm.hpp"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"

int main()
{
	GLFWwindow* window;
	
	//Initialise GLFW, make sure it works. Put an error message here if you like
	if (!glfwInit())
	{
		return -1;
	}

	//Set resolution here, and give your window a different title
	window = glfwCreateWindow(1280, 720, "Graphics", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate(); //Again, you can put a real error message here
		return -1;
	}

	//This tells GLFW that the window we created is the one we should render to
	glfwMakeContextCurrent(window);

	//Tell GLAF to load all it's OpenGL functions
	if (!gladLoadGL())
	{
		return -1;
	}

	ShaderProgram theShader("SimpleShader.vsd", "SimpleShader.fsd");

	GLuint triangleID;
	glGenBuffers(1, &triangleID);

	float aBunchOfFloats[] = { -0.5f, -0.5f,
								-0.5f, 0.5f,
								0.5f, 0.5f,
								0.5f, 0.5f,
								0.5f, -0.5f,
								-0.5f, -0.5f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, triangleID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, aBunchOfFloats, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);

	//The main 'game' loop
	while (!glfwWindowShouldClose(window))
	{
		//Clear the screen - eventually do rendering code here
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER, triangleID);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

		theShader.UseShader();

		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		//Swapping the buffers - this means this frame is over
		glfwSwapBuffers(window);

		//Tell GLFW to check if anything is going on with input, etc
		glfwPollEvents();
	}

	//If we get to this point, the window has close, so clean up GLFW and exit
	glfwTerminate();
	return 0;
}