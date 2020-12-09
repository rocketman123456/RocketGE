#include "GEWindow/Window.h"

#if defined(PLATFORM_WINDOWS)
#include "GEWindow/WindowWindows.h"
#elif defined(PLATFORM_APPLE)
#include "GEWindow/WindowApple.h"
#elif defined(PLATFORM_LINUX)
#include "GEWindow/WindowLinux.h"
#endif

namespace Rocket
{
	Ref<Window> Window::Create(const WindowProps& props)
	{
	#if defined(PLATFORM_WINDOWS)
		return CreateRef<WindowWindows>(props);
	#elif defined(PLATFORM_APPLE)
		return CreateRef<WindowApple>(props);
    #elif defined(PLATFORM_LINUX)
        return CreateRef<WindowLinux>(props);
    #else
        RK_CORE_ASSERT(false, "Unknown platform!");
        return nullptr;
    #endif
	}

}
