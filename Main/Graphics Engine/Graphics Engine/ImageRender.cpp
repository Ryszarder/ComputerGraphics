#include "ImageRender.h"
#include "Graphics.h"
#include "ShaderProgram.h"

ImageRender::ImageRender()
{
	glGenBuffers(1, &triangleID);

	float vertexData[] = { -0.5f, -0.5f,
							-0.5f, 0.5f,
							0.5f, 0.5f,
							0.5f, 0.5f,
							0.5f, -0.5f,
							-0.5f, -0.5f,
	};

	glBindBuffer(GL_ARRAY_BUFFER, triangleID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
}

ImageRender::~ImageRender()
{
}

void ImageRender::Draw(ShaderProgram shader)
{
	shader.UseShader();

	glBindBuffer(GL_ARRAY_BUFFER, triangleID);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}
