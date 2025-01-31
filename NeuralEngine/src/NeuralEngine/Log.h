#pragma once

#include "NeuralEngineCore.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <spdlog/fmt/ostr.h>

namespace NeuralEngine {

	class NEURAL_ENGINE_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

	// Core Log Macros
	#define EN_CORE_ERROR(...)		::NeuralEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define EN_CORE_WARN(...)		::NeuralEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define EN_CORE_INFO(...)		::NeuralEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define EN_CORE_TRACE(...)		::NeuralEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define EN_CORE_FATAL(...)		::NeuralEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

	// Core Log Macros
	#define EN_CLIENT_ERROR(...)	::NeuralEngine::Log::GetClientLogger()->error(__VA_ARGS__)
	#define EN_CLIENT_WARN(...)		::NeuralEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define EN_CLIENT_INFO(...)		::NeuralEngine::Log::GetClientLogger()->info(__VA_ARGS__)
	#define EN_CLIENT_TRACE(...)    ::NeuralEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define EN_CLIENT_FATAL(...)    ::NeuralEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)
}
