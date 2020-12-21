#include "GECommon/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Rocket
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far)
		: Camera(glm::ortho(left, right, bottom, top, near, far))
	{
		Camera::UpdateProjectView();
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top, float near, float far)
	{
		Camera::SetProjection(glm::ortho(left, right, bottom, top, near, far));
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		m_RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * m_RotationMatrix;
		Camera::SetView(glm::inverse(transform));
	}
} // namespace Rocket