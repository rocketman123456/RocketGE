#pragma once
#include "GERender/Camera.h"

namespace Rocket {
	class PerspectiveCamera : public Camera
	{
	public:
		PerspectiveCamera(const glm::mat4& projection) : Camera(projection) {}
		PerspectiveCamera(float fovy, float aspect, float zNear, float zFar);

		void SetProjection(float fovy, float aspect, float zNear, float zFar);

		inline const glm::vec3& GetPosition() const { return m_Position; }
		inline void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		inline float GetRotation() const { return m_Rotation; }
		inline void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }
	public:
		CAMERA_CLASS_TYPE(Perspective);
	private:
		void RecalculateViewMatrix();
	private:
		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};
}