#include "Logger.h"

namespace util
{
    std::shared_ptr<spdlog::logger> Logger::m_logger;

    void Logger::init()
    {
        std::vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("SERVER.log", true));

        logSinks[0]->set_pattern("%^[%T] %n: %v%$");
        logSinks[1]->set_pattern("[%T] [%l] %n: %v");

        m_logger = std::make_shared<spdlog::logger>("SERVER", begin(logSinks), end(logSinks));
        spdlog::register_logger(m_logger);
        m_logger->set_level(spdlog::level::trace);
        m_logger->flush_on(spdlog::level::trace);
    }

    std::shared_ptr<spdlog::logger>& Logger::getLogger()
    {
        return m_logger;
    }
}