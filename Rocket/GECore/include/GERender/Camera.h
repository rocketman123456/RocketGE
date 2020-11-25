#pragma once
#include "GECore/Core.h"
#include <glm/glm.hpp>
#include <Eigen/Eigen>

namespace Rocket {
    enum class CameraType
    {
        None = 0,
        Orthographic,
        Perspective,
        Frustum,
    };

#define CAMERA_CLASS_TYPE(type) static CameraType GetStaticType() { return CameraType::type; }\
            virtual CameraType GetCameraType() const override { return GetStaticType(); }\
            virtual const char* GetName() const override { return #type; }

    class Camera
    {
    public:
        Camera() = default;
        virtual ~Camera() = default;

        Camera(const glm::mat4& projection)
			: m_ProjectionMatrix(projection), m_ViewMatrix(1.0f) {}
        Camera(const glm::mat4& projection, const glm::mat4& view)
            : m_ProjectionMatrix(projection), m_ViewMatrix(view) {}
        Camera(const Eigen::Matrix4f& projection)
			: m_ProjectionMatrixEigen(projection), m_ViewMatrix(1.0f) {}
        Camera(const Eigen::Matrix4f& projection, const Eigen::Matrix4f& view)
            : m_ProjectionMatrixEigen(projection), m_ViewMatrixEigen(view) {}

        virtual CameraType GetCameraType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }

        inline void SetProjection(const glm::mat4& projection) { m_ProjectionMatrix = projection; UpdateProjectView(); }
        inline void SetView(const glm::mat4& view) { m_ViewMatrix = view; UpdateProjectView(); }
        inline virtual void UpdateProjectView() { m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; }

        inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
        inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }

        inline const Eigen::Matrix4f& GetProjectionMatrixEigen() const { return m_ProjectionMatrixEigen; }
    protected:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        Eigen::Matrix4f m_ProjectionMatrixEigen;
        Eigen::Matrix4f m_ViewMatrixEigen;
        Eigen::Matrix4f m_ViewProjectionMatrixEigen;
    };
}