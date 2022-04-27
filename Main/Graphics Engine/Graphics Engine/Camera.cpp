#include "Camera.h"

Camera::Camera(glm::vec3 vPosition, glm::vec3 vUp, float fYaw, float fPitch) : 
		m_vfront(glm::vec3(0.0f, 0.0f, -0.1f)), m_fmovementSpeed(SPEED), m_fmouseSensitivity(SENSITIVITY), m_fzoom(ZOOM)
{
	m_vposition = vPosition;
	m_vup = vUp;
	m_fyaw = fYaw;
	m_fpitch = fPitch;
	UpdateCameraVectors();
}

Camera::Camera(float fposX, float fposY, float fposZ, float fupX, float fupY, float fupZ, float fyaw, float fpitch) : 
		m_vfront(glm::vec3(0.0f, 0.0f, -0.1f)), m_fmovementSpeed(SPEED), m_fmouseSensitivity(SENSITIVITY), m_fzoom(ZOOM)
{
	m_vposition = glm::vec3(fposX, fposY, fposZ);
	m_vworldUp = glm::vec3(fupX, fupY, fupZ);
	m_fyaw = fyaw;
	m_fpitch = fpitch;
	UpdateCameraVectors();
}

void Camera::ProcessKeyBoard(Camera_Movement direction, float fDeltaTime)
{
	float velocity = m_fmovementSpeed * fDeltaTime;
	if (direction == FORWARD)
		m_vposition += m_vfront * velocity;
	if (direction == BACKWARD)
		m_vposition -= m_vfront * velocity;
	if (direction == LEFT)
		m_vposition -= m_vright * velocity;
	if (direction == RIGHT)
		m_vposition += m_vright * velocity;
}

void Camera::ProcessMouseMovement(float fxOffSet, float fyOffSet, bool bconstrainPitch)
{
	fxOffSet *= m_fmouseSensitivity;
	fyOffSet *= m_fmouseSensitivity;

	m_fyaw += fxOffSet;
	m_fpitch += fyOffSet;

	if (bconstrainPitch)
	{
		if (m_fpitch > 89.0f)
			m_fpitch = 89.0f;
		if (m_fpitch < -89.0f)
			m_fpitch = -89.0f;
	}

	UpdateCameraVectors();
}

void Camera::ProcessMouseScroll(float fyOffSet)
{
	m_fzoom -= fyOffSet;
	if (m_fzoom < 1.0f)
		m_fzoom = 1.0f;
	if (m_fzoom > 45.0f)
		m_fzoom = 45.0f;
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 m_vnewFront;
	m_vnewFront.x = cos(glm::radians(m_fyaw)) * cos(glm::radians(m_fpitch));
	m_vnewFront.y = sin(glm::radians(m_fpitch));
	m_vnewFront.z = sin(glm::radians(m_fyaw)) * cos(glm::radians(m_fpitch));
	m_vfront = glm::normalize(m_vnewFront);

	m_vright = glm::normalize(glm::cross(m_vfront, m_vworldUp));
	m_vup = glm::normalize(glm::cross(m_vright, m_vfront));
}