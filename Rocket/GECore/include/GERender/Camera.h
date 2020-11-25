#pragma once
#include "GECore/Core.h"
#include <glm/glm.hpp>
#include <Eigen/Eigen>

namespace Rocket {
    enum CameraType
    {
        None = 0,
        Orthographic,
        Projection,
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
			: m_ProjectionMatrix(projection) {}
        Camera(const Eigen::Matrix4f& projection)
			: m_ProjectionMatrixEigen(projection) {}

        virtual CameraType GetCameraType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }

        inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        inline const Eigen::Matrix4f& GetProjectionMatrixEigen() const { return m_ProjectionMatrixEigen; }
    protected:
        glm::mat4 m_ProjectionMatrix;
        Eigen::Matrix4f m_ProjectionMatrixEigen;
    };
}