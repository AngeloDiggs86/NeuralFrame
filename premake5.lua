workspace "NeuralEngine"
	architecture "x64" 

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "NeuralEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "NeuralEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "NeuralEngine/vendor/imgui"
IncludeDir["glm"] = "NeuralEngine/vendor/glm"

include "NeuralEngine/vendor/GLFW"
include "NeuralEngine/vendor/Glad"
include "NeuralEngine/vendor/imgui"

project "NeuralEngine"
	location "NeuralEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Enpch.h"
	pchsource "NeuralEngine/src/Enpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	characterset "MBCS" -- Set Character Set to Multi-Byte Character Set

	filter "system:windows"
		systemversion "latest"
		
		buildoptions 
		{ 
			"/utf-8" -- Enables UTF-8 encoding
		}

		defines 
		{
			"NE_PLATFORM_WINDOWS",
			"NE_BUILD_DLL",
			"_WINDLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "NE_DEBUG"
		runtime "Debug"
		--buildoptions {"/utf-8", "/MDd"}
		symbols "on"

	filter "configurations:Release"
		defines "NE_RELEASE"
		runtime "Release"
		--buildoptions "/utf-8"
		optimize "on"

	filter "configurations:Dist"
		defines "NE_DIST"
		runtime "Release"
		--buildoptions "/utf-8"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"NeuralEngine/vendor/spdlog/include",
		"NeuralEngine/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"NeuralEngine"
	}

	characterset "MBCS" -- Set Character Set to Multi-Byte Character Set

	filter "system:windows"
		systemversion "latest"
	
		buildoptions 
		{ 
			"/utf-8" -- Enables UTF-8 encoding
		}

		defines 
		{
			"NE_PLATFORM_WINDOWS",
			"_MBCS"
		}

	filter "configurations:Debug"
		defines "NE_DEBUG"
		--buildoptions "/utf-8"
		symbols "on"

	filter "configurations:Release"
		defines "NE_RELEASE"
		--buildoptions "/utf-8"
		optimize "on"

	filter "configurations:Dist"
		defines "NE_DIST"
		--buildoptions "/utf-8"
		optimize "on"
