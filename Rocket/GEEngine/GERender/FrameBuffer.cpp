#include "GERender/FrameBuffer.h"
#include "GERender/Renderer.h"
#if defined(RK_OPENGL)
#include "GERender/OpenGLFrameBuffer.h"
#elif defined(RK_VULKAN)
#include "GERender/VulkanFrameBuffer.h"
#elif defined(RK_METAL)
#include "GERender/MetalFrameBuffer.h"
#endif

namespace Rocket
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification &spec)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			RK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
#if defined(RK_OPENGL)
		case RenderAPI::API::OpenGL:
			return CreateRef<OpenGLFrameBuffer>(spec);
#elif defined(RK_VULKAN)
		case RenderAPI::API::Vulkan:
			return CreateRef<VulkanFrameBuffer>(size);
#elif defined(RK_METAL)
		case RenderAPI::API::Metal:
			return CreateRef<MetalFrameBuffer>(size);
#endif
		default:
			RK_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
} // namespace Rocket