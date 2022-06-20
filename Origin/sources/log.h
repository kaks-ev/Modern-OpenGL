#pragma once

#include "core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Origin {

	class Log
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};
}

// ORIGIN LOG
#define ORG_CORE_ERROR(...)			::Origin::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ORG_CORE_WARN(...)			::Origin::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ORG_CORE_INFO(...)			::Origin::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ORG_CORE_TRACE(...)			::Origin::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ORG_CORE_CRITICAL(...)	::Origin::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define ORG_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { ORG##type##ERROR(msg, __VA_ARGS__); ORG_DEBUGBREAK(); } }
#define ORG_INTERNAL_ASSERT_WITH_MSG(type, check, ...) ORG_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
#define ORG_INTERNAL_ASSERT_NO_MSG(type, check) ORG_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", ORG_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)
#define ORG_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
#define ORG_INTERNAL_ASSERT_GET_MACRO(...) ORG_EXPAND_MACRO( ORG_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, ORG_INTERNAL_ASSERT_WITH_MSG, ORG_INTERNAL_ASSERT_NO_MSG) )
#define ORG_ASSERT(...) ORG_EXPAND_MACRO( ORG_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
#define ORG_CORE_ASSERT(...) ORG_EXPAND_MACRO( ORG_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#define ORG_ASSERT(...)
#define ORG_CORE_ASSERT(...)