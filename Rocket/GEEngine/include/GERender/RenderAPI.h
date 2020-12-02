#pragma once
#include "GECore/Core.h"
#include "GERender/VertexArray.h"
#include <glm/glm.hpp>

namespace Rocket {
    Interface RenderAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1, Vulkan = 2, Metal = 3
		};
	public:
		virtual ~RenderAPI() = default;
        static API GetAPI() { return s_API; }

		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height, float xscale = 1.0f, float yscale = 1.0f) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		static Scope<RenderAPI> Create();
	private:
		static API s_API;
    };
}