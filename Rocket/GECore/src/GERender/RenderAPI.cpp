#include "GERender/RenderAPI.h"

namespace Rocket {
#if defined(RK_OPENGL)
    RenderAPI::API RenderAPI::s_API = RenderAPI::API::OpenGL;
#elif defined(RK_VULKAN)
    RenderAPI::API RenderAPI::s_API = RenderAPI::API::Vulkan;
#elif defined(RK_METAL)
    RenderAPI::API RenderAPI::s_API = RenderAPI::API::Metal;
#else
    RenderAPI::API RenderAPI::s_API = RenderAPI::API::None;
#endif
}