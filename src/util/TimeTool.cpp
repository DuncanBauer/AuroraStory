#include <chrono>
#include <ctime>

#include "TimeTool.h"

namespace util
{
    namespace TimeTool
    {
        i64 getEpochSeconds()
        {
            // Get the current time as a time_point
            auto now = std::chrono::system_clock::now();

            // Convert to epoch seconds
            return std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
        }

        i64 getEpochMilliseconds()
        {
            // Get the current time as a time_point
            auto now = std::chrono::system_clock::now();

            // Convert to epoch seconds
            return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
        }

        i64 dateToEpochSeconds(u32 year, u32 month, u32 day)
        {
            std::tm timeInfo = {};
            timeInfo.tm_year = year - 1900; // Year since 1900
            timeInfo.tm_mon = month;        // Month (0-11, so July is 6)
            timeInfo.tm_mday = day;         // Day of the month
            return static_cast<i64>(std::mktime(&timeInfo));
        }
    };
}