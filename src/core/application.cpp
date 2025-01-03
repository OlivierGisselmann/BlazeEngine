#include "application.hpp"
#include "../logger/logger.hpp"

#include <stdexcept>

namespace Core
{
    Application::Application()
    {
        m_rendererConfig = Render::RendererConfig(800, 600, "BlazeEngine", true);
    }

    Application::~Application()
    {
        Log::Logger::Log(Log::INFO, "Cleaning Application");
    }

    void Application::run()
    {
        m_renderer = std::make_unique<Render::Renderer>(m_rendererConfig); // Create and run the renderer
    }
}
