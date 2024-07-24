workspace "AuroraStory"
	configurations
	{
		"Debug",
		"Release"
	}
	platforms
	{
		"Windows",
		"Unix"
	}

outputdir = "%{cfg.buildcfg}/%{cfg.system}"
vcpkgdir = "C:/repos/vcpkg/packages"

-- Include dirs relative to root folder
IncludeDir = {}
-- submodule libraries
IncludeDir["aes"]				= "%{os.getcwd()}/vendor/aes"
IncludeDir["ASIO"]	 			= "%{os.getcwd()}/vendor/asio/asio/include"
IncludeDir["spdlog"] 			= "%{os.getcwd()}/vendor/spdlog/include"

-- vcpkg libraries
IncludeDir["Bson"]				= "%{vcpkgdir}/libbson_x64-windows/include"
IncludeDir["BsonCXX"]			= "%{vcpkgdir}/mongo-cxx-driver_x64-windows/include/bsoncxx/v_noabi"

IncludeDir["MongoC"]			= "%{vcpkgdir}/mongo-c-driver_x64-windows/include"
IncludeDir["MongoCXX"]			= "%{vcpkgdir}/mongo-cxx-driver_x64-windows/include/mongocxx/v_noabi"

LinkDir = {}
-- Need separate debug and release links for CryptoPP and MongoCxx. (I'm sure theres a better way)
LinkDir["Bson"]					= "%{vcpkgdir}/libbson_x64-windows/lib/bson-1.0"
LinkDir["BsonCXX"]				= "%{vcpkgdir}/mongo-cxx-driver_x64-windows/lib/bsoncxx-v_noabi-rhs-md"
LinkDir["MongoC"]				= "%{vcpkgdir}/mongo-c-driver_x64-windows/lib/mongoc-1.0"
LinkDir["MongoCXX"]				= "%{vcpkgdir}/mongo-cxx-driver_x64-windows/lib/mongocxx-v_noabi-rhs-md"

LinkDir["Bsond"]				= "%{vcpkgdir}/libbson_x64-windows/debug/lib/bson-1.0"
LinkDir["BsonCXXd"]				= "%{vcpkgdir}/mongo-cxx-driver_x64-windows/debug/lib/bsoncxx-v_noabi-dhs-mdd"
LinkDir["MongoCd"]				= "%{vcpkgdir}/mongo-c-driver_x64-windows/debug/lib/mongoc-1.0"
LinkDir["MongoCXXd"]			= "%{vcpkgdir}/mongo-cxx-driver_x64-windows/debug/lib/mongocxx-v_noabi-dhs-mdd"

project "AuroraStory"
	location "."
	kind "ConsoleApp"
	staticruntime "off"
	language "C++"
	cppdialect "C++20"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"src/**.cpp",
		"src/**.h",
		"vendor/aes/**.c",
		"vendor/aes/**.h"
	}
	
	includedirs
	{
		"src/",
		"%{IncludeDir.aes}",
		"%{IncludeDir.ASIO}",
		"%{IncludeDir.spdlog}",

		"%{IncludeDir.Bson}",
		"%{IncludeDir.BsonCXX}",
		"%{IncludeDir.MongoC}",
		"%{IncludeDir.MongoCXX}"
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
			"DEBUG",
		}
		links
		{
			"%{LinkDir.MongoCd}",
			"%{LinkDir.MongoCXXd}",
			"%{LinkDir.Bsond}",
			"%{LinkDir.BsonCXXd}"
		}
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines
		{
			"NDEBUG",
		}
		links
		{
			"%{LinkDir.MongoC}",
			"%{LinkDir.MongoCXX}",
			"%{LinkDir.Bson}",
			"%{LinkDir.BsonCXX}"
		}
		runtime "Release"
		optimize "on"