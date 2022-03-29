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
	Vertex vertices[36];
	vertices[0].m_Vposition  = {0.0f, 0.0f, 1.0f};	vertices[0].m_Vcolour  = {1.0f, 0.0f, 0.0f};	vertices[0].m_Vnormal  = {0.0f, 0.0f, 1.0f};
	vertices[1].m_Vposition  = {0.0f, 1.0f, 1.0f};	vertices[1].m_Vcolour  = {1.0f, 0.0f, 0.0f};	vertices[1].m_Vnormal  = {0.0f, 0.0f, 1.0f};
	vertices[2].m_Vposition  = {1.0f, 0.0f, 1.0f};	vertices[2].m_Vcolour  = {1.0f, 0.0f, 0.0f};	vertices[2].m_Vnormal  = {0.0f, 0.0f, 1.0f};
	
	vertices[3].m_Vposition  = {0.0f, 1.0f, 1.0f};	vertices[3].m_Vcolour  = {1.0f, 0.0f, 0.0f};	vertices[3].m_Vnormal  = {0.0f, 0.0f, 1.0f};
	vertices[4].m_Vposition  = {1.0f, 1.0f, 1.0f};	vertices[4].m_Vcolour  = {1.0f, 0.0f, 0.0f};	vertices[4].m_Vnormal  = {0.0f, 0.0f, 1.0f};
	vertices[5].m_Vposition  = {1.0f, 0.0f, 1.0f};	vertices[5].m_Vcolour  = {1.0f, 0.0f, 0.0f};	vertices[5].m_Vnormal  = {0.0f, 0.0f, 1.0f};

	vertices[6].m_Vposition  = {0.0f, 0.0f, 0.0f};	vertices[6].m_Vcolour  = {0.0f, 0.0f, 1.0f};	vertices[6].m_Vnormal  = {0.0f, 0.0f, -1.0f};
	vertices[7].m_Vposition  = {0.0f, 1.0f, 0.0f};	vertices[7].m_Vcolour  = {0.0f, 0.0f, 1.0f};	vertices[7].m_Vnormal  = {0.0f, 0.0f, -1.0f};
	vertices[8].m_Vposition  = {1.0f, 0.0f, 0.0f};	vertices[8].m_Vcolour  = {0.0f, 0.0f, 1.0f};	vertices[8].m_Vnormal  = {0.0f, 0.0f, -1.0f};

	vertices[9].m_Vposition  = {0.0f, 1.0f, 0.0f};	vertices[9].m_Vcolour  = {0.0f, 0.0f, 1.0f};    vertices[9].m_Vnormal  = {0.0f, 0.0f, -1.0f};
	vertices[10].m_Vposition = {1.0f, 1.0f, 0.0f};	vertices[10].m_Vcolour = {0.0f, 0.0f, 1.0f};	vertices[10].m_Vnormal = {0.0f, 0.0f, -1.0f};
	vertices[11].m_Vposition = {1.0f, 0.0f, 0.0f};	vertices[11].m_Vcolour = {0.0f, 0.0f, 1.0f};	vertices[11].m_Vnormal = {0.0f, 0.0f, -1.0f};

	vertices[12].m_Vposition = {0.0f, 0.0f, 0.0f};	vertices[12].m_Vcolour = {0.0f, 1.0f, 0.0f};	vertices[12].m_Vnormal = {-1.0f, 0.0f, 0.0f};
	vertices[13].m_Vposition = {0.0f, 0.0f, 1.0f};	vertices[13].m_Vcolour = {0.0f, 1.0f, 0.0f};	vertices[13].m_Vnormal = {-1.0f, 0.0f, 0.0f};
	vertices[14].m_Vposition = {0.0f, 1.0f, 0.0f};	vertices[14].m_Vcolour = {0.0f, 1.0f, 0.0f};	vertices[14].m_Vnormal = {-1.0f, 0.0f, 0.0f};

	vertices[15].m_Vposition = {0.0f, 0.0f, 1.0f};	vertices[15].m_Vcolour = {0.0f, 1.0f, 0.0f};	vertices[15].m_Vnormal = {-1.0f, 0.0f, 0.0f};
	vertices[16].m_Vposition = {0.0f, 1.0f, 1.0f};	vertices[16].m_Vcolour = {0.0f, 1.0f, 0.0f};	vertices[16].m_Vnormal = {-1.0f, 0.0f, 0.0f};
	vertices[17].m_Vposition = {0.0f, 1.0f, 0.0f};	vertices[17].m_Vcolour = {0.0f, 1.0f, 0.0f};	vertices[17].m_Vnormal = {-1.0f, 0.0f, 0.0f};

	vertices[18].m_Vposition = {1.0f, 0.0f, 0.0f};	vertices[18].m_Vcolour = {0.0f, 1.0f, 1.0f};	vertices[18].m_Vnormal = {1.0f, 0.0f, 0.0f};
	vertices[19].m_Vposition = {1.0f, 0.0f, 1.0f};	vertices[19].m_Vcolour = {0.0f, 1.0f, 1.0f};	vertices[19].m_Vnormal = {1.0f, 0.0f, 0.0f};
	vertices[20].m_Vposition = {1.0f, 1.0f, 0.0f};	vertices[20].m_Vcolour = {0.0f, 1.0f, 1.0f};	vertices[20].m_Vnormal = {1.0f, 0.0f, 0.0f};

	vertices[21].m_Vposition = {1.0f, 0.0f, 1.0f};	vertices[21].m_Vcolour = {0.0f, 1.0f, 1.0f};	vertices[21].m_Vnormal = {1.0f, 0.0f, 0.0f};
	vertices[22].m_Vposition = {1.0f, 1.0f, 1.0f};	vertices[22].m_Vcolour = {0.0f, 1.0f, 1.0f};	vertices[22].m_Vnormal = {1.0f, 0.0f, 0.0f};
	vertices[23].m_Vposition = {1.0f, 1.0f, 0.0f};	vertices[23].m_Vcolour = {0.0f, 1.0f, 1.0f};	vertices[23].m_Vnormal = {1.0f, 0.0f, 0.0f};

	vertices[24].m_Vposition = {0.0f, 0.0f, 0.0f};	vertices[24].m_Vcolour = {1.0f, 1.0f, 0.0f};	vertices[24].m_Vnormal = {0.0f, -1.0f, 0.0f};
	vertices[25].m_Vposition = {0.0f, 0.0f, 1.0f};	vertices[25].m_Vcolour = {1.0f, 1.0f, 0.0f};	vertices[25].m_Vnormal = {0.0f, -1.0f, 0.0f};
	vertices[26].m_Vposition = {1.0f, 0.0f, 0.0f};	vertices[26].m_Vcolour = {1.0f, 1.0f, 0.0f};	vertices[26].m_Vnormal = {0.0f, -1.0f, 0.0f};

	vertices[27].m_Vposition = {0.0f, 0.0f, 1.0f};	vertices[27].m_Vcolour = {1.0f, 1.0f, 0.0f};	vertices[27].m_Vnormal = {0.0f, -1.0f, 0.0f};
	vertices[28].m_Vposition = {1.0f, 0.0f, 1.0f};	vertices[28].m_Vcolour = {1.0f, 1.0f, 0.0f};	vertices[28].m_Vnormal = {0.0f, -1.0f, 0.0f};
	vertices[29].m_Vposition = {1.0f, 0.0f, 0.0f};	vertices[29].m_Vcolour = {1.0f, 1.0f, 0.0f};	vertices[29].m_Vnormal = {0.0f, -1.0f, 0.0f};

	vertices[30].m_Vposition = {0.0f, 1.0f, 0.0f};	vertices[30].m_Vcolour = {1.0f, 0.0f, 1.0f};	vertices[30].m_Vnormal = {0.0f, 1.0f, 0.0f};
	vertices[31].m_Vposition = {0.0f, 1.0f, 1.0f};	vertices[31].m_Vcolour = {1.0f, 0.0f, 1.0f};	vertices[31].m_Vnormal = {0.0f, 1.0f, 0.0f};
	vertices[32].m_Vposition = {1.0f, 1.0f, 0.0f};	vertices[32].m_Vcolour = {1.0f, 0.0f, 1.0f};	vertices[32].m_Vnormal = {0.0f, 1.0f, 0.0f};

	vertices[33].m_Vposition = {0.0f, 1.0f, 1.0f};	vertices[33].m_Vcolour = {1.0f, 0.0f, 1.0f};	vertices[33].m_Vnormal = {0.0f, 1.0f, 0.0f};
	vertices[34].m_Vposition = {1.0f, 1.0f, 1.0f};	vertices[34].m_Vcolour = {1.0f, 0.0f, 1.0f};	vertices[34].m_Vnormal = {0.0f, 1.0f, 0.0f};
	vertices[35].m_Vposition = {1.0f, 1.0f, 0.0f};	vertices[35].m_Vcolour = {1.0f, 0.0f, 1.0f};	vertices[35].m_Vnormal = {0.0f, 1.0f, 0.0f};

	glBindBuffer(GL_ARRAY_BUFFER, triangleID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	//pyramid 
	//Vertex vertices[18];
	//vertices[0].m_Vposition  = {0, 1, 0};		vertices[0].m_Vcolour  = {1, 0, 0};		vertices[0].m_Vnormal  = {0, 0, 1};
	//vertices[1].m_Vposition  = {-1, -1, 1};		vertices[1].m_Vcolour  = {0, 0, 1};		vertices[1].m_Vnormal  = {0, 0, 1};
	//vertices[2].m_Vposition  = {1, -1, 1 };		vertices[2].m_Vcolour  = {0, 1, 0};		vertices[2].m_Vnormal  = {0, 0, 1};

	//vertices[3].m_Vposition  = {0, 1, 0};		vertices[3].m_Vcolour  = {1, 0, 0};		vertices[3].m_Vnormal  = {1, 0, 0};
	//vertices[4].m_Vposition  = {1, -1, 1};		vertices[4].m_Vcolour  = {1, 1, 0};		vertices[4].m_Vnormal  = {1, 0, 0};
	//vertices[5].m_Vposition  = {1, -1, -1};		vertices[5].m_Vcolour  = {0, 0, 1};		vertices[5].m_Vnormal  = {1, 0, 0};

	//vertices[6].m_Vposition  = {0, 1, 0};		vertices[6].m_Vcolour  = {1, 0, 0};		vertices[6].m_Vnormal  = {0, 0, -1};
	//vertices[7].m_Vposition  = {1, -1, -1};		vertices[7].m_Vcolour  = {1, 0, 1};		vertices[7].m_Vnormal  = {0, 0, -1};
	//vertices[8].m_Vposition  = {-1, -1, -1};	vertices[8].m_Vcolour  = {1, 1, 0};		vertices[8].m_Vnormal  = {0, 0, -1};

	//vertices[9].m_Vposition  = {0, 1, 0};		vertices[9].m_Vcolour  = {1, 0, 0};		vertices[9].m_Vnormal  = {-1, 0, 0};
	//vertices[10].m_Vposition = {-1, -1, -1};	vertices[10].m_Vcolour = {0, 1, 0};		vertices[10].m_Vnormal = {-1, 0, 0};
	//vertices[11].m_Vposition = {-1, -1, 1};		vertices[11].m_Vcolour = {1, 0, 1};		vertices[11].m_Vnormal = {-1, 0, 0};

	//vertices[12].m_Vposition = {-1, -1, -1};	vertices[12].m_Vcolour = {0, 1, 0};		vertices[12].m_Vnormal = {0, -1, 0};
	//vertices[13].m_Vposition = {1, -1, -1};		vertices[13].m_Vcolour = {0, 0, 1};		vertices[13].m_Vnormal = {0, -1, 0};
	//vertices[14].m_Vposition = {-1, -1, 1};		vertices[14].m_Vcolour = {1, 1, 0};		vertices[14].m_Vnormal = {0, -1, 0};

	//vertices[15].m_Vposition = { 1, -1, 1 };	vertices[15].m_Vcolour = {0, 1, 0};		vertices[15].m_Vnormal = { 0, -1, 0 };
	//vertices[16].m_Vposition = {-1, -1, 1};		vertices[16].m_Vcolour = {0, 1, 0};		vertices[16].m_Vnormal = {0, -1, 0};
	//vertices[17].m_Vposition = {1, -1, -1};		vertices[17].m_Vcolour = {1, 0, 1};		vertices[17].m_Vnormal = {0, -1, 0};

	//glBindBuffer(GL_ARRAY_BUFFER, triangleID);
	//glBufferData(GL_ARRAY_BUFFER, 15 * sizeof(Vertex), vertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);

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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(12));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(24));

	glm::mat4 projection = glm::perspective(3.14159f / 4, 1920.0f / 1080, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(5, 5, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glm::mat4 rotImage = glm::rotate(glm::mat4(1), (float)glfwGetTime(), glm::vec3(0, 1, 0));

	shader.SetUniform("mvpMatrix", projection * view * rotImage);
	shader.SetUniform("modelMatrix", rotImage);
	shader.SetUniform("fromLight", -glm::normalize(glm::vec3(1, 1, 1)));

	glDrawArrays(GL_TRIANGLES, 0, 108);
}
