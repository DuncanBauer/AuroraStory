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
-- I had to steal these from a github repo. There's no library, so we need to build with the project
IncludeDir["aes"]				= "%{os.getcwd()}/vendor/aes"

-- submodule libraries
IncludeDir["ASIO"]	 			= "%{os.getcwd()}/vendor/asio/asio/include"
IncludeDir["bcrypt"]	 		= "%{os.getcwd()}/vendor/bcrypt/include"
IncludeDir["spdlog"] 			= "%{os.getcwd()}/vendor/spdlog/include"
IncludeDir["yamlcpp"] 			= "%{os.getcwd()}/vendor/yaml-cpp/include"

-- vcpkg libraries
IncludeDir["Bson"]				= "%{vcpkgdir}/libbson_x64-windows/include"
IncludeDir["BsonCXX"]			= "%{vcpkgdir}/mongo-cxx-driver_x64-windows/include/bsoncxx/v_noabi"
IncludeDir["MongoC"]			= "%{vcpkgdir}/mongo-c-driver_x64-windows/include"
IncludeDir["MongoCXX"]			= "%{vcpkgdir}/mongo-cxx-driver_x64-windows/include/mongocxx/v_noabi"

LinkDir = {}
-- Need separate debug and release links. (I'm sure theres a better way)
LinkDir["bcrypt"]				= "%{os.getcwd()}/vendor/bcrypt/build/%{cfg.buildcfg}/bcrypt"
LinkDir["yamlcpp"]				= "%{os.getcwd()}/vendor/yaml-cpp/build/%{cfg.buildcfg}/yaml-cpp"
LinkDir["yamlcppd"]				= "%{os.getcwd()}/vendor/yaml-cpp/build/%{cfg.buildcfg}/yaml-cppd"

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
			"DEBUG",
			"YAML_CPP_STATIC_DEFINE"
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
			"NDEBUG",
			"YAML_CPP_STATIC_DEFINE"
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