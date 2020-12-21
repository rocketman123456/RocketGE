#pragma once
#include "GERender/RenderAPI.h"

namespace Rocket
{
	class OpenGLRenderAPI : implements RenderAPI
	{
	public:
		OpenGLRenderAPI() {}
		virtual ~OpenGLRenderAPI() {}

		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height, float xscale = 1.0f, float yscale = 1.0f) override;
		virtual void SetClearColor(const glm::vec4 &color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray> &vertexArray, uint32_t indexCount = 0) override;
		virtual void DrawInstance(const Ref<VertexArray> &vertexArray, uint32_t indexCount = 0, uint32_t count = 0) override;
	};
} // namespace Rocket