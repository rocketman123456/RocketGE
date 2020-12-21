#pragma once
#include "GECommon/Camera.h"

namespace Rocket
{
	class PerspectiveCamera : implements Camera
	{
	public:
		PerspectiveCamera(const glm::mat4 &projection) : Camera(projection) {}
		PerspectiveCamera(float fovy, float aspect, float zNear = 0.1f, float zFar = 100.0f);

		inline virtual void SetPosition(const glm::vec3 &position) override
		{
			Camera::SetPosition(position);
			RecalculateViewMatrix();
		}
		void SetProjectionMatrix(float fovy, float aspect, float zNear = 0.1f, float zFar = 100.0f);

		inline float GetRotation() const { return m_Rotation; }
		inline void SetRotation(float rotation)
		{
			m_Rotation = rotation;
			RecalculateViewMatrix();
		}

	public:
		CAMERA_CLASS_TYPE(Perspective);

	private:
		void RecalculateViewMatrix();

	private:
		float m_Rotation = 0.0f;
	};
} // namespace Rocket