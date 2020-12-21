#include "GECommon/PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Rocket
{
	PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float zNear, float zFar)
		: Camera(glm::perspective(fovy, aspect, zNear, zFar))
	{
		Camera::UpdateProjectView();
	}

	void PerspectiveCamera::SetProjectionMatrix(float fovy, float aspect, float zNear, float zFar)
	{
		Camera::SetProjectionMatrix(glm::perspective(fovy, aspect, zNear, zFar));
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		m_RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * m_RotationMatrix;
		Camera::SetViewMatrix(glm::inverse(transform));
	}
} // namespace Rocket