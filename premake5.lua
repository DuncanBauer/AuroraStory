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
IncludeDir["aes"] = "MapleLib/vendor/plusaes/include"
IncludeDir["lz4"] = "MapleLib/vendor/lz4/lib"
IncludeDir["MapleLib"]  = "MapleLib/src"

LinkDir = {}
LinkDir["lz4"] = "MapleLib/vendor/lz4/build/VS2022/liblz4/bin/x64_%{cfg.buildcfg}"

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
	
	removefiles
	{
		"%{prj.name}/src/Wz/**.cpp",
		"%{prj.name}/src/Wz/**.h",
		"%{prj.name}/src/Nx/**.cpp",
		"%{prj.name}/src/Nx/**.h",
	}

	includedirs
	{
		"%{IncludeDir.MapleLib}",
		"%{IncludeDir.Boost}",
		"%{IncludeDir.aes}",
		"%{IncludeDir.lz4}"
	}

	libdirs
	{
		"%{LinkDir.lz4}"
	}

	links
	{
		"liblz4_static"
	}

	filter "system:windows"
		systemversion "latest"
		defines
		{
			"PA_PLATFORM_WINDOWS",
			"PA_ASSERTS_ENABLED",
			"PA_MAPLE_BUILD_DLL"
		}

--		postbuildcommands {
--			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/MapleUnitTesting"),
--			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/MapleServer"),
--			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/MapleWzEditor"),
--			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/MapleClient")
--		}

	filter "configurations:Debug"
		defines "PA_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "PA_RELEASE"
		runtime "Release"
		optimize "on"


project "MapleUnitTesting"
	location "MapleUnitTesting"
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
		"%{IncludeDir.aes}",
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
		"%{IncludeDir.aes}",
		"%{IncludeDir.yaml_cpp}",
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