#include "GERender/OpenGLVertexBuffer.h"
#include <glad/glad.h>

namespace Rocket {
	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		RK_PROFILE_FUNCTION();
#if defined(HIGH_OPENGL_VERSION)
		glCreateBuffers(1, &m_RendererID);
#else
		glGenBuffers(1, &m_RendererID);
#endif
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		RK_PROFILE_FUNCTION();
#if defined(HIGH_OPENGL_VERSION)
		glCreateBuffers(1, &m_RendererID);
#else
		glGenBuffers(1, &m_RendererID);
#endif
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		RK_PROFILE_FUNCTION();
		
		glDeleteBuffers(1, &m_RendererID);
	}

	void Rocket::OpenGLVertexBuffer::Bind() const
	{
		RK_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	}
	void Rocket::OpenGLVertexBuffer::Unbind() const
	{
		RK_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void Rocket::OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		RK_PROFILE_FUNCTION();

		glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
}