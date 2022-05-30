#ifndef CAMERA_H
#define CAMERA_H
#include "core.h"

enum class CameraDirection
{
	NONE = 0,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera {
public:

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraY;
	glm::vec3 cameraX;
	glm::vec3 worldUp;

	float yaw, pitch, speed, zoom;

	Camera(glm::vec3 position);

	void updateCameraDirection(double dx, double dy);
	void updateCameraPos(CameraDirection dir, double dt);
	void updateCameraZoom(double dy);

	glm::mat4 getViewMatrix();

private:
	void updateCameraVectors();
};

#endif