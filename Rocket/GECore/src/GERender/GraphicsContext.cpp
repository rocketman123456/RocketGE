#include "GERender/GraphicsContext.h"

#include "GERender/RenderAPI.h"
#include "GERender/OpenGLContext.h"

namespace Rocket {
	Scope<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (RenderAPI::GetAPI())
		{
			case RenderAPI::API::None:    RK_CORE_ASSERT(false, "RenderAPI::None is currently not supported!"); return nullptr;
			case RenderAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}
		RK_CORE_ASSERT(false, "Unknown RenderAPI!");
		return nullptr;
	}
}