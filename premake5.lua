workspace "NeuralEngine"
	architecture "x64" -- Fixed typo here

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "NeuralEngine"
	location "NeuralEngine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	characterset "MBCS" -- Set Character Set to Multi-Byte Character Set

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
	
	buildoptions 
    { 
        "/utf-8" -- Enables UTF-8 encoding
        --"/D%(PreprocessorDefinitions)" -- Appends preprocessor definitions
    }

	defines 
	{
		"NE_PLATFORM_WINDOWS",
		"NE_BUILD_DLL",
		"_WINDLL"
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
	}

	filter "configurations:Debug"
		defines "NE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "NE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "NE_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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
		"NeuralEngine/src"
	}

	links
	{
		"NeuralEngine"
	}

	characterset "MBCS" -- Set Character Set to Multi-Byte Character Set

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
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
		symbols "On"

	filter "configurations:Release"
		defines "NE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "NE_DIST"
		optimize "On"
