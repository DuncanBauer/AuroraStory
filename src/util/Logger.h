#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace util
{
    class Logger
    {
    public:
        static void init();
        static std::shared_ptr<spdlog::logger>& getLogger();

    private:
        static std::shared_ptr<spdlog::logger> m_logger;
    };
}

#ifdef DEBUG
// SPDLog Macros for the SERVER Library
#define SERVER_TRACE(...)    util::Logger::getLogger()->trace(__VA_ARGS__)
#define SERVER_INFO(...)     util::Logger::getLogger()->info(__VA_ARGS__)
#define SERVER_WARN(...)     util::Logger::getLogger()->warn(__VA_ARGS__)
#define SERVER_ERROR(...)    util::Logger::getLogger()->error(__VA_ARGS__)
#define SERVER_CRITICAL(...) util::Logger::getLogger()->critical(__VA_ARGS__)
#else
// SPDLog Macros for the SERVER Library
#define SERVER_TRACE(...)
#define SERVER_INFO(...)
#define SERVER_WARN(...)
#define SERVER_ERROR(...)
#define SERVER_CRITICAL(...)
#endif
