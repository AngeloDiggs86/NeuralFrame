#pragma once

#ifdef NE_PLATFORM_WINDOWS
	#ifdef	NE_BUILD_DLL
		#define NEURAL_ENGINE_API __declspec(dllexport)
	#else
		#define NEURAL_ENGINE_API __declspec(dllimport)
#endif 
#else 
	#error Neural Engine Only Supports Windows!
#endif // NE_PLATFORM_WINDOWS

#define BIT(X) (1<<X)

#define EN_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)