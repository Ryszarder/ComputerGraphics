#include "ImageRender.h"
#include "Graphics.h"
#include "ShaderProgram.h"

ImageRender::ImageRender()
{
	//glGenBuffers(1, &triangleID);

	//float positionData[] = { -0.5f, -0.5f,
	//						 -0.5f, 1.0f,
	//						 0.0f, 1.0f };

	//glBindBuffer(GL_ARRAY_BUFFER, triangleID);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, positionData, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glEnableVertexAttribArray(0);
}

ImageRender::~ImageRender()
{

}

void ImageRender::Draw(ShaderProgram* shader)
{
	//glBindBuffer(GL_ARRAY_BUFFER, triangleID);

	//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//theShader.UseShader();

	//glDrawArrays(GL_TRIANGLES, 0, 6);
}