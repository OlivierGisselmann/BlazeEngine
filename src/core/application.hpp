#pragma once
#include "../renderer/renderer.hpp"

#include <memory>

namespace Core
{
    class Application
    {
    public:
        Application();
        ~Application();
        void run();

    private:
        std::unique_ptr<Render::Renderer> m_renderer;
        Render::RendererConfig m_rendererConfig{};
    };
}
