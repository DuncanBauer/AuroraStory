#pragma once

#include <chrono>
#include <ctime>

namespace util
{
    static inline long long getEpochSeconds()
    {
        // Get the current time as a time_point
        auto now = std::chrono::system_clock::now();

        // Convert to epoch seconds
        return std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count();
    }

    static inline long long getEpochMilliseconds()
    {
        // Get the current time as a time_point
        auto now = std::chrono::system_clock::now();

        // Convert to epoch seconds
        return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
    }

    static inline long long dateToEpochSeconds(uint32_t year, uint32_t month, uint32_t day)
    {
        std::tm timeInfo = {};
        timeInfo.tm_year = year - 1900; // Year since 1900
        timeInfo.tm_mon = month;        // Month (0-11, so July is 6)
        timeInfo.tm_mday = day;         // Day of the month

        return std::mktime(&timeInfo);
    }
}