#include "MeshRender.h"
#include "Graphics.h"
#include "ShaderProgram.h"
#include "Utilities.h"

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

MeshRender::MeshRender()
{
	glGenBuffers(1, &vertexBufferID);
	
	glGenBuffers(1, &indexBufferID);

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile("Mesh/soulspear.obj", aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	aiMesh* meshPointer = *scene->mMeshes;

	for (int i = 0; i < meshPointer->mNumVertices; i++)
	{
		Vertex thisVertex;
		thisVertex.m_Vposition.x = meshPointer->mVertices[i].x;
		thisVertex.m_Vposition.y = meshPointer->mVertices[i].y;
		thisVertex.m_Vposition.z = meshPointer->mVertices[i].z;

		thisVertex.m_Vcolour = { 1, 1, 1 };

		thisVertex.m_Vnormal.x = meshPointer->mNormals[i].x;
		thisVertex.m_Vnormal.y = meshPointer->mNormals[i].y;
		thisVertex.m_Vnormal.z = meshPointer->mNormals[i].z;

		thisVertex.m_VtexCoord.x = meshPointer->mTextureCoords[0][i].x;
		thisVertex.m_VtexCoord.y = meshPointer->mTextureCoords[0][i].y;
		
		thisVertex.m_Vtangent.x = meshPointer->mTangents[i].x;
		thisVertex.m_Vtangent.y = meshPointer->mTangents[i].y;
		thisVertex.m_Vtangent.z = meshPointer->mTangents[i].z;

		thisVertex.m_VbiTangent.x = meshPointer->mBitangents[i].x;
		thisVertex.m_VbiTangent.y = meshPointer->mBitangents[i].y;
		thisVertex.m_VbiTangent.z = meshPointer->mBitangents[i].z;

		m_Vvertices.push_back(thisVertex);
	}
	for (int i = 0; i < meshPointer->mNumFaces; i++)
	{
		m_Vindices.push_back((unsigned short)meshPointer->mFaces[i].mIndices[0]);
		m_Vindices.push_back((unsigned short)meshPointer->mFaces[i].mIndices[1]);
		m_Vindices.push_back((unsigned short)meshPointer->mFaces[i].mIndices[2]);
	}

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_Vvertices.size(), m_Vvertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * m_Vindices.size(), m_Vindices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);

	m_Tdiffuse = new Texture("Mesh/soulspear_diffuse.tga");
	m_Tnormal = new Texture("Mesh/soulspear_normal.tga");
	m_Tspecual = new Texture("Mesh/soulspear_specular.tga");
}

void MeshRender::Draw(ShaderProgram meshShader)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Vposition));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Vcolour));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Vnormal));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_VtexCoord));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Vtangent));
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_VbiTangent));

	meshShader.UseShader();

	glm::mat4 projection = glm::perspective(3.14159f / 4, 1920.0f / 1080, 0.1f, 100.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(3, 3, 3), glm::vec3(0, 2, 0), glm::vec3(0, 1, 0));
	glm::mat4 rotImage = glm::rotate(glm::mat4(1), 0*(float)glfwGetTime(), glm::vec3(0, 1, 0));
	float lightX = 2.0f * sin(glfwGetTime());
	float lightY = 1.5f;
	float lightZ = 1.5f * cos(glfwGetTime());
	glm::vec3 pointLightPos = glm::vec3(lightX, lightY, lightZ);

	meshShader.SetUniform("mvpMatrix", projection * view * rotImage);
	meshShader.SetUniform("modelMatrix", rotImage);
	meshShader.SetUniform("dirLightPos", glm::vec3(-1, 2, 2));
	meshShader.SetUniform("pointLightPos", pointLightPos);
	meshShader.SetUniform("viewPos", glm::vec3(3, 3, 3));
	meshShader.SetUniform("redColour", glm::vec3(0, 1, 1));
	meshShader.SetUniform("blueColour", glm::vec3(1, 1, 1));
	meshShader.SetUniform("diffTexture", 0);
	meshShader.SetUniform("normTexture", 1);
	meshShader.SetUniform("specTexture", 2);
	m_Tdiffuse->Bind(0);
	m_Tnormal->Bind(1);
	m_Tspecual->Bind(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glDrawElements(GL_TRIANGLES, m_Vindices.size(), GL_UNSIGNED_SHORT, 0);
}