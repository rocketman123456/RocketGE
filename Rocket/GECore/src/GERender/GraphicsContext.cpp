#include "GERender/GraphicsContext.h"

//#include "Hazel/Renderer/Renderer.h"
//#include "Platform/OpenGL/OpenGLContext.h"

namespace Rocket {
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		//switch (Renderer::GetAPI())
		//{
		//	case RendererAPI::API::None:    RK_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		//	case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		//}
		RK_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}