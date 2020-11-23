#pragma once
#include "GERender/RenderAPI.h"
#include "GERender/VertexArray.h"

namespace Rocket {
	class RenderCommand
	{
	public:
		static void Init()
		{
			s_RenderAPI->Init();
		}

		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_RenderAPI->SetViewport(x, y, width, height);
		}

		static void SetClearColor(const glm::vec4& color)
		{
			s_RenderAPI->SetClearColor(color);
		}

		static void Clear()
		{
			s_RenderAPI->Clear();
		}

		static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0)
		{
			s_RenderAPI->DrawIndexed(vertexArray, count);
		}
	private:
		static Scope<RenderAPI> s_RenderAPI;
	};
}
