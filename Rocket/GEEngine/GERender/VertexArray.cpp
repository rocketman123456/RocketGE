#include "GERender/VertexArray.h"
#include "GERender/Renderer.h"
#if defined(RK_OPENGL)
#include "GERender/OpenGLVertexArray.h"
#elif defined(RK_VULKAN)
#include "GERender/VulkanVertexArray.h"
#elif defined(RK_METAL)
#include "GERender/MetalVertexArray.h"
#endif

namespace Rocket
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			RK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
#if defined(RK_OPENGL)
		case RenderAPI::API::OpenGL:
			return CreateRef<OpenGLVertexArray>();
#elif defined(RK_VULKAN)
		case RenderAPI::API::Vulkan:
			return CreateRef<VulkanVertexArray>();
#elif defined(RK_METAL)
		case RenderAPI::API::Metal:
			return CreateRef<MetalVertexArray>();
#endif
		default:
			RK_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
} // namespace Rocket