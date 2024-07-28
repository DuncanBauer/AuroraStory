project "Core"
	location "."
	kind "SharedLib"
	staticruntime "off"
	language "C++"
	cppdialect "C++20"
	targetdir ("../bin/" .. outputdir)
	objdir ("../bin-int/" .. outputdir)
    defines
    {
        "DLL_EXPORT"
    }

	files
	{
		"src/**.cpp",
		"src/**.h",
		"../vendor/aes/**.c",
		"../vendor/aes/**.h"
	}
	
	includedirs
	{
		"src/",
		"%{IncludeDir.aes}",
		"%{IncludeDir.ASIO}",
		"%{IncludeDir.bcrypt}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.yamlcpp}",
		"%{IncludeDir.Bson}",
		"%{IncludeDir.BsonCXX}",
		"%{IncludeDir.MongoC}",
		"%{IncludeDir.MongoCXX}"
	}

	links
	{
		"%{LinkDir.bcrypt}"
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
		links
		{
			"%{LinkDir.MongoCd}",
			"%{LinkDir.MongoCXXd}",
			"%{LinkDir.Bsond}",
			"%{LinkDir.BsonCXXd}",
			"%{LinkDir.yamlcppd}",
		}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines
		{
			"NDEBUG"
		}
		links
		{
			"%{LinkDir.MongoC}",
			"%{LinkDir.MongoCXX}",
			"%{LinkDir.Bson}",
			"%{LinkDir.BsonCXX}",
			"%{LinkDir.yamlcpp}",
		}
		runtime "Release"
		optimize "on"