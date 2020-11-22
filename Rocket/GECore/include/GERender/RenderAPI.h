#pragma once
#include "GECore/Core.h"

namespace Rocket {
    class RenderAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1, Vulkan = 2, Metal = 3
		};
	public:
		virtual ~RenderAPI() = default;
        static API GetAPI() { return s_API; }
	private:
		static API s_API;
    };
}