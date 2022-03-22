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

	GLFWwindow* window;	//The pointer to the GLFW window that gives us a place to draw.


	if (!glfwInit())
		return -1;	//glfw failed to initialise.

	//Can choose resolution here.
	window = glfwCreateWindow(1280, 720, "GPU Graphics", nullptr, nullptr);

	if (!window)
	{
		//If the window failed to create for some reason, abandon ship.
		glfwTerminate();
		return -1;
	}

	//We have to tell glfw to use the OpenGL context from the window.
	//This stuff can be relevant if you have multiple windows - you're
	//telling OpenGL which one to apply render commands to.
	//But if we only have one window we just do this once at the start.
	glfwMakeContextCurrent(window);

	//This is where GLAD gets set up. After this point we can use openGL functions.
	if (!gladLoadGL())
		return -1;

	glEnable(GL_DEPTH_TEST);

	ShaderProgram aShader("SimpleShader.vsd", "SimpleShader.fsd");


	GLuint triangleID;
	glGenBuffers(1, &triangleID);

	float aBunchOfFloats[] = {

		0, 0, 1,   1, 0, 0,   0, 0, 1,
		0, 1, 1,   1, 0, 0,   0, 0, 1,
		1, 0, 1,   1, 0, 0,   0, 0, 1,
		0, 1, 1,   1, 0, 0,   0, 0, 1,
		1, 1, 1,   1, 0, 0,   0, 0, 1,
		1, 0, 1,   1, 0, 0,   0, 0, 1,

		0, 0, 0,   0, 0, 1,   0, 0, -1,
		0, 1, 0,   0, 0, 1,   0, 0, -1,
		1, 0, 0,   0, 0, 1,   0, 0, -1,
		0, 1, 0,   0, 0, 1,   0, 0, -1,
		1, 1, 0,   0, 0, 1,   0, 0, -1,
		1, 0, 0,   0, 0, 1,   0, 0, -1,

		0, 0, 0,   0, 1, 0,   -1, 0, 0,
		0, 0, 1,   0, 1, 0,   -1, 0, 0,
		0, 1, 0,   0, 1, 0,   -1, 0, 0,
		0, 0, 1,   0, 1, 0,   -1, 0, 0,
		0, 1, 1,   0, 1, 0,   -1, 0, 0,
		0, 1, 0,   0, 1, 0,   -1, 0, 0,

		1, 0, 0,   0, 1, 1,   1, 0, 0,
		1, 0, 1,   0, 1, 1,   1, 0, 0,
		1, 1, 0,   0, 1, 1,   1, 0, 0,
		1, 0, 1,   0, 1, 1,   1, 0, 0,
		1, 1, 1,   0, 1, 1,   1, 0, 0,
		1, 1, 0,   0, 1, 1,   1, 0, 0,

		0, 0, 0,   1, 1, 0,   0, -1, 0,
		0, 0, 1,   1, 1, 0,   0, -1, 0,
		1, 0, 0,   1, 1, 0,   0, -1, 0,
		0, 0, 1,   1, 1, 0,   0, -1, 0,
		1, 0, 1,   1, 1, 0,   0, -1, 0,
		1, 0, 0,   1, 1, 0,   0, -1, 0,

		0, 1, 0,   1, 0, 1,   0, 1, 0,
		0, 1, 1,   1, 0, 1,   0, 1, 0,
		1, 1, 0,   1, 0, 1,   0, 1, 0,
		0, 1, 1,   1, 0, 1,   0, 1, 0,
		1, 1, 1,   1, 0, 1,   0, 1, 0,
		1, 1, 0,   1, 0, 1,   0, 1, 0,

	
	};

	glBindBuffer(GL_ARRAY_BUFFER, triangleID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(aBunchOfFloats), aBunchOfFloats, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	
	while (!glfwWindowShouldClose(window))
	{

		//Your game goes here.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER, triangleID);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));

		aShader.UseShader();

		glm::mat4 rotMat = glm::rotate(glm::mat4(1), (float)glfwGetTime(), glm::vec3(0, 1, 0));

		glm::mat4 view = glm::lookAt(glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0, 2, 0));

		//FIXME this hardcoded projection matrix kind of sucks, do it properly!
		glm::mat4 projection = glm::perspective(3.14159f / 4, 1920.0f / 1080, 0.1f, 100.0f);

		aShader.SetUniform("mvpMatrix", projection * view * rotMat);
		aShader.SetUniform("modelMatrix", rotMat);
		aShader.SetUniform("fromLight", -glm::normalize(glm::vec3(1, 1, 1)));


		glDrawArrays(GL_TRIANGLES, 0, 108);


		glfwSwapBuffers(window);


		glfwPollEvents();
	}


	glfwTerminate();
	return 0;
}