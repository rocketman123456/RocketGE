#pragma once
#include "GECore/Core.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <Eigen/Eigen>

namespace Rocket {
    enum class CameraType
    {
        None = 0,
        Orthographic,
        Perspective,
    };

#define CAMERA_CLASS_TYPE(type) static CameraType GetStaticType() { return CameraType::type; }\
            virtual CameraType GetCameraType() const override { return GetStaticType(); }\
            virtual const char* GetName() const override { return #type; }

    Interface Camera
    {
    public:
        Camera() = default;
        virtual ~Camera() = default;
        // glm Version
        Camera(const glm::mat4& projection, const glm::mat4& view = glm::mat4(1.0f))
            : m_ProjectionMatrix(projection), m_ViewMatrix(view) {}

        inline virtual void SetPosition(const glm::vec3& position) { m_Position = position; }
        inline const glm::vec3& GetPosition() const { return m_Position; }
        inline virtual void SetRotationMatrix(const glm::mat4& rotation) { m_RotationMatrix = rotation; }
        inline const glm::mat4& GetRotationMatrix() const { return m_RotationMatrix; }

        inline virtual void SetProjection(const glm::mat4& projection) { m_ProjectionMatrix = projection; UpdateProjectView(); }
        inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        inline virtual void SetView(const glm::mat4& view) { m_ViewMatrix = view; UpdateProjectView(); }
        inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        inline virtual void UpdateProjectView() { m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix; }
        inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

        static Ref<Camera> Create(CameraType type, std::vector<float> setting);
    public:
        virtual CameraType GetCameraType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
    protected:
        // TODO : make all math in eigen3
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;
        glm::mat4 m_RotationMatrix;
        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
        // for view matrix
        glm::vec3 m_Front;
        glm::vec3 m_Up;
        glm::vec3 m_Right;
        glm::vec3 m_WorldUp;
    };

    inline std::ostream& operator<<(std::ostream& os, const Camera& c)
	{
		return os << c.ToString();
	}
}