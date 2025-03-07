#pragma once
/*
    This header file is a precompiled header (PCH) used for including large APIs and frequently
    used standard libraries that will be shared throughout the project. Precompiled headers
    help reduce compilation time by allowing commonly used header files to be compiled once
    and reused across multiple source files. This file includes necessary libraries such as
    standard containers, memory management, string manipulation, and the NeuralEngine logging system.
*/

#define _SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS
#define FMT_HEADER_ONLY

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "NeuralEngine/Log.h"

#ifdef NE_PLATFORM_WINDOWS
#include "Windows.h"
#endif // NE_PLATFORM_WINDOWS
