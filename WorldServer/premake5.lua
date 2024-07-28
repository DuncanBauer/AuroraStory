project "WorldServer"
	location "."
	kind "ConsoleApp"
	staticruntime "off"
	language "C++"
	cppdialect "C++20"
	targetdir ("../bin/" .. outputdir)
	objdir ("../bin-int/" .. outputdir)

	files
	{
		"src/**.cpp",
		"src/**.h",
	}
	
	includedirs
	{
		"src/",
		"%{IncludeDir.Core}",
	}

	links
	{
		"Core"
	}

	filter "system:windows"
		architecture "x86_64"
		defines 
		{
			"_WIN32_WINNT=0x0601"
		}

	filter "system:linux"
		architecture "x86_64"

	filter "configurations:Debug"
		defines 
		{
			"DEBUG"
		}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines
		{
			"NDEBUG"
		}
		runtime "Release"
		optimize "on"