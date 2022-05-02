#pragma once

#include "Graphics.h"

class ShaderProgram;

class ImageRender
{
public:
	ImageRender();
	~ImageRender();

	void Draw(ShaderProgram meshShader, ShaderProgram lightShader);

private:
	GLuint triangleID;
	GLuint LightID;
};

