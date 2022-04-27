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

Camera::Camera(float fPosX, float fPosY, float fPosZ, float fUpX, float fUpY, float fUpZ, float fYaw, float fPitch) : 
		m_vfront(glm::vec3(0.0f, 0.0f, -0.1f)), m_fmovementSpeed(SPEED), m_fmouseSensitivity(SENSITIVITY), m_fzoom(ZOOM)
{
}

void Camera::ProcessKeyBoard(Camera_Movment direction, float fDeltaTime)
{
}

void Camera::ProcessMouseMovement(float fXOffSet, float fYOffSet, bool bConstrainPitch)
{
}

void Camera::ProcessMouseScroll(float fYOffSet)
{
}

void Camera::UpdateCameraVectors()
{
}
