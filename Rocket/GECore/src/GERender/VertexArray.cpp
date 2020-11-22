#include "GERender/VertexArray.h"
#include "GERender/RenderAPI.h"
#if defined(RK_OPENGL)
#include "GERender/OpenGLVertexArray.h"
#elif defined(RK_VULKAN)
#include "GERender/VulkanVertexArray.h"
#elif defined(RK_METAL)
#include "GERender/MetalVertexArray.h"
#endif

namespace Rocket {
	Ref<VertexArray> VertexArray::Create()
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:    RK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RenderAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		RK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}