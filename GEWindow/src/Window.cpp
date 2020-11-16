#include "GEWindow/Window.h"

#ifdef PLATFORM_WINDOWS
#include "WindowWindows.h"
#endif
#ifdef PLATFORM_APPLE
#include "WindowApple.h"
#endif
#ifdef PLATFORM_LINUX
#include "WindowLinux.h"
#endif

namespace Rocket
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
	#ifdef PLATFORM_WINDOWS
		return CreateScope<WindowWindows>(props);
    #endif
	#ifdef PLATFORM_APPLE
		return CreateScope<WindowApple>(props);
	#endif
    #ifdef PLATFORM_LINUX
        return CreateScope<WindowLinux>(props);
    #endif
    #if !defined(PLATFORM_WINDOWS) && !defined(PLATFORM_APPLE) && !defined(PLATFORM_LINUX)
        RK_CORE_ASSERT(false, "Unknown platform!");
        return nullptr;
    #endif
	}

}
