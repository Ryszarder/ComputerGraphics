#pragma once

#include "Graphics.h"
#include "Vertex.h"
#include "Texture.h"

class ShaderProgram;

class MeshRender
{
public:
	MeshRender();

	void Draw(ShaderProgram meshShader);

	std::vector<Vertex> m_Vvertices;
	std::vector<unsigned short> m_Vindices;

private:
	GLuint vertexBufferID;
	GLuint indexBufferID;
	Texture* m_Tdiffuse;
	Texture* m_Tnormal;
	Texture* m_Tspecual;
};