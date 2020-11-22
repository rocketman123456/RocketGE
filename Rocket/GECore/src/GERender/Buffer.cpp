#include "GERender/Buffer.h"
#include "GERender/RenderAPI.h"
#if defined(RK_OPENGL)
#include "GERender/OpenGLVertexBuffer.h"
#include "GERender/OpenGLIndexBuffer.h"
#elif defined(RK_VULKAN)
#include "GERender/VulkanVertexBuffer.h"
#include "GERender/VulkanIndexBuffer.h"
#elif defined(RK_METAL)
#include "GERender/MetalVertexBuffer.h"
#include "GERender/MetalIndexBuffer.h"
#endif

namespace Rocket {
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:    RK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
#if defined(RK_OPENGL)
		case RenderAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(size);
#elif defined(RK_VULKAN)
		case RenderAPI::API::OpenGL:  return CreateRef<VulkanVertexBuffer>(size);
#elif defined(RK_METAL)
		case RenderAPI::API::OpenGL:  return CreateRef<MetalVertexBuffer>(size);
#endif
		}

		RK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:    RK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
#if defined(RK_OPENGL)
		case RenderAPI::API::OpenGL:  return CreateRef<OpenGLVertexBuffer>(vertices, size);
#elif defined(RK_VULKAN)
		case RenderAPI::API::OpenGL:  return CreateRef<VulkanVertexBuffer>(vertices, size);
#elif defined(RK_METAL)
		case RenderAPI::API::OpenGL:  return CreateRef<MetalVertexBuffer>(vertices, size);
#endif
		}

		RK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (RenderAPI::GetAPI())
		{
		case RenderAPI::API::None:    RK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
#if defined(RK_OPENGL)
		case RenderAPI::API::OpenGL:  return CreateRef<OpenGLIndexBuffer>(indices, size);
#elif defined(RK_VULKAN)
		case RenderAPI::API::OpenGL:  return CreateRef<VulkanIndexBuffer>(indices, size);
#elif defined(RK_METAL)
		case RenderAPI::API::OpenGL:  return CreateRef<MetalIndexBuffer>(indices, size);
#endif
		}

		RK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}