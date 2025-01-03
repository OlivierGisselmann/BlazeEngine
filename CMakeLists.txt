cmake_minimum_required(VERSION "3.30.5")

# Project settings
project("BlazeEngine" VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

# Find Vulkan
find_package(Vulkan REQUIRED)

# Add third party
SET(GLM_TEST_ENABLE OFF CACHE BOOL "GLM Build unit tests")
add_subdirectory("third_party/glm" EXCLUDE_FROM_ALL)
add_subdirectory("third_party/glfw-3.4")

# Add all cpp files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

# Target dependencies
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        Vulkan::Vulkan
        glm::glm
        glfw
)