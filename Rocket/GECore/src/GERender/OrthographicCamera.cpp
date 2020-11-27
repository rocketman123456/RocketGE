#include "GERender/OrthographicCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Rocket {
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: Camera(glm::ortho(left, right, bottom, top, 0.1f, 100.0f))
	{
		Camera::UpdateProjectView();
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		Camera::SetProjection(glm::ortho(left, right, bottom, top, 0.1f, 100.0f));
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = 
			glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		Camera::SetView(glm::inverse(transform));
	}
}