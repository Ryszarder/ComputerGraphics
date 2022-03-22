#pragma once

class ShaderProgram;

#include "Graphics.h"

class ImageRenderer
{
private:
	//unsigned char image[HEIGHT][WIDTH][3];

	unsigned char* image = nullptr;
	int width = 0;
	int height = 0;
	GLuint textureID;
	GLuint quadBuffer;

public:
	ImageRenderer(int widthInit, int heightInit);
	~ImageRenderer();

	void Draw(ShaderProgram* shader);


	void SetPixel(int x, int y, float red, float green, float blue);
	float GetPixelChannel(int x, int y, int colour);

	void Clear();

	//Add whatever draw functions here that you can think of!

};