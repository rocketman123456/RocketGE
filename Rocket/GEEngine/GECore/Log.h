#pragma once

#include <memory>

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Rocket
{
    class Log
    {
    public:
        Log() {}
        ~Log() {}

        static void Init();

        inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }

    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
} // namespace Rocket

#ifdef RK_DEBUG
#define RK_CORE_CRITICAL(...) ::Rocket::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define RK_CORE_ERROR(...) ::Rocket::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RK_CORE_WARN(...) ::Rocket::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RK_CORE_INFO(...) ::Rocket::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RK_CORE_TRACE(...) ::Rocket::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define RK_CRITICAL(...) ::Rocket::Log::GetClientLogger()->critical(__VA_ARGS__)
#define RK_ERROR(...) ::Rocket::Log::GetClientLogger()->error(__VA_ARGS__)
#define RK_WARN(...) ::Rocket::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RK_INFO(...) ::Rocket::Log::GetClientLogger()->info(__VA_ARGS__)
#define RK_TRACE(...) ::Rocket::Log::GetClientLogger()->trace(__VA_ARGS__)
#else
#define RK_CORE_CRITICAL(...)
#define RK_CORE_ERROR(...)
#define RK_CORE_WARN(...)
#define RK_CORE_INFO(...)
#define RK_CORE_TRACE(...)

#define RK_CRITICAL(...)
#define RK_ERROR(...)
#define RK_WARN(...)
#define RK_INFO(...)
#define RK_TRACE(...)
#endif