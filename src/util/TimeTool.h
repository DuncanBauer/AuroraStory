#pragma once

#include "Typedefs.h"

namespace util
{
    namespace TimeTool
    {
        i64 getEpochSeconds();
        i64 getEpochMilliseconds();
        i64 dateToEpochSeconds(u32 year, u32 month, u32 day);
    };
}