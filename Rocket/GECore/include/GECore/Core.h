#pragma once
#include "GECore/Basic.h"

#include "RKConfig.h"
const std::string ProjectSourceDir = PROJECT_SOURCE_DIR;
const std::string RenderAPI = RENDER_API;

#ifdef RK_DEBUG
	#if defined(PLATFORM_WINDOWS)
		#define RK_DEBUGBREAK() __debugbreak()
	#elif defined(PLATFORM_LINUX) || defined(PLATFORM_APPLE)
		#include <signal.h>
		#define RK_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define RK_ENABLE_ASSERTS
#else
	#define RK_DEBUGBREAK()
#endif

// These just for glfw
#if defined(RK_OPENGL)
	#define GLFW_INCLUDE_NONE
#elif defined(RK_VULKAN)
	#define GLFW_INCLUDE_NONE
	#define GLFW_INCLUDE_VULKAN
#elif defined(RK_METAL)
	#define GLFW_INCLUDE_NONE
	#define GLFW_EXPOSE_NATIVE_COCOA
#endif

#define RK_EXPAND_MACRO(x) x
#define RK_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)
#define RK_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#define Interface class
#define implements public

template<class T>
inline void SafeRelease(T **ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != nullptr)
	{
		(*ppInterfaceToRelease) = nullptr;
	}
}

namespace Rocket {
	template<typename Base, typename T>
	inline bool instanceof(const T*) {
		return std::is_base_of<Base, T>::value;
	}
	
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#include "GECore/Assert.h"
#include "GECore/Log.h"
