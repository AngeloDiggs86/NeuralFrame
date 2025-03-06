#pragma once

#ifdef NE_PLATFORM_WINDOWS
#ifdef NE_DYNAMIC_LINK
	#ifdef	NE_BUILD_DLL
		#define NEURAL_ENGINE_API __declspec(dllexport)
	#else
		#define NEURAL_ENGINE_API __declspec(dllimport)
	#endif 

#else
	#define NEURAL_ENGINE_API
#endif // NE_DYNAMIC_LINK
#else 
	#error Neural Engine Only Supports Windows!
#endif // NE_PLATFORM_WINDOWS

#define BIT(X) (1<<X)

#define EN_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)