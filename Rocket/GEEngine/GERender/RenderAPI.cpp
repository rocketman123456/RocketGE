#include "GERender/RenderAPI.h"
#if defined(RK_OPENGL)
#include "GERender/OpenGLRenderAPI.h"
#elif defined(RK_VULKAN)
#include "GERender/VulkanRenderAPI.h"
#elif defined(RK_METAL)
#include "GERender/MetalRenderAPI.h"
#endif

namespace Rocket
{
#if defined(RK_OPENGL)
	RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;
#elif defined(RK_VULKAN)
	RenderAPI::API RenderAPI::s_API = RenderAPI::API::Vulkan;
#elif defined(RK_METAL)
	RenderAPI::API RenderAPI::s_API = RenderAPI::API::Metal;
#else
	RenderAPI::API RenderAPI::s_API = RenderAPI::API::None;
#endif

	Scope<RenderAPI> RenderAPI::Create()
	{
		switch (s_API)
		{
		case RenderAPI::API::None:
			RK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
#if defined(RK_OPENGL)
		case RenderAPI::API::OpenGL:
			return CreateScope<OpenGLRenderAPI>();
#elif defined(RK_VULKAN)
		case RenderAPI::API::Vulkan:
			return CreateScope<VulkanRenderAPI>();
#elif defined(RK_METAL)
		case RenderAPI::API::Metal:
			return CreateScope<MetalRenderAPI>();
#endif
		default:
			RK_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
} // namespace Rocket