workspace "ProjectAurora"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include dirs relative to root folder
IncludeDir = {}
IncludeDir["Boost"] = "C:/boost/boost_1_81_0"
IncludeDir["CryptoPP"] = "MapleLib/vendor/"
IncludeDir["MapleLib"]  = "MapleLib/src"

LinkDir = {}
LinkDir["CryptoPP"] = "MapleLib/vendor/cryptopp/x64/Output/%{cfg.buildcfg}"

project "MapleLib"
	location "MapleLib"
	kind "StaticLib"
	staticruntime "on"
	language "C++"
	cppdialect "C++20"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "MapleLibPCH.h"
	pchsource "MapleLib/src/MapleLibPCH.cpp"

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h"
	}

	includedirs
	{
		"%{IncludeDir.MapleLib}",
		"%{IncludeDir.Boost}",
		"%{IncludeDir.CryptoPP}"
	}

	libdirs
	{
		"%{LinkDir.CryptoPP}"
	}
		links
	{
		"cryptlib.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"PA_PLATFORM_WINDOWS",
			"PA_ASSERTS_ENABLED",
			"PA_MAPLE_BUILD_DLL"
		}

	filter "configurations:Debug"
		defines "PA_DEBUG"
		runtime "Debug"
		symbols "on"

		filter "configurations:Release"
		defines "PA_RELEASE"
		runtime "Release"
		optimize "on"

project "MapleServer"
	location "MapleServer"
	kind "ConsoleApp"
	staticruntime "on"
	language "C++"
	cppdialect "C++20"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h"
	}

	includedirs
	{
		"%{IncludeDir.MapleLib}",
		"%{IncludeDir.Boost}",
		"%{IncludeDir.CryptoPP}",
	}

	links
	{
		"MapleLib",
	}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"PA_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "PA_DEBUG"
		runtime "Debug"
		symbols "on"

		filter "configurations:Release"
		defines "PA_RELEASE"
		runtime "Release"
		optimize "on"


project "MapleWzEditor"
	location "MapleWzEditor"
	kind "ConsoleApp"
	staticruntime "on"
	language "C++"
	cppdialect "C++20"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h"
	}

	includedirs
	{
		"%{IncludeDir.MapleLib}",
		"%{IncludeDir.CryptoPP}",
	}

	links
	{
		"MapleLib",
	}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"PA_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "PA_DEBUG"
		runtime "Debug"
		symbols "on"

		filter "configurations:Release"
		defines "PA_RELEASE"
		runtime "Release"
		optimize "on"



project "MapleClient"
	location "MapleClient"
	kind "ConsoleApp"
	staticruntime "on"
	language "C++"
	cppdialect "C++20"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h"
	}

	includedirs
	{
		"%{IncludeDir.MapleLib}",
		"%{IncludeDir.CryptoPP}",
	}

	links
	{
		"MapleLib",
	}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"PA_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "PA_DEBUG"
		runtime "Debug"
		symbols "on"

		filter "configurations:Release"
		defines "PA_RELEASE"
		runtime "Release"
		optimize "on"