#pragma once

#include "glm.hpp"

#include <vector>

struct Vertex
{
	glm::vec3 m_Vposition;
	glm::vec3 m_Vcolour;
	glm::vec3 m_Vnormal;
	glm::vec2 m_VtexCoord;
	glm::vec3 m_Vtangent;
	glm::vec3 m_VbiTangent;
};