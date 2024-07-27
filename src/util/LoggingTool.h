#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace util
{
    class LoggingTool
    {
    public:
        static inline void initialize()
        {
            std::vector<spdlog::sink_ptr> logSinks;
            logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
            logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("SERVER.log", true));

            logSinks[0]->set_pattern("%^[%T] %n: %v%$");
            logSinks[1]->set_pattern("[%T] [%l] %n: %v");

            m_serverLogger = std::make_shared<spdlog::logger>("SERVER", begin(logSinks), end(logSinks));
            spdlog::register_logger(m_serverLogger);
            m_serverLogger->set_level(spdlog::level::trace);
            m_serverLogger->flush_on(spdlog::level::trace);
        }

        static inline std::shared_ptr<spdlog::logger>& getServerLogger() 
        { 
            return m_serverLogger;
        }

    private:
        static inline std::shared_ptr<spdlog::logger> m_serverLogger;
    };
}

#ifdef DEBUG
// SPDLog Macros for the SERVER Library
#define SERVER_TRACE(...)    ::util::LoggingTool::getServerLogger()->trace(__VA_ARGS__)
#define SERVER_INFO(...)     ::util::LoggingTool::getServerLogger()->info(__VA_ARGS__)
#define SERVER_WARN(...)     ::util::LoggingTool::getServerLogger()->warn(__VA_ARGS__)
#define SERVER_ERROR(...)    ::util::LoggingTool::getServerLogger()->error(__VA_ARGS__)
#define SERVER_CRITICAL(...) ::util::LoggingTool::getServerLogger()->critical(__VA_ARGS__)
#else
// SPDLog Macros for the SERVER Library
#define SERVER_TRACE(...)
#define SERVER_INFO(...)
#define SERVER_WARN(...)
#define SERVER_ERROR(...)
#define SERVER_CRITICAL(...)
#endif
