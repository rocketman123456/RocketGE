#include "GERender/Texture.h"
#include "GERender/Renderer.h"
#if defined(RK_OPENGL)
#include "GERender/OpenGLTexture2D.h"
#elif defined(RK_VULKAN)
#include "GERender/VulkanTexture2D.h"
#elif defined(RK_METAL)
#include "GERender/MetalTexture2D.h"
#endif

namespace Rocket {
    Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RenderAPI::API::None:    RK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
#if defined(RK_OPENGL)
            case RenderAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(path);
#elif defined(RK_VULKAN)
            case RenderAPI::API::Vulkan:  return CreateRef<VulkanTexture2D>(path);
#elif defined(RK_METAL)
            case RenderAPI::API::Metal:   return CreateRef<MetalTexture2D>(path);
#endif
            default: RK_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}

    Ref<Texture2D> Texture2D::Create(uint32_t width, uint32_t height)
	{
		switch (Renderer::GetAPI())
		{
			case RenderAPI::API::None:    RK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
#if defined(RK_OPENGL)
            case RenderAPI::API::OpenGL:  return CreateRef<OpenGLTexture2D>(width, height);
#elif defined(RK_VULKAN)
            case RenderAPI::API::Vulkan:  return CreateRef<VulkanTexture2D>(width, height);
#elif defined(RK_METAL)
            case RenderAPI::API::Metal:   return CreateRef<MetalTexture2D>(width, height);
#endif
            default: RK_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}
}