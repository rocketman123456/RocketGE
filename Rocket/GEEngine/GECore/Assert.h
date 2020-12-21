#pragma once

#include "GECore/Core.h"

#ifdef RK_ENABLE_ASSERTS
// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
#define RK_INTERNAL_ASSERT_IMPL(type, check, msg, ...) \
	{                                                  \
		if (!(check))                                  \
		{                                              \
			RK##type##ERROR(msg, __VA_ARGS__);         \
			RK_DEBUGBREAK();                           \
		}                                              \
	}
#define RK_INTERNAL_ASSERT_WITH_MSG(type, check, ...) RK_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define RK_INTERNAL_ASSERT_NO_MSG(type, check) RK_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", RK_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

#define RK_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define RK_INTERNAL_ASSERT_GET_MACRO(...) RK_EXPAND_MACRO(RK_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, RK_INTERNAL_ASSERT_WITH_MSG, RK_INTERNAL_ASSERT_NO_MSG))

// Currently accepts at least the condition and one additional parameter (the message) being optional
#define RK_ASSERT(...) RK_EXPAND_MACRO(RK_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__))
#define RK_CORE_ASSERT(...) RK_EXPAND_MACRO(RK_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__))
#else
#define RK_ASSERT(...)
#define RK_CORE_ASSERT(...)
#endif
