#pragma once
#include "GECommon/Camera.h"

namespace Rocket
{
    class OrthographicCamera : implements Camera
    {
    public:
        OrthographicCamera(const glm::mat4 &projection) : Camera(projection) {}
        OrthographicCamera(float left, float right, float bottom, float top, float znear = -1.0f, float zfar = 100.0f);

        inline virtual void SetPosition(const glm::vec3 &position) override
        {
            Camera::SetPosition(position);
            RecalculateViewMatrix();
        }
        void SetProjection(float left, float right, float bottom, float top, float znear = -1.0f, float zfar = 100.0f); 

        inline float GetRotation() const { return m_Rotation; }
        inline void SetRotation(float rotation)
        {
            m_Rotation = rotation;
            RecalculateViewMatrix();
        }

    public:
        CAMERA_CLASS_TYPE(Orthographic);

    private:
        void RecalculateViewMatrix();

    private:
        float m_Rotation = 0.0f;
    };
} // namespace Rocket