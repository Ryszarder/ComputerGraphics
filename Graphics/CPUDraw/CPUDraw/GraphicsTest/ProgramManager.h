#pragma once
#include "Graphics.h"
#include "ShaderProgram.h"
#include "ImageRenderer.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define PIXEL_SCALE 10

class ProgramManager
{

private:
	GLFWwindow* window = nullptr;
	ShaderProgram* simpleShader = nullptr;
	ImageRenderer* image = nullptr;

	int mouseX = 0;
	int mouseY = 0;
	bool mouseLeftDown = false;
	bool mouseRightDown = false;

	void UpdateMouseState();

public:
	bool Initialise();
	void Run();
	void ShutDown();

private:
	void Draw();
};