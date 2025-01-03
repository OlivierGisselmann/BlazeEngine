#include "application.hpp"
#include "../logger/logger.hpp"

#include <stdexcept>

Application::Application()
{

}

Application::~Application()
{

}

void Application::run()
{
    Logger::Log(LOG_LEVEL::INFO, "Running...");
    throw std::runtime_error("No code kek");
}