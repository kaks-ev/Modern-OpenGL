#include "Camera.h"

Camera::Camera(glm::vec3 camPos)
	: Position(camPos), cameraUp(0.0f, 1.0f, 0.0f), cameraFront(0.0f, 0.0f, -1.0f)
{
	OrthoProjection();
}

glm::mat4 Camera::GetViewMatrix()
{
	m_View = glm::lookAt(Position, cameraFront + Position, cameraUp);
	return m_View;
}

void Camera::OrthoProjection()
{
	m_Projection = glm::ortho(-1.0f, 15.0f * 1.2f, -1.0f, 8.0f * 1.2f, 0.0f, 100.0f);
}

