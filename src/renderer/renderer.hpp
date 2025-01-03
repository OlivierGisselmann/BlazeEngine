#pragma once

#define GLFW_INCLUDE_VULKAN
#include <vector>
#include <GLFW/glfw3.h>

namespace Render
{
    struct RendererConfig
    {
        int window_width;
        int window_height;
        const char* window_title;
        bool debug_mode;
    };

    class Renderer {
    public:
        Renderer(RendererConfig config);
        ~Renderer();

    private:
        void initialize();
        void run();
        void cleanup();

        void createInstance();
        void setupDebugMessenger();
        std::vector<const char*>getRequiredExtensions();
        void createSurface();
        void pickPhysicalDevice();
        void createDevice();

        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void *pUserData);

        const std::vector<const char*> m_validationLayers = { "VK_LAYER_KHRONOS_validation" };

        RendererConfig m_config;
        GLFWwindow* m_window;
        VkInstance m_instance;
        VkPhysicalDevice* m_physicalDevice;
        VkDevice* m_device;
        VkDebugUtilsMessengerEXT m_debugMessenger;
    };

}