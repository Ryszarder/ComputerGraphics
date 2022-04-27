#include "Graphics.h"

#include <math.h>
#include "Utilities.h"
#include "ShaderProgram.h"
#include "ImageRender.h"
#include "MeshRender.h"
#include "Camera.h"

#include <iostream>

#include "glm.hpp"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"

void ProcessInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void Mouse_Callback(GLFWwindow* window, double fxPos, double fyPos);
void scroll_callback(GLFWwindow* window, double fxOffset, double fyOffset);

Camera camera;
float m_fxLast = 1280.0f;
float m_fyLast = 720.0f;
bool m_bfirstMouse = true;

float m_fdeltaTime = 0.0f;
float m_flastFrame = 0.0f;

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

	glEnable(GL_DEPTH_TEST);

	//ImageRender image;
	MeshRender mesh;

	//ShaderProgram TriangleShader("SimpleShader.vsd", "SimpleShader.fsd");
	//ShaderProgram lightShader("LightShader.vsd", "LightShader.fsd");
	ShaderProgram meshShader("MeshShader.vsd", "MeshShader.fsd");

	//The main 'game' loop
	while (!glfwWindowShouldClose(window))
	{
		//Clear the screen - eventually do rendering code here
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float m_fcurrentFrame = (float)glfwGetTime();
		m_fdeltaTime = m_fcurrentFrame - m_flastFrame;
		m_flastFrame = m_fcurrentFrame;

		ProcessInput(window);

		//image.Draw(TriangleShader, lightShader);
		
		mesh.Draw(meshShader);

		//Swapping the buffers - this means this frame is over
		glfwSwapBuffers(window);

		//Tell GLFW to check if anything is going on with input, etc
		glfwPollEvents();
	}

	//If we get to this point, the window has close, so clean up GLFW and exit
	glfwTerminate();
	return 0;
}

void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyBoard(FORWARD, m_fdeltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyBoard(BACKWARD, m_fdeltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyBoard(LEFT, m_fdeltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyBoard(RIGHT, m_fdeltaTime);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Mouse_Callback(GLFWwindow* window, double fxPos, double fyPos)
{
	float m_fxPos = (float)fxPos;
	float m_fyPos = (float)fyPos;
	if (m_bfirstMouse)
	{
		m_fxLast = m_fxPos;
		m_fyLast = m_fyPos;
		m_bfirstMouse = false;
	}

	float m_fxOffSet = m_fxPos - m_fxLast;
	float m_fyOffSet = m_fxLast - m_fyPos;

	m_fxLast = m_fxPos;
	m_fyLast = m_fyPos;

	camera.ProcessMouseMovement(m_fxOffSet, m_fyOffSet);
}

void scroll_callback(GLFWwindow* window, double fxOffset, double fyOffset)
{
	camera.ProcessMouseScroll((float)(fyOffset));
}