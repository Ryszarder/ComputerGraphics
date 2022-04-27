#pragma once
#include <glm.hpp>

#include "ext/matrix_transform.hpp"
#include "ext/matrix_clip_space.hpp"

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

const float YAW			= -90.0f;
const float PITCH		= 0.0f;
const float SPEED		= 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM		= 45.0f;

class Camera
{
public:
	glm::vec3 m_vposition;
	glm::vec3 m_vfront;
	glm::vec3 m_vup;
	glm::vec3 m_vright;
	glm::vec3 m_vworldUp;

	float m_fyaw;
	float m_fpitch;

	float m_fmovementSpeed;
	float m_fmouseSensitivity;
	float m_fzoom;

	Camera(glm::vec3 vposition = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 vup = glm::vec3(0.0f, 1.0f, 0.0f),
		float fyaw = YAW, float fpitch = PITCH);
		// : m_vFront(glm::vec3(0.0f, 0.0f, -0.1f)), m_fMovementSpeed(SPEED), m_fMouseSensitivity(SENSITIVITY), m_fZoom(ZOOM)

	Camera(float fposX, float fposY, float fposZ, float fupX, float fupY, float fupZ, float fyaw, float fpitch);

	glm::mat4 GetViewMatrix() { return glm::lookAt(m_vposition, m_vposition + m_vfront, m_vup); }

	void ProcessKeyBoard(Camera_Movement direction, float fDeltaTime);

	void ProcessMouseMovement(float fXOffSet, float fYOffSet, bool bConstrainPitch = true);

	void ProcessMouseScroll(float fYOffSet);

	void UpdateCameraVectors();
};