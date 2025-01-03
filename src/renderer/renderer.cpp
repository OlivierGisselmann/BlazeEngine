#include "renderer.hpp"
#include "../logger/logger.hpp"

#include <stdexcept>

namespace Render
{
    Renderer::Renderer(RendererConfig config) : m_config(config)
    {
        m_instance = nullptr;
        m_device = nullptr;
        m_window = nullptr;
        m_physicalDevice = nullptr;

        initialize();
        run();
    }

    void Renderer::initialize()
    {
        Log::Logger::Log(Log::INFO,
            "Initializing Renderer: Width("
            + std::to_string(m_config.window_width)
            + "), Height(" + std::to_string(m_config.window_height)
            + "), Title:'" + m_config.window_title + "'"
        );

        // Windows initialization
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
        m_window = glfwCreateWindow(m_config.window_width, m_config.window_height, m_config.window_title, nullptr, nullptr);

        if (m_window == nullptr)
            throw std::runtime_error("Failed to create GLFW window");

        createInstance();
        setupDebugMessenger();
        createSurface();
        pickPhysicalDevice();
        createDevice();
    }

    void Renderer::run()
    {
        glfwShowWindow(m_window);

        while (!glfwWindowShouldClose(m_window)) {
            glfwPollEvents();
        }
    }

    Renderer::~Renderer()
    {
        cleanup();

        m_instance = nullptr;
        m_device = nullptr;
        m_window = nullptr;
        m_physicalDevice = nullptr;
    }

    void Renderer::createInstance()
    {
        VkApplicationInfo app_info{};
        app_info.sType                                  = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        app_info.pApplicationName                       = m_config.window_title;
        app_info.applicationVersion                     = VK_MAKE_VERSION(1, 0, 0);
        app_info.pEngineName                            = m_config.window_title;
        app_info.engineVersion                          = VK_MAKE_VERSION(1, 0, 0);
        app_info.apiVersion                             = VK_API_VERSION_1_0;

        VkInstanceCreateInfo create_info{};
        create_info.sType                               = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.pApplicationInfo                    = &app_info;

        const auto extensions           = getRequiredExtensions();
        create_info.enabledExtensionCount               = static_cast<uint32_t>(extensions.size());
        create_info.ppEnabledExtensionNames             = extensions.data();

        if (m_config.debug_mode)
        {
            Log::Logger::Log(Log::INFO, "Extensions required :");
            for (const auto& extension : extensions) {
                Log::Logger::Log(Log::INFO, extension);
            }
        }

        if (m_config.debug_mode) {
            create_info.enabledLayerCount               = static_cast<uint32_t>(m_validationLayers.size());
            create_info.ppEnabledLayerNames             = m_validationLayers.data();
        }else {
            create_info.enabledLayerCount               = 0;
            create_info.ppEnabledLayerNames             = nullptr;
        }

        if (vkCreateInstance(&create_info, nullptr, &m_instance) != VK_SUCCESS)
            throw std::runtime_error("Failed to create Vulkan Instance");
    }

    std::vector<const char*> Renderer::getRequiredExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

        if (m_config.debug_mode)
            extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

        return extensions;
    }

    // Debug Utils functions
    VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
        if (func != nullptr) {
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        } else {
            return VK_ERROR_EXTENSION_NOT_PRESENT;
        }
    }

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
        auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
        if (func != nullptr) {
            func(instance, debugMessenger, pAllocator);
        }
    }

    void Renderer::setupDebugMessenger()
    {
        if (!m_config.debug_mode) return;

        VkDebugUtilsMessengerCreateInfoEXT create_info{};
        create_info.sType                               = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        create_info.messageSeverity                     = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        create_info.messageType                         = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        create_info.pfnUserCallback                     = debugCallback;
        create_info.pUserData                           = nullptr;

        if (CreateDebugUtilsMessengerEXT(m_instance, &create_info, nullptr, &m_debugMessenger) != VK_SUCCESS) {
            throw std::runtime_error("Failed to set up debug messenger");
        }
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL Renderer::debugCallback(
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void *pUserData)
    {
        if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
            Log::Logger::Log(Log::WARN, pCallbackData->pMessage);
        else if (messageSeverity == VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
            Log::Logger::Log(Log::ERR, pCallbackData->pMessage);

        return VK_FALSE;
    }

    void Renderer::createSurface()
    {

    }

    void Renderer::pickPhysicalDevice()
    {

    }

    void Renderer::createDevice()
    {

    }

    void Renderer::cleanup()
    {
        Log::Logger::Log(Log::INFO, "Cleaning Renderer");
        if (m_config.debug_mode)
            //DestroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr);

        vkDestroyInstance(m_instance, nullptr);
        glfwDestroyWindow(m_window);
        glfwTerminate();
    }

}