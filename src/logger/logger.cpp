#include <iostream>

#include <windows.h>
#include "logger.hpp"

void Logger::Log(const LOG_LEVEL log_level, const std::string& message)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    switch (log_level)
    {
        case INFO:
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            std::cout << "[INFO]: " << message << "\n";
            break;

        case WARN:
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
            std::cout << "[WARN]: " << message << "\n";
            break;

        case ERR:
            SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
            std::cout << "[ERROR]: " << message << "\n";
            break;
    }
}