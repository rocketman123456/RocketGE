cmake_minimum_required (VERSION 2.6)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    set(VCPKG_ROOT "/usr/local/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    set(VCPKG_ROOT "C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE PATH "")
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    set(VCPKG_ROOT "/Users/developer/Program/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
endif ()
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_ROOT})

message(STATUS "###################################")

message(STATUS "CMAKE_TOOLCHAIN_FILE ${CMAKE_TOOLCHAIN_FILE}")
project( RocketGE )
message(STATUS "Project Name ${PROJECT_NAME}")

set(RENDER_API "OpenGL")
set(CMAKE_BUILD_TYPE "Debug")

message(STATUS "###################################")

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DRELEASE)
endif()
message(STATUS "Build System Set to ${CMAKE_BUILD_TYPE}")

message(STATUS "###################################")

message(STATUS "operation system is ${CMAKE_SYSTEM}")
if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    message(STATUS "current platform: Linux ")
    set(Linux 1)
    add_definitions(-DPLATFORM_LINUX)
elseif (CMAKE_SYSTEM_NAME MATCHES "Windows")
    message(STATUS "current platform: Windows")
    set(Windows 1)
    add_definitions(-DPLATFORM_WINDOWS)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    message(STATUS "current platform: Apple Darwin")
    set(Apple 1)
    add_definitions(-DPLATFORM_APPLE)
else ()
    message(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
endif ()

message(STATUS "###################################")

find_package(Threads REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

message(STATUS "Render API Set to ${RENDER_API}")
if (RENDER_API MATCHES "OpenGL")
    set(OpenGL 1)
    add_definitions(-DRK_OPENGL)
elseif (RENDER_API MATCHES "Vulkan")
    set(Vulkan 1)
    add_definitions(-DRK_VULKAN)
elseif (RENDER_API MATCHES "Metal")
    set(Metal 1)
    add_definitions(-DRK_METAL)
endif()

message(STATUS "###################################")

include_directories(
    ${PROJECT_SOURCE_DIR}/Thirdparty/entt/include
    ${PROJECT_SOURCE_DIR}/Thirdparty/glad/include
    ${PROJECT_SOURCE_DIR}/Thirdparty/spdlog/include
    ${PROJECT_SOURCE_DIR}/Thirdparty/stb_image
    ${PROJECT_SOURCE_DIR}/Thirdparty/imgui
    ${PROJECT_SOURCE_DIR}/Thirdparty/glm
)

include_directories(
    ${PROJECT_SOURCE_DIR}/Rocket/GECore/include
    ${PROJECT_SOURCE_DIR}/Rocket/GEEngine/include
    ${PROJECT_SOURCE_DIR}/Sandbox/include
)

if(OpenGL)
    include_directories(${PROJECT_SOURCE_DIR}/Rocket/GERender/OpenGL/include)
elseif(Vulkan)
    include_directories(${PROJECT_SOURCE_DIR}/Rocket/GERender/Vulkan/include)
elseif(Metal)
    include_directories(${PROJECT_SOURCE_DIR}/Rocket/GERender/Metal/include)
endif()

if(Apple)
    include_directories( ${PROJECT_SOURCE_DIR}/Rocket/Platform/Apple/include )
elseif(Linux)
    include_directories( ${PROJECT_SOURCE_DIR}/Rocket/Platform/Linux/include )
elseif(Windows)
    include_directories( ${PROJECT_SOURCE_DIR}/Rocket/Platform/Windows/include )
endif()

add_subdirectory( Thirdparty )
add_subdirectory( Rocket )
add_subdirectory( Sandbox )
