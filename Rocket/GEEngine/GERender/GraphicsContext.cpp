#include "GERender/GraphicsContext.h"
#include "GERender/Renderer.h"
#if defined(RK_OPENGL)
#include "GERender/OpenGLContext.h"
#elif defined(RK_VULKAN)
#include "GERender/VulkanContext.h"
#elif defined(RK_METAL)
#include "GERender/MetalContext.h"
#endif

namespace Rocket
{
	Scope<GraphicsContext> GraphicsContext::Create(void *window)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			RK_CORE_ASSERT(false, "RenderAPI::None is currently not supported!");
			return nullptr;
#if defined(RK_OPENGL)
		case RenderAPI::API::OpenGL:
			return CreateScope<OpenGLContext>(static_cast<GLFWwindow *>(window));
#elif defined(RK_VULKAN)
		case RenderAPI::API::Vulkan:
			return CreateScope<VulkanContext>(static_cast<GLFWwindow *>(window));
#elif defined(RK_METAL)
		case RenderAPI::API::Metal:
			return CreateScope<MetalContext>(static_cast<GLFWwindow *>(window));
#endif
		default:
			RK_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
} // namespace Rocket