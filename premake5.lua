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
	defines
	{
		"YAML_CPP_STATIC_DEFINE"
	}

outputdir = "%{cfg.buildcfg}"

project "AuroraStory"
	location "."
	kind "ConsoleApp"
	staticruntime "off"
	language "C++"
	cppdialect "c++20"
	targetdir ("bin/" .. outputdir)
	objdir ("bin-int/" .. outputdir)
	
	files
	{
		"src/**.cpp",
		"src/**.h"
	}
	
	includedirs
	{
		"src/",
		"/usr/local/include",
		"/usr/local/include/asio",
		"/usr/local/include/bcrypt",
		"/usr/local/include/LuaCpp",
		"/usr/local/include/bsoncxx/v_noabi",
		"/usr/local/include/libbson-1.0",
		"/usr/local/include/libmongoc-1.0",
		"/usr/local/include/mongocxx/v_noabi",
		"/usr/local/include/spdlog",
		"/usr/local/include/yaml-cpp"
	}

	libdirs { "/usr/local/lib" }
	
	links
	{
		-- "../usr/local/lib/bcrypt",
		-- "../usr/local/lib/luacpp",
		-- "../usr/local/lib/bson-static-1.0",
		-- "../usr/local/lib/bsoncxx-static",
		-- "../usr/local/lib/mongoc-static-1.0",
		-- "../usr/local/lib/mongocxx-static",
		-- "../usr/local/lib/spdlogd",
		-- "../usr/local/lib/yaml-cppd"
		"bcrypt",
		"lua5.3",
		"luacpp",
		"bson-static-1.0",
		"mongoc-static-1.0",
		"bsoncxx-static",
		"mongocxx-static",
		"spdlogd",
		"yaml-cppd",
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