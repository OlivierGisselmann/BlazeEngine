#include "core/application.hpp"
#include "logger/logger.hpp"

#include <iostream>
#include <cstdlib>

int main(int argc, char** argv)
{
    Logger::Log(INFO, "Initializing Blaze Engine");

    try {
        Application app;
        app.run();
    } catch (const std::exception& e) {
        Logger::Log(ERR, e.what());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}