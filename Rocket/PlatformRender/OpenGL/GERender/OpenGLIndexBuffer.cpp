#include "GERender/OpenGLIndexBuffer.h"
#include <glad/glad.h>

namespace Rocket
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t *indices, uint32_t count)
		: m_Count(count)
	{
		RK_PROFILE_FUNCTION();

#if defined(HIGH_OPENGL_VERSION)
		glCreateBuffers(1, &m_RendererID);
		// GL_ELEMENT_ARRAY_BUFFER is not valid without an actively bound VAO
		// Binding with GL_ARRAY_BUFFER allows the data to be loaded regardless of VAO state.
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
#else
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
#endif
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		RK_PROFILE_FUNCTION();

		glDeleteBuffers(1, &m_RendererID);
	}
	void Rocket::OpenGLIndexBuffer::Bind() const
	{
		RK_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	}
	void Rocket::OpenGLIndexBuffer::Unbind() const
	{
		RK_PROFILE_FUNCTION();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
} // namespace Rocket