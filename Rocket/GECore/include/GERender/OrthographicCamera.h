#pragma once
#include "GERender/Camera.h"

namespace Rocket {
    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera(const glm::mat4& projection) : Camera(projection) {}
        OrthographicCamera(const Eigen::Matrix4f& projection) : Camera(projection) {}
        OrthographicCamera(float left, float right, float bottom, float top);

        void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
    public:
        CAMERA_CLASS_TYPE(Orthographic);
    private:
		void RecalculateViewMatrix();
    private:
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
    };
}