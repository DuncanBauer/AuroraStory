workspace "AuroraStory"
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
IncludeDir["lz4"]  = "MapleLib/vendor/lz4/lib"

LinkDir = {}
LinkDir["CryptoPP"] = "MapleLib/vendor/cryptopp/x64/Output/%{cfg.buildcfg}"
LinkDir["lz4"] = "MapleLib/vendor/lz4/build/VS2022/bin/x64-%{cfg.buildcfg}"
-- LinkDir["CryptoPP"] = "MapleLib/vendor/cryptopp/x64/DLL_Output/%{cfg.buildcfg}"

project "MapleLib"
	location "MapleLib"
	kind "SharedLib"
	staticruntime "off"
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
		"%{IncludeDir.CryptoPP}",
		"%{IncludeDir.lz4}"
	}
	libdirs
	{
		"%{LinkDir.CryptoPP}",
		"%{LinkDir.lz4}"
	}
	links
	{
		"cryptlib.lib",
		"liblz4-static.lib"
	}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"PA_PLATFORM_WINDOWS",
			"PA_ASSERTS_ENABLED",
			"PA_MAPLE_BUILD_DLL"
		}
		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/MapleServer"),
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/MapleWzEditor"),
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/MapleClient")
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
	staticruntime "off"
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
		"%{IncludeDir.CryptoPP}"
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


-- project "MapleWzEditor"
-- 	location "MapleWzEditor"
-- 	kind "ConsoleApp"
-- 	staticruntime "off"
-- 	language "C++"
-- 	cppdialect "C++20"

-- 	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
-- 	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

-- 	files
-- 	{
-- 		"%{prj.name}/src/**.cpp",
-- 		"%{prj.name}/src/**.h"
-- 	}

-- 	includedirs
-- 	{
-- 		"%{IncludeDir.MapleLib}",
-- 		"%{IncludeDir.CryptoPP}",
-- 	}

-- 	links
-- 	{
-- 		"MapleLib",
-- 	}

-- 	filter "system:windows"
-- 		systemversion "latest"
-- 		defines
-- 		{
-- 			"PA_PLATFORM_WINDOWS",
-- 		}

-- 	filter "configurations:Debug"
-- 		defines "PA_DEBUG"
-- 		runtime "Debug"
-- 		symbols "on"

-- 		filter "configurations:Release"
-- 		defines "PA_RELEASE"
-- 		runtime "Release"
-- 		optimize "on"



-- project "MapleClient"
	-- location "MapleClient"
	-- kind "ConsoleApp"
	-- staticruntime "off"
	-- language "C++"
	-- cppdialect "C++20"

	-- targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	-- objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- files
	-- {
	-- 	"%{prj.name}/src/**.cpp",
	-- 	"%{prj.name}/src/**.h"
	-- }

	-- includedirs
	-- {
	-- 	"%{IncludeDir.MapleLib}",
	-- }

	-- links
	-- {
	-- 	"MapleLib",
	-- }

	-- filter "system:windows"
	-- 	systemversion "latest"
	-- 	defines
	-- 	{
	-- 		"PA_PLATFORM_WINDOWS",
	-- 	}

	-- filter "configurations:Debug"
	-- 	defines "PA_DEBUG"
	-- 	runtime "Debug"
	-- 	symbols "on"

	-- 	filter "configurations:Release"
	-- 	defines "PA_RELEASE"
	-- 	runtime "Release"
	-- 	optimize "on"