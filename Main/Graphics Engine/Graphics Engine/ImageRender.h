#pragma once

#include "Graphics.h"

class ShaderProgram;

class ImageRender
{
public:
	ImageRender();
	~ImageRender();

	void Draw(ShaderProgram shader);

private:
	GLuint triangleID;
};

