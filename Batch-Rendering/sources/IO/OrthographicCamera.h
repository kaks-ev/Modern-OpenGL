#pragma once

#include "core.h"

namespace Yotta
{
	class OrthographicCamera
	{
	private:
		glm::mat4 mProjection;
		glm::mat4 mView;
		glm::mat4 mViewProjection;

		glm::vec3 mPosition = { 0.0f, 0.0f, 0.0f };
		float mRotation = 0.0f;
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return mPosition; }
		void SetPosition(const glm::vec3& position) { mPosition = position; }

		float GetRotation() const { return mRotation; }

	};

}