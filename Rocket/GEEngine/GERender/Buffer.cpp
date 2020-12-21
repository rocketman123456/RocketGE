#include "GERender/Buffer.h"
#include "GERender/Renderer.h"
#if defined(RK_OPENGL)
#include "GERender/OpenGLBuffer.h"
#elif defined(RK_VULKAN)
#include "GERender/VulkanBuffer.h"
#elif defined(RK_METAL)
#include "GERender/MetalBuffer.h"
#endif

namespace Rocket
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			RK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
#if defined(RK_OPENGL)
		case RenderAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(size);
#elif defined(RK_VULKAN)
		case RenderAPI::API::OpenGL:
			return CreateRef<VulkanVertexBuffer>(size);
#elif defined(RK_METAL)
		case RenderAPI::API::OpenGL:
			return CreateRef<MetalVertexBuffer>(size);
#endif
		default:
			RK_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}

	Ref<VertexBuffer> VertexBuffer::Create(float *vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			RK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
#if defined(RK_OPENGL)
		case RenderAPI::API::OpenGL:
			return CreateRef<OpenGLVertexBuffer>(vertices, size);
#elif defined(RK_VULKAN)
		case RenderAPI::API::OpenGL:
			return CreateRef<VulkanVertexBuffer>(vertices, size);
#elif defined(RK_METAL)
		case RenderAPI::API::OpenGL:
			return CreateRef<MetalVertexBuffer>(vertices, size);
#endif
		default:
			RK_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}

	template <typename T>
	Ref<InstanceBuffer<T>> InstanceBuffer<T>::Create(T *data, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			RK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
#if defined(RK_OPENGL)
		case RenderAPI::API::OpenGL:
			return CreateRef<OpenGLInstanceBuffer<T>>(data, count);
#elif defined(RK_VULKAN)
		case RenderAPI::API::OpenGL:
			return CreateRef<VulkanInstanceBuffer>(data, count);
#elif defined(RK_METAL)
		case RenderAPI::API::OpenGL:
			return CreateRef<MetalInstanceBuffer>(data, count);
#endif
		default:
			RK_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t *indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:
			RK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
#if defined(RK_OPENGL)
		case RenderAPI::API::OpenGL:
			return CreateRef<OpenGLIndexBuffer>(indices, size);
#elif defined(RK_VULKAN)
		case RenderAPI::API::OpenGL:
			return CreateRef<VulkanIndexBuffer>(indices, size);
#elif defined(RK_METAL)
		case RenderAPI::API::OpenGL:
			return CreateRef<MetalIndexBuffer>(indices, size);
#endif
		default:
			RK_CORE_ASSERT(false, "Unknown RendererAPI!");
			return nullptr;
		}
	}
} // namespace Rocket