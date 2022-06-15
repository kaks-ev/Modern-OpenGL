#ifndef CAMERA_H
#define CAMERA_H

#include "core.h"
#include "renderer/window.h"

class Camera {
private:

	glm::vec3 cameraUp;
	glm::vec3 cameraFront;
	glm::mat4 m_Projection;
	glm::mat4 m_View;

public:
	glm::vec3 Position;

	Camera(glm::vec3 camPos);
	void OrthoProjection();
	void PerspectiveProjection();
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix() { return m_Projection;  }
};
#endif
