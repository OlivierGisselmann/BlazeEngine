#pragma once

#include <string>

namespace Log
{
    enum LOG_LEVEL
    {
        INFO,
        WARN,
        ERR
    };

    class Logger
    {
    public:
        static void Log(LOG_LEVEL log_level, const std::string& message);
    };
}

