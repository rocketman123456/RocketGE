#include "GECommon/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Rocket
{
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float znear, float zfar)
		: Camera(glm::ortho(left, right, bottom, top, znear, zfar))
	{
		Camera::UpdateProjectView();
	}
	
	void OrthographicCamera::SetProjectionMatrix(float left, float right, float bottom, float top, float znear, float zfar)
	{
		Camera::SetProjectionMatrix(glm::ortho(left, right, bottom, top, znear, zfar));
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		m_RotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) * m_RotationMatrix;
		Camera::SetViewMatrix(glm::inverse(transform));
	}
} // namespace Rocket