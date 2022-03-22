#include "ImageRenderer.h"
#include "Graphics.h"
#include "ShaderProgram.h"
#include <memory>
#include <algorithm>


ImageRenderer::ImageRenderer(int widthInit, int heightInit) : width(widthInit), height(heightInit)
{
	image = new unsigned char[width * height * 3];
	memset(image, 0, width * height * 3);	//Initialise image to black.

	glGenTextures(1, &textureID);

	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenBuffers(1, &quadBuffer);

	float vertexPositionData[] = {
		1.0f, 1.0f,
		-1.0f, -1.0f,
		1.0f, -1.0f,

		-1.0f, -1.0f,				
		1.0f, 1.0f,									
		-1.0f, 1.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, quadBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, vertexPositionData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ImageRenderer::~ImageRenderer()
{
	glDeleteBuffers(1, &quadBuffer);
	glDeleteTextures(1, &textureID);
	delete[] image;
}

void ImageRenderer::Draw(ShaderProgram* shader)
{

	shader->UseProgram();
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);



	GLuint texLocation = shader->GetUniformLocation("defaultTexture");
	glUniform1i(texLocation, 0);

	glBindBuffer(GL_ARRAY_BUFFER, quadBuffer);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	ShaderProgram::ClearPrograms();

}

void ImageRenderer::SetPixel(int x, int y, float red, float green, float blue)
{
	//Unsafe function! Setting a pixel outside the bounds of the screen might crash the program.
	unsigned char redChar = (unsigned char)(red * 255);
	unsigned char greenChar = (unsigned char)(green * 255);
	unsigned char blueChar = (unsigned char)(blue * 255);
	image[y * width * 3 + x * 3] = redChar;
	image[y * width * 3 + x * 3 + 1] = greenChar;
	image[y * width * 3 + x * 3 + 2] = blueChar;
}

float ImageRenderer::GetPixelChannel(int x, int y, int colour)
{
	return image[y * width * 3 + x * 3 + colour] / 255.0f;
}

void ImageRenderer::Clear()
{
	memset(image, 0, width * height * 3);
}
