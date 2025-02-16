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

include "NeuralEngine/vendor/GLFW"
include "NeuralEngine/vendor/Glad"
include "NeuralEngine/vendor/imgui"

project "NeuralEngine"
	location "NeuralEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	characterset "MBCS" -- Set Character Set to Multi-Byte Character Set

	filter "system:windows"
		cppdialect "C++17"
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

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
	}

	filter "configurations:Debug"
		defines "NE_DEBUG"
		runtime "Debug"
		buildoptions "/utf-8"
		symbols "On"

	filter "configurations:Release"
		defines "NE_RELEASE"
		runtime "Release"
		buildoptions "/utf-8"
		optimize "On"

	filter "configurations:Dist"
		defines "NE_DIST"
		runtime "Release"
		buildoptions "/utf-8"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		"%{IncludeDir.Glad}"
		
	}

	links
	{
		"NeuralEngine"
	}

	characterset "MBCS" -- Set Character Set to Multi-Byte Character Set

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "off"
		systemversion "latest"
	
	buildoptions 
    { 
        "/utf-8" -- Enables UTF-8 encoding
        --"/D%(PreprocessorDefinitions)" -- Appends preprocessor definitions
    }

	defines 
	{
		"NE_PLATFORM_WINDOWS",
		"_MBCS"
	}

	filter "configurations:Debug"
		defines "NE_DEBUG"
		buildoptions "/utf-8"
		symbols "On"

	filter "configurations:Release"
		defines "NE_RELEASE"
		buildoptions "/utf-8"
		optimize "On"

	filter "configurations:Dist"
		defines "NE_DIST"
		buildoptions "/utf-8"
		optimize "On"
