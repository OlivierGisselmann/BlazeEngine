#include "core/application.hpp"
#include "logger/logger.hpp"

#include <cstdlib>
#include <memory>

int main()
{
    Log::Logger::Log(Log::INFO, "Initializing Blaze Engine");

    try {
        const auto app = std::make_unique<Core::Application>();
        app->run();
    } catch (const std::exception& e) {
        Log::Logger::Log(Log::ERR, e.what());
        return EXIT_FAILURE;
    }

    Log::Logger::Log(Log::INFO, "Shutting down Blaze Engine");
    return EXIT_SUCCESS;
}