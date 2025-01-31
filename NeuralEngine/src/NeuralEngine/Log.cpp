#include "Enpch.h"
#include "log.h"
namespace NeuralEngine {

	// Static member definitions
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		// Set a custom pattern for log messages 
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// Initialize the Core logger
		s_CoreLogger = spdlog::stdout_color_mt("NEURAL ENGINE");
		s_CoreLogger->set_level(spdlog::level::trace);

		// Initialize the Client logger
		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

}

