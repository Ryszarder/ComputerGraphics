#include "ImageRender.h"
#include "Graphics.h"
#include "ShaderProgram.h"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"

ImageRender::ImageRender()
{
	glGenBuffers(1, &triangleID);

	float vertexData[] = { 
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

ImageRender::~ImageRender()
{
}

void ImageRender::Draw(ShaderProgram shader)
{
	shader.UseShader();

	glBindBuffer(GL_ARRAY_BUFFER, triangleID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));

	glm::mat4 projection = glm::perspective(3.14159f / 4, 1920.0f / 1080, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 rotImage = glm::rotate(glm::mat4(1), (float)glfwGetTime(), glm::vec3(0, 1, 0));

	shader.SetUniform("mvpMatrix", projection * view * rotImage);
	shader.SetUniform("modelMatrix", rotImage);
	shader.SetUniform("fromLight", -glm::normalize(glm::vec3(1, 1, 1)));

	glDrawArrays(GL_TRIANGLES, 0, 108);
}
