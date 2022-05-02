#include "ImageRender.h"
#include "Graphics.h"
#include "ShaderProgram.h"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"

#include "Vertex.h"

ImageRender::ImageRender()
{
	glGenBuffers(1, &triangleID);

	//Cube
	Vertex vertices[] = {

		{{0.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
		{{0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
		{{1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},

		{{0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
		{{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
		{{1.0f, 0.0f, 1.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},

		{{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
		{{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
		{{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},

		{{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
		{{1.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},
		{{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}},

		{{0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
		{{0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
		{{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},

		{{0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
		{{0.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},
		{{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f}},

		{{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
		{{1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
		{{1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},

		{{1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
		{{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},
		{{1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0f}},

		{{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
		{{0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
		{{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},

		{{0.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f},{0.0f, -1.0f, 0.0f}},
		{{1.0f, 0.0f, 1.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},
		{{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}},

		{{0.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
		{{0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
		{{1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},

		{{0.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
		{{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
		{{1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},

	};
	glBindBuffer(GL_ARRAY_BUFFER, triangleID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &LightID);

	glBindBuffer(GL_ARRAY_BUFFER, LightID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
}

ImageRender::~ImageRender()
{
}

void ImageRender::Draw(ShaderProgram meshShader, ShaderProgram lightShader)
{
	meshShader.UseShader();
	lightShader.UseShader();

	glBindBuffer(GL_ARRAY_BUFFER, triangleID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(12));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(24));

	glm::mat4 projection = glm::perspective(3.14159f / 4, 1920.0f / 1080, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 rotImage = glm::rotate(glm::mat4(1), (float)glfwGetTime(), glm::vec3(0, 1, 0));
	glm::vec3 lightPos(2.0f, 2.0f, 0.0f);

	meshShader.SetUniform("mvpMatrix", projection * view * rotImage);
	meshShader.SetUniform("modelMatrix", rotImage);
	meshShader.SetUniform("lightPos", lightPos);
	meshShader.SetUniform("viewPos", glm::vec3(5, 5, 5));
	meshShader.SetUniform("lightColour", -glm::vec3(1.0f, 1.0f, 1.0f));

	glDrawArrays(GL_TRIANGLES, 0, 108);

	glBindBuffer(GL_ARRAY_BUFFER, LightID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	glm::mat4 model;
	model = glm::mat4(1.0f);
	model = glm::translate(model, lightPos);
	model = glm::scale(model, glm::vec3(0.2f));

	lightShader.SetUniform("mvpMatrix", projection * view * model);

	glDrawArrays(GL_TRIANGLES, 0, 108);
}
