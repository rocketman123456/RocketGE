#include "GERender/OpenGLRenderAPI.h"
#include "glad/glad.h"

namespace Rocket
{
	void OpenGLMessageCallback(
		unsigned source,
		unsigned type,
		unsigned id,
		unsigned severity,
		int length,
		const char *message,
		const void *userParam)
	{
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			RK_CORE_CRITICAL(message);
			return;
		case GL_DEBUG_SEVERITY_MEDIUM:
			RK_CORE_ERROR(message);
			return;
		case GL_DEBUG_SEVERITY_LOW:
			RK_CORE_WARN(message);
			return;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			RK_CORE_TRACE(message);
			return;
		}

		RK_CORE_ASSERT(false, "Unknown severity level!");
	}

	void OpenGLRenderAPI::Init()
	{
		RK_PROFILE_FUNCTION();

		int flags;
		glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
		if (flags & GL_CONTEXT_FLAG_DEBUG_BIT)
		{
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(OpenGLMessageCallback, nullptr);
			glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRenderAPI::SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height, float xscale, float yscale)
	{
		RK_PROFILE_FUNCTION();
		glViewport(x, y, width * xscale, height * yscale);
	}

	void OpenGLRenderAPI::SetClearColor(const glm::vec4 &color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderAPI::DrawIndexed(const Ref<VertexArray> &vertexArray, uint32_t indexCount)
	{
		RK_PROFILE_FUNCTION();

		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		//glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLRenderAPI::DrawInstance(const Ref<VertexArray> &vertexArray, uint32_t indexCount, uint32_t numCount)
	{
		RK_PROFILE_FUNCTION();

		uint32_t count = indexCount ? indexCount : vertexArray->GetIndexBuffer()->GetCount();
		glDrawArraysInstanced(GL_TRIANGLES, count, GL_UNSIGNED_INT, numCount);
		//glBindTexture(GL_TEXTURE_2D, 0);
	}
} // namespace Rocket
