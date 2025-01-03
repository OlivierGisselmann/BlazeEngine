#pragma once

#include <string>

enum LOG_LEVEL
{
    INFO,
    WARN,
    ERR
};

class Logger {
public:
    static void Log(LOG_LEVEL log_level, const std::string& message);
};
